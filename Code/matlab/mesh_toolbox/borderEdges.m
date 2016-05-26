function Es = borderEdjes(mesh)

if ~isfield(mesh,'EFM1')
    mesh = getEdgeFaceMatrix(mesh);
end
    
Es = [];
EFM1 = mesh.EFM1;
EFM2 = mesh.EFM2;
numverts = size(mesh.V,2);
for i = 1:(numverts-1)
    for j = (i+1):numverts
        if xor(EFM1(i,j) == 0, EFM2(i,j) == 0)
            Es = [Es,[i;j]];
        end
    end
end

