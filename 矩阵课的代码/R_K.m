
function R_K(h)
%ŷ����
y = 1;
% fprintf('ŷ������x=%f, y=%f\n',0,1);
for i=1:1/h
    x = (i-1) * h;
    K = f(x,y);
    y = y + h * K;
    
end
fprintf('ŷ������x = %.10f, y = %.10f\n',x+h,y);
fprintf('\n');
%�Ľ���ŷ����
y = 1;
% fprintf('�Ľ���ŷ������x=%f, y=%f\n',0,1);
for i=1:1/h
    x=(i-1)*h;
    K1=f(x,y);
    K2=f(x+h,y+h*K1);
    y=y+(h/2)*(K1+K2);
   
end
fprintf('�Ľ���ŷ������x = %.10f, y = %.10f\n',x+h,y);
fprintf('\n');
 %�����������
 y=1;
% fprintf('�����������x=%f, y=%f\n',0,1);
for i=1:1/h
    x=(i-1)*h;
    K1=f(x,y);
    K2=f(x+h/2,y+(h/2)*K1);
    K3=f(x+h/2,y+(h/2)*K2);
    K4=f(x+h,y+h*K3);
    y=y+(h/6)*(K1+2*K2+2*K3+K4);
    
end
fprintf('�����������x=%.10f, y = %.10f\n',x+h,y);
end
function z = f(x,y)
    z = (1/(x^2 + 1)) * (x^2 * y^2 - y);
end