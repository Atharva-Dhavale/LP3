import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix, classification_report

df = pd.read_csv("2-emails.csv")
print(df.head())
print(df.isnull().sum())
df = df.drop("Email No.", axis=1)
X = df.drop("Prediction", axis=1)
y = df["Prediction"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

knn = KNeighborsClassifier()
knn.fit(X_train, y_train)

y_pred_knn = knn.predict(X_test)

print("KNN Confusion Matrix:")
print(confusion_matrix(y_test, y_pred_knn))

print("KNN Classification Report:")
print(classification_report(y_test, y_pred_knn))

svm = SVC(kernel="linear")
svm.fit(X_train, y_train)
y_pred_svm = svm.predict(X_test)


print("\nSVM Confusion Matrix:")
print(confusion_matrix(y_test, y_pred_svm))

print("SVM Classification Report:")
print(classification_report(y_test, y_pred_svm))