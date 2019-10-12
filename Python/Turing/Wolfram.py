def read_rule():
    d = dict()
    N = bin(int(input()))
    s = N.find('b')
    h = N[s + 1:]
    j = len(h)
    y = (8 - j) * '0' + h
    data = tuple(y)
    p = list(data)
    arr = p[::-1]
    for i in range(8):
        d[i] = arr[i]
    return d


def read_data(file):
    d = dict()
    f = open(file, 'r')
    data = tuple(f.read())
    arr = list(data)
    return arr


def get_neighbors(a, i):
    if i == 0:
        return a[-1], a[i], a[1]
    if i == len(a) - 1:
        return a[-2], a[i], a[0]
    return a[i - 1], a[i], a[i + 1]


def print_field(field):
    for cell in field:
        print('■' if int(cell) else '□', end='')
    print()


rule = read_rule()
data = read_data('wolfdata.txt')
print_field(data)
repeat = []
i = 0
lim = 100
while data != repeat:
    i += 1
    repeat = data
    curr = data[:]
    for j in range(len(data)):
        x, y, z = get_neighbors(data, j)
        n = 4 * int(x) + 2 * int(y) + int(z)
        curr[j] = rule[n]
    data = curr
    print_field(data)
    if i > lim:
        break
if data == repeat:
    print('...')
