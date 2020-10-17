function x=lufenjie(a,b)
n=size(a,1);
m = eye(n,n);  
% initial the n*n matrix m zeros 
x=zeros(n,1);
y=zeros(n,1);
for j = 1 : n-1
    if abs(a(j,j))<eps; 
        error('zero pivot encountered');       
end
    for i = j+1 : n
        mult = a(i,j)/a(j,j);
        m(i,j) = mult;  
        for k = j:n
            a(i,k) = a(i,k) - mult*a(j,k);
        end
    end
    y(1)=b(1);
for k=2:n
    y(k)=b(k)-m(k,1:k-1)*y(1:k-1);
end
x(n)=y(n)/a(n,n);
for k=n-1:-1:1
    x(k)=(y(k)-a(k,k+1:n)*x(k+1:n))/a(k,k);
end
end