import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

y = []
x = []


def read_text_file(file_path):
    with open(file_path, 'r') as f:
        temp = len(f.readlines())
        return temp/4


for file in os.listdir('.'):
    if file.endswith(".txt"):
        path = f"{'.'}/{file}"
        y.append(read_text_file(path))
        x.append(int(file.replace('.txt', '')))

print(x)
print(y)

print(x[y.index(max(y))])
print(max(y))

plt.bar(x, y)
plt.xlabel("Number of rounds", fontsize=18)
plt.ylabel("Number of games with x rounds", fontsize=18)
plt.xticks(x)
plt.show()
