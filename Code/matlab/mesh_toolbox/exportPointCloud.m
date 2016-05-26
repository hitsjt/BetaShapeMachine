function exportPointCloud(mesh, file, flipaxes)

if nargin < 3
    flipaxes = false;
end


if flipaxes
    mesh.V(1:3,:) =  mesh.V([1,3,2],:);
    mesh.V(3,:)   = -mesh.V(3,:);
end

Y = [mesh.V(1:3, :)' mesh.Nv(1:3, :)'];

fid = fopen(file, 'w');
fprintf(fid, '%d\n', size(mesh.V, 2) );
for i=1:size(mesh.V, 2)
    fprintf(fid, '%f %f %f %f %f %f\n', Y(i, 1), Y(i, 2), Y(i, 3), Y(i, 4), Y(i, 5), Y(i, 6) );
end
fclose(fid);

