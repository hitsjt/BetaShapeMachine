function mesh = faceAdjacencyMatrix(mesh)

% if isfield(mesh, 'FaceAdj')
%     rmfield(mesh, 'FaceAdj');
% end
% mesh.FaceAdj = logical(sparse(size(mesh.F,2),size(mesh.F,2)));
% 
% if ~isfield(mesh, 'EFM1') || ~isfield(mesh, 'EFM2')
%     mesh = getEdgeFaceMatrix(mesh);
% end
% 
% Edges = find((mesh.EFM1(:) ~= 0) & (mesh.EFM2(:) ~= 0));
% 
% for i = 1:length(Edges)
%     e = Edges(i);
%     mesh.FaceAdj(mesh.EFM1(e), mesh.EFM2(e)) = true;
%     mesh.FaceAdj(mesh.EFM2(e), mesh.EFM1(e)) = true;
% end

F = mesh.F;
vertexToFace = cell( size(mesh.V, 2), 1 );
for i = 1:size(mesh.V, 2)
    if (mod(i, 1000) == 0)
        i
    end
    [tmp f] = find(F == i);
    vertexToFace{i} = [vertexToFace{i} f];
end

for i = 1:size(F, 2)
    if (mod(i, 1000) == 0)
        i
    end
    V = F(1:3, i);
    F2 = vertexToFace{V(1)};
    for j=1:length(F2)
        V1 = F(1:3, i);
        V2 = F(1:3, F2(j));
        k = ( V1(1) == V2(1) || V1(1) == V2(2) || V1(1) == V2(3) ) + ( V1(2) == V2(1) || V1(2) == V2(2) || V1(2) == V2(3) ) + ( V1(3) == V2(1) || V1(3) == V2(2) || V1(3) == V2(3) );
        mesh.FaceAdj(i, F2(j)) = (k>=2);
    end
    F2 = vertexToFace{V(2)};
    for j=1:length(F2)
        V1 = F(1:3, i);
        V2 = F(1:3, F2(j));
        k = ( V1(1) == V2(1) || V1(1) == V2(2) || V1(1) == V2(3) ) + ( V1(2) == V2(1) || V1(2) == V2(2) || V1(2) == V2(3) ) + ( V1(3) == V2(1) || V1(3) == V2(2) || V1(3) == V2(3) );
        mesh.FaceAdj(i, F2(j)) = (k>=2);
    end
    F2 = vertexToFace{V(3)};
    for j=1:length(F2)
        V1 = F(1:3, i);
        V2 = F(1:3, F2(j));
        k = ( V1(1) == V2(1) || V1(1) == V2(2) || V1(1) == V2(3) ) + ( V1(2) == V2(1) || V1(2) == V2(2) || V1(2) == V2(3) ) + ( V1(3) == V2(1) || V1(3) == V2(2) || V1(3) == V2(3) );
        mesh.FaceAdj(i, F2(j)) = (k>=2);
    end
    mesh.FaceAdj(i, i) = 0;
end