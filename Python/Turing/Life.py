def read_data(file):
    a = []
    with open(file, 'r') as f:
        for line in f:
            s=line.rstrip()
            t=s.replace('.', '0')
            g=t.replace('O', '1')
            v = tuple(g)
            a.append(list(v))
    return a


def how_many(a, i, j):
    return grab(a, i - 1, j - 1) + grab(a, i, j - 1) + grab(a, i - 1, j) + grab(a, i + 1, j + 1) + grab(a, i + 1,
                                                                                                        j - 1) + grab(a,
                                                                                                                      i - 1,
                                                                                                                      j + 1) + grab(
        a, i, j + 1) + grab(a, i + 1, j)


def grab(a, i, j):
    try:
        if i>=0 and j>=0:
            return int(a[i][j])
        return 0
    except IndexError:
        return 0
    except ValueError:
        return 0


def print_field(field):
    for cell in field:
        print('■' if int(cell) else '□', end='')
    print()


data = read_data('lifedata.txt')#в этот файл можно вставить поля из файлов
# oscillators.txt, gun.txt и т.д.
print('t = 0')
for i in range(len(data)):
    print_field(data[i])
repeat = []
k = 0
lim = 1000
while data != repeat:
    print('t =', k+1)
    k += 1
    repeat = data
    curr=[data[i][:] for i in range(len(data))]
    for i in range(len(data)):
        for j in range(len(data[i])):
            n=how_many(data,i,j)
            if data[i][j] == '0':
                if n == 3:
                    curr[i][j] = '1'
            elif n==2 or n==3:
                curr[i][j] = '1'
            else:
                curr[i][j] = '0'
    data = curr
    for i in range(len(data)):
        print_field(data[i])
    if k >= lim:
        break
if data == repeat:
    print('...')

