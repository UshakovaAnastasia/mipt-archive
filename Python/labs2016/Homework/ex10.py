#работа 1, упражнение 10
s=input()
a=s.find('h')
t = s[:a+1]
p = s[a+1:]
p=p.replace('h', 'H', p.count('h')-1)
print(t+p)