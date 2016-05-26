function plotVertex(mesh, I, showMesh)
if ~isfield(mesh, 'Nv')
    mesh.Nv = zeros( 3, size(mesh.V, 2));
end

if nargin == 1
    I = 1:size(mesh.V, 2);
end

% plot vertex with a red star
if nargin == 3
    mesh = normals(mesh);
    plotMesh(mesh, type);
    hold on;
end

for i=1:length(I)
    hold on;
    X = mesh.V(1:3, I(i)) + .001 * mesh.Nv(1:3, I(i));
    plot3(X(1), X(2), X(3), 'm.', 'MarkerSize', 5);
end

hold off;