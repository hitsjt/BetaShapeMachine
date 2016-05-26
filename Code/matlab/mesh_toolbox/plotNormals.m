function plotNormals(mesh, type, method)

if nargin < 3
    method = 'quiver';
end

if strcmpi(type, 'face')    
    
    
    if ~isfield(mesh,'Nf')
        mesh = faceNormals(mesh);
    end
    
    if strcmpi(method, 'quiver')
    
        if ~isfield(mesh,'Fc')
            mesh = faceCenters(mesh);
        end

        hold on;
        plotMesh(mesh,'solidbws');
        quiver3(mesh.Fc(1,:)', mesh.Fc(2,:)', mesh.Fc(3,:)', ...
            mesh.Nf(1,:)', mesh.Nf(2,:)', mesh.Nf(3,:)');
        hold off;

    elseif strcmpi(method, 'color')
    
        mesh.C = mesh.Nf(1:3,:)';
        plotMesh(mesh, 'solid');
    
    else
        error(sprintf('Unrecognized plot method: %s', type));
    end
    
elseif strcmpi(type, 'vertex')
    
    if ~isfield(mesh,'Nv')
        mesh = normals(mesh);
    end
    
    if strcmpi(method, 'quiver')
       
        hold on;
        plotMesh(mesh,'solidbws');
        quiver3(mesh.V(1,:)', mesh.V(2,:)', mesh.V(3,:)', ...
            mesh.Nv(1,:)', mesh.Nv(2,:)', mesh.Nv(3,:)');
        hold off;

    elseif strcmpi(method, 'color')
        
        mesh.C = mesh.Nv(1:3,:)'; 
        plotMesh(mesh, 'solid');
        
    else
        error(sprintf('Unrecognized plot method: %s', type));
    end

else
    error(sprintf('Unrecognized normal type %s', type));
end
