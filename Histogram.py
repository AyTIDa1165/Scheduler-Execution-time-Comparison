import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = np.genfromtxt("Data.txt", dtype=None, names=["Policy", "Time"], encoding=None)

labels = data["Policy"].astype(str)
values = data["Time"]
colors = ["red", "blue", "green"]
plt.bar(labels, values, color = colors)

plt.xlabel('Labels')
plt.ylabel('Values')
plt.title('Bar Chart with String Labels')

plt.savefig('Historgram_image.png')