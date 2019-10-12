require(stats)
layout(matrix(c(1,1,2,1,1,3,4,5,3,4,5,6),ncol=4))
image(cor(mtcars),col=rev(heat.colors(100)), axes=FALSE, main='correlation')
axis(1, at=(0:10) / 10, labels= names(mtcars))
axis(1, labels=colnames(corrr), at=seq(0,1, length=11))
box(which = "plot", lty = "solid")
d = mtcars[4:5]
z <- lm(drat ~ hp, data = d)
plot(d, pch = 16, 
     col = rgb(red = 0, green = 0, blue = 0, alpha = 0.5))
abline(z, col = 'red', lty = 2, lwd = 3)
l = paste("rho=", toString(signif(summary(z)$coefficients[2], digits = 1)), sep = '')
legend("topright", legend=l, col=c("red"), lty=2, lwd = 3)
counts <- table(mtcars$carb, mtcars$am)
counts
barplot(counts, col = heat.colors(nrow(counts)), names.arg = c('auto', 'manual'))
legend("topright", legend = rownames(counts), 
       fill = heat.colors(nrow(counts)), title ="# carb") 

hist(mtcars$wt, xlab = '# of cars', ylab = 'lb', main = 'Weight')
legend("topright", legend = 'mpg', 
       col=c("red"),  lwd = 3, bty = "n")
par(new=TRUE)
plot(mtcars$wt, mtcars$mpg, col = 'red', axes = FALSE, ylab = "", xlab = "")
axis(side=4)
mtext("mpg", side = 4, cex=1.1, line = 1.2)
lines(predict(smooth.spline(mtcars$wt, mtcars$mpg,df=3)),col='red',lwd=3)
boxplot(mpg~carb,data=mtcars, col = 'grey',  
        xlab="# of carburetors", ylab="mpg")
par(new=TRUE)
lines(predict(smooth.spline(mtcars$carb, mtcars$mpg,df=2.5)),col='black',lwd=3)

plot(density(mtcars[mtcars$am==0,]$mpg), xlab = 'mpg', main = "speed vs transm", col = 'red')
lines(density(mtcars[mtcars$am==1,]$mpg), col = 'blue')
legend("topright", legend = c('auto', 'manual'), col=c("red", 'blue'), lwd = 1)
title("Cars", line = -1, outer = TRUE)


