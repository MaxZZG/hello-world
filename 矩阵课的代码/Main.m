
clc
clear
clf


%% 第一题
%{
% for i = 1:1:100
%    Y(i) = i^2;
% end

for i = 1:1:10000
   Y(i) = i^2;
end

[x1, x8, x2] = fanshu(Y);
fprintf('一范数x1 = %f\n',x1);
fprintf('二范数x2 = %f\n',x2);
fprintf('无穷范数x8 = %f\n',x8);
%}
%% 第二题
%{
kesai = 10^(-4);
qiugen( kesai );
erfen(kesai);
%}
%% 第三题
%{
n = 20;
A = zeros(n,n);
for i = 1:1:n
    A(i,i) = 6;
    try
       A(i,i-1) = 8;
    catch
    end

end
for i = 1:1:n-1
       A(i,i+1) = 1;
end


B = zeros(n,1);
B(1) = 7;
B(100) = 14;
for i = 2:1:n-1
    B(i) = 15;
end

x = lufenjie(A,B);
x1 = zhuyuanfenjie(A,B);

[c] = nijuzhen(n);

d = A * c;
%}
%% 第四题
%{
n = 500;
[x1,x2]=matrixa(n);
%}
%% 第五题
%{
% sin(pi*x)曲线
x = 0:0.0000001:1;
y = sin(pi * x);
plot(x,y,'r-');
hold on

% 拉格朗日插值的曲线
x = 0:0.01:1;
y = sin(pi * x);
yh = lagrange(x,y,x); % 拉格朗日插值函数
% plot(x,yh,'b-');
% hold on

yi = NewtonInterp(x,y,x);
plot(x,yh,'g-');
%}
%% 第六题
% 求函数精确积分
%{
syms x;
jingque = int(exp(1 * x) * cos(1 * x), -pi, pi);

disp('精确解为：');
fprintf('%f\n',jingque);


a = 2;
b = 2;
n = 800;
fx = inline('exp(1 * x) * cos(1 * x)','x');
res = ComTrapezium(fx,n,-pi,pi); % 复化的梯形公式
 
m = abs(jingque - res)/abs(jingque);
% disp('复化梯形解为：');
% fprintf('%f\n',res);
% disp('相对误差为：');
% fprintf('%f\n',m);

[result] = ComplexSimpson(-pi, pi,n);
mc = abs(jingque - result)/abs(jingque);
disp('复化Simpson解为：');
fprintf('%f\n',result);
disp('相对误差为：');
fprintf('%.15f\n',mc);
%}

%% 第七题
%{
syms x
f=exp(x)/x;
[quad1,quad2,quad3]=gaosishuzhijifen(f,1,exp(1));
fprintf('两点的结果为%f\n',quad1);
fprintf('三点的结果为%f\n',quad2);
fprintf('五点的结果为%f\n',quad3);
%}

%% 第八题
%{
h = 0.001;
R_K(h);
%}
%% 第九题
[Q,R] = qrfenjie();













