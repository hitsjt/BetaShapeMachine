function mesh = surfacePriorSmoothing(mesh, iterations, lambda)

mesh = taubinSmoothing(mesh, 2, 0.9, -1.0);
mesh.V = double(mesh.V);
W = eye(3) * lambda;
mesh.originalV = mesh.V;
mesh = normals(mesh);
mesh = faceAdjacencyMatrix(mesh);
mesh.adjF = [];
for k=1:size(mesh.F, 2)
    adjF = find( mesh.FaceAdj(k, :) );
    for j = adjF
        mesh.adjF = [mesh.adjF; [k j]];
    end
end

options = optimset('FinDiffType', 'central', 'DerivativeCheck', 'off', 'GradObj','on', 'LargeScale','off', 'MaxIter', iterations,'TolFun', 1e-12, 'TolX', 1e-12, 'Display', 'iter-detailed');
V = fminunc(@(V) costFunction(V, mesh, W), mesh.V(:), options);
mesh.V = reshape(V, 3, size(mesh.V, 2));


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%






function [E, G] = costFunction(V, mesh, W)
mesh.V = reshape(V, 3, size(mesh.V, 2));

clf;
plotMesh(mesh,'solidbw');
drawnow;


E = 0;

mesh.Nf = zeros(3, size(mesh.F,2));
mesh.Nf = cross(mesh.V(1:3,mesh.F(2,:)) - mesh.V(1:3,mesh.F(1,:)), mesh.V(1:3,mesh.F(3,:)) - mesh.V(1:3,mesh.F(1,:)));
mesh.Fa = sqrt( sum( mesh.Nf.^2, 1) );
for i = 1:size(mesh.F,2)
    mesh.Nf(:, i) = mesh.Nf(:, i) ./ sqrt( sum( mesh.Nf(:, i).^2 ) );
end

for i = 1:size(mesh.V, 2)
    E = E + ( mesh.originalV(:, i) - mesh.V(:, i)  )' * W * ( mesh.originalV(:, i) - mesh.V(:, i) );
end

for a=1:size(mesh.adjF, 1)
    k = mesh.adjF(a, 1);
    j = mesh.adjF(a, 2);
     E = E + sqrt( sum( ( mesh.Nf(:, k ) -  mesh.Nf(:, j ) ).^2 ) );    
%     E = E + ( sum( ( mesh.Nf(:, k ) -  mesh.Nf(:, j ) ).^2 ) ); % quadratic potential
end

G = zeros( size(mesh.V, 2)*3, 1 );

for i = 1:size(mesh.V, 2)
    G( (i-1)*3+1:(i-1)*3+3 ) = -2 * W * ( mesh.originalV(:, i) - mesh.V(:, i) );
end

for a=1:size(mesh.adjF, 1)
    k = mesh.adjF(a, 1);
    j = mesh.adjF(a, 2);
    
    dfdn = ( mesh.Nf(:, k ) -  mesh.Nf(:, j ) ) / sqrt( sum( ( mesh.Nf(:, k ) -  mesh.Nf(:, j ) ).^2 ) );
    %dfdn = 2 * ( mesh.Nf(:, k ) -  mesh.Nf(:, j ) ); % quadratic potential  
    
    % find all vertices that these faces contain
    vks = unique( [ mesh.F(:, k); mesh.F(:, j) ] );
    
    for vk = vks'
        rk = find( mesh.F(:, k) == vk );
        if isempty(rk)
            dnidk = zeros(3, 3);
        else
            vkp = mesh.F( mod(rk, 3)+1, k);
            vkpp = mesh.F( mod(rk+1, 3)+1, k);
            dnidk1 = ( eye(3) - mesh.Nf(:, k ) * mesh.Nf(:, k )' ) /  mesh.Fa(k) ;
            eee = mesh.V(:, vkp) - mesh.V(:, vkpp);
            dnidk2 = [ fcross( [1 0 0]', eee ) fcross( [0 1 0]', eee ) fcross( [0 0 1]', eee) ];            
            dnidk = dnidk1 * dnidk2;
        end
        
        rj = find( mesh.F(:, j) == vk );
        if isempty(rj)
            dnjdk = zeros(3, 3);
        else
            vkp = mesh.F( mod(rj, 3)+1, j);
            vkpp = mesh.F( mod(rj+1, 3)+1, j);
            dnjdk1 = ( eye(3) - mesh.Nf(:, j ) * mesh.Nf(:, j )' ) / mesh.Fa(j);
            eee = mesh.V(:, vkp) - mesh.V(:, vkpp);
            dnjdk2 = [ fcross( [1 0 0]', eee ) fcross( [0 1 0]', eee ) fcross( [0 0 1]', eee) ];  
            dnjdk = dnjdk1 * dnjdk2;
        end
        
        G( (vk-1)*3+1:(vk-1)*3+3 ) = G( (vk-1)*3+1:(vk-1)*3+3 ) + ( dnidk - dnjdk )' * dfdn;

    end
    
end


