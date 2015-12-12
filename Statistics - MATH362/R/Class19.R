? chisq.test

obs.freq = c(45,20,35)
probs = c(0.393, 0.239, 0.368) 

chisq.test(obs.freq, p=probs) 


c = (45-100*0.393)^2/(100*0.393)+(20-100*0.239)^2/(100*0.239)+(35-100*0.368)^2/(100*0.368)



obs.freq = c(65,35)
probs = c(0.632, 0.368) 

chisq.test(obs.freq, p=probs) 

install.packages("MASS")       # load the MASS package 
library("MASS")
levels(survey$Smoke) 

# we can find the frequency distribution with the table function.

smoke.freq = table(survey$Smoke) 
smoke.freq 

# Problem:  Suppose the campus smoking statistics is as below. 
# Heavy   Never   Occas   Regul 
#  4.5%   79.5%    8.5%    7.5%
  
# Determine whether the sample data in survey supports it at .05 significance level.
# We save the campus smoking statistics in a variable named smoke.prob. 
# Then we apply the chisq.test function and perform the Chi-Squared test.

smoke.prob = c(.045, .795, .085, .075) 
chisq.test(smoke.freq, p=smoke.prob) 


# http://www.radiolab.org/story/91699-from-benford-to-erdos/

# Benfords Law Example
river <- c(104,55,36,38,24,29,18,14,17)
p <- 1/9
n <- 335
probs <- c(p,p,p,p,p,p,p,p,p) 

expected <- n*probs
discrep <-river-expected
d <- sum(discrep^2/expected)

chisq.test(river, p=probs)

# P(1st digit is k) = log_10(k+1)-log_10(k)
ben_probs <- c(log10(1+1)-log10(1), log10(2+1)-log10(2), log10(3+1)-log10(3), log10(4+1)-log10(4),
               log10(5+1)-log10(5), log10(6+1)-log10(6),log10(7+1)-log10(7),log10(8+1)-log10(8),
               log10(9+1)-log10(9))
sum(ben_probs)

chisq.test(river, p = ben_probs)
