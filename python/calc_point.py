#!/usr/bin/env python
import sys, math
from tf.transformations import euler_from_quaternion, quaternion_from_euler

def main(ox, oy, oz, ow, ds, pn):
    if ow != 0.707:
        # calculate the line: y=kx+b
        (r, p, y) = euler_from_quaternion([0, 0, oz, ow])
        k = math.tan(y)
        b = oy - k * ox
        
        '''
        # calculate the ratio of Ax*x + B*x + C = 0
        A = ds*ds + k*k
        B = 2*k*b - 2*ox - 2*k*oy
        C = ox*ox + oy*oy + b*b - 2*oy*b - ds*ds
        x = 0
        print("k: ", k, ", b: ", b, ", A: ", A, ", B: ", B, ", C: ", C)
        if( (B*B-4*A*C) > 0):
            x1 = (-B + math.sqrt(B*B-4*A*C)) / (2*A)
            x2 = (-B - math.sqrt(B*B-4*A*C)) / (2*A)
            print("x1: ", x1, ", x2: ", x2)
            if k > 0:
                x = max(x1, x2)
            else:
                x = min(x1, x2)
        elif (B*B-4*A*C) == 0:
            x = -b/(2*A)
        else:
            print("Can't get points with given value.")
            sys.exit(0)
        '''
        x = ox + ds*math.cos(y)
        y = k * x + b
        print("First point: (%d, %d)" % (x, y))

        f = open("points", 'a')
        # f.write(str(ox)+" "+str(oy)+" "+str(oz)+" "+str(ow)+"\n")
        f.write(str(x)+" "+str(y)+" "+str(oz)+" "+str(ow)+"\n")
        # get other points
        if (pn-1) > 0:
            if k > 0:
                interval = abs(x - ox)
            else:
                interval = -abs(x - ox)
            for i in range(2, pn):
                x = ox + interval*i
                y = k * x + b
                f.write(str(x)+" "+str(y)+" "+str(oz)+" "+str(ow)+"\n")
        print("Save %d points to file: points" % (pn+1))
        f.close()
    else:
        x = ox
        if oz == 0.707:
            interval = ds
        else:
            interval = -ds
        f = open("points", 'a')
        for i in range(pn+1):
            y = oy + interval*i
            f.write(str(x)+" "+str(y)+" "+str(oz)+" "+str(ow)+"\n")
        print("Save %d points to file: points" % pn+1)
        f.close()        


if __name__ == "__main__":
    if len(sys.argv)==7:
        ox = float(sys.argv[1])
        oy = float(sys.argv[2])
        oz = float(sys.argv[3])
        ow = float(sys.argv[4])
        ds = float(sys.argv[5])
        pn = int(sys.argv[6])
    else:
        ox = 0
        oy = 0
        oz = 0
        ow = 1
        ds = 0
        pn = 0
        
    main(ox, oy, oz, ow, ds, pn)