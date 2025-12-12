= Fibonacci Sequence 

The Fibonacci sequence is defined through the recursive relation
$F_n=F_(n-1)+F_(n-2)$

$
F_n = round(1/sqrt(5) phi.alt^n),
quad phi.alt = (1+sqrt(5)) / 2
$

#let count = 9

The first #count numbers in the sequence are:

#let fib(n) = {
if n <=2 {1}
else { fib(n - 1) + fib(n - 2) }
}

#let nums = range(1,count+1)
#align(center, table(columns: count, 
        ..nums.map(n => $F_#n$),
        ..nums.map(n => str(fib(n)))
    ))


