def longest_repeated_substring(s):
    res = ''
    res_l = 0
    n = len(s)
    M = [[0] * (n + 1) for i in range(n + 1)]
    ind = 0
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if s[i - 1] == s[j - 1]:
                M[i][j] = M[i - 1][j - 1] + 1
                if M[i][j] > res_l:
                    res_l = M[i][j]
                    ind = max(i, ind)
            else:
                M[i][j] = 0
    if res_l:
        for i in range(ind - res_l + 1, ind + 1):
            res = res + (s[i - 1])
    return res


s = input()
print("'" + longest_repeated_substring(s) + "'", sep='')
