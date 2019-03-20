#!/usr/bin/env python

import matplotlib.pyplot as plt

f = open("current_goal_ipa_apartment.txt", "r")
data = f.readlines()
f.close()
x_list = []
y_list = []
read = False
for line in data:
    if "position" in line:
        read = True
        continue
    elif "orientation" in line:
        read = False
        continue
    elif read:
        if "x:" in line:
            x_list.append(float(line.split(":")[1].replace("\n","").replace(" ", "")))
        elif "y:" in line:
            y_list.append(float(line.split(":")[1].replace("\n","").replace(" ", "")))
        # elif len(y_list) <10:
        #     continue
        # else:
        #     break

# print(x_list)
# print(y_list)
plt.plot(x_list, y_list, color='g')
plt.show()
