Cig <- read.csv("~/Dropbox/Syllabi/14Spring/Math362/Cig.csv")
View(Cig)
n <-length(Cig$Cigarette.Consuption)
sum.x2 <- sum(Cig$Cigarette.Consuption^2)
sum.xy <- sum(Cig$Cigarette.Consuption*Cig$CHD.Mortality)

xbar <- mean(Cig$Cigarette.Consuption) 
ybar <- mean(Cig$CHD.Mortality)

beta_1 <- (sum.xy-n*xbar*ybar)/(sum.x2-n*xbar^2)
beta_0 <- ybar - beta_1*xbar

linear_model <-lm(Cig$CHD.Mortality~Cig$Cigarette.Consuption)
linear_model

attach(Cig)
plot(Cigarette.Consuption, CHD.Mortality)
abline(linear_model)

cig.res = resid(linear_model)

plot(Cigarette.Consuption, cig.res, ylab="Residuals", xlab="Cig Consuption 2 Score", main="Grades") 
abline(0, 0)  

# Inference on Beta_1

alpha <- sqrt(sum.x2-n*xbar^2)
s2 <- sum((CHD.Mortality- beta_0-beta_1*Cigarette.Consuption)^2)/(n-2)
s <- sqrt(s2)
t_stat <- alpha/s*(beta_1)
dt(t_stat,n-2)

summary(linear_model)


cen <- beta_0+beta_1*2000
qt(0.025,19)*s*sqrt(1/n+(2000-xbar)^2/alpha^2)
