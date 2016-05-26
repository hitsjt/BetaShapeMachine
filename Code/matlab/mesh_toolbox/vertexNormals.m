function mesh = vertexNormals(mesh, method)

if nargin < 2
    method = 'area';
end

if strcmpi(method, 'uniform') 
    
    mesh.Nv = zeros(size(mesh.V));
    for i = 1:size(mesh.V,2)
        mesh.Nv(:,i) = normalize(sum(mesh.Nf(:,any(mesh.F==i)), 2));
    end
    
elseif strcmpi(method, 'area')
    
    % weighted by face area
    
    if ~isfield(mesh,'Nf')
        mesh = faceNormals(mesh);
    end
    if ~isfield(mesh,'Fa')
        mesh = faceAreas(mesh);
    end
    mesh.Nv = zeros(size(mesh.V));
    for i = 1:size(mesh.F,2)
        mesh.Nv(1:3,mesh.F(:,i)) = mesh.Nv(1:3,mesh.F(:,i)) + repmat(mesh.Nf(1:3,i)*mesh.Fa(:,i),1,3);
    end
    mesh.Nv = normalize(mesh.Nv);
    
elseif strcmpi(method, 'area2')
    % weighted by areas of faces divided by product of squared lengths of 
    % edges incident on vertex
    
    if ~isfield(mesh,'Nf')
        mesh = faceNormals(mesh);
    end
    if ~isfield(mesh,'Fa')
        mesh = faceAreas(mesh);
    end
    mesh.Nv = zeros(4, size(mesh.V, 2));
    for i = 1:size(mesh.F,2)
        for j = 1:3
            if j == 1
                la = sum((mesh.V( 1:3, mesh.F(1, i) ) - mesh.V( 1:3, mesh.F(2, i) )).^2);
                lb = sum((mesh.V( 1:3, mesh.F(1, i) ) - mesh.V( 1:3, mesh.F(3, i) )).^2);
                W = 2*mesh.Fa(i) / (la * lb);
                if (isinf(W) || isnan(W)) W = 0; end
            elseif j == 2
                la = sum((mesh.V( 1:3, mesh.F(2, i) ) - mesh.V( 1:3, mesh.F(1, i) )).^2);
                lb = sum((mesh.V( 1:3, mesh.F(2, i) ) - mesh.V( 1:3, mesh.F(3, i) )).^2);
                W = 2*mesh.Fa(i) / (la * lb);
                if (isinf(W) || isnan(W)) W = 0; end
            else
                la = sum((mesh.V( 1:3, mesh.F(3, i) ) - mesh.V( 1:3, mesh.F(1, i) )).^2);
                lb = sum((mesh.V( 1:3, mesh.F(3, i) ) - mesh.V( 1:3, mesh.F(2, i) )).^2);
                W = 2*mesh.Fa(i) / (la * lb);
                if (isinf(W) || isnan(W)) W = 0; end
            end
            mesh.Nv(1:3, mesh.F(j, i) ) = mesh.Nv(1:3, mesh.F(j, i)) + mesh.Nf(1:3, i) * W;
        end
    end
    mesh.Nv = normalize(mesh.Nv);
end