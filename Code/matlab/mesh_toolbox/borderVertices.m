function isBorder = borderVertices(mesh)

if ~isfield(mesh,'EFM1')
    mesh = getEdgeFaceMatrix(mesh);
end
    
%k = full(any(xor(mesh.EFM1,mesh.EFM2),1));

Es = borderEdges(mesh);
k = unique(Es(:));
isBorder = false(1,size(mesh.V,2));
isBorder(k) = true;