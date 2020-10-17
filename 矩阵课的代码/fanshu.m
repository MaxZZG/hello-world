function [x1, x8, x2] = fanshu(Y)
% ���룺Y �����������
% �����x1 ��һ������x2 �Ƕ�������x8 �����

x1 = 0;
x2 = 0;
x8 = 0;

% ��һ����
for i = 1:1:numel(Y)
    x1 = x1 + abs(Y(i));
end

% �������
for i = 1:1:numel(Y)
    x2 = x2 + Y(i)^2;
end
x2 = sqrt(x2);

% �������
for i = 1:1:numel(Y)
   if(abs(Y(i)) > x8)
       x8 = Y(i);
   end     
end

end
