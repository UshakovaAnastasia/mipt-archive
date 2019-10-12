png("plot.png", width = 500, height = 500)

layout(matrix(c(1,1,2,3,3,2),ncol=3, byrow=TRUE))
boxplot(mtcars$mpg)
hist(mtcars$mpg, ylab = 'Frequency', main = 'Histogram of mtcars$mpg ')
plot(mtcars$disp, mtcars$mpg, pch = 1)
dev.off()

