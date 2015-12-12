
# Bivariate Normal Galton Height
install.packages("psych")
library(psych)
data(galton)
describe(galton)
plot(galton)
lm1 <- lm(galton$child ~ galton$parent)
lines(galton$parent, lm1$fitted, col="red", lwd=3)
plot(galton$parent, lm1$residuals, pch=19, col="blue")
beta_0 = lm1$coeff[1] 
beta_1 = lm1$coeff[2] 

childs_height = beta_0+beta_1*(137.96/2)

summary(lm1)

lm2 <- lm(galton$parent~galton$child)
summary(lm2)


# Corn Yield 12.2.4
variety <- as.factor(c(1,1,1,2,2,2,3,3,3,4,4,4,5,5,5))
yield <- c(46.2, 51.9, 48.7, 49.2, 58.6, 57.4, 60.3, 58.7, 60.4, 48.9, 51.4, 44.6, 52.5, 54.0, 49.3)

anova(lm(yield~variety))


# Twain vs Snodgrass 12.2.4
auth <- as.factor(c(1,1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2))
freq <- c(0.225, 0.262, 0.217, 0.240, 0.230, 0.229, 0.235, 0.217,0.209, 0.205, 0.196, 0.210, 0.202, 0.207, 0.224, 0.223, 0.220, 0.201)

anova(lm(freq~auth))


#Example: Twan vs Snodgrass#######################################
# Enter data
tw <- c(0.225, 0.262, 0.217, 0.240, 0.230, 0.229, 0.235, 0.217)
qcs <- c(0.209, 0.205, 0.196, 0.210, 0.202, 0.207, 0.224, 0.223, 0.220, 0.201)

# find the lengths of the data sets
n <- length(tw)
m <- length(qcs)

# calculate the means
xbar <-mean(tw)
ybar <- mean(qcs)

# calculate the pooled variance
Sp2 <- ((n-1)*sd(tw)^2 +(m-1)*sd(qcs)^2)/(n+m-2)

# calculate the test statistic
t <- (xbar-ybar)/sqrt((1/n+1/m)*Sp2)
t
t^2

