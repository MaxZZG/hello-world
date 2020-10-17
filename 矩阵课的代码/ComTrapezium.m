function res = ComTrapezium(f,n,a,b)
    format long;
    if b < a
        c = b;
        b = a;
        a = c;
    end
    h = (b-a)/n;
    d = f(a);
    for i = a+h:h:b-h 
        d = d + (2 * f(i));
    end
    d = d + f(b);
    res = (d * h / 2);
end