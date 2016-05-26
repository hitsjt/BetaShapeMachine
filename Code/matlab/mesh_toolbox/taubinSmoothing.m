function mesh = taubinSmoothing(mesh, iterations, lambda, mu)

if ~isfield(mesh,'Adj')
    mesh = adjacencyMatrix(mesh);
end

newV = mesh.V; 

for iter = 1:iterations
    disp(sprintf('Iteration %d',iter'));
    clf;
    plotMesh(mesh,'solidbw');
    drawnow;
    pause
    
    for i=1:size(mesh.V, 2)
        adjV = find( mesh.Adj(i,:) );
        meanV =  mean( mesh.V( :, adjV ), 2 );
        dir = meanV - mesh.V(:, i);
        newV(:, i) = mesh.V(:, i) + lambda * dir;        
    end
    
    mesh.V = newV;          

    for i=1:size(mesh.V, 2)
        adjV = find( mesh.Adj(i,:) );
        meanV =  mean( mesh.V( :, adjV ), 2 );
        dir = meanV - mesh.V(:, i);
        newV(:, i) = mesh.V(:, i) + mu * dir;        
    end
 
    mesh.V = newV;  
    
end

