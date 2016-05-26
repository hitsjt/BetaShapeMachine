function mesh = laplacianSmoothing(mesh, iterations, lambda, verbose)
if nargin == 3
    verbose = true;
end

if ~isfield(mesh,'Adj')
    mesh = adjacencyMatrix(mesh);
end

newV = mesh.V; 

for iter = 1:iterations
    if verbose
        disp(sprintf('Iteration %d',iter'));
        clf;
        plotMesh(mesh,'solidbw');
        drawnow;
    end
%     pause
    
    for i=1:size(mesh.V, 2)
        meanV =  mean( mesh.V( :, mesh.Adj(i,:) ), 2 );
        dir = meanV - mesh.V(:, i);
        newV(:, i) = mesh.V(:, i) + lambda * dir;        
    end
    
    mesh.V = newV;          
end

mesh = normals(mesh);

