#!/usr/bin/env python
# coding=utf-8

import numpy as np
import cv2

count = 0

cap = cv2.VideoCapture(0)
while(1):
    # get a frame
    ret, frame = cap.read()
    #show a frame
    cv2.imshow("capture", frame)
    key = cv2.waitKey(1) & 0xFF
    if key == ord(' '):
        count = count + 1
        if count < 10:
            cv2.imwrite("000%d.png" % count, frame)
            print("000%d.png" % count)
        else:
            cv2.imwrite("00%d.png" % count, frame)
            print("00%d.png" % count)
        
    elif key == ord('q'):
        break
    

cap.release()
cv2.destroyAllWindows()
