function plotSymmetryPlane(plane, mesh)

if length(plane) == 6
	p = plane(4:6);
	n = plane(1:3);
	d = -sum( n .* p);
	plane = [n;d];
end

verts = 1:size(mesh.V,2);

x_min = min(mesh.V(1,verts),[],2);
x_max = max(mesh.V(1,verts),[],2);
y_min = min(mesh.V(2,verts),[],2);
y_max = max(mesh.V(2,verts),[],2);
z_min = min(mesh.V(3,verts),[],2);
z_max = max(mesh.V(3,verts),[],2);

vol = inf;
for k = 1:3

    if k == 1
    
        xs = linspace(x_min,x_max,2);
        ys = linspace(y_min,y_max,2);
        [x y] = meshgrid(xs,ys);

        z = (-plane(1)*x - plane(2)*y - plane(4)) / plane(3);

    elseif k == 2
        
        xs = linspace(x_min,x_max,2);
        zs = linspace(z_min,z_max,2);
        [x z] = meshgrid(xs,zs);

        y = (-plane(1)*x - plane(3)*z - plane(4)) / plane(2);
    elseif k == 3

        ys = linspace(y_min,y_max,2);
        zs = linspace(z_min,z_max,2);
        [y z] = meshgrid(ys,zs);

        x = (-plane(2)*y - plane(3)*z - plane(4)) / plane(1);
    end
    
    vol_tmp = (max(x(:)) - min(x(:)))*(max(y(:)) - min(y(:)))*(max(z(:)) - min(z(:)));
    if vol_tmp < vol
        vol = vol_tmp;
        X = x;
        Y = y;
        Z = z;
    end
end

surf(X,Y,Z, 1, 'FaceColor','g','EdgeColor','k','FaceAlpha',.5);







% if nargin >=3
%     verts = unique(mesh.F(:,SymRegion));
% else
%     verts = 1:size(mesh.V,2);
% end
% 
% a = min(mesh.V(1:3,verts),[],2);
% b = max(mesh.V(1:3,verts),[],2);
% 
% m = (a + b)/2;
% 
% a = (a - m)*2 + m;
% b = (b - m)*2 + m;
% 
% s = norm(b(1:3) - a(1:3));
% 
% %[x y] = meshgrid(a(1):s/10:b(1), a(2):s/10:b(2));
% [x y] = meshgrid(a(1):(b(1)-a(1)):b(1), a(2):(b(2)-a(2)):b(2));
% 
% d = -sum(plane(4:6) .* plane(1:3));
% z = (-plane(4)*x - plane(5)*y - d) / plane(6);
% 
% % cx = mean(x(:));
% % cy = mean(y(:));
% % cz = mean(z(:));
% % 
% % sx = max(x(:)) - min(x(:));
% % sy = max(y(:)) - min(y(:));
% % sz = max(z(:)) - min(z(:));
% % 
% % x = (x - cx(ones(size(x))))*100/sx + cx(ones(size(x)));
% % y = (y - cy(ones(size(y))))*100/sy + cy(ones(size(y)));
% % z = (z - cz(ones(size(z))))*100/sz + cz(ones(size(z)));
% 
% surf(x,y,z,'FaceColor','g','EdgeColor','k','FaceAlpha',.5);
