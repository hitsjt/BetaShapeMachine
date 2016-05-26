function plotPointsDebugEdgeWeights(V, edge_filename, edge_type_id, coordinate_id)
% plotPointsDebugEdgeWeights(V, 'C:\Users\V\Desktop\AttribGenModel\Code_C++\Build\Test\tmp_edges_0.txt', 1, 1);
% plotPointsDebugEdgeWeights(mesh, 'C:\Users\V\Desktop\AttribGenModel\Code_C++\Build\Test\tmp_edges_0.txt', 1, 1);

if ( ~isstruct(V) )
    m = 1;
    Vm = V(m, :);
    Vm = reshape(Vm, 3, size(Vm, 2)/3);
    size(Vm)
else
    mesh = V;
    size(mesh.V)
end

E = load(edge_filename);
E = E(:, edge_type_id);
E = E( coordinate_id:3:end);

E = E - min(E);
E = E / max(E);

size(E)
min(E)
max(E)

if ( ~isstruct(V) )
    scatter3(Vm(1,:), Vm(2,:), Vm(3,:), 10 , E );
else
    mesh.C = E;
    plotMesh(mesh, 'solid');
end
