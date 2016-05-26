function mesh = removeSliverFaces(mesh)

isSliver = (mesh.F(1,:) == mesh.F(2,:)) | (mesh.F(2,:) == mesh.F(3,:)) | (mesh.F(1,:) == mesh.F(3,:));
mesh.F(:,isSliver) = [];
if isfield(mesh, 'parts')
    mesh.faceLabels(:,isSliver) = [];
end
disp(sprintf('Done. %d faces removed.', sum(isSliver)));

if isfield(mesh, 'parts')
    for j=1:length(mesh.parts)
        mesh.parts(j).faces = find( mesh.faceLabels == j );
    end
end



% i = 1;
% count = 0;
%
% disp('Removing sliver faces')
% dispPercent(0);
% tic;
% while i <= size(mesh.F,2)
%     if length(unique(mesh.F(:,i))) < 3
%         mesh.F(:,i) = [];
%         count = count + 1;
%     else
%         i = i + 1;
%     end
%
%     if toc > 2
%         dispPercent(i/size(mesh.F,2));
%         tic;
%     end
% end
%
% dispPercent(1);
% disp(sprintf('Done. %d faces removed.', count));