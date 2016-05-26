function mesh = patchFittingCurvature(mesh, method)
% complete this function to compute principal curvatures,
% mean curvature, and Gaussian curvature for the input mesh

% input: mesh structure from 'loadObj' or 'createTestSurface' functions
% output: values in fields mesh.GK1, mesh.GK2, mesh.GMK, mesh.GGK
% mesh.GK1 should be maximum principal curvature value per vertex
% mesh.GK2 should be minimum principal curvature value per vertex
% mesh.GMK should be mean curvature value per vertex
% mesh.GGK should be Gaussian curvature value per vertex
% *** each of these fields should be 1xV matrices (V is the number of vertices) ***

addpath('mesh_toolbox\');

if nargin ~= 2
    error('you have to provide a mesh, and a method: e.g. ''quad'' or ''cubic''');
end

mesh = adjacencyMatrix(mesh); % returns the adjacency matrix of the graph representing the mesh
mesh = normals(mesh); % compute normals per vertex and per face
mesh.E1 = zeros( 3, size(mesh.V, 2) );
mesh.E2 = mesh.E1;

for i = 1:size(mesh.V, 2)
    % adjV contains ids of vertices in the 2-ring neighborhood of each vertex
    % to access the position of the adjacent vertex j: mesh.V(1:3, adjV(j))
    adjV = getNRingNeighborVertices(mesh, i, 2);
    
    % you should complete the function localCoordinateSystem (see below)
    % construct an orthnormal basis for vertex i
    % the orthonormal basis should be formed by its normal vector
    % and two orthogonal vectors on the tangent plane
    Q = localCoordinateSystem(mesh, i);
    
    if strcmp( method, 'quad')
        %%%%%%%%%%%%%%%%
        % fill code here
        %%%%%%%%%%%%%%%%
        A = [];
        B = [];
        for j = 1:size(adjV, 1)
            if size(adjV, 1) < 3
                break;
            end
            adjVLocalCoords(:, j) = Q' * (mesh.V(1:3, adjV(j)) - mesh.V(1:3, i) );
            x = adjVLocalCoords(1, j);
            y = adjVLocalCoords(2, j);
            z = adjVLocalCoords(3, j);
            norm = 1 / (x^2 + y^2 + 1e-30);
            A(j, 1) = 0.5 * x^2;
            A(j, 2) = x * y;
            A(j, 3) = 0.5 * y^2;
            A(j, :) = A(j, :) * norm;
            B(j, 1) = z * norm;
        end
    elseif strcmp( method, 'cubic')
        %%%%%%%%%%%%%%%%
        % fill code here
        %%%%%%%%%%%%%%%%
        A = [];
        B = [];
        for j = 1:size(adjV, 1)
            if size(adjV, 1) < 3
                break;
            end
            adjVLocalCoords(:, j) = Q' * (mesh.V(1:3, adjV(j)) - mesh.V(1:3, i) );
            adjVNormals(:, j) = Q' * mesh.Nv(1:3,  adjV(j));
            x = adjVLocalCoords(1, j);
            y = adjVLocalCoords(2, j);
            z = adjVLocalCoords(3, j);
            xn = adjVNormals(1, j);
            yn = adjVNormals(2, j);
            zn = adjVNormals(3, j);
            
            if isinf( xn / zn ) || isnan( xn / zn ) || ...
               isinf( yn / zn ) || isnan( yn / zn )
                continue;
            end
            
            norm = 1 / (x^2 + y^2 + 1e-30);
            A(3*j-2, 1) = 0.5 * x^2;
            A(3*j-2, 2) = x * y;
            A(3*j-2, 3) = 0.5 * y^2;
            A(3*j-2, 4) = x^3;
            A(3*j-2, 5) = x^2 * y;
            A(3*j-2, 6) = x * y^2;
            A(3*j-2, 7) = y^3;
            B(3*j-2, 1) = z;
            
            A(3*j-1, 1) = x;
            A(3*j-1, 2) = y;
            A(3*j-1, 3) = 0;
            A(3*j-1, 4) = 3 * x^2;
            A(3*j-1, 5) = 2 * x * y;
            A(3*j-1, 6) = y^2;
            A(3*j-1, 7) = 0;
            B(3*j-1, 1) = -xn / zn;
            
            A(3*j, 1) = 0;
            A(3*j, 2) = x;
            A(3*j, 3) = y;
            A(3*j, 4) = 0;
            A(3*j, 5) = x^2;
            A(3*j, 6) = 2 * x * y;
            A(3*j, 7) = 3 * y^2;
            B(3*j, 1) = -yn / zn;
            
            A(3*j-2, :) = A(3*j-2, :) * norm;
            A(3*j-1, :) = A(3*j-1, :) * norm;
            A(3*j, :)   = A(3*j, :) * norm;
            
            B(3*j-2, 1) = B(3*j-2, 1) * norm;
            B(3*j-1, 1) = B(3*j-1, 1) * norm;
            B(3*j, 1)   = B(3*j, 1) * norm;
        end
    end
    
    X = A\B;
    if isempty(X)
        X = zeros(3,1);
    end
    W = -[X(1) X(2); X(2) X(3)];
    if (sum(sum(isinf(W))) > 0) || (sum(sum(isnan(W))) > 0)
        K = [0; 0];
    else
        K = eig(W);
    end
    mesh.GK1(i) = K(2); % largest
    mesh.GK2(i) = K(1); % smallest
    
    % eigenvectors - bonus
    [E K] = eig(W);
    e1 = [E(:, 1); 0];
    e2 = [E(:, 2); 0];
    mesh.E1(:, i) = Q * e1;    
    mesh.E2(:, i) = Q * e2;
end

mesh.GMK = 0.5 * (mesh.GK1 + mesh.GK2);
mesh.GGK = mesh.GK1 .* mesh.GK2;


%%%%%%%%%%%%%%%%%
end

%--------------------------------------------------------------------------
function adjV = getNRingNeighborVertices(mesh, i, N)
adjV = find( mesh.Adj(:, i) );
for r = 1:N-1
    adjV2 = [];
    for j = 1:size(adjV,1)
        adjV2 = union(adjV2, find( mesh.Adj(:, adjV(j)) ));
    end
    adjV = unique ( union(adjV, adjV2) );
    adjV( find(adjV == i) ) = [];
end
end

%--------------------------------------------------------------------------
function Q = localCoordinateSystem(mesh, i)
% fill code here
% input: mesh, vertex id i
% output: orthonormal basis (local coordinate system)
% containing two orthogonal tangent directions and normal vector
% for vertex i
% Q should be 3x3 matrix - each column contains a basis vector

adjV = find( mesh.Adj(:, i) );
e0 = mesh.V(1:3, adjV(1)) - mesh.V(1:3, i);
n = mesh.Nv(1:3, i);
t = cross( e0, n);
t = t / norm(t);
s = cross( t, n);
s = s / norm(s);
Q = [s t n];
end