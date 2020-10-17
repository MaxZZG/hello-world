function [Q,R] = qrfenjie()
A=zeros(10,8);
for i=1:10
    for j=1:8
        A(i,j)=1/(i*j);
    end
end
[M,N]=size(A);
A1=A;
H1=zeros(M,M);
for j=1:M
 H1(j,j)=1;
end 
for k=1:N
  H0=zeros(M,M);
  for i=1:M
  H0(i,i)=1;
  end 
  s=0;
  for i=k:M
   s=s+A1(i,k)*A1(i,k);
  end 

  s=sqrt(s);
  u=zeros(N,1);
  if (A1(k,k)>=0) 
  u(k)=A1(k,k)+s;
  else 
  u(k)=A1(k,k)-s;
  end 
%-------------------------------  
  for i=k+1:M
  u(i)=A1(i,k);
  end   
  du=0;
  for i=k:M
  du=du+u(i)*u(i);
  end 
  for i=k:M
    for j=k:M
        H0(i,j)=-2*u(i)*u(j)/du;            
        if i==j 
        H0(i,j)=1+H0(i,j);
        end
    end 
  end 
A2=H0*A1;
H1=H1*H0;
end 
Q=H1;
R=A1;
end