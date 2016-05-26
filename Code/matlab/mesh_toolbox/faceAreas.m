function mesh = faceAreas(mesh)

% area = 0.5*|u x v|

%mesh.Fa = zeros(size(mesh.F,2),1);
mesh.Fa = 0.5*norms(cross(mesh.V(1:3,mesh.F(2,:)) - mesh.V(1:3,mesh.F(1,:)), ...
                    mesh.V(1:3,mesh.F(3,:)) - mesh.V(1:3,mesh.F(1,:))));
