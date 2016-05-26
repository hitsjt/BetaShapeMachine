function exportMesh(mesh, file, flipaxes)

if nargin < 3
    flipaxes = false;
end

if flipaxes
    mesh.V(1:3,:) =  mesh.V([1,3,2],:);
    mesh.V(3,:)   = -mesh.V(3,:);
end

if strcmpi(file(end-3:end),'.obj')
   
    if ~isfield(mesh, 'parts')
        fid = fopen(file, 'wt');
%         fprintf(fid, 'g Mesh_0\n');
        fprintf(fid, 'v %f %f %f\n', mesh.V(1:3,:));
%         if isfield(mesh, 'Nv')
%             fprintf(fid, 'vn %e %e %e\n', mesh.Nv(1:3,:));
%         end
%         fprintf(fid, '\n');
        %     fprintf(fid, 'f %d//%d %d//%d %d//%d\n', mesh.F([1,1,2,2,3,3],:));
        fprintf(fid, 'f %d %d %d\n', mesh.F([1,2,3],:));
        fclose(fid);
    else
        fid = fopen(file, 'wt');        
        fprintf(fid, 'v %f %f %f\n', mesh.V(1:3,:));
        for p=1:length(mesh.parts)
            fprintf(fid, 'g %s\n', mesh.parts(p).name);
            fprintf(fid, 'f %u %u %u\n', mesh.F(1:3, mesh.parts(p).faces));
        end
        fclose(fid);
    end
    
% for i=1:size(mesh.F, 2)    
%     fprintf(fid, '%e %e %e\n%e %e %e\n%e %e %e\n', mesh.Nv(1:3, mesh.F(1, i)), mesh.Nv(1:3, mesh.F(2, i)), mesh.Nv(1:3, mesh.F(3, i)) );
% end
    
    
elseif strcmpi(file(end-3:end),'.off')
    
    fid = fopen(file, 'w');
    fprintf(fid, 'OFF\n');
    fprintf(fid, '%d %d %d\n', size(mesh.V,2), size(mesh.F,2), 0);
    fprintf(fid, '%e %e %e\n', mesh.V(1:3,:));
    fprintf(fid, '3 %d %d %d\n', mesh.F - 1);
    fclose(fid);
elseif strcmpi(file(end-4:end),'.ply2') 
    fid = fopen(file, 'w');    
    fprintf(fid, '%d\n', size(mesh.V,2));
    fprintf(fid, '%d\n', size(mesh.F,2));
    fprintf(fid, '%d\n', 2);
    fprintf(fid, '%d\n', 1);    
    fprintf(fid, '%.20f %.20f %.20f\n', mesh.V(1:3,:));
    fprintf(fid, '%d %d %d\n', mesh.F - 1);
    fclose(fid);
else
    error('Unsupported file format. Currently only .obj and .off formats are supported.');
end