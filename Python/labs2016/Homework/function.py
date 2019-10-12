#2.7
import numpy as np
import matplotlib.pyplot as plt
x = []
y = []
b=0.5
a=3
p = 20000
start = -1
fin = 1
s = (fin-start)/p
for i in range (0, p):
    x.append(start+i*s)
    o = 0
    for k in range (0, 200):
        o+=b**k * np.cos(a**k*(start+i*s)*np.pi)
    y.append(o)
plt.plot (x, y)
plt.show()