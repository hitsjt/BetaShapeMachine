function mesh = conformFaces(mesh)

if isempty(mesh.F)
    return
end

if ~isfield(mesh,'FaceAdj')
    mesh = faceAdjacencyMatrix(mesh);
end

conformed = [1];
n_conf = 0;

while length(conformed) < size(mesh.F,2)
    
    dispPercent(length(conformed)/size(mesh.F,2));
        
    % find unconformed adjacents to conformed
    list = setdiff(find(any(mesh.FaceAdj(conformed,:),1)), conformed);
    
    if isempty(list)
        disp('Completed connected component...')
        remaining = setdiff(1:size(mesh.F,2), conformed);
        conformed = [conformed, remaining(1)];
        list = setdiff(find(any(mesh.FaceAdj(conformed,:),1)), conformed);
    end
    
    for i = 1:length(list)
        % get unconformed face from list
        uf = list(i);
        
        % find an adjacent, conformed face
        cf = intersect(find(mesh.FaceAdj(uf, :)), conformed);
        cf = cf(1);
        
        % now, enumeration of verts in uf should follow same rotation as cf
        [tf, loc] = ismember(mesh.F(:,uf), mesh.F(:,cf));
        loc = circshift(loc, 3 - find(loc == 0));        
        loc = loc(1:2) - 1;
        
        % if they don't, reverse order of verts in uf
        if loc(1) ~= mod(loc(2) + 1,3)
            mesh.F(:,uf) = flipud(mesh.F(:,uf));
            n_conf = n_conf + 1;
        end
    end
    
    conformed = [conformed, list];
end

mesh = faceCenters(mesh);
mesh = faceNormals(mesh);

C = mean(mesh.Fc,2);

if mean(dot(normalize(mesh.Fc(1:3, :) - C(1:3,ones(1,size(mesh.F,2)))),mesh.Nf(1:3, :) )) < 0
    mesh.F = flipud(mesh.F);
    mesh.Nf = -mesh.Nf;
    mesh.Nf = -mesh.Nf;
    
    disp('Reversing all...');
end

disp(sprintf('Changed %d faces.',n_conf));