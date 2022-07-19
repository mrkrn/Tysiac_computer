import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas as pd

cp1 = [0, 0, 80, 190, 290, 340, 450, 510, 640, 660, 560,
       640, 540, 590, 650, 700, 810, 860, 760, 890, 960, 1060]
k = [0, 100, 0, 20, 40, -60, -60, -160, -120, 0, 60,
     140, 290, 290, 290, 390, 290, 340, 370, 370, 410, 470]
d = [0, 40, 40, 70, 90, 110, 140, 140, 170, 190, 220,
     120, 130, 250, 150, 180, 180, 80, 80, 110, 10, 60]
cp2 = [0, 140, 270, 290, 390, 410, 500, 400, 430, 470, 600, 630,
       680, 760, 800, 670, 710, 610, 610, 650, 760, 800, 930, 1030]
m1 = [0, 120, 140, 170, 210, 110, 110, 150, 190, 190, 230, 130,
      250, 260, 160, 210, 210, 290, 390, 290, 390, 430, 470, 500]
q1 = [0, 30, -70, 80, 80, 200, 100, 110, 210, 110, 150, 170,
      170, 280, 300, 360, 460, 460, 500, 530, 530, 430, 450, 510]
cp3 = [0, -100, -50, 40, 70, 100, 150, 280, 420,
       490, 590, 680, 690, 710, 730, 780, 890, 1010]
q2 = [0, 40, -60, -60, -10, -110, -80, -30, -
      10, -10, 20, -80, -20, -20, 80, 120, 180, 200]
r1 = [0, 50, 80, -20, 80, 120, 220, 320, 440,
      570, 570, 570, 470, 580, 610, 510, 530, 590]
cp4 = [0, 0, 130, 160, 160, 230, 290, 310, 380, 420, 520, 590,
       620, 730, 770, 810, 910, 910, 910, 910, 910, 910, 1020]
r2 = [0, 20, 40, 150, 310, 210, 210, 310, 210, 350, 370, 270,
      320, 410, 580, 460, 480, 580, 600, 700, 820, 860, 940]
p = [0, -100, -90, -60, -40, 10, 120, 120, 190, 90, 130,
     150, 50, 170, 200, 240, 280, 310, 430, 440, 440, 340, 390]
cp5 = [0, 30, 30, 60, 130, 160, 210, 250, 350, 350,
       250, 250, 280, 310, 360, 400, 500, 620, 640, 540]
q3 = [0, 20, 20, 70, 180, 230, 330, 430, 460, 460,
      480, 380, 380, 280, 180, 340, 370, 410, 450, 470]
m2 = [0, 100, 200, 100, 100, 200, 240, 280, 330, 500,
      560, 580, 680, 680, 750, 750, 750, 750, 870, 1000]
cp6 = [0, 50, 100, 230, 330, 400, 500, 530,
       590, 700, 750, 880, 780, 870, 890, 1000]
m3 = [0, -100, 0, 40, 70, 170, 210, 310,
      330, 380, 280, 330, 370, 390, 290, 350]
q4 = [0, 40, 60, 80, 90, 140, 190, 240,
      340, 370, 400, 420, 440, 540, 600, 630]

total = [cp1, k, d, cp2, q1, m1, cp3, q2,
         r1, cp4, r2, p, cp5, q3, m2, cp6, m3, q4]

max_len = max(len(cp1), len(cp2), len(cp3), len(cp4), len(cp5), len(cp6))

for i in range(len(total)):
    print(len(total[i]))
    if (len(total[i]) != max_len):
        total[i].extend([None]*(max_len-len(total[i])))

df = pd.DataFrame({"Computer_1": cp1, "Player 1": k,
                  "Player 2": d, "Computer_2": cp2,
                   "Player 3_1": m1, "Player 4_1": q1, "Computer_3": cp3, "Player 4_2": q2, "Player 5": r1,
                   "Computer_4": cp4, "Player 5_2": r2, "Player 6": p, "Computer_5": cp5, "Player 4_3": q3,
                   "Player 3_2": m2, "Computer_6": cp6, "Player 3_3": m3, "Player 4_4": q4})


# plt.gca().set_color_cycle(['red', 'green', 'blue', 'red', 'yellow', 'purple',
#                            'red', 'purple', 'orange', 'red', 'orange', 'pink', 'red', 'purple', 'yellow'])
mpl.rcParams["axes.prop_cycle"] = mpl.cycler(color=['red', 'green', 'blue', 'red', 'yellow',
                                             'purple', 'red', 'purple', 'orange', 'red', 'orange', 'pink', 'red', 'purple', 'yellow', 'red', 'yellow', 'purple'])


df.plot()

df1 = pd.DataFrame({"Computer_5": cp5, "Player 4_3": q3,
                   "Player 3_2": m2})

mpl.rcParams["axes.prop_cycle"] = mpl.cycler(color=['red', 'purple', 'yellow'])

df1.plot()

df2 = pd.DataFrame({"Player 3_1": m1, "Player 3_2": m2,
                   "Player 3_3": m3})

mpl.rcParams["axes.prop_cycle"] = mpl.cycler(color=['orange', 'red', 'yellow'])

df2.plot()

df3 = pd.DataFrame({"Player 5_1": r1, "Player 5_2": r2})

mpl.rcParams["axes.prop_cycle"] = mpl.cycler(color=['red', 'orange'])

df3.plot()

df4 = pd.DataFrame({"Player 4_1": q1, "Player 4_2": q2,
                   "Player 4_3": q3, "Player 4_4": q4, })

mpl.rcParams["axes.prop_cycle"] = mpl.cycler(
    color=['red', 'orange', 'yellow', 'green'])

df4.plot()

plt.xticks(range(max_len))
plt.xlabel("Round", fontsize=18)
plt.ylabel("Points", fontsize=18)
plt.show()
