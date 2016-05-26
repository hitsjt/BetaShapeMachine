function alignCollectionOfMeshes(input_folder1, input_folder2, output_folder)
% aligns the meshes of folder 1 to meshes of folder 2
% for each mesh of folder 1, compute optimal rigid transformation that brings it
% close to the corresponding mesh of folder 2
% assumptions: all meshes are upwards oriented according to y-axis
% run:
% alignCollectionOfMeshes('../../Data/Chairs/ground_truth/Peter_meshes', '../../Data/Chairs/ground_truth/Vova_meshes',  '../../Data/Chairs/ground_truth/alignments_Peter_to_Vova_meshes');

mesh_filenames = dir( input_folder1 );
mesh_counter = 0;
num_meshes = 0;

for m=1:length(mesh_filenames);
    if length( mesh_filenames(m).name ) <= 3
        continue;
    end
    num_meshes = num_meshes + 1;
end
%list_of_meshes_to_process_again = 
%list_of_meshes_to_process_again = ...
%{'chair012124', 'chair005993', 'chair004867', 'chair000039'};
%{'chair005690'}; % no mesh!

mesh_counter = 0;
for m=1:length(mesh_filenames);
    if length( mesh_filenames(m).name ) <= 3
        continue;
    end
    
    mesh_counter = mesh_counter + 1;
    mesh_id_to_process = mesh_filenames(m).name(1:end-4);
    
%     found = false;
%     for j=1:length(list_of_meshes_to_process_again)
%         if ( strcmp( mesh_id_to_process, list_of_meshes_to_process_again{j} ) )
%             found = true;
%             break;
%         end
%     end
%     if ~found
%         continue;
%     end
        
    fprintf('Processing %s [%d out of %d] \n', mesh_id_to_process, mesh_counter, num_meshes  );
    
    mesh1 = loadObj( sprintf( '%s/%s', input_folder1, mesh_filenames(m).name ), false, true  );
    mesh2 = loadObj( sprintf( '%s/%s', input_folder2, mesh_filenames(m).name ), false, true );
    if ( (size(mesh1.F, 2) > 20000) )
        disp('mesh too big... attempting to decimate them with reducePatch...');
        mesh1 = reduceMesh(mesh1, 20000);
    end
    if ( (size(mesh2.F, 2) > 20000) )
        disp('mesh too big... attempting to decimate them with reducePatch...');
        mesh2 = reduceMesh(mesh2, 20000);
    end    
    mesh1 = removeUnrefVerts(mesh1);
    mesh2 = removeUnrefVerts(mesh2);
    mesh1.V = single(mesh1.V);
    mesh2.V = single(mesh2.V);
    
    warning off;
    mesh1 = normals(mesh1);
    mesh2 = normals(mesh2);
    warning on;
   
    bounding_box1.max = [max(mesh1.V(1:3,:),[],2); 1];
    bounding_box1.min = [min(mesh1.V(1:3,:),[],2); 1];
    bounding_box1.center = ( bounding_box1.max + bounding_box1.min ) / 2;

    bounding_box2.max = [max(mesh2.V(1:3,:),[],2); 1];
    bounding_box2.min = [min(mesh2.V(1:3,:),[],2); 1];
    bounding_box2.center = ( bounding_box2.max + bounding_box2.min ) / 2;
    
    min_d = Inf;
    best_M = eye(4);
    best_ry = 0;
    for ry = 0:90:359.9 %45:55 %0:1:359 %0:90:359.9
        % compute rotation matrix for y axis
        R = [ cosd(ry) 0 sind(ry) 0; 0 1 0 0; -sind(ry) 0 cosd(ry) 0; 0 0 0 1];        
        TC1 = eye(4);
        TC1(:, 4) = -bounding_box2.center;
        TC1(4, 4) = 1;
        TC2 = eye(4);
        TC2(:, 4) = bounding_box2.center;
        TC2(4, 4) = 1;        
        V2 =  TC2 * R' * TC1 * mesh2.V;
        bounding_box2.rmax = [max(V2(1:3,:),[],2); 1];
        
        % compute optimal scale
        s = (bounding_box2.rmax - bounding_box2.center) ./ (bounding_box1.max - bounding_box1.center);       
        s(4) = 1;
        S = diag(abs(s));
        
        % compute translation
        t = bounding_box2.center - TC2 * R * S * TC1 * bounding_box1.center;
        T = eye(4);
        T(:, 4) = t;
        T(4, 4) = 1;        
        
        % compute distance for these two bounding box points
        M = T * TC2 * R * S * TC1;
        V1 = M * mesh1.V;
        V2 = mesh2.V;
        D = allPairsSqDist(V1(1:3, :), V2(1:3, :));
        d = mean( sqrt(min(D)) );
                        
        if (d < min_d)
            min_d = d;
            best_ry = ry;
            best_M = M;
        end
    end
    
    % show result
    mesh1.V = best_M * mesh1.V;
    figure;
    plotMesh(mesh1, 'solid');
    drawnow;
    saveas(gcf, sprintf('%s_1.jpg', mesh_id_to_process), 'png' )
    
    figure;
    plotMesh(mesh2, 'solid');
    drawnow;
    saveas(gcf, sprintf('%s_2.jpg', mesh_id_to_process), 'png' )
    
    exportMesh(mesh1, 'tmp1.obj');
    exportMesh(mesh2, 'tmp2.obj');
    close all;
    
    % export M
    save_filename = sprintf('%s/%s.txt', output_folder, mesh_id_to_process);
    f = fopen(save_filename, 'wt');
    for mi=1:4
        for mj=1:4
            fprintf(f, '%.12f ', best_M(mi, mj) );
        end
        fprintf(f, '\n' );
    end
    fclose(f);
end
