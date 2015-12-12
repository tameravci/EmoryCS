##################################
# Import and explore the dataset
##################################
#sales <- read.csv("~/Dropbox/Syllabi/14Spring/Math362/sales.csv")
#View(sales)
# Get a summary of the data
s<-summary(sales)
s

par(mfrow=c(1,2))
boxplot(sales$Total, names=c("Tips"))
title("Receipt Totals")
boxplot(sales$Tips, names=c("Tips"))
title("Tips")

# If you are using Latex and want to capture your plot as an eps file you can use this code.
#dev.print(device=postscript, "~/Dropbox/Syllabi/14Spring/Math362/boxplot.eps", onefile=FALSE, horizontal=FALSE)
#dev.off()
# If you are using Latex and want to capture your output you can use this code.
#capture.output(s, file = "~/Dropbox/Syllabi/14Spring/Math362/summary.txt", append = FALSE)
##################################
# Problem: In the United States is it common that you tip a server at a restaurant
# 15% of the receipt total. Here we ask, if the baristias at a coffee shop are tipped
# at the same rate as a full scale restaurant. The coffee shop data has an mean receipt 
# total per customer of $5.47. So, a baristia would expect to make a mean tip of $0.82 
# per customer. In the given data we have the totals for 5211 customers and in (1) it 
# was was also found that the mean tip of this data is $0.67. Assume the standard 
# deviation of the tips is $0.70.  At 0.05 significance level, can we reject the claim 
# At 0.05 significance level, can we reject the claim that the tips at this coffee shop
# are at 15%?
##################################
# One-sided Test (lower tail)
##################################

xbar = 0.67          # sample mean 
mu0 =  0.82          # hypothesized value 
sigma =  0.70        # population standard deviation 
n =   5211           # sample size 
z = (xbar-mu0)/(sigma/sqrt(n))
z                      # test statistic 

# Compute the critical value at 0.05 significance level.
alpha = 0.05 
z.alpha = qnorm(1-alpha) 
-z.alpha               # critical value 

# Compute the p-value.
pval = pnorm(z) 
pval                   # lower tail p−value 

##################################
# Problem: The owner of the coffee shop decides to run a lunch special on Saturday. 
# Test if the lunch specail changed the mean of the ticket total for the day, the 
# owner pulls the sales data for the day. He had 303 customers with a mean ticket 
# price of $5.70. We will take the coffee shop data as the standard. Letting the
# hypothesised mean receipt total per customer be $5.47 with a standar devation of
# $3.40. Using 0.05 significance level, tell the owner if he should run 
# the speical again? What if we change the signifcance level to 0.10?
##################################
# Two-sided Test
##################################

xbar =  5.7           # sample mean 
mu0 =   5.47           # hypothesized value 
sigma = 3.4           # population standard deviation 
n =     303           # sample size 
z = (xbar-mu0)/(sigma/sqrt(n)) 
z                      # test statistic 

# Compute the critical value at 0.05 significance level.

alpha = 0.05 
z.half.alpha = qnorm(1-alpha/2) 
c(-z.half.alpha, z.half.alpha) 

# Compute the p-value.
pval = 2 * (1-pnorm(z))  # lower tail 
pval                   # two−tailed p−value 