function mesh = reduceMesh(mesh, r)

[nf, nv] = reducepatch(mesh.F',mesh.V(1:3,:)',r);
mesh.F = nf';
mesh.V = [nv'; ones(1, size(nv, 1))];

% disp('Recomputing face centres...');
% mesh = faceCenters(mesh);
% 
% disp('Recomputing face and vertex normals...');
% mesh = normals(mesh);
% 
% disp('Recomputing face and vertex adjacencies...');
% mesh = adjacencyMatrix(mesh);
% mesh = faceAdjacencyMatrix(mesh);
