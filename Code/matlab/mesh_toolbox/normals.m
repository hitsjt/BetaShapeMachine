function mesh = normals(mesh)
% complete this function to compute normals per vertex
% the face normals and face areas are computed already

% input: mesh structure from 'loadObj' or 'createTestSurface' functions
% output: mesh structures with 3 new fields: mesh.Nf, Mesh.Fa, mesh.Nv

% you should put normals per vertex in mesh.Nv according 
% to the Max's weighting scheme discussed in the class:
% MAX, N. 1999. Weights for Computing Vertex Normals from
% Facet Normals. Journal of Graphics Tools, Vol. 4, No. 2.
% *** mesh.Nv should be a 3xV matrix (V is the number of vertices) ***

%addpath('mesh_toolbox\');

% understand what the following lines of code do
mesh.Nf = zeros(3, size(mesh.F,2));
mesh.Nf = cross(mesh.V(1:3,mesh.F(2,:)) - mesh.V(1:3,mesh.F(1,:)), mesh.V(1:3,mesh.F(3,:)) - mesh.V(1:3,mesh.F(1,:)));
mesh.Fa = 0.5 * sqrt( sum( mesh.Nf.^2, 1) );
for i = 1:size(mesh.F,2)
    mesh.Nf(:, i) = mesh.Nf(:, i) ./ sqrt( sum( mesh.Nf(:, i).^2 ) );
end

mesh.Nv = zeros(3, size(mesh.V, 2));

%%%%%%%%%%%%%%%%
% fill code below
%%%%%%%%%%%%%%%%
for i = 1:size(mesh.F,2)
    for j = 1:3
        if j == 1
            la = sum((mesh.V( 1:3, mesh.F(1, i) ) - mesh.V( 1:3, mesh.F(2, i) )).^2);
            lb = sum((mesh.V( 1:3, mesh.F(1, i) ) - mesh.V( 1:3, mesh.F(3, i) )).^2);
            W = mesh.Fa(i) / (la * lb);
            if (isinf(W) || isnan(W)) W = 0; end
        elseif j == 2
            la = sum((mesh.V( 1:3, mesh.F(2, i) ) - mesh.V( 1:3, mesh.F(1, i) )).^2);
            lb = sum((mesh.V( 1:3, mesh.F(2, i) ) - mesh.V( 1:3, mesh.F(3, i) )).^2);
            W = mesh.Fa(i) / (la * lb);
            if (isinf(W) || isnan(W)) W = 0; end
        else
            la = sum((mesh.V( 1:3, mesh.F(3, i) ) - mesh.V( 1:3, mesh.F(1, i) )).^2);
            lb = sum((mesh.V( 1:3, mesh.F(3, i) ) - mesh.V( 1:3, mesh.F(2, i) )).^2);
            W = mesh.Fa(i) / (la * lb);
            if (isinf(W) || isnan(W)) W = 0; end
        end
        mesh.Nv(1:3, mesh.F(j, i) ) = mesh.Nv(1:3, mesh.F(j, i)) + mesh.Nf(1:3, i) * W;
    end
end
%%%%%%%%%%%%%%


% normalize the normal vectors so that they are unit length
for i = 1:size(mesh.V,2)
    mesh.Nv(:, i) = mesh.Nv(:, i) ./ sqrt( sum( mesh.Nv(:, i).^2 ) );
end