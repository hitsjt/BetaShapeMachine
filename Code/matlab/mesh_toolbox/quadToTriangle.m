function mesh = quadToTriangle(mesh);

F = mesh.F;
NEWF = zeros( 3, 2 * size(mesh.F, 2) );

for i=1:size(F, 2)
    NEWF(:, 2 * (i-1) + 1) = F([1 2 3], i);
    NEWF(:, 2 * (i-1) + 2) = F([1 3 4], i);
end

mesh.F = NEWF;