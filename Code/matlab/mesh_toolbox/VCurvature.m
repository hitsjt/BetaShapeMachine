function mesh = VCurvature(mesh)
% one-ring curvature operator based on the siggraph paper
% RESULTS STORED IN MESH.BK1, mesh.BK2, mesh.BMK and mesh.BGK

mesh = normals(mesh);

if ~isfield(mesh, 'Fa')
    disp('Computing face areas...');
    mesh = faceAreas(mesh);
end

if ~isfield(mesh, 'Adj')
    disp('Computing vertex adjacency...');
    mesh = adjacencyMatrix(mesh);
end


% disp('Computing curvatures with XFCO (eXtreme Fucking Curvature Operator) - F22 Version...');
% disp('May the Force be with You!!! Die with Honour!!!...');

for i = 1:size(mesh.V, 2)    
    Q = localCoordinateSystem(mesh, i);
    [tmp, adjF] = find( mesh.F == i );
    A = zeros(5, 5);
    B = zeros(5, 1);
    
    for j = 1:length(adjF)
        if mesh.F(3, adjF(j)) == i
            E0 = mesh.V(1:3, mesh.F(3, adjF(j)) ) - mesh.V(1:3, mesh.F(2, adjF(j)) );
            E1 = mesh.V(1:3, mesh.F(1, adjF(j)) ) - mesh.V(1:3, mesh.F(3, adjF(j)) );
            E2 = mesh.V(1:3, mesh.F(2, adjF(j)) ) - mesh.V(1:3, mesh.F(1, adjF(j)) );
            DN0 = mesh.Nv(1:3, mesh.F(3, adjF(j)) ) - mesh.Nv(1:3, mesh.F(2, adjF(j)) );
            DN1 = mesh.Nv(1:3, mesh.F(1, adjF(j)) ) - mesh.Nv(1:3, mesh.F(3, adjF(j)) );
            DN2 = mesh.Nv(1:3, mesh.F(2, adjF(j)) ) - mesh.Nv(1:3, mesh.F(1, adjF(j)) );
        elseif mesh.F(2, adjF(j)) == i
            E0 = mesh.V(1:3, mesh.F(3, adjF(j)) ) - mesh.V(1:3, mesh.F(2, adjF(j)) );
            E2 = mesh.V(1:3, mesh.F(1, adjF(j)) ) - mesh.V(1:3, mesh.F(3, adjF(j)) );
            E1 = mesh.V(1:3, mesh.F(2, adjF(j)) ) - mesh.V(1:3, mesh.F(1, adjF(j)) );
            DN0 = mesh.Nv(1:3, mesh.F(3, adjF(j)) ) - mesh.Nv(1:3, mesh.F(2, adjF(j)) );
            DN2 = mesh.Nv(1:3, mesh.F(1, adjF(j)) ) - mesh.Nv(1:3, mesh.F(3, adjF(j)) );
            DN1 = mesh.Nv(1:3, mesh.F(2, adjF(j)) ) - mesh.Nv(1:3, mesh.F(1, adjF(j)) );
        else
            E2 = mesh.V(1:3, mesh.F(3, adjF(j)) ) - mesh.V(1:3, mesh.F(2, adjF(j)) );
            E1 = mesh.V(1:3, mesh.F(1, adjF(j)) ) - mesh.V(1:3, mesh.F(3, adjF(j)) );
            E0 = mesh.V(1:3, mesh.F(2, adjF(j)) ) - mesh.V(1:3, mesh.F(1, adjF(j)) );
            DN2 = mesh.Nv(1:3, mesh.F(3, adjF(j)) ) - mesh.Nv(1:3, mesh.F(2, adjF(j)) );
            DN1 = mesh.Nv(1:3, mesh.F(1, adjF(j)) ) - mesh.Nv(1:3, mesh.F(3, adjF(j)) );
            DN0 = mesh.Nv(1:3, mesh.F(2, adjF(j)) ) - mesh.Nv(1:3, mesh.F(1, adjF(j)) );            
        end
        
        if norm(E0) < 1e-10 || norm(E1) < 1e-10 || norm(E2) < 1e-10
            continue;
        end

        R = .5 * voronoiArea(mesh, i, adjF(j) ) / (norm(E0) * norm(E0));
        U = sum(E0 .* Q(:, 1));
        V = sum(E0 .* Q(:, 2));
        W = 0;

        K = sum(DN0 .* Q(:, 1));
        L = sum(DN0 .* Q(:, 2));
        M = sum(DN0 .* Q(:, 3));
                
        A(1, 1) = A(1, 1) + U * U * R;
        A(1, 2) = A(1, 2) + U * V * R;
        A(1, 3) = A(1, 3) + U * W * R;
        B(1, 1) = B(1, 1) + K * U * R;
        A(2, 1) = A(2, 1) + U * V * R;
        A(2, 2) = A(2, 2) + U * U * R + V * V * R;
        A(2, 3) = A(2, 3) + V * W * R;
        A(2, 4) = A(2, 4) + U * V * R;
        A(2, 5) = A(2, 5) + U * W * R;
        B(2, 1) = B(2, 1) + K * V * R + L * U * R;
        A(3, 1) = A(3, 1) + U * W * R;
        A(3, 2) = A(3, 2) + V * W * R;
        A(3, 3) = A(3, 3) + W * W * R;
        B(3, 1) = B(3, 1) + K * W * R;        
        A(4, 2) = A(4, 2) + U * V * R;
        A(4, 4) = A(4, 4) + V * V * R;
        A(4, 5) = A(4, 5) + W * V * R;
        B(4, 1) = B(4, 1) + L * V * R;
        A(5, 2) = A(5, 2) + U * W * R;
        A(5, 4) = A(5, 4) + V * W * R;
        A(5, 5) = A(5, 5) + W * W * R;
        B(5, 1) = B(5, 1) + L * W * R;

        
        R = .5 * voronoiArea(mesh, i, adjF(j) ) / (norm(E1) * norm(E1));
        
        U = sum(E1 .* Q(:, 1));
        V = sum(E1 .* Q(:, 2));
        W = 0;

        K = sum(DN1 .* Q(:, 1));
        L = sum(DN1 .* Q(:, 2));
        M = sum(DN1 .* Q(:, 3));
        
        A(1, 1) = A(1, 1) + U * U * R;
        A(1, 2) = A(1, 2) + U * V * R;
        A(1, 3) = A(1, 3) + U * W * R;
        B(1, 1) = B(1, 1) + K * U * R;
        A(2, 1) = A(2, 1) + U * V * R;
        A(2, 2) = A(2, 2) + U * U * R + V * V * R;
        A(2, 3) = A(2, 3) + V * W * R;
        A(2, 4) = A(2, 4) + U * V * R;
        A(2, 5) = A(2, 5) + U * W * R;
        B(2, 1) = B(2, 1) + K * V * R + L * U * R;
        A(3, 1) = A(3, 1) + U * W * R;
        A(3, 2) = A(3, 2) + V * W * R;
        A(3, 3) = A(3, 3) + W * W * R;
        B(3, 1) = B(3, 1) + K * W * R;        
        A(4, 2) = A(4, 2) + U * V * R;
        A(4, 4) = A(4, 4) + V * V * R;
        A(4, 5) = A(4, 5) + W * V * R;
        B(4, 1) = B(4, 1) + L * V * R;
        A(5, 2) = A(5, 2) + U * W * R;
        A(5, 4) = A(5, 4) + V * W * R;
        A(5, 5) = A(5, 5) + W * W * R;
        B(5, 1) = B(5, 1) + L * W * R;
        
        
%        R = voronoiArea(mesh, i, adjF(j) ) / ( .5 * ( norm(E1) * norm(E1) + norm(E0) * norm(E0) ) );
        R = voronoiArea(mesh, i, adjF(j) ) / (norm(E2) * norm(E2));
        U = sum(E2 .* Q(:, 1));
        V = sum(E2 .* Q(:, 2));
        W = 0;

        K = sum(DN2 .* Q(:, 1));
        L = sum(DN2 .* Q(:, 2));
        M = sum(DN2 .* Q(:, 3)); 
        
        A(1, 1) = A(1, 1) + U * U * R;
        A(1, 2) = A(1, 2) + U * V * R;
        A(1, 3) = A(1, 3) + U * W * R;
        B(1, 1) = B(1, 1) + K * U * R;
        A(2, 1) = A(2, 1) + U * V * R;
        A(2, 2) = A(2, 2) + U * U * R + V * V * R;
        A(2, 3) = A(2, 3) + V * W * R;
        A(2, 4) = A(2, 4) + U * V * R;
        A(2, 5) = A(2, 5) + U * W * R;
        B(2, 1) = B(2, 1) + K * V * R + L * U * R;
        A(3, 1) = A(3, 1) + U * W * R;
        A(3, 2) = A(3, 2) + V * W * R;
        A(3, 3) = A(3, 3) + W * W * R;
        B(3, 1) = B(3, 1) + K * W * R;        
        A(4, 2) = A(4, 2) + U * V * R;
        A(4, 4) = A(4, 4) + V * V * R;
        A(4, 5) = A(4, 5) + W * V * R;
        B(4, 1) = B(4, 1) + L * V * R;
        A(5, 2) = A(5, 2) + U * W * R;
        A(5, 4) = A(5, 4) + V * W * R;
        A(5, 5) = A(5, 5) + W * W * R;
        B(5, 1) = B(5, 1) + L * W * R;
%         A(6, 6) = A(6, 6) + U * U * R;
%         A(6, 7) = A(6, 7) + U * V * R;
%         A(6, 8) = A(6, 8) + U * W * R;
%         B(6, 1) = B(6, 1) + U * M * R;
%         A(7, 6) = A(7, 6) + U * V * R;
%         A(7, 7) = A(7, 7) + V * V * R;
%         A(7, 8) = A(7, 8) + V * W * R;
%         B(7, 1) = B(7, 1) + V * M * R;
%         A(8, 6) = A(8, 6) + U * W * R;
%         A(8, 7) = A(8, 7) + V * W * R;
%         A(8, 8) = A(8, 8) + W * W * R;
%         B(8, 1) = B(8, 1) + W * M * R;        
    end
    
    if any(any(isinf(A))) || any(any(isnan(A))) || any(any(isinf(B))) || any(any(isnan(B)))
        continue
    end        
    Y = pinv(A) * B;
    X = [Y(1) Y(2); Y(2) Y(4)];
    [R K] = eig(X);
    K1 = K(1, 1);
    K2 = K(2, 2);    
    R(3, 1:2) = [0 0];
    K1V = Q * R(:, 1);    
    K2V = Q * R(:, 2);    
    
    if K1 > K2
        mesh.BK1(i) = K1;
        mesh.BK2(i) = K2;
        mesh.BK1V(:, i) = K2V;
        mesh.BK2V(:, i) = K1V;        
    else
        mesh.BK1(i) = K2;
        mesh.BK2(i) = K1;
        mesh.BK1V(:, i) = K1V;
        mesh.BK2V(:, i) = K2V;                
    end
end

mesh.BMK = .5 * (mesh.BK1 + mesh.BK2);
mesh.BGK = mesh.BK1 .* mesh.BK2;


%''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

function Q = localCoordinateSystem(mesh, i)
adjV = find( mesh.Adj(:, i) );
if length(adjV) == 0
    Q = eye(3);
    return;
end
e0 = mesh.V(1:3, adjV(1)) - mesh.V(1:3, i);
n = mesh.Nv(1:3, i);
t = cross( e0, n);
t = t / norm(t);
s = cross( t, n);
s = s / norm(s);
Q = [t s mesh.Nv(1:3, i)];

%''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

function A = voronoiArea(mesh, i, f)
v0ind = find( mesh.F(:, f) == i);
v0 = mesh.V(1:3, mesh.F( v0ind, f ));

if v0ind == 1
    v1 = mesh.V(1:3, mesh.F( 2, f ));
    v2 = mesh.V(1:3, mesh.F( 3, f ));
elseif v0ind == 2
    v1 = mesh.V(1:3, mesh.F( 1, f ));
    v2 = mesh.V(1:3, mesh.F( 3, f ));
else
    v1 = mesh.V(1:3, mesh.F( 1, f ));
    v2 = mesh.V(1:3, mesh.F( 2, f ));
end

PR_sq = sum( (v0 - v2) .* (v0 - v2) );
PQ_sq = sum( (v0 - v1) .* (v0 - v1) );
RQ_sq = sum( (v1 - v2) .* (v1 - v2) );

cos_Q = (PR_sq - PQ_sq - RQ_sq) / ( -2 * sqrt(PQ_sq) * sqrt(RQ_sq) );
cot_Q = cos_Q/sqrt(1 - cos_Q^2);

cos_R = (PQ_sq - PR_sq - RQ_sq) / ( -2 * sqrt(PR_sq) * sqrt(RQ_sq) );
cot_R = cos_R/sqrt(1 - cos_R^2);

Q = acos(cos_Q);
R = acos(cos_R);
X = pi - Q - R;
if Q > pi / 2 || R > pi / 2 || X > pi / 2
    if X > pi / 2
        A = mesh.Fa(f) / 2;
    else
        A = mesh.Fa(f) / 4;
    end
else
    A = (1/8) * ( PR_sq * cot_Q + PQ_sq * cot_R );
end
