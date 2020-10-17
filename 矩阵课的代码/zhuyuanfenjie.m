function [x] = zhuyuanfenjie(A,b)
n=size(A,1);
x=zeros(n,1);
y=zeros(n,1);
temprow=zeros(n,1);
tempconstant=0;
%p=zeros(n,1);
for i=1:n-1
    [max_value,index]=max(abs(A(i:n,i)));
    temprow=A(i,:);
    A(i,:)=A(i+index-1,:);
    A(i+index-1,:)=temprow;
    tempconstant=b(i);
    b(i)=b(index+i-1);
    b(index+i-1)=tempconstant;
    if A(i,i)==0
        disp('æÿ’ÛAŒ™∑«∆Ê“Ï');
    end
    for j=i+1;n
        miu=A(j,i)/A(i,i);
        A(j,i)=miu;
        A(j,i+1:n)=A(j,i+1:n)-miu*A(i,i+1:n);
    end
end
y(1)=b(1);
for k=2:n
    y(k)=b(k)-A(k,1:k-1)*y(1:k-1);
end
x(n)=y(n)/A(n,n);
for k=n-1:-1:1
    x(k)=(y(k)-A(k,k+1:n)*x(k+1:n))/A(k,k);
end
end