# need pakage
install.packages("plotrix")
# For consistancy set the seed
set.seed(0815)

#########################################
# Uniform
#########################################

# Set random sample size n
n<-10

# Set the true value for the parameter
theta <- 2

# Set the number of simulations you want to run
#   i.e. the number of random samples (each of size n) you want to test
numsim <- 20
#numsim <- 100

# initialize vecters for 
# x - each simulation to be ploted on along the x-axis
# L/L_clt the Lower bound of the CI
# U/U_clt the Upper bound of the CI
x <- 1:numsim
L<- rep(0,numsim)
U<- rep(0,numsim)
T<- rep(0,numsim)

L_clt<- rep(0,numsim)
U_clt<- rep(0,numsim)
T_clt<- rep(0,numsim)

# for each simulation
for (i in 1:numsim){
  # draw a random sample of size n from a uniform distribution with parameters a = 0, b = theta
  rs <- runif(n,0,theta)
  # calculate the Lower bound via MLE estimate
  L[i] <- max(rs)
  # calculate the Upper bound via the MLE estimate
  U[i] <- max(rs)/(0.05^(1/n))
  # calculate the center of the interval
  T[i] <- (U[i]+L[i])/2
  
  # calculate the Lower bound via the CLT
  L_clt[i] <- 2*mean(rs)/(1+1.96/sqrt(3*n))
  # calculate the Upper bound via the CLT
  U_clt[i] <- 2*mean(rs)/(1-1.96/sqrt(3*n))
  # calculate the center of the CLT interval
  T_clt[i] <- (U_clt[i]+L_clt[i])/2
}
# plot
require(plotrix)
par(mfrow=c(2,1))
plotCI(x, T, ui=U, li=L)
abline(theta,0, col="blue")
title("95% CIs for Uniform(0,2) via MLE")
plotCI(x, T_clt, ui=U_clt, li=L_clt)
abline(theta,0, col="blue")
title("95% CIs for Uniform(0,2) via CLT")


#########################################
# Binomial
#########################################

# Set random sample size n
n<-100

# Set the true value for the parameter
prob <- 1/2
# we assumed that this parameter was known in the 
numsim <- n
x <- 1:numsim

# initialize vecters for 
# x - each simulation to be ploted on along the x-axis
# L/L_clt the Lower bound of the CI
# U/U_clt the Upper bound of the CI
L_clt<- rep(0,numsim)
U_clt<- rep(0,numsim)
p_clt<- rep(0,numsim)

# for each simulation
for (i in 1:numsim){
  rs <- rbinom(1, n, prob)
  # calculate the Lower bound via the CLT
  L_clt[i] <- rs/n-1.96*sqrt(rs*(1-rs/n))/n
  # calculate the Upper bound via the CLT
  U_clt[i] <- rs/n+1.96*sqrt(rs*(1-rs/n))/n
  # calculate the center of the CLT interval
  p_clt[i] <- rs/n
}
# plot
par(mfrow=c(1,1))
plotCI(x, p_clt, ui=U_clt, li=L_clt)
abline(prob,0, col="blue")
title("95% CIs for Binomial(n,1/2) via CLT")

