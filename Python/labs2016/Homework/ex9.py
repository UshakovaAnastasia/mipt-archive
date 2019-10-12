#работа 1, упражнение 9
s=input()
t=s[1:len(s)-1]
print(s[0]+t.replace("", "*")+s[len(s)-1])
