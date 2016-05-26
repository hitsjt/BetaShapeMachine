function mesh = removeUnrefVerts(mesh)

verts = unique(mesh.F(:));
remcount = size(mesh.V,2) - length(verts);

if remcount > 0    
    mesh.V = mesh.V(:,verts);
    [tf, mesh.F] = ismember(mesh.F,verts);
    if ~all(tf(:))
        error('Face indices reference non-existent vertices.');
    end
end    
disp(sprintf('Removed %d vertices.', remcount));