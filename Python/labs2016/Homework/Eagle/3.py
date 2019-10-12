import random
import matplotlib.pyplot as plt
import numpy as np
values = [3.0, 4.0, 1.0, 2.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0]
def get_percentile(values, bunket_number):
    a=[np.percentile(values, (100//bunket_number)*i) for i in range (bunket_number)]
    a[0]=0
    return a
def get_percentile_number(value, percentiles):
    c=0
    for i in range (len(percentiles)):
        if percentiles[i] <= value:
            c=i
    return c
def value_equalization(value, percentiles, add_random):
    step = 1/len(percentiles)
    if add_random:
        idx=get_percentile_number(value, percentiles)
        new_value = idx*step+step*random.random()
    else:
        idx = get_percentile_number(value, percentiles)
        new_value = idx * step
    return new_value
def values_equalization(values, percentiles, add_random):
    return [value_equalization(values[i], percentiles, add_random=add_random) for i in range (len(values))]
n=5
v=5.5
value=5.5
print(get_percentile(values, n))
print(get_percentile_number(v, get_percentile(values, n)))
print(value_equalization(value, get_percentile(values, n), add_random=True))
print(values_equalization(values, get_percentile(values, n), add_random=True))
arr=[]
#6-10
with open('img.txt', 'r') as f:
    for line in f:
        v = map(float, line.strip().split())
        arr.append(list(v))
data = np.array(arr)
dat= data.flatten()
plt.subplot(321)
plt.imshow(data, cmap = plt.get_cmap('gray'))
plt.subplot(322)
plt.hist(dat, bins=10)
k=values_equalization(dat, get_percentile(dat, 3), add_random=True)
m=values_equalization(dat, get_percentile(dat, 10), add_random=True)
new=np.reshape(k, (200, 267))
new2=np.reshape(m, (200, 267))
plt.subplot(323)#bunket_number=3
plt.imshow(new, cmap = plt.get_cmap('gray'))
#11
plt.subplot(324)
plt.hist(k, bins=10)
plt.subplot(325) #bunket_number=10
plt.imshow(new2, cmap = plt.get_cmap('gray'))
plt.subplot(326)
plt.hist(m, bins=10)
plt.show()
#12
s = [i+1 for i in range(200)]
b=[]
for i in range(100):
    p = random.choice(s)
    s.pop(s.index(p))
    b.append(arr[p-1])
randomdata12=np.array(b)
#13
d = random.sample(s, 100)
u = []
for i in range(100):
    u.append(arr[d[i]-1])
randomdata13=np.array(u)
plt.subplot(121)
plt.imshow(randomdata12, cmap = plt.get_cmap('gray'))
plt.subplot(122)
plt.imshow(randomdata13, cmap = plt.get_cmap('gray'))
plt.show()
#14
y=sum(k)/len(k)#среднее значение
print(y)