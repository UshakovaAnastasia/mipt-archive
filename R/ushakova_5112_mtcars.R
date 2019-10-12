m=mtcars # data.frame
# второй столбец - numeric vector
corr=cor(m) # matrix (of numeric elements)

#минимальное количество цилиндров
min(m[,'cyl'])
#все машины с минимальным числом цилиндров
row.names(m)[which(m[,'cyl']==min(m[,'cyl']))]
#с какими свойствами у потребления бензина (mpg) коэффициент корреляции менее -0.7
rownames(corr)[which(corr[,'mpg']<(-0.7))]

