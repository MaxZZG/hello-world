
function R_K(h)
%欧拉法
y = 1;
% fprintf('欧拉法：x=%f, y=%f\n',0,1);
for i=1:1/h
    x = (i-1) * h;
    K = f(x,y);
    y = y + h * K;
    
end
fprintf('欧拉法：x = %.10f, y = %.10f\n',x+h,y);
fprintf('\n');
%改进的欧拉法
y = 1;
% fprintf('改进的欧拉法：x=%f, y=%f\n',0,1);
for i=1:1/h
    x=(i-1)*h;
    K1=f(x,y);
    K2=f(x+h,y+h*K1);
    y=y+(h/2)*(K1+K2);
   
end
fprintf('改进的欧拉法：x = %.10f, y = %.10f\n',x+h,y);
fprintf('\n');
 %龙格库塔方法
 y=1;
% fprintf('龙格库塔法：x=%f, y=%f\n',0,1);
for i=1:1/h
    x=(i-1)*h;
    K1=f(x,y);
    K2=f(x+h/2,y+(h/2)*K1);
    K3=f(x+h/2,y+(h/2)*K2);
    K4=f(x+h,y+h*K3);
    y=y+(h/6)*(K1+2*K2+2*K3+K4);
    
end
fprintf('龙格库塔法：x=%.10f, y = %.10f\n',x+h,y);
end
function z = f(x,y)
    z = (1/(x^2 + 1)) * (x^2 * y^2 - y);
end