function [c] = nijuzhen(n)
temp=eye(n);
c=zeros(n,n);
a=zeros(n,n);
a(1,1)=6;
a(1,2)=1;
a(n,n)=6;
a(n,n-1)=8;
for i=2:n-1
        a(i,i-1)=8;
        a(i,i)=6;
        a(i,i+1)=1;
end
for i=1:n
    c(:,i)=lufenjie(a,temp(:,i));
   
end
end