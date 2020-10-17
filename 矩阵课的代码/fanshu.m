function [x1, x8, x2] = fanshu(Y)
% 输入：Y 是输入的向量
% 输出：x1 是一范数，x2 是二范数，x8 无穷范数

x1 = 0;
x2 = 0;
x8 = 0;

% 算一范数
for i = 1:1:numel(Y)
    x1 = x1 + abs(Y(i));
end

% 算二范数
for i = 1:1:numel(Y)
    x2 = x2 + Y(i)^2;
end
x2 = sqrt(x2);

% 算无穷范数
for i = 1:1:numel(Y)
   if(abs(Y(i)) > x8)
       x8 = Y(i);
   end     
end

end
