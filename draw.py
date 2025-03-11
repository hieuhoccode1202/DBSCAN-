import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def plot_dbscan_results(data):
    plt.figure(figsize=(10, 6))
    
    if data['color'].min() < 0:
        print("Warning: Negative cluster values detected. Setting to 0.")
        data['color'] = data['color'].apply(lambda x: max(0, x))
    #24 8
    predefined_colors = {
        0: 'black',
        1: 'red',
        2: 'blue',
        3: 'green',
        4: 'yellow',
        5: 'purple',
        6: 'orange',
        7: 'pink',
        8: 'brown',
        9: 'gray'
    }
    
    unique_clusters = sorted(data['color'].unique()) 
    cluster_map = {cluster: predefined_colors.get(cluster, 'black') for cluster in unique_clusters}
    data['color_rgb'] = data['color'].map(cluster_map)
    print("Cluster colors:")
    for cluster, color in cluster_map.items():
        print(f"Cluster {cluster}: {color}")
    
    scatter = plt.scatter(data['x'], data['y'], c=data['color_rgb'], s=50)
    cbar = plt.colorbar()
    cbar.set_ticks(unique_clusters)
    cbar.set_label('Cluster')
    
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('DBSCAN Clustering Results')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.show()

try:
    data = pd.read_csv("output.csv", sep='\s+', skiprows=1, names=['x', 'y', 'color'])
    if data.empty:
        print("Error: output.csv is empty.")
    else:
        plot_dbscan_results(data)
except FileNotFoundError:
    exit()
except KeyError as e:
    exit()
except Exception as e:
    exit()