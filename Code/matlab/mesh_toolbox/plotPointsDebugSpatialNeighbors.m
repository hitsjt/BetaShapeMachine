function plotPointsDebugSpatialNeighbors(V, m, Vc, Vn, Vnw)
% V is the array with all vertices of models
% m is the model id
% Vc is the center vertex to visualize
% Vn is the center neighbors to visualize
% Vnw is their weights (color)
Vc = Vc + 1;
Vn = Vn + 1;

Vm = V(m, :);
Vm = reshape(Vm, 3, size(Vm, 2)/3);
plotPoints(Vm);
hold on;

plot3( Vm(1, Vc), Vm(2, Vc), Vm(3, Vc), 'g.', 'MarkerSize', 20)

for i=1:length(Vn)
    plot3( Vm(1, Vn(i)), Vm(2, Vn(i)), Vm(3, Vn(i)), '.', 'MarkerSize', 25, 'MarkerEdgeColor', 1 - [ Vnw(i) Vnw(i) Vnw(i) ])    
end
% black: high weight
% white: low weight

hold off;


%  X = load('C:\Users\V\Desktop\AttribGenModel\Code_C++\Build\Test\tmp.txt');
% Vn = X( 1:size(X,1)/2 );
% Vnw = X( size(X,1)/2+1:end );
% plotPointsDebugSpatialNeighbors(V, 1, 0, Vn, Vnw)