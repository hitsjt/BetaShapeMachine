function mesh = loadPly(file)

fid = fopen(file);

% find number of vertices and faces
s = [];
for i = 1:2 
    while ~strcmpi(s, 'element')
        s = fscanf(fid, '%s[^ \n]');
    end
    s = fscanf(fid, '%s[^ \n]');
    if strcmpi(s, 'vertex')
        nverts = fscanf(fid, '%d');
    else
        nfaces = fscanf(fid, '%d');
    end
end

% skip rest of the header
while ~strcmpi(s, 'end_header')
    s = fscanf(fid, '%s[^ \n]');
end

V = zeros(5, nverts);
for i = 1:nverts
    mesh.V(:,i) = fscanf(fid, '%lg %lg %lg %lg %lg', [1 5])';
end
mesh.V(4,:) = 1;
mesh.V = mesh.V(1:4, :);

mesh.F = zeros(4, nfaces);
for i = 1:nfaces
    mesh.F(:,i) = fscanf(fid, '%d %d %d %d', [1 4])';
end
mesh.F = mesh.F(2:4,:) + 1;

fclose(fid);