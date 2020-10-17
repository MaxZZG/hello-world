%chol·Ö½â
function [x] = choleskyfenjie(a,b)
n=size(a,1);
y=zeros(n,1);
x=zeros(n,1);
for k=1:n
    a(k,k)=sqrt(a(k,k));
    a(k+1:n,k)=a(k+1:n,k)/a(k,k);
    for j=k+1:n
        a(j:n,j)=a(j:n,j)-a(j:n,k)*a(j,k);
    end
end

y(1)=b(1)/a(1,1);
for i=2:n
    y(i)=(b(i)-a(i,1:i-1)*y(1:i-1))/a(i,i);
end
x(n)=y(n)/a(n,n);
for i=n-1:-1:1
 x(i)=(y(i)-a(i+1:n,i)'*x(i+1:n))/a(i,i);
end
end