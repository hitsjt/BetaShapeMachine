function plotCurvatureValues(mesh, C)

invalid = isnan(C);
C(invalid) = 0;
invalid = isinf(C);
C(invalid) = 0;

% clamp values if necessary
% thr = 5 * median(abs(C));
% if (thr == 0)
%     thr = 1;
% end
% C( find(abs(C) > thr) ) = thr;

% C = round(10*C) / 10 % for curious students: uncomment this line if you want to visualize mesh.GK2, think why
C = .5 * (C./max(abs(C)) + 1);

C(invalid) = 1;

trimesh(mesh.F',mesh.V(1,:)',mesh.V(2,:)',mesh.V(3,:)', ...
        'FaceLighting', 'none', 'FaceVertexCData', C', ...
        'FaceColor', 'interp', 'EdgeColor','none', 'CDataMapping','scaled');
    
set(gcf,'Renderer', 'OpenGL');
set(gca, 'Projection', 'perspective');

axis equal;
axis off;
hold off;