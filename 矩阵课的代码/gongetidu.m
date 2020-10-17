function [x] = gongetidu(a,b)
n=size(a,1);
x=zeros(n,1);
r=b-a*x;
p=r;
for k=0:n-1
    alpha=(r'*r)/(p'*a*p);
    x=x+alpha*p;
    r2=b-a*x;
    if((norm(r2)<=1e-3)||(k==n-1))
        break;
    end
    beta=norm(r2)^2/norm(r)^2;
    p=r2+beta*p;
    r=r2;
end

end