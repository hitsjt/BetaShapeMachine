function plotPoints(P, c, s, plotNormals, args)

if nargin < 2 || isempty(c)
    c = 'r';
end

if nargin < 3
    s = 15;
end

cm = colormap;

if ischar(c)
    color = c;
else
    color = cm(c,:);
end

if nargin == 5
    scatter3(P(1,:), P(2,:), P(3,:), s , color, args );
else
    scatter3(P(1,:), P(2,:), P(3,:), s , color );
end

grid on;
axis equal;

if nargin >= 4 && plotNormals == 1
    hold on;
    quiver3(P(1,:)', P(2,:)', P(3,:)', P(4,:)', P(5,:)', P(6,:)', .5,'b');
end


if nargin >= 4 && plotNormals == 2
    hold on;
    quiver3(P(1,:)', P(2,:)', P(3,:)', P(4,:)', P(5,:)', P(6,:)', .5, 'r');
    quiver3(P(1,:)', P(2,:)', P(3,:)', P(7,:)', P(8,:)', P(9,:)', .5, 'g');
    quiver3(P(1,:)', P(2,:)', P(3,:)', -P(4,:)', -P(5,:)', -P(6,:)', .5, 'r');
    quiver3(P(1,:)', P(2,:)', P(3,:)', -P(7,:)', -P(8,:)', -P(9,:)', .5, 'g');    
end


set(gcf, 'Color', 'w');
set(gca, 'Projection', 'perspective');

axis equal
axis tight
axis off