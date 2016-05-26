function [tf, mesh] = hasHoles(mesh)

mesh = getEdgeFaceMatrix(mesh);
BoundaryEdges = xor(mesh.EFM1 == 0, mesh.EFM2 == 0);
tf = any(BoundaryEdges(:));
