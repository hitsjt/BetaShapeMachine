function mesh = TaubinCurvature(mesh)

if ~isfield(mesh, 'EFM1') || ~isfield(mesh, 'EFM2')
    disp('Computing Edge-Face Matrix...')
    mesh = getEdgeFaceMatrix(mesh);
end

if ~isfield(mesh, 'Nv')
    disp('Computing vertex normals...');
    mesh = vertexNormals(mesh);
end

if ~isfield(mesh, 'Adj')
    disp('Computing vertex adjacency...');
    mesh = adjacencyMatrix(mesh);
end

if ~isfield(mesh, 'Fa') 
    disp('Computing face areas...');
    mesh = faceAreas(mesh);
end

for i = 1:size(mesh.V,2)
    adjv = find( mesh.Adj(:, i) );
    Ni = mesh.Nv(1:3, i);
    Vi = mesh.V(1:3, i);
    T = [];
    K = [];
    W = [];
    Mi = zeros(3, 3);
    
    for j=1:length(adjv)
        TR = find( (mesh.F(1, :) == i | mesh.F(2, :) == i | mesh.F(3, :) == i) & (mesh.F(1, :) == adjv(j) | mesh.F(2, :) == adjv(j) | mesh.F(3, :) == adjv(j)) );
        W(j) = sum( mesh.Fa(TR) );
        Vj = mesh.V(1:3, adjv(j) );
        E = Vi - Vj;
        T(:, j) = (eye(3) - Ni * Ni') * E;
        T(:, j) = T(:, j) / norm( T(:, j) );
        K(j) = (2 * Ni' * (-E)) / (norm(-E)^2);
    end
    W = W / sum(W);
    for j=1:length(adjv)
        Mi = Mi + W(j) * K(j) * T(:, j) * T(:, j)';
    end

%     E1 = [1 0 0]';
%     if norm(E1 - Ni) > norm(E1 + Ni)    
%         Wi = (E1 - Ni) / norm(E1 - Ni);
%     else
%         Wi = (E1 + Ni) / norm(E1 + Ni);
%     end    
%     Qi = eye(3) - 2 * Wi * Wi';
%     MT = Qi' * Mi * Qi;
%     MT = MT(2:3, 2:3);
%     R = eig(Mi)
    R = eig(Mi);
    [N KI1] = max( abs( R ) );
    K1 = R(KI1);
    R(KI1) = [];
    [N KI2] = max( abs( R ) );
    K2 = R(KI2);    
%     mesh.TK1(i) = 3*K1 - K2;  % for some reason, this fails
%     mesh.TK2(i) = 3*K2 - K1;    
    mesh.TMK(i) = .5*(mesh.TK1(i) + mesh.TK2(i));
end