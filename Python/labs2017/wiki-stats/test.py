#!/usr/bin/python3

import os
import sys
import math

import array

import statistics

from matplotlib import rc

rc('font', family='Droid Sans', weight='normal', size=14)

import matplotlib.pyplot as plt


class WikiGraph:
    def load_from_file(self, filename):
        print('Загружаю граф из файла: ' + filename)

        with open(filename) as f:
            s = f.readline()
            (n, _nlinks) = map(int, s.split())  # TODO: прочитать

            self._titles = []
            self._sizes = array.array('L', [0] * n)
            self._links = array.array('L', [])  # edges
            self._redirect = array.array('B', [0] * n)
            self._offset = array.array('L', [0] * (n + 1))  # offset
            self._number = array.array('L', [0] * n)
            j = 0
            skolko = [0]

            for line in f:
                curr = line.rstrip().split()
                str = line.rstrip().replace(' ', '')
                if not str.isdigit():
                    self._titles.append(line.rstrip())
                    j = self._titles.index(line.rstrip()) + 0
                elif len(curr) == 3:

                    self._sizes[j] = int(curr[0])
                    self._redirect[j] = int(curr[1])

                    self._number[j] = int(curr[2])
                    if j == 0:
                        skolko = [int(curr[2])]

                    elif j >= 1:

                        self._offset[j] = self._offset[j - 1] + skolko[0]
                        skolko = [int(curr[2])]
                    if j == n - 1:
                        self._offset[j + 1] = self._offset[j] + skolko[0]
                elif len(curr) == 1:
                    self._links.append(int(line))

                    # TODO: прочитать граф из файла

        print('Граф загружен')

    def check(self):
        print(self._titles, '- titles\n',
              self._sizes, '- sizes\n',
              self._links, '- links or edges\n',
              self._redirect, '- redirect\n',
              self._offset, '- offset')  # offset)

    def bfs(self, start, finish, fired):
        path = [[] for i in range(len(self._titles))]
        if fired is None:
            fired = set()
        s = self._titles.index(start)
        fired.add(s)
        Q = [s]
        while Q:
            current = Q.pop(0)
            for n in self._links[self._offset[current]:self._offset[current + 1]]:
                if n not in fired:
                    fired.add(n)
                    Q.append(n)

                    path[n] = path[current] + [current]

                if n == self._titles.index(finish):
                    o = path[n] + [n]
                    for i in range(len(o)):
                        o[i] = self._titles[o[i]]
                    print('\n'.join(o))
                    return
        print('Bad luck')
        return

    def how_many_redirects(self):
        return(sum(self._redirect))

    def min_links(self):
        min = float('+inf')
        for i in range(len(self._titles)):
            if len(self._links[self._offset[i]:self._offset[i + 1]]) < min:
                min = len(self._links[self._offset[i]:self._offset[i + 1]])
        return min

    def how_many_with_min_links(self):
        min = self.min_links()
        count = 0
        for i in range(len(self._titles)):
            if len(self._links[self._offset[i]:self._offset[i + 1]]) == min:
                count += 1
        return count

    def max_links(self):
        max = float('-inf')
        for i in range(len(self._titles)):
            if len(self._links[self._offset[i]:self._offset[i + 1]]) > max:
                max = len(self._links[self._offset[i]:self._offset[i + 1]])
        return max

    def how_many_with_max_links(self):
        max = self.max_links()
        count = 0
        for i in range(len(self._titles)):
            if len(self._links[self._offset[i]:self._offset[i + 1]]) == max:
                count += 1
        return count

    def winner(self):
        max = self.max_links()
        winner = 0
        for i in range(len(self._titles)):
            if len(self._links[self._offset[i]:self._offset[i + 1]]) == max:
                winner = self._titles[i]
        return winner

    def average(self):
        return statistics.mean(self._number), statistics.stdev(self._number)

    def min_na(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return min(A)

    def number_min_na(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = min(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                c += 1
        return (c)

    def max_na(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return max(A)

    def number_max_na(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = max(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                c += 1
        return (c)

    def most_referred(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = max(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                return(self._titles[i])

    def average_ext(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] != 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return sum(A) / len(A), statistics.stdev(A)

    def min_redirect(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return min(A)

    def number_min_redirect(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = min(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                c += 1
        return (c)

    def max_redirect(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return max(A)

    def number_max_redirect(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = max(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                c += 1
        return (c)

    def redirected_the_most(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        a = max(A)
        c = 0
        for i in range(len(A)):
            if A[i] == a:
                return(self._titles[i])

    def average_redirect(self):
        A = [0] * len(self._titles)
        for i in range(len(self._titles)):
            if self._redirect[i] == 1:
                for j in self._links[self._offset[i]:self._offset[i + 1]]:
                    A[j] += 1
        return sum(A) / len(A), statistics.stdev(A)

    def get_number_of_links_from(self, _id):
        return len(self._links[self._offset[_id]:self._offset[_id + 1]])

    def get_links_from(self, _id):
        return self._links[self._offset[_id]:self._offset[_id + 1]]

    def get_id(self, title):
        return self._titles.index(title)

    def get_number_of_pages(self):
        return len(self._titles)

    def is_redirect(self, _id):
        if self._redirect[_id] == 1:
            return True
        return False

    def get_title(self, _id):
        return self._titles[_id]

    def get_page_size(self, _id):
        return self._sizes[_id]



wg = WikiGraph()
wg.load_from_file('wiki_small.txt')
# wg.check()
wg.bfs('Python', 'Список_файловых_систем', None)  # 3 упражнение
# wg.bfs('Python', 'Боль', None) # 4 упражнение
print('Количество статей с перенаправлением:', wg.how_many_redirects())
print('Минимальное количество ссылок из статьи:', wg.min_links())
print('Количество статей с минимальным количеством ссылок:', wg.how_many_with_min_links())
print('Максимальное количество ссылок из статьи:', wg.max_links())
print('Количество статей с максимальным количеством ссылок:', wg.how_many_with_max_links())
print('Статья с наибольшим количеством ссылок:', wg.winner())
print('Среднее количество ссылок в статье и ср. откл.:', *wg.average())
print('Минимальное количество ссылок на статью:', wg.min_na())
print('Количество статей с минимальным количеством внешних ссылок:', wg.number_min_na())
print('Максимальное количество ссылок на статью:', wg.max_na())
print('Количество статей с максимальным количеством внешних ссылок:', wg.number_max_na())
print('Статья с наибольшим количеством внешних ссылок:', wg.most_referred())
print('Среднее количество внешних ссылок на статью и ср. откл.', *wg.average_ext())
print('Минимальное количество перенаправлений на статью:', wg.min_redirect())
print('Количество статей с минимальным количеством внешних перенаправлений:', wg.number_min_redirect())
print('Максимальное количество перенаправлений на статью:', wg.max_redirect())
print('Количество статей с максимальным количеством внешних перенаправлений:', wg.number_max_redirect())
print('Статья с наибольшим количеством внешних перенаправлений:', wg.redirected_the_most())
print('Среднее количество внешних перенаправлений на статью и ср. откл.:',*wg.average_redirect())
