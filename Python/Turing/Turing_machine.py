go = {'R': 1, 'L': -1, 'S': 0}
N = 105


# 'o' - выполняет роль пробела
# ST  - останов

def read_data(file):
    f = open(file, 'r')
    data = tuple(f.read())
    arr = list(data)
    return arr


def read_algorythm(file):
    d = dict()
    with open(file, 'r') as f:
        for line in f:
            v = line.strip().split('->')
            initchar = v[0][0]
            initstate = v[0][1:]
            fchar = v[1][0]
            fstate = v[1][1:-1]
            dir = v[1][-1]
            d[(initchar, initstate)] = [fchar, fstate, dir]
    return d


datafiles = [('data21.txt', 'alg21.txt'), ('data22.txt', 'alg22.txt'), ('data23.txt', 'alg23.txt'),
             ('data24.txt', 'alg24.txt'), ('data25.txt', 'alg25.txt')]
i = 1
for tup in datafiles:
    print('Пункт', i)
    i += 1
    d, a = tup
    data = ['o'] + read_data(d) + ['o'] * N
    alg = read_algorythm(a)
    print(''.join(data))
    print('...')
    state = 'q1'
    pos = 1
    while state != 'ST':
        s = (data[pos], state)
        f = alg[s]
        data[pos] = f[0]
        state = f[1]
        pos = pos + go[f[2]]
    print(''.join(data))
    print('pos =', pos, 'char =', data[pos])  # положение автомата в конце
    # (номер позиции и символ), счет от 0
    print()
