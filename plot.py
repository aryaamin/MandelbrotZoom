import numpy as np 
import matplotlib.pyplot as plt

list1=[]
list2=[]

f = open("itertimes.txt", "r")
for i in range(6):
	list1.append(f.readline())

itertimes = [int(i)/100000000 for i in list1]

N = [50,100,150,200,250,300]


g = open("zoomtimes.txt", "r")
for i in range(6):
	list2.append(g.readline())

zoomtimes = [int(i)/100000000 for i in list2]
M = [300,600,1200,2400,4800,9600]


plt.subplot(1,2,1)
plt.plot(N,itertimes)
plt.xlabel("Maxiter")
plt.ylabel("Time")
plt.title("MAXITER - TIME")

plt.subplot(1,2,2)
plt.plot(M,zoomtimes)
plt.xlabel("Zoom")
plt.ylabel("Time")
plt.yticks(np.arange(0, 10, step=1))
plt.title("ZOOM - TIME")


plt.show()
