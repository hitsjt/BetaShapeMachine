function plotCurvatureDirections(mesh, K1V, K2V, type)
% plots curvature directions, still buggy

%avg = avgEdgeLength(mesh) * scale;

invalid = isnan( K1V );
K1V(invalid) = 0;
invalid = isnan( K2V );
K2V(invalid) = 0;

if strcmpi(type,'max') || strcmpi(type,'both')
    c = 'r';
    quiver3(mesh.V(1, :)', mesh.V(2, :)', mesh.V(3, :)', K1V(1, :)', K1V(2, :)', K1V(3, :)', [c,'-']); 
    hold on;
    %quiver3(mesh.V(1, :)', mesh.V(2, :)', mesh.V(3, :)', -K1V(1, :)', -K1V(2, :)', -K1V(3, :)', avg, [c,'-']); 
end
if strcmpi(type,'min') || strcmpi(type,'both') 
    c = 'b';
    quiver3(mesh.V(1, :)', mesh.V(2, :)', mesh.V(3, :)', K2V(1, :)', K2V(2, :)', K2V(3, :)', [c,'-']); 
    hold on;
    %quiver3(mesh.V(1, :)', mesh.V(2, :)', mesh.V(3, :)', -K2V(1, :)', -K2V(2, :)', -K2V(3, :)', avg, [c,'-']); 
end

hold on;
plotMesh(mesh,'solidbw'); 

set(gcf, 'Color', 'w', 'Renderer', 'OpenGL');