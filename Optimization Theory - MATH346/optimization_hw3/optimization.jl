
x = [1/21 * i for i=0:20]
g = [cos(2 * pi * xi) for xi in x]

function vandermonde(n)
    return [x[row]^(n+1-col) for row = 1:21, col = 1:n+1]
end

for n = 2:5
    A = vandermonde(n)
    H = A' * A
    eigenvalues = eigvals(H)
    convex_message = minimum(eigenvalues) > 0 ? "IS strictly convex" :
                                                "IS NOT strictly convex"
    print ("""

for n = $n, the eigenvalues are,
$eigenvalues, so the objective function $convex_message
""")
end

coefficients = [zeros(i)' for i=0:10]
for n = 2:5
    A = vandermonde(n)
    c =  (A' * g)' * inv(A' * A)
    print( "for n = $n, the optimal coefficients are $c")
    coefficients[n] = c
end

function approximate_solution(n, x)
    c = coefficients[n]
    return sum([c[n+1-i] * x^(i) for i=0:n])
end

actual_solution(x) = cos(2 * pi * x)
space = linspace(0,1,200)
actual_values = [actual_solution(p) for p in space]

using Gadfly
layers = Layer[layer(x=space, y=actual_values, Geom.line,
                     Theme(default_color=color("red")))]
for n = 2:5
    estimates = [approximate_solution(n,p) for p in space]
    println ("For n = $n, the maximum absolute error is $(maximum(map(abs, estimates - actual_values)))")
    push!(layers, layer(x=space, y=estimates, Geom.line,
                        Theme(default_color=color("blue"))))
end

draw(SVG("optimization_hw3_plot.jpg", 6inch, 3inch), plot(layers...))
#plot(layers...)

g = [cos(2 * pi * xi) + (rand() - 0.5) * 0.2 for xi in x]
for n = 2:5
    A = vandermonde(n)
    coefficients[n] =  (A' * g)' * inv(A' * A)
end

for n = 2:5
    estimates = [approximate_solution(n,p) for p in space]
    println ("For n = $n, the maximum absolute error is $(maximum(map(abs, estimates - actual_values)))")
end
