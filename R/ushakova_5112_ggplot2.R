library("ggplot2")
library('gridExtra')
library("reshape2")
data <- mtcars
cmat <- cor(mtcars)
cmat[upper.tri(cmat)] <- NA
melted <- melt(cmat, na.rm = TRUE)
p0 <- ggplot(data = melted, aes(Var1, Var2, fill = value))+geom_tile(color = "white")+
  scale_fill_gradient2(low = "blue", high = "red", mid = "white", midpoint = 0, limit = c(-1,1),name="Pearson\nCorrelation") +
  theme_minimal()+
  theme(axis.text.x = element_text(angle = 45, vjust = 1,size = 10, hjust = 1))+
  coord_fixed()
p1 <- ggplot(data, aes(data$wt, fill=as.factor(data$am)))+ 
  labs(title="Weight", subtitle = "Weight and automatic/manual proportions on one plot", x="lb", y="# of cars")+
  labs(fill = "Transmission")+
  geom_histogram(bins=9, binwidth = 0.5, col="white") + theme_classic()
p2<-ggplot(data, aes(x = carb, y = data$mpg, group = factor(data$carb)))  +
  labs(x="# of carburetors", y="mpg")+
  geom_boxplot(fill='grey') + theme_minimal() + theme(panel.border = element_rect(colour = "black", fill=NA))
p2<-p2+ geom_smooth(aes(group=1))
p3 <- ggplot(data, aes(x = data$hp, y = data$drat)) + labs(x="Gross horsepower", y="Rear axle ratio", color="gear", size="cyl")+
  geom_point(aes(color = factor(data$gear), size = factor(data$cyl))) + geom_smooth(method='lm', se=FALSE) +
  theme_minimal()+ theme(legend.position="bottom")+theme(panel.border = element_rect(colour = "black", fill=NA))
p4 <- ggplot(data, aes(x = factor(data$am), fill = factor(data$carb)))+geom_histogram(stat='count')+
  labs(x="Transmission", fill='carb') + scale_fill_brewer(palette = "Reds") + theme_minimal()+theme(panel.background = element_rect(colour = "black"))
p5 <- ggplot(data, aes(x=data$mpg, color = factor(data$am),fill = factor(data$am))) + 
  geom_density() + labs(x="mpg", fill = "Transmission", color = "Transmission")+
  theme_minimal()+theme(panel.border = element_rect(colour = "black", fill=NA))
png("plot.png", width = 1024, height = 768)
grid.arrange(p0,p1,p2,p3,p4,p5, widths=c(2,1,1,2), layout_matrix= rbind(c(1,1,2,2), c(1,1,3,3), c(4,5,5,6)))
dev.off()

