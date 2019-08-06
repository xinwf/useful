#!/usr/bin/env python
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
import sys
from matplotlib.font_manager import FontProperties 

if len(sys.argv) == 1:
    print("%s datafile" % sys.argv[0])
    sys.exit(0)

f = open(sys.argv[1], "r")
data = f.readlines()
f.close()

xValue = []
yValue = []
for line in data:
    if len(line.replace("\n", ""))==0:
        continue
    # print(line.split(" "))
    xValue.append(line.split(" ")[0])
    yValue.append(line.split(" ")[1].replace("\n", ""))

# plt.title('Scatter plot example')

# plt.xlabel('x-value')
# plt.ylabel('y-label')
# plt.scatter(x, y, s, c, marker)
# x: x轴坐标
# y：y轴坐标
# s：点的大小/粗细 标量或array_like 默认是 rcParams['lines.markersize'] ** 2
# c: 点的颜色 
# marker: 标记的样式 默认是 'o'
# plt.legend()

# plt.scatter(xValue, yValue, s=20, c="#ff1212", marker='o')
print(xValue)
print(yValue)
plt.plot(xValue, yValue, color='g')

plt.show()
