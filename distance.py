import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class TargetPoint():  # define by (R,A,S)
    def __init__(self, r=0, a=0, s=0):
        self.r = r
        self.a = a
        self.s = s

    def pointArray(self):
        return np.array([self.r, self.a, self.s])


class TemplatePlane:  # define by (A,B,C,D) and Ax+By+Cz+D = 0
    def __init__(self, A=1, B=1, C=1, D=1):
        if (A == 0) & (B == 0) & (C == 0):
            print "A, B, C shouldn't all == 0!"
            exit()
        else:
            self.A = A
            self.B = B
            self.C = C
            self.D = D

    def planeNormalArray(self):
        return np.array([self.A, self.B, self.C])

#--------------------------------------------------
def disPoint2Plane(TargetPoint, TemplatePlane):
   numer = math.fabs(TemplatePlane.A*TargetPoint.r + TemplatePlane.B*TargetPoint.a + TemplatePlane.C*TargetPoint.s + TemplatePlane.D)
   denom = math.sqrt(pow(TemplatePlane.A,2) + pow(TemplatePlane.B,2) + pow(TemplatePlane.C,2))
   dis = numer/denom
   return dis


def projectPointArray(pointArray, planeNormalArray):
    pointOnPlane = planeNormalArray    
    pointProjectOnPlane = pointArray - np.dot(pointArray-pointOnPlane, planeNormalArray)*planeNormalArray
    return pointProjectOnPlane  # in np.array([x,y,z])


def nearestHole(targetPoint, templatePlane):  # point=TargetPoint(r,a,s), plane=TemplatePlane(a,b,c,d) 
    # project point on the plane
    pointProject = projectPointArray(targetPoint.pointArray(), templatePlane.planeNormalArray())
    
    # compare with blocks

#-------------------------------------------------- test
p = TargetPoint(5, -5, 3)
q = TemplatePlane(0, 0, 1, 0)
dis = disPoint2Plane(p, q) 

nH = nearestHole(p,q)

print "point: ", p.pointArray()
print "disPoint2Plane: ", dis
print "planeNormal: ", q.planeNormalArray()

point = np.array([q.A, q.B, q.C])
normal = np.array([q.A, q.B, q.C])
d = -point.dot(normal)
xx, yy = np.meshgrid(range(10), range(10))
z = (-normal[0]*xx - normal[1]*yy - d) * 1./normal[2]

point_project = projectPointArray(p.pointArray(), q.planeNormalArray())
print point_project


#fig = plt.figure().gca(projection='3d')
#fig.plot_surface(xx,yy,z)
#fig.scatter(p.r, p.a, p.s, c='r', marker='o')
#fig.scatter(point_project[0], point_project[1], point_project[2], c='r', marker='*')
#plt.show()

