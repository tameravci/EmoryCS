function newton(f::Function,df::Function,H::Function,x0::Vector;maxIter=20,atol=1e-8,doPrint=false)

	x = copy(x0)
    his = zeros(maxIter,2)
    n = length(x)
    X = zeros(n,maxIter)
   
    i   = 1
    d   = df(x)
    d2f = H(x)

    while i<=maxIter
        fc = f(x)
        his[i,:] = [norm(fc) norm(d)]
 		X[:,i] = x
       # get search direction
        pk    = - (d2f\d)
        if doPrint
            @printf "iter=%04d\t|f|=%1.2e\t|df|=%1.2e\n" i his[i,1] his[i,2]
        end
        # update x and H
        x    += pk
        d  = df(x)
        if(norm(d)<atol)
            his = his[1:i,:]
 			X   = X[:,1:i]
           break
        end
		d2f = H(x)
        i+=1   
    end
    return x,his,X
end

function dampedNewton(f::Function,J::Function,H::Function,x::Vector;linesearch=armijo,maxIter=20,atol=1e-8,doPrint=false)
	
    his = zeros(maxIter,2)
    n = length(x)
   X = zeros(n,maxIter)
    
    i = 1
    xOld = x
    df   = J(x)
	df = df[:]
    d2f = H(x)

    while i<=maxIter
        fc = f(x)
        his[i,:] = [norm(fc) norm(df)]
 		X[:,i] = x
       # get search direction
      	pk    = - (d2f\df)
		if dot(pk,df)> 0
			pk *= -1
		end
        # line search
        ak,LS = linesearch(f,fc,df,x,pk) 
		if LS==-1
			@printf "Linesearch failed!"
            his = his[1:i,:]
 			X   = X[:,1:i]
			break;
		end
        if doPrint
            @printf "iter=%04d\t|f|=%1.2e\t|df|=%1.2e\tLS=%d\n" i his[i,1] his[i,2] LS
        end
        # update x and H
        x    += ak*pk
        df  = J(x)
		df = df[:]
        if(norm(df)<atol)
            his = his[1:i,:]
  			X   = X[:,1:i]
           break
        end
		d2f = H(x)
        i+=1   
    end
    return x,his
end
function gd(f::Function,df::Function,x::Vector;maxIter=20,atol=1e-8,doPrint=false,ls::Function=armijo)

    his = zeros(maxIter,2)
    n = length(x)
    I = eye(n)
	X = zeros(n,maxIter)
    
    i = 1
    xOld = x
    d   = df(x)
    
    while i<=maxIter
        fc = f(x)
        his[i,:] = [fc norm(d)]
		X[:,i] = x
        # get search direction
        pk    = - d/norm(d)
        # line search
        ak,LS = ls(f,fc,d,x,pk) 
        if doPrint && i >= 2
            @printf "iter=%04d\t|f|=%1.2e\t|f-fold|=%1.e2\t|df|=%1.2e\tLS=%d\n" i his[i,1] his[i,1]-his[i-1,1] his[i,2] LS
        end
		if LS==-1
			@printf "Linesearch failed!"
            his = his[1:i,:]
			X   = X[:,1:i]
			break;
		end

        # update x and H
        x    += ak*pk
        d  = df(x)
        if(norm(d)<atol)
            his = his[1:i,:]
			X = X[:,1:i]
            break
        end
        i+=1   
    end
    return x,his,X
end

function armijo(f::Function,fc,df,xc,pc;maxIter=100, alpha=1e-4,b=0.9)
LS = 1
t  = 1
while LS<=maxIter
    if f(xc+t*pc) <= fc + t*alpha*dot(df,pc)
        break
    end
    t *= b
    LS += 1
end
if LS>maxIter
	LS= -1
	t = 0.0
end
return t,LS
end


