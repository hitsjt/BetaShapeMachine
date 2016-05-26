function vol = boundingBoxVolume(mesh)

vol = prod(max(mesh.V(1:3,:),[],2) - min(mesh.V(1:3,:),[],2));