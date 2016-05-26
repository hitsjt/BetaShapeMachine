function showBoundaryEdges(mesh)

if ~isfield(mesh,'EFM1')
    mesh = getEdgeFaceMatrix(mesh);
end

[I,J] = find(xor(mesh.EFM1,mesh.EFM2));

if isempty(I)
    disp('No boundary edges found.');
else
    hold on;
    plotMesh(mesh);
    for i = 1:size(I,1)
        plot3(mesh.V(1,[I(i);J(i)]), mesh.V(2,[I(i);J(i)]), ...
              mesh.V(3,[I(i);J(i)]),'r','LineWidth',3);
    end
    hold off;
    axis off;
end