function mel = minEdgeLength(mesh)

D12 = sqrt(sum((mesh.V(:,mesh.F(1,:)) - mesh.V(:,mesh.F(2,:))).^2));
D23 = sqrt(sum((mesh.V(:,mesh.F(2,:)) - mesh.V(:,mesh.F(3,:))).^2));
D13 = sqrt(sum((mesh.V(:,mesh.F(1,:)) - mesh.V(:,mesh.F(3,:))).^2));

mel = min([D12, D23, D13]);
