function [mesh, dup, prob] = getEdgeFaceMatrix(mesh, maxvert)

if nargin < 2
    maxvert = size(mesh.V,2);
end

if isfield(mesh,'EFM1')
    mesh = rmfield(mesh,'EFM1');
end

if isfield(mesh,'EFM2')
    mesh = rmfield(mesh,'EFM2');
end

mesh.EFM1 = sparse(maxvert,maxvert);
mesh.EFM2 = sparse(maxvert,maxvert);

dup = false(size(mesh.F,2),1);
prob = [];

for i = 1:size(mesh.F,2)
    [mesh, dup, prob] = registerFaceEFM(mesh, i, dup, prob);
end
