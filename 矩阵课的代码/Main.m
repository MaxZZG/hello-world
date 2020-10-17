
clc
clear
clf


%% ��һ��
%{
% for i = 1:1:100
%    Y(i) = i^2;
% end

for i = 1:1:10000
   Y(i) = i^2;
end

[x1, x8, x2] = fanshu(Y);
fprintf('һ����x1 = %f\n',x1);
fprintf('������x2 = %f\n',x2);
fprintf('�����x8 = %f\n',x8);
%}
%% �ڶ���
%{
kesai = 10^(-4);
qiugen( kesai );
erfen(kesai);
%}
%% ������
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
%% ������
%{
n = 500;
[x1,x2]=matrixa(n);
%}
%% ������
%{
% sin(pi*x)����
x = 0:0.0000001:1;
y = sin(pi * x);
plot(x,y,'r-');
hold on

% �������ղ�ֵ������
x = 0:0.01:1;
y = sin(pi * x);
yh = lagrange(x,y,x); % �������ղ�ֵ����
% plot(x,yh,'b-');
% hold on

yi = NewtonInterp(x,y,x);
plot(x,yh,'g-');
%}
%% ������
% ������ȷ����
%{
syms x;
jingque = int(exp(1 * x) * cos(1 * x), -pi, pi);

disp('��ȷ��Ϊ��');
fprintf('%f\n',jingque);


a = 2;
b = 2;
n = 800;
fx = inline('exp(1 * x) * cos(1 * x)','x');
res = ComTrapezium(fx,n,-pi,pi); % ���������ι�ʽ
 
m = abs(jingque - res)/abs(jingque);
% disp('�������ν�Ϊ��');
% fprintf('%f\n',res);
% disp('������Ϊ��');
% fprintf('%f\n',m);

[result] = ComplexSimpson(-pi, pi,n);
mc = abs(jingque - result)/abs(jingque);
disp('����Simpson��Ϊ��');
fprintf('%f\n',result);
disp('������Ϊ��');
fprintf('%.15f\n',mc);
%}

%% ������
%{
syms x
f=exp(x)/x;
[quad1,quad2,quad3]=gaosishuzhijifen(f,1,exp(1));
fprintf('����Ľ��Ϊ%f\n',quad1);
fprintf('����Ľ��Ϊ%f\n',quad2);
fprintf('���Ľ��Ϊ%f\n',quad3);
%}

%% �ڰ���
%{
h = 0.001;
R_K(h);
%}
%% �ھ���
[Q,R] = qrfenjie();













