#!/usr/bin/python3
#-*-encoding:utf-8-*-
#usage: ./scriptprogram processname
import os,sys
processLine = os.popen("ps aux | grep %s" % sys.argv[1])
line = processLine.readline()

killCount = 0
while line != '':
    if 'grep' in line or sys.argv[0] in line:
        line = processLine.readline()
        continue
    if sys.argv[1] in line :
        print("kill process: %s" % " ".join(line.split()[10:]))
        ret = os.system("kill -9 %s" % line.split()[1])
        killCount += 1
    line = processLine.readline()

print("Kill %d process together." % killCount)