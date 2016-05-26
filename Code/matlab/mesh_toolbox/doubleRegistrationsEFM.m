function tf = doubleRegistrationsEFM(mesh)

for i = 1:size(mesh.V,2)
    for j = 1:size(mesh.V,2)
        if mesh.EFM(i,j,1) == mesh.EFM(i,j,2)
            tf = true;
            return
        end
    end
end
tf = false