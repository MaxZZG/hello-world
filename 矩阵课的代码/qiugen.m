function [] = qiugen( kesai ) 
flag=1;
x0=2.1;
y0=2.1;
while(flag)
    x1=x0-(x0-2)^9/(9*(x0-2)^8);
    if (abs(x1-x0)<kesai)
       fprintf('牛顿法的结果为%f\n',x1);
        break;
    end
    x0=x1;
end
while(flag)
    y1=y0-8*(y0-2)^9/(9*(y0-2)^8);
   if (abs(y1-y0)<kesai)
       fprintf('修改牛顿法的结果为%f\n',y1);
       break;
   end
   y0=y1;
end
end