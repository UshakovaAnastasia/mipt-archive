from scipy.optimize import curve_fit
from scipy import asarray as ar, exp
import numpy as np
import sys
from scipy.stats import norm
import matplotlib.pyplot as plt
from scipy.optimize import least_squares


def gauss(x, a, b, m, s):
    result = []
    for i in range(len(x)):
        result += [b + a / (s * np.sqrt(2 * np.pi)) * np.exp(-(x[i] - m) ** 2 / (2 * s ** 2))]
    return result


def model_point(x, t):
    return t[0] / (t[2] * np.sqrt(2 * np.pi)) * np.exp(-(x - t[1]) ** 2 / (2 * t[2] ** 2)) + \
           t[3] / (t[5] * np.sqrt(2 * np.pi)) * np.exp(-(x - (t[4])) ** 2 / (2 * t[5] ** 2))


def model_arr(x, t):
    result = []
    for i in range(len(x)):
        result += [model_point(x[i], t)]
    return result


def residuals(t, y, x):
    u = []
    for i in range(len(x)):
        u += [y[i] - model_point(x[i], t)]
    return np.array(u)


I = []
print("Пожалуйста, введите название файла (температура в цельсиях.txt)")
name = input()
print("Введите длину волны возбуждающего излучения в А")
spr = ' '
wl = int(input())

X = []
Y = []
with open(name, 'r') as f:
    for line in f:
        v = line.strip().split(spr)
        # t = float(v[0].replace(',', '.'))

        X.append(v[0].replace(',', '.'))
        Y.append(v[1].replace(',', '.'))

x = X
y_real = Y
lbl = name.split('.')[0] + " °C"
# axes = plt.gca()
# axes.set_xlim([3800, 6000])
# axes.set_ylim([-2000, 8000])
plt.plot(x, y_real, label=lbl)
plt.xlabel('wavelength, Å')
plt.ylabel('I')
plt.legend()
plt.show()
print(
    "\nВведите границы отрезка по оси х через пробел, например, \"0 5660\".")
mi, ma = map(float, input().split())
X = []
Y = []
with open(name, 'r') as f:
    for line in f:
        v = line.strip().split(spr)
        t = float(v[0].replace(',', '.'))
        if t > mi and t < ma:
            X.append(v[0].replace(',', '.'))
            Y.append(float(v[1].replace(',', '.')))

x = X
y_real = Y
lbl = name.split('.')[0] + " °C"
axes = plt.gca()
axes.set_xlim([mi, ma])
plt.plot(x, y_real, label=lbl)
plt.xlabel('wavelength, Å')
plt.ylabel('I')
plt.legend()
plt.show()
print("Переведем в волновые числа (Shift)")

Z = []
for obj in X:
    Z.append((1 / wl - 1 / float(obj)) * pow(10, 8))
x = Z
t0 = np.array([pow(2100, 2), 3200, 100, pow(2700, 2), 3400, 100])  # b=0, да вообще произвольный "вектор" может быть
plt.plot(x, y_real, label=lbl)
axes = plt.gca()
axes.set_xlim([(1 / wl - 1 / mi) * pow(10, 8), (1 / wl - 1 / ma) * pow(10, 8)])
plt.xlabel('Shift, cm-1')
plt.ylabel('I')
plt.legend()
plt.show()
print(
    "Есть ли предположение, в каких пределах лежат коэффициенты сдвига (то есть на каких отрезках должны быть точки максимумов пиков)?\nЕсли да, то 1, если нет, то 0")
answer = int(input())
if (answer == 1):
    print(
        "Введите в формате \"min1 max1 min2 max2\",\nmax, min - верхняя и нижняя границы для первого и второго гаусса соответственно; нужная бесконечность= \"+inf\" или \"-inf\"")
    mn1, mx1, mn2, mx2 = map(float, input().split())
    param_bounds = ([0, mn1, 0, 0, mn2, 0], [np.inf, mx1, np.inf, np.inf, mx2, np.inf])
else:
    param_bounds = ([0, 0, 0, 0, 0, 0], [np.inf, np.inf, np.inf, np.inf, np.inf, np.inf])
plshelp = least_squares(residuals, t0, bounds=param_bounds, args=(y_real, x))
# print(type(plshelp['x']))
optimal_parameters = plshelp['x']
print(optimal_parameters)
print(
    "[a1, m1, s1, a2, m2, s2], каждая кривая = ai*(gauss, sigma = s_i, mean = m_i)")
gauss1 = (optimal_parameters[0], 0, optimal_parameters[1], optimal_parameters[2])
gauss2 = (optimal_parameters[3], 0, optimal_parameters[4], optimal_parameters[5])
# print(*gauss1)
# print(*gauss2)
y_sum = model_arr(x, optimal_parameters)
y1 = gauss(x, *gauss1)
y2 = gauss(x, *gauss2)
plt.plot(x, y_real, label=lbl)
plt.plot(x, y_sum, 'm.', marker=',', linestyle='-')
plt.plot(x, y1, 'r.', marker=',', linestyle='-')
plt.plot(x, y2, 'g.', marker=',', linestyle='-')

axes = plt.gca()
axes.set_xlim([(1 / wl - 1 / mi) * pow(10, 8), (1 / wl - 1 / ma) * pow(10, 8)])
plt.xlabel('Shift, cm-1')
plt.ylabel('I')
plt.legend()
i1 = optimal_parameters[0] / (optimal_parameters[2] * np.sqrt(2 * np.pi))
i2 = optimal_parameters[3] / (optimal_parameters[5] * np.sqrt(2 * np.pi))
print(i1, i2, np.log(i1 / i2), 1 / (float(name.split('.')[0]) + 273.15),
      "- максимум интенсивности меньшего пика(=i1), макс инт большего(=i2), ln(i1/i2), 1/T", sep='\t')
plt.show()
