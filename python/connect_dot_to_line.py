#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt

f = open(sys.argv[1], "r")
data = f.readlines()
f.close()
x_list = []
y_list = []

def readComplex(data):
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

def readSimple(data):
    for line in data:
        rd = line.replace("\n", "").split(" ")
        x_list.append(rd[0])
        y_list.append(rd[1])

# print(x_list)
# print(y_list)
readSimple(data)
plt.plot(x_list, y_list, color='g')
plt.show()
