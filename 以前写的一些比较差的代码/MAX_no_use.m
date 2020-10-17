% MAX
% something just no use




%这个函数直接可以运行
function MAX()
%   初始权因子W
    R1x = 0;
    R2x = 0;
    R1y = 0;
    R2y = 0;
    R1z = 0;
    R2z = 0;
    Rx = [];
    Ry = [];
    Rz = [];
    q=1;
    a=1;
    z=1;
    
    % 权因子
    
    W = [1,2,1;
         2,2,2;
         1,2,1 ];
     
 %初始点坐标,这其实是课本上八分之一圆的点
 
  Px = [1,1,0;1,1,0;0,0,0];
  Py = [0,0,0;1,1,0;1,1,0];
  Pz = [0,1,1;0,1,1;0,1,1];
  
for u=0:0.01:1
    for v=0:0.01:1 
        Bu = Bernstein(u,2);
        Bv = Bernstein(v,2);
        R1x=0;
        R2x=0;
        R1y=0;
        R2y=0;
        R1z=0;
        R2z=0;
         for i=1:1:3
               for j=1:1:3
                   
                 %  这里用课本的公式
                 
                R1x=R1x + Px(i,j)*Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
                R2x=R2x + Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
                R1y=R1y + Py(i,j)*Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
                R2y=R2y + Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
                R1z=R1z + Pz(i,j)*Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
                R2z=R2z + Bu(i)*Bu(i)*Bv(j)*Bv(j)*W(i,j);
               end
         end
         Rx(q) = R1x/R2x;q=q+1;
         Ry(a) = R1y/R2y;a=a+1;
         Rz(z) = R1z/R2z;z=z+1;
         
    end
end


  title('双二次有理Bezier曲面','FontSize',14);
  %  先画一个较大范围的三维空间
  axis([-1,2,-1,2,-1,2]);hold on
  grid on
  %  画曲面
  Rx=double(Rx);
  Ry=double(Ry);
  Rz=double(Rz);
  xlabel('x轴');
  ylabel('y轴');
  zlabel('z轴');
  tri2=delaunay(Rx',Ry',Rz');
  trisurf(tri2,Rx,Ry,Rz,0.5,'EdgeAlpha',0);hold on

  
  % 画出控制网格
  
  Px = [1,1,0,1,1,0,0,0,0];
  Py = [0,0,0,1,1,0,1,1,0];
  Pz = [0,1,1,0,1,1,0,1,1];
  tri1=delaunay(Px',Py');
  plot3(Px,Py,Pz,'k.','MarkerSize',15);hold on
  trimesh(tri1,Px',Py',Pz', 'EdgeColor', 'r', 'FaceAlpha',0);hold on
  Px = [1,1,0,0,1,0];
  Py = [0,1,1,0,1,1];
  Pz = [1,1,1,1,0,0];
  tri1=delaunay(Px',Py');
  plot3(Px,Py,Pz,'k.','MarkerSize',15);hold on
  trimesh(tri1,Px',Py',Pz', 'EdgeColor', 'r', 'FaceAlpha',0);hold on
  
  plot3([1 1],[0 0],[0 1]);hold on
  plot3([1 1],[0 1],[1 1]);hold on
   plot3([1 1],[1 1],[0 1]);hold on
   plot3([0 0],[1 1],[0 1]);hold on
  %scatter3(Px,Py,Pz,'k');hold off
 
    
end

% 求Bernstein基函数

function output = Bernstein(t,p)
    %使用de Casteljau算法
    B = eye(p + 1);
    
    for i = p : -1 : 1
        % Save memory by overwriting the entries of B
        for j = 1 : i
            B(:, j) = (1 - t) * B(:, j) + t * B(:, j + 1);
        end
    end
    
    output = B(:, 1);
    
end
    
    
        
    