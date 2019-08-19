#!/usr/bin/python3
#-*-encoding:utf-8-*-
#usage: ./scriptprogram processname
import os,sys
if len(sys.argv) == 1:
    exit(0)
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
    
# print("\nKill process: %s, together: %d." % (sys.argv[1], killCount))
print("\nKill %d together." % killCount)
