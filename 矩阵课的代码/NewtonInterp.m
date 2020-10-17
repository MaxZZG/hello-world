function  yi = NewtonInterp(x,y,xi)

%  Newton 基本插值公式，调用格式为

%   yi = NewtonInterp(x,y,xi)

%  其中

%  x 为插值节点，y为节点处函数值，

%  xi 为为估计函数自变量，yi 为xi处函数估计值

%

%计算差商表

n = length(x);  Y= zeros(n); Y(:,1) = y';

for k = 1 : n-1

   for i = 1 : n - k

      if abs(x(i+k) - x(i))<eps

         error('% 输入的插值节点必须互异！');

      end

    Y(i,k+1) = (Y(i+1,k) - Y(i,k))/(x(i+k) - x(i));

   end

end

m = length(xi); yi = zeros(1,m);

for i = 1 : n   % 计算Newton插值公式

   z = ones(1,m);

   for k = 1 :  i - 1

       z = z .*(xi - x(k));

   end

   yi = yi + Y(1,i) * z;

end