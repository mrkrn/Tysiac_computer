import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

bot1 = []
bot2 = []
bot3 = []

f = open("22.txt", "r")
lines = f.readlines()
for i in range(0, int(len(lines)), 4):
    bot1.append(list(map(int, lines[i].split(','))))
    bot2.append(list(map(int, lines[i+1].split(','))))
    bot3.append(list(map(int, lines[i+2].split(','))))

f.close()

numpy_array = np.array(bot1)
numpy_array2 = np.array(bot2)
numpy_array3 = np.array(bot3)
df = pd.DataFrame(numpy_array)
df2 = pd.DataFrame(numpy_array2)
df3 = pd.DataFrame(numpy_array3)
temp = df.agg(['min', 'max', 'mean'])
temp = temp.transpose()
temp.rename(columns={"min": "Minimum Computer",
            "max": "Maximum Computer", "mean": "Mean Computer"}, inplace=True)
temp['Rounds'] = temp.index
extra = df2.agg(['min', 'max', 'mean'])
extra = extra.transpose()
extra.rename(columns={"min": "Minimum bot1",
                      "max": "Maximum bot1", "mean": "Mean bot1"}, inplace=True)
temp = pd.concat([temp, extra], axis=1)
extra = df3.agg(['min', 'max', 'mean'])
extra = extra.transpose()
extra.rename(columns={"min": "Minimum bot2",
                      "max": "Maximum bot2", "mean": "Mean bot2"}, inplace=True)
temp = pd.concat([temp, extra], axis=1)
print(temp)

ax = plt.gca()

temp.plot(x='Rounds', y='Mean Computer', c='blue', ax=ax)
temp.plot(x='Rounds', y='Mean bot1', c='orange', ax=ax)
temp.plot(x='Rounds', y='Mean bot2', c='green', ax=ax)

print(temp.shape[0])
plt.fill_between(x='Rounds', y1='Minimum Computer',
                 y2='Maximum Computer', data=temp, alpha=0.5, label='Computer')
plt.fill_between(x='Rounds', y1='Minimum bot1',
                 y2='Maximum bot1', data=temp, alpha=0.5, label='bot1')
plt.fill_between(x='Rounds', y1='Minimum bot2',
                 y2='Maximum bot2', data=temp, alpha=0.5, label='bot2')

# plt.xticks(np.arange(min(temp['Rounds']), max(temp['Rounds'])+1, 1))
plt.legend()

plt.xlabel("Round", fontsize=18)
plt.ylabel("Points", fontsize=18)

plt.show()
