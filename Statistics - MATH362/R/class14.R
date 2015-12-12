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

# find the critical values
qt(0.025,16)

# OR use the R command
t.test(tw,qcs, var.equal=TRUE, paired = FALSE)

# Example: Alcoholic Authors/Problem 9.2.6 ###################
al <- c(48, 66, 71, 65, 56, 67, 67, 70, 77)
non <- c(65, 87, 32, 77, 89, 86, 77, 84, 64, 88, 90, 67)

xbar <- mean(al)
ybar <- mean(non)

n <- length(al)
m <- length(non)

Sp2 <- ((n-1)*sd(al)^2 +(m-1)*sd(non)^2)/(n+m-2)

t <- (xbar-ybar)/sqrt((1/n+1/m)*Sp2)

qt(0.05,19)

t.test(al,non, alternative = "less", var.equal=TRUE, paired = FALSE)

non2 <- c(65, 87, 77, 89, 86, 77, 84, 64, 88, 90, 67)

t.test(al,non2, alternative = "less", var.equal=TRUE, paired = FALSE)
