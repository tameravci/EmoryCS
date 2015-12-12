## Draw a random sample of size n 
n<-20
## from a poisson distribution with parameter lambda
# lambda<-4 
# rs <- rpois(n, lambda)

## from a normal distribution with parameters mu and sigma
 mu<-2
 sigma<-5
rs <- rnorm(n,mu,sigma)

## Estimate of the of the mean
lambda_e<-sum(rs)/n+1/n
lambda_e

## Show that the estimate is biased by running simulations
## looking at the box plot
numsim <- 2000
lambda_e_sims<- rep(0,numsim)

for (i in 1:numsim){
  rs <- rnorm(n,mu,sigma)
  lambda_e_sims[i]<-sum(rs)/n+1/n
}
par(mfrow=c(1,2))
boxplot(lambda_e_sims, names=c("lambda_e"))
title("Estimates mu and sigma ")

## Explore consistency by creating a sequence of estimates
## We do this by taking larger and larger randome sample sizes
n<-100
lambda_e_n<- rep(0,n)
for (i in 1:n){
  rs <- rnorm(i,mu,sigma)
  lambda_e_n[i]<-sum(rs)/n+1/n
}

plot(1:n,lambda_e_n, xlab='n',ylab='lambda_e')
title("n to infinity ")
