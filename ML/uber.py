import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score, mean_squared_error

df = pd.read_csv("1-uber.csv")
print(df.head())
print(df.isnull().sum())
df.dropna(inplace=True)
df.drop(['Unnamed: 0', 'key'], axis=1, inplace=True)

df['pickup_datetime'] = pd.to_datetime(df['pickup_datetime'])
df['time'] = df['pickup_datetime'].dt.hour
df.drop('pickup_datetime', axis=1, inplace=True)

df['distance'] = np.sqrt(
 (df['pickup_latitude'] - df['dropoff_latitude'])**2 +
 (df['pickup_longitude'] - df['dropoff_longitude'])**2
)

df = df[(df['fare_amount'] > 0) &
 (df['passenger_count'] > 0) &
 (df['passenger_count'] <= 6)]

for col in ['pickup_latitude', 'pickup_longitude',
 'dropoff_latitude', 'dropoff_longitude']:
 q1 = df[col].quantile(0.25)
 q3 = df[col].quantile(0.75)
 iqr = q3 - q1
 df = df[(df[col] >= q1 - 1.5*iqr) &
 (df[col] <= q3 + 1.5*iqr)]

print("Correlation:")
print(df.corr(numeric_only=True))

sns.heatmap(df.corr(numeric_only=True), annot=True)
plt.show()

X = df.drop('fare_amount', axis=1)
y = df['fare_amount']
X_train, X_test, y_train, y_test = train_test_split(
 X, y, test_size=0.2, random_state=42
)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)
lr = LinearRegression()
lr.fit(X_train, y_train)
pred1 = lr.predict(X_test)
rf = RandomForestRegressor(n_estimators=50, random_state=42, n_jobs=-1)
rf.fit(X_train, y_train)
pred2 = rf.predict(X_test)
print("Linear Regression")
print("R2:", r2_score(y_test, pred1))
print("RMSE:", np.sqrt(mean_squared_error(y_test, pred1)))
print("\nRandom Forest")
print("R2:", r2_score(y_test, pred2))
print("RMSE:", np.sqrt(mean_squared_error(y_test, pred2)))

