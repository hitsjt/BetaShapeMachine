function [mesh, dup, prob] = registerFaceEFM(mesh, i, dup, prob)

F = sort(mesh.F(:,i));
if nargin < 3
    dup = false(size(mesh.F,2),1);
end

[mesh, dup, prob] = registerToEdge(mesh, F(1),F(2), i, dup, prob);
[mesh, dup, prob] = registerToEdge(mesh, F(2),F(3), i, dup, prob);
[mesh, dup, prob] = registerToEdge(mesh, F(1),F(3), i, dup, prob);

% -------------------------------------------------------------------------
function [mesh, dup, prob] = registerToEdge(mesh,i,j,f,dup, prob)

if (mesh.EFM1(i,j) == f) || (mesh.EFM2(i,j) == f)
    warning('Tried to register face %d to EFM twice', f);
    return
end

% check for duplicate faces
if (mesh.EFM1(i,j) ~= 0) && ...
        isequal(sort(mesh.F(:,mesh.EFM1(i,j))), sort(mesh.F(:,f)))
    dup(f) = true;
    return
end
if (mesh.EFM2(i,j) ~= 0) && ...
        isequal(sort(mesh.F(:,mesh.EFM2(i,j))), sort(mesh.F(:,f)))
    dup(f) = true;
    return
end

if (mesh.EFM1(i,j) == 0)
    mesh.EFM1(i,j) = f;
elseif (mesh.EFM2(i,j) == 0)
    mesh.EFM2(i,j) = f;
else
    warning('More than two faces tried to register to edge (%d,%d). f = %d',i,j,f);
    prob = [prob;f];
    return
end
