function [] = erfen(kesai)
a=1.5;
b=2.5;
z0=(a+b)/2;
c=a;
d=b;
fun=@(x)(x-2)^9;
while(abs(c-d)>kesai)
   if feval(fun,z0)*feval(fun,c)>0
       c=z0;
   else
       d=z0;
   end
    z0=(c+d)/2;
end
fprintf('二分法根为%f\n',z0);
end