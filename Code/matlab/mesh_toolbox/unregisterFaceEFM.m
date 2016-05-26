function mesh = unregisterFaceEFM(mesh, i)

F = sort(mesh.F(:,i));

mesh = unregisterFromEdge(mesh,F(1),F(2), i);
mesh = unregisterFromEdge(mesh,F(2),F(3), i);
mesh = unregisterFromEdge(mesh,F(1),F(3), i);

% -------------------------------------------------------------------------
function mesh = unregisterFromEdge(mesh,i,j,f)

if (mesh.EFM1(i,j) == f)
    mesh.EFM1(i,j) = 0;
elseif (mesh.EFM2(i,j) == f)
    mesh.EFM2(i,j) = 0;
else
    warning('Tried to unregister face %d from edge (%d,%d) when it wasn''t registered', f, i, j);
    return
end
