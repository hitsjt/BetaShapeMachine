function plotMeshSegmentation(mesh,Seg)
% 
% cm = colormap(hsv(max(Seg)));
% 
% trimesh(mesh.F',mesh.V(1,:)',mesh.V(2,:)',mesh.V(3,:)', ...
%        'FaceColor', 'flat', 'EdgeColor', 'k', 'EdgeAlpha', .05, ...
%        'EdgeLighting', 'none', 'FaceLighting','none', ...
%        'FaceVertexCData', cm(Seg,:));
%    
%    
% 
% 
% set(gcf, 'Color', 'w', 'Renderer', 'Zbuffer');
% set(gca, 'Projection', 'perspective');
% 
% axis equal;
% axis tight;
% axis off;




% % % % CC = [255 255 255; 178 161 199];
% % % % CC = CC ./ 255;
% % % % C = zeros(size(mesh.V, 2), 3);
% % % % for i=1:size(mesh.V, 2)
% % % %     C(i, 1:3) = CC( Seg(i), 1:3 );
% % % % end


% 1. keep the axes the same: RGB
% 2. change the grey to (146,205,220)
% 3. change the purple to (178,161,199)
% 4. change green to (194,214,155)
% 5. change yellow to either (217,149,148) OR (250,191


             %bottom med              %bottom right            %up left  %up right 
% CC = [178/255 161/255 199/255; 250/255 192/255 143/255; 217/255 149/255 148/255; 146/255 205/255 220/255];
% C = zeros(size(mesh.V, 2), 3);
% for i=1:size(mesh.V, 2)
%     C(i, 1:3) = CC( Seg(i), 1:3 );
% end
% 
% load customJetColormap;
% colormap(customJet);

C = (256 / max(Seg)) .* Seg;
C = C' ./ max(C);

plotMesh(mesh, 'solidbw');
hold on;
caxis([0 1]);
trimesh(mesh.F',mesh.V(1,:)',mesh.V(2,:)',mesh.V(3,:)', ...
        'FaceLighting', 'none', 'FaceVertexCData', C, ...
        'FaceColor', 'interp', 'EdgeColor','none', 'CDataMapping','scaled');
set(gcf,'Renderer', 'ZBuffer');
set(gca, 'Projection', 'perspective');
axis equal;
axis off;
hold off;   