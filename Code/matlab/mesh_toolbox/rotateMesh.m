function rmesh = rotateMesh(mesh, angle, x, y, z)

s = sind(angle);
c = cosd(angle);
xs = x*s;
ys = y*s;
zs = z*s;
c1 = 1-c;
xx = c1*x*x;
yy = c1*y*y;
zz = c1*z*z;
xy = c1*x*y; 
xz = c1*x*z; 
yz = c1*y*z;

T = [xx+c,  xy+zs, xz-ys,
     xy-zs, yy+c,  yz+xs,
     xz+ys, yz-xs, zz+c]';

center = mean(mesh.V, 2);
rmesh = mesh; 

for i=1:size(mesh.V, 2)
    rmesh.V(:, i) = T * (mesh.V(:, i) - center);
end

%  mesh = loadMesh('C:\Users\V\Desktop\BetaShapeMachine\Data\chair_gt_new\chair\chair004867.obj');
%  mesh1 = loadMesh('C:\Users\V\Desktop\BetaShapeMachine\Data\chair_gt_new\chair\bench000022.obj');
% for rx = 240:60:369
%     for ry = 330:60:369
%         for rz = 300:60:369
% 	    plotMesh( mesh1 );
% 	    hold on;
%             [rx ry rz]
% 	    rmesh = rotateMesh(mesh, rx, 1, 0, 0);
% 	    rmesh = rotateMesh(rmesh, ry, 0, 1, 0);
% 	    rmesh = rotateMesh(rmesh, rz, 0, 0, 1);
%             plotMesh( rmesh )
% 	    hold off;
%             pause;
%         end
%     end
% end
%         

% rx = 240;
% ry = 330;
% rz = 300;
% rmesh = rotateMesh(mesh, rx, 1, 0, 0);
% rmesh = rotateMesh(rmesh, ry, 0, 1, 0);
% rmesh = rotateMesh(rmesh, rz, 0, 0, 1);
% plotMesh( rmesh )
% hold on;
% 
% V = load( 'C:\Users\V\Desktop\BetaShapeMachine\Code\BSM\Build\Test\test.asc');
% plotPoints(V');
