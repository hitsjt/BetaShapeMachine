function d = boundingBoxDiagonal(mesh)

d = norm(max(mesh.V(1:3,:),[],2) - min(mesh.V(1:3,:),[],2));