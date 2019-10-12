import sys
from functools import partial


def find_reads(p, s, d=1):
    return [i for i in range(len(s) - len(p) + 1) if hamming_dist(p, s[i:i + len(p)]) == d]


def hamming_dist(s, t):
    return sum([s[i] != t[i] for i in range(len(s))])


def burrows_wheeler_transform(s):
    return ''.join(s[i - 1] for i in sort(range(len(s)), partial(letter, s)))


def sort(values, digit, shift=0):
    if len(values) <= 1:
        for v in values:
            yield v
        return
    buckets = {}
    for v in values:
        buckets.setdefault(digit(v, shift), []).append(v)
    for k in sorted(buckets.keys()):
        for r in sort(buckets[k], digit, shift + 1):
            yield r


def letter(s, value, shift):
    return s[(value + shift) % len(s)]


s = ''
with open('genome.txt', 'r') as f:
    for line in f:
        s += line.strip()
f.close()
s += '$'
orig_stdout = sys.stdout
f = open('bwt.txt', 'w')
sys.stdout = f
print(burrows_wheeler_transform(s))
sys.stdout = orig_stdout
f.close()
with open('read.txt', 'r') as f:
    for line in f:
        t = line.strip()
        print('read =', t)
        print('positions:', *find_reads(t, s), sep='\n')
f.close()
