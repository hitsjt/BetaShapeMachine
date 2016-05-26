% NORMALS Compute face and vertex normals

function mesh = faceNormals(mesh)

% Face Normals

% cross product of edges (vertices are specified counterclockwise)
% If face is made up of points P1, P2 and P3, the face normal is the unit 
% vector parallel to (P2 - P1) x (P3 - P1)

mesh.Nf = zeros(4, size(mesh.F,2));
mesh.Nf(1:3,:) = cross(mesh.V(1:3,mesh.F(2,:)) - mesh.V(1:3,mesh.F(1,:)), ...
                       mesh.V(1:3,mesh.F(3,:)) - mesh.V(1:3,mesh.F(1,:)));
mesh.Nf = normalize(mesh.Nf);
