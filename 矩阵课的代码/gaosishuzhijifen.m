function[quad1,quad2,quad3] = gaosishuzhijifen(f,a,b)
x1=[0.7745966692,0,-0.774596692];
w1=[0.5555555556,0.8888888889,0.5555555556];
T1=(a+b)/2+(b-a)/2*x1;
quad1=(b-a)/2*sum(w1.*subs (f,T1));
%����
x2=[0.8611363116,-0.8611363116,0.3399810436,-0.3399810436];
w2=[0.3478548451,0.3478548451,0.6521451549,0.6521451549];
T2=(a+b)/2+(b-a)/2*x2;
quad2=(b-a)/2*sum(w2.*subs (f,T2));
%���
x3=[0.9324695142,-0.9324695142,0.6612093865,-0.6612093865,0.2366191861,-0.2366191861];
w3=[0.2369268851,0.2369268851,0.4786286705,0.4786286705,0.5688888889,0.5688888889];
T3=(a+b)/2+(b-a)/2*x3;
quad3=(b-a)/2*sum(w3.*subs (f,T3));
end