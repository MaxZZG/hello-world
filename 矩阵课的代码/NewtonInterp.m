function  yi = NewtonInterp(x,y,xi)

%  Newton ������ֵ��ʽ�����ø�ʽΪ

%   yi = NewtonInterp(x,y,xi)

%  ����

%  x Ϊ��ֵ�ڵ㣬yΪ�ڵ㴦����ֵ��

%  xi ΪΪ���ƺ����Ա�����yi Ϊxi����������ֵ

%

%������̱�

n = length(x);  Y= zeros(n); Y(:,1) = y';

for k = 1 : n-1

   for i = 1 : n - k

      if abs(x(i+k) - x(i))<eps

         error('% ����Ĳ�ֵ�ڵ���뻥�죡');

      end

    Y(i,k+1) = (Y(i+1,k) - Y(i,k))/(x(i+k) - x(i));

   end

end

m = length(xi); yi = zeros(1,m);

for i = 1 : n   % ����Newton��ֵ��ʽ

   z = ones(1,m);

   for k = 1 :  i - 1

       z = z .*(xi - x(k));

   end

   yi = yi + Y(1,i) * z;

end