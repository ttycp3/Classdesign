import os
from flask import Flask, request, jsonify, render_template, send_file
import tensorflow.compat.v1 as tf
import numpy as np
from quart import send_from_directory

import train
import datetime
from PIL import Image
import io
import cv2
app = Flask(__name__)
LOG_FILE = 'logs/captcha_logs.txt'


def log_prediction(correct, predicted):
    with open(LOG_FILE, 'a') as log_file:
        log_file.write(f"{datetime.datetime.now()} - Correct: {correct}, Predicted: {predicted},{correct==predicted}\n")


def load_model(captcha_image, captcha_label):
    global dz, sess, output, predict
    dz = train.Discuz()
    output = dz.crack_captcha_cnn()
    saver = tf.train.Saver()
    with tf.Session(config=dz.config) as sess:
        sess = tf.Session(config=dz.config)
        saver.restore(sess, tf.train.latest_checkpoint('.'))
        for i in range(len(captcha_label)):
            img = captcha_image[i].flatten()
            label = captcha_label[i]
            predict = tf.argmax(tf.reshape(output, [-1, dz.max_captcha, dz.char_set_len]), 2)
            text_list = sess.run(predict, feed_dict={dz.X: [img], dz.keep_prob: 1})
            text = text_list[0].tolist()
            vector = np.zeros(dz.max_captcha * dz.char_set_len)
            i = 0
            for n in text:
                vector[i * dz.char_set_len + n] = 1
                i += 1
            prediction_text = dz.vec2text(vector)
            return dz.vec2text(label),prediction_text



def preprocess_image(image_data,image_name):
    global dz, sess, output, predict
    dz = train.Discuz()
    batch_x = np.zeros([1, 100*30])
    batch_y = np.zeros([1, 4*63])
    img = cv2.imdecode(np.frombuffer(image_data, np.uint8), cv2.IMREAD_COLOR)
    #img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = cv2.resize(img, (100, 30))
    img = np.mean(img, -1)
    img = img.flatten() / 255

    # Store processed image into batch_x
    batch_x[0, :] = img

    # Example of dummy label assignment (replace with your actual label logic)
    #label = np.random.randint(0, 10)  # Example label from 0 to 9
    batch_y[0,] = dz.text2vec(image_name)

    return batch_x, batch_y


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/upload', methods=['POST'])
def upload():
    if 'captchaImage' not in request.files:
        return jsonify({'error': 'No file part'})

    file = request.files['captchaImage']
    if file.filename == '':
        return jsonify({'error': 'No selected file'})

    captcha_image = file.read()
    print(captcha_image)
    batch_x, batch_y = preprocess_image(captcha_image,file.filename.split('.')[0])
    true_text,prediction_text=load_model(batch_x, batch_y)
    log_prediction(true_text, prediction_text)
    response = jsonify({'prediction': prediction_text})
    response.headers.add('Access-Control-Allow-Origin', '*')
    return response


@app.route('/logs', methods=['GET'])
def get_logs():
    with open(LOG_FILE, 'r') as log_file:
        return log_file.read()


@app.route('/uploads/<filename>')
def send_file(filename):
    return send_from_directory(app.config["UPLOAD_FOLDER"], filename)


if __name__ == '__main__':
    app.run(debug=True)
