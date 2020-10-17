%计算x对应的函数值f(x)

function [y_x] = CalcuFunctionValue(x)
% inputs:
%        x:待求值
% outputs:
%        y_x:x对应的函数值

    y_x = exp(1 * x) * cos(1 * x);

end
