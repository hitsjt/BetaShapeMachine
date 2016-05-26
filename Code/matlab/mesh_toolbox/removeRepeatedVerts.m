function [mesh Del] = removeRepeatedVerts(mesh, tol)

if nargin < 2
    tol = 2*sqrt(realmin('single'));
end

tol2 = tol*tol;

% disp('Finding duplicate vertices...');


if size(mesh.V, 2) > 25000
    Del = zeros(2,1);
    last = 0;

    i = 1;
    n = size(mesh.V,2);
    V = mesh.V;

    for i=1:n
        VVI = V(:, i);
        for j=i+1:n
            VVJ = V(:, j);
            if (VVI(1) - VVJ(1))^2 + (VVI(2) - VVJ(2))^2 + (VVI(3) - VVJ(3))^2  < tol
                last = last + 1;
                Del(:,last) = [i;j];
            end
        end
    end
%    disp(sprintf('%d duplicate vertices found', last));

    if last > 0
%        disp('Removing...')
        for i = 1:last
            mesh.F(mesh.F == Del(2,i)) = Del(1,i);
        end

%        disp('Correcting face indices...');
        VertIndices = unique(mesh.F(:));
        mesh.V = mesh.V(:,VertIndices);
        [tf, mesh.F] = ismember(mesh.F,VertIndices);
    end
else
    D = sqdist(mesh.V,mesh.V);
    Del = zeros(2,1);
    last = 0;

    i = 1;
    n = size(mesh.V,2);

    for i=1:n
        for j=i+1:n
            if D(i,j) < tol2
                last = last + 1;
                Del(:,last) = [i;j];
            end
        end
    end
%    disp(sprintf('%d duplicate vertices found', last));

    if last > 0
%        disp('Removing...')
        for i = 1:last
            mesh.F(mesh.F == Del(2,i)) = Del(1,i);
        end

%        disp('Correcting face indices...');
        VertIndices = unique(mesh.F(:));
        mesh.V = mesh.V(:,VertIndices);
        [tf, mesh.F] = ismember(mesh.F,VertIndices);
    end
end

disp('Done');


