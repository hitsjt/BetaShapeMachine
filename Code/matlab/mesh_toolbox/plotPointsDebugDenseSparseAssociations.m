function plotPointsDebugDenseSparseAssociations(Q, V, m, Vc, Vn)
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

Qm = Q(m, :);
Qm = reshape(Qm, 3, size(Qm, 2)/3);
plot3( Qm(1, Vc), Qm(2, Vc), Qm(3, Vc), 'g.', 'MarkerSize', 30)

for i=1:length(Vn)
    plot3( Vm(1, Vn(i)), Vm(2, Vn(i)), Vm(3, Vn(i)), 'b.', 'MarkerSize', 25)    
end
% black: high weight
% white: low weight

hold off;


%  plotPointsDebugDenseSparseAssociations(Q, V, 1, 117799, Vn(1:100))