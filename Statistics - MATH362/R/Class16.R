x <- c(160, 175, 180, 185, 185, 185, 190, 190, 195, 195, 195 , 200 , 200,
       200, 200, 205, 205, 210, 210, 218, 219, 220, 222, 225 , 225, 232)
y <- c(155,  155,  160,  160,  160, 166, 170, 175, 175, 175,  180, 185, 185,
       185 , 185 , 185 , 185 ,185 , 190, 190, 190, 190,190, 195, 195, 195,
       195, 200, 205, 207,210,211, 230)

# (1)
xbar = mean(x)
ybar = mean(y)

n = length(x)
m = length(y)

Sp2 <- ((n-1)*sd(x)^2 +(m-1)*sd(y)^2)/(n+m-2)

tl = qt(0.025,n+m-2)
t = qt(0.975,n+m-2)

CI_Lower = xbar -ybar -t*sqrt((1/n+1/m)*Sp2)
CI_UPer = xbar -ybar +t*sqrt((1/n+1/m)*Sp2)

#(2)

x = 15
n = 59

# approximate  11% as 11 out of 100
y = 11
m=100

z_alpha = qnorm(0.975)

CI_Lower = (x/n - y/m) - z_alpha*sqrt((x/n*(1-x/n))/n + (y/m*(1-y/m)/m))

CI_Upper = (x/n - y/m) + z_alpha*sqrt((x/n*(1-x/n))/n + (y/m*(1-y/m)/m))


#(3)

Sx = sd(x)
Sy = sd(y)

n = length(x)
m = length(y)

alpha = 0.05

F_l = qf(alpha/2,m-1,n-1)
F_u = qf(1-alpha/2,m-1,n-1)


CI_Lower = Sx/Sy*F_l

CI_Upper = Sx/Sy*F_u

var.test(x,y)
