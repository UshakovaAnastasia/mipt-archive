# 2.6
import numpy as np
import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [0.99, 0.49, 0.35, 0.253, 0.18]
v, p = np.polyfit(x, y, deg=1, cov=True)
c, d = np.polyfit(x, y, deg=2, cov=True)
plt.errorbar(x, y, xerr=0.05, yerr=0.1)
a, b = v[0], v[1]
e, f, g = c[0], c[1], c[2]
t = np.arange(1, 5, 0.01)
plt.plot(t, a * t + b, t, e * t ** 2 + f * t + g)
plt.grid()
plt.show()
