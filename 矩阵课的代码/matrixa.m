function [x1,x2]=matrixa(n)
a=zeros(n);
for i=1:n
    for j=1:i
        a(i,j)=1/(i+j-1);
        a(j,i)=a(i,j);
    end
end

b=ones(n,1);
x1=gongetidu(a,b);
fprintf('chol分解的误差为：%f\n',norm(a*x1-b));
x2=choleskyfenjie(a,b);
fprintf('共轭梯度的误差为：%f\n',norm(a*x2-b));
end