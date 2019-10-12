import copy


def debruijn(reads):
    graph = {}
    for r in reads:
        pref = r[:-1]
        suf = r[1:]
        graph.setdefault(pref, set()).add(suf)
        graph.setdefault(suf, set())
    return graph


def edges(graph):
    for v in graph:
        for neigh in graph[v]:
            yield (v, neigh)


def is_tour_eulerian(tour, graph):
    edgs = list(edges(graph))
    for start, end in zip(tour, tour[1:]):
        try:
            edgs.remove((start, end))
        except ValueError:
            return False
    if edgs:
        return False
    else:
        return True


def try_tour(start, graph):
    t = euler_tour(start, graph)
    validity = is_tour_eulerian(t, graph)
    return validity, ''.join(s[0] for s in t)


def euler_tour(start_node, graph):
    graph = copy.deepcopy(graph)
    return path(start_node, graph)


def path(start_node, graph, end=None):
    pth = [start_node]
    if end is not None:
        finish_on = end
    else:
        finish_on = start_node
    while True:
        options = graph[pth[-1]]
        if not options:
            break
        pth.append(options.pop())
        if pth[-1] == finish_on:
            break
    offset = 0
    for n, step in enumerate(pth[:]):
        options = graph[step]
        if options:
            t = path(options.pop(), graph, step)
            n += offset
            pth = pth[:n + 1] + t + pth[n + 1:]
            offset += len(t)
    return pth


def start_end(g):
    deg = in_out(g)
    starts = set()
    ends = set()
    for v in deg:
        if deg[v][0] == deg[v][1] + 1:
            starts.add(v)
        elif deg[v][0] == deg[v][1] - 1:
            ends.add(v)
        elif deg[v][0] != deg[v][1]:
            return None
    if len(starts) != 1 or len(ends) != 1:
        return None
    return list(starts)[0], list(ends)[0]


def is_there_euler_path(g):
    deg = in_out(g)
    starts = 0
    ends = 0
    for v in deg:
        if deg[v][0] == deg[v][1] + 1:
            starts += 1
        elif deg[v][0] == deg[v][1] - 1:
            ends += 1
        elif deg[v][0] != deg[v][1]:
            return False
    if starts != 1 or ends != 1:
        return False
    return True


def in_out(g):
    tr_g = transpose(g)
    deg = {}
    for v in g:
        deg.setdefault(v, []).append(len(g[v]))
        deg.setdefault(v, []).append(len(tr_g[v]))
    return deg


def not_directed(dirgraph):
    neor = {}
    for v in dirgraph:
        neor.setdefault(v, set())
    for v in dirgraph:
        for g in dirgraph[v]:
            neor[g].add(v)
            neor[v].add(g)
    return neor


def transpose(graph):
    transposed = {}
    for v in graph:
        transposed.setdefault(v, set())
    for v in graph:
        for g in graph[v]:
            transposed[g].add(v)
    return transposed


def bfs(start, g, used=set()):
    used.add(start)
    Q = [start]
    while Q:
        current = Q.pop(0)
        for n in g[current]:
            if n not in used:
                used.add(n)
                Q.append(n)
                # return dist


reads = set()
n = 0
kmer_l = 25  # в строке 100 символов, можно разбить на меньшие k-меры
with open("Carsonella_ruddii_reads_bwa_read1.fastq", 'r') as f:
    for line in f:
        if n % 4 == 1:
            m = line.strip()
            for j in range(len(m) - kmer_l + 1):
                reads.add(m[j:j + kmer_l])
        n += 1
debruijnized = debruijn(reads)
print("is_there_euler_path(debruijnized) =", is_there_euler_path(debruijnized))  # эйлеров путь отсутствует

# пример для идеального случая
lines = set()
length = 16  # длина k-мера
m = 'TTTATTATAAAAGTATTTTTTCTAATTTTTATTATATTACCTATTAAAAAATTAACTTTATTATCAACTAAATATGTAATTAAAATTTTATCATTTTTTTTAGATAGTAAAATTTTAGTTAAAGATTTATCTTTTTTAATTAATAAACCTGTTATAGAATTAATAAAAGATTTTTTTGTAAATGGTATTTCTGTGAAAAT'
for j in range(len(m) - length + 1):
    lines.add(m[j:j + length])
gr = debruijn(lines)
print("is_there_euler_path(gr) =", is_there_euler_path(gr))
start, end = start_end(gr)
valid, t = try_tour(start, gr)
if valid:
    s = t + end[1:]
    print('result =', s)
    print("result==input =", s == m)
