# -*- coding:utf-8 -*-
import tensorflow.compat.v1 as tf
import numpy as np
import train
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score


def crack_captcha(captcha_image, captcha_label):
    output = dz.crack_captcha_cnn()
    saver = tf.train.Saver()
    with tf.Session(config=dz.config) as sess:
        saver.restore(sess, tf.train.latest_checkpoint('.'))
        all_labels = []
        all_predictions = []
        for i in range(len(captcha_label)):
            img = captcha_image[i].flatten()
            label = captcha_label[i]
            predict = tf.argmax(tf.reshape(output, [-1, dz.max_captcha, dz.char_set_len]), 2)
            text_list = sess.run(predict, feed_dict={dz.X: [img], dz.keep_prob: 1})
            text = text_list[0].tolist()
            vector = np.zeros(dz.max_captcha * dz.char_set_len)
            idx = 0
            for n in text:
                vector[idx * dz.char_set_len + n] = 1
                idx += 1
            prediction_text = dz.vec2text(vector)
            print("正确: {}  预测: {}".format(dz.vec2text(label), prediction_text))
            all_labels.append(dz.vec2text(label))
            all_predictions.append(prediction_text)
        accuracy = accuracy_score(all_labels, all_predictions)
        precision = precision_score(all_labels, all_predictions, average='macro')
        recall = recall_score(all_labels, all_predictions, average='macro')
        f1 = f1_score(all_labels, all_predictions, average='macro')

        print("Accuracy: {:.4f}".format(accuracy))
        print("Precision: {:.4f}".format(precision))
        print("Recall: {:.4f}".format(recall))
        print("F1-Score: {:.4f}".format(f1))


if __name__ == '__main__':
    dz = train.Discuz()
    batch_x, batch_y = dz.get_next_batch(False, 9)
    crack_captcha(batch_x, batch_y)



def convert_to_pure_black_white(image):
    width = image.shape[1]
    height = image.shape[0]
    image[0] = 255
    for line in image:
        line[0] = 255
        line[-1] = 255
    image[-1] = 255
    for w in range(width):
        for h in range(height):
            if image[h][w] < 237:
                image[h][w] = 0
            else:
                image[h][w] = 255
    image2 = image[:, 13:73]
    return image2
def remove_noise_line(image):
    width = image.shape[1]
    height = image.shape[0]
    for w in range(width):
        count = 0
        for h in range(height):
            if image[h][w] < 100:
                count += 1
            else:
                if 2 > count > 0:
                    for c in range(count):
                        image[h - c - 1][w] = 255
                count = 0
    for h in range(height):
        count = 0
        for w in range(width):
            if image[h][w] < 100:
                count += 1
            else:
                if 2 > count > 0:
                    for c in range(count):
                        image[h][w - c - 1] = 255
                count = 0
    return image
