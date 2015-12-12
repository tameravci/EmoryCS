# Look at the Ratio of two chi-squareds

# Let's take 2000 simulations
numsim <- 2000
# Set up the vector to store the result of each simulation
x.F_sims<- rep(0,numsim)
# Set the degrees of freedom for the numerator and demoninator
n=10
m=15
# For each simulation
for (i in 1:numsim){
  num.y <- rchisq(1,m)/(m-1)
  den.x <- rchisq(1,n)/(n-1)
  x.F_sims[i]<- num.y/den.x
}

hist(x.F_sims,prob=TRUE)
# plot the chi-squared distribution over the histogram
curve( df(x, df1=n, df2 =m), col='blue', add=TRUE)




# Example: Alcoholic Authors/Problem 9.2.6 ###################
al <- c(48, 66, 71, 65, 56, 67, 67, 70, 77)
non <- c(65, 87, 32, 77, 89, 86, 77, 84, 64, 88, 90, 67)

xbar <- mean(al)
ybar <- mean(non)

n <- length(al)
m <- length(non)

sx2 <- sd(al)^2
sx2
sy2 <- sd(non)^2
sy2

F <- sy2/sx2
F
alpha = 0.05
qf(alpha/2,m-1,n-1)
qf(1-alpha/2,m-1,n-1)

var.test(al,non)

#Example: Twan vs Snodgrass#######################################
# Enter data
tw <- c(0.225, 0.262, 0.217, 0.240, 0.230, 0.229, 0.235, 0.217)
qcs <- c(0.209, 0.205, 0.196, 0.210, 0.202, 0.207, 0.224, 0.223, 0.220, 0.201)


# Example: Pawedness/Problem 9.4.1 #######################################
# http://www.radiolab.org/story/whats-left-when-youre-right/
px <- 55/200
py <- 40/200

phat <- (55+40)/(200+200)

z <- (px-py)/sqrt((1/200+1/200)*phat*(1-phat))

qnorm(0.025)
