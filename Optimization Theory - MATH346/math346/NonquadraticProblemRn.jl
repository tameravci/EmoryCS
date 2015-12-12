using PyPlot

include("/Users/lruthot/Google Drive/Julia/notebooks/math346/optiFuncs.jl")

n = 10000
e = ones(Float64,n)
A = sprandn(n,n,3*n./n^2)
b = rand(n)

f(x) = ((minimum(1-x.^2)>=0) && (minimum(b - A*x)>=0)) ? - dot(e,log(1-x.^2)) - dot(e,log(b - A*x)) : Inf
df(x) = 2.*(x./(1-x.^2))+A'*(1./(b-A*x))  
d2f(x) = 2* spdiagm((x.^2 + 1)./(x.^2-1).^2,0,n,n) +A'*spdiagm(1./((b-A*x).^2),0,n,n)*A


myLS(f,fc,df,x,pk) =  armijo(f,fc,df,x,pk,alpha=1e-1,b=0.9,maxIter=2000)
x0 = zeros(Float64,n)
xgd,hisgd = gd(f,df,x0,maxIter=100,doPrint=true,ls=myLS);

 figure("Gradient Descent")
 subplot(1,2,1)
 semilogy(hisgd[:,1]-hisgd[end,1])
 title("suboptimality, f(xk) - p*")
 xlabel("iteration")
 subplot(1,2,2)
 semilogy(abs(hisgd[:,2]))
 title("norm of gradient, |df(x_k)|")
 xlabel("iteration")

x0 = zeros(Float64,n)
xnt,hisnt = newton(f,df,d2f,x0,doPrint=false,maxIter=20);

figure("Newton's Method")
subplot(1,2,1)
semilogy(abs(hisnt[:,1]-hisnt[end,1]))
title("suboptimality, f(xk) - p*")
xlabel("iteration")
subplot(1,2,2)
semilogy(abs(hisnt[:,2]))
title("norm of gradient, |df(x_k)|")
xlabel("iteration")