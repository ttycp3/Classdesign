import numpy as np
import os
import joblib
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, classification_report
from sklearn.preprocessing import LabelBinarizer
import cv2

# 数据加载与预处理
def load_data(data_dir):
    images = []
    labels = []
    i=0
    for filename in os.listdir(data_dir):
        if filename.endswith('.jpg'):  # 假设图片是png格式
            img_path = os.path.join(data_dir, filename)
            img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
            img = cv2.resize(img, (100, 30))  # 假设验证码图片大小统一调整为100x100
            img = img.flatten()  # 将图像展平为一维向量
            label = filename.split('_')[0]  # 假设文件名格式为 'label_xxx.png'
            images.append(img)
            labels.append(label)
            print(filename)
            i+=1
            if i>100:
                break
    return np.array(images), np.array(labels)

data_dir = './datas'
X_test, y_test = load_data(data_dir)

# 加载字符标签的二进制化器
lb = LabelBinarizer()
y_test = lb.fit_transform(y_test)

# 加载训练好的KNN模型
model_path = 'sipo_knn2.job'
knn = joblib.load(model_path)

# 模型预测
y_pred = knn.predict(X_test)

# 模型评估
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, average='macro')
recall = recall_score(y_test, y_pred, average='macro')
f1 = f1_score(y_test, y_pred, average='macro')

print(f'Accuracy: {accuracy:.4f}')
print(f'Precision: {precision:.4f}')
print(f'Recall: {recall:.4f}')
print(f'F1 Score: {f1:.4f}')

# 打印详细分类报告
print(classification_report(y_test, y_pred, target_names=lb.classes_))