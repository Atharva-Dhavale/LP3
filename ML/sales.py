import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans

df = pd.read_csv('5-sales_data_sample.csv', encoding="unicode_escape")
df = df.dropna()

X = df[['SALES', 'QUANTITYORDERED', 'PRICEEACH']]
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
inertia = []
K = range(1, 11)
for k in K:
    kmeans = KMeans(n_clusters=k, random_state=42)
    kmeans.fit(X_scaled)
    inertia.append(kmeans.inertia_)

plt.figure(figsize=(8, 6))
plt.plot(K, inertia, 'bo-')
plt.xlabel('Number of clusters (k)')
plt.ylabel('Inertia')
plt.title('Elbow Method for Optimal k')
plt.show()

optimal_k = 4
kmeans = KMeans(n_clusters=optimal_k, random_state=42)
df['Cluster'] = kmeans.fit_predict(X_scaled)
print(df[['SALES', 'QUANTITYORDERED', 'PRICEEACH', 'Cluster']])
