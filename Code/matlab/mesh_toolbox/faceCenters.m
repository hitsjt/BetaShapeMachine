function mesh = faceCenters(mesh);

if isfield(mesh,'Fc')
    mesh = rmfield(mesh,'Fc');
end

mesh.Fc = (mesh.V(:,mesh.F(1,:)) + mesh.V(:,mesh.F(2,:)) + ... 
           mesh.V(:,mesh.F(3,:)))/3;