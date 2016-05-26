function plotPoints3D(P)
% size(P, 2) should be number of points

for i=1:size(P, 2)
    hold on;
    plot3(P(1, i), P(2, i), P(3, i), 'r.', 'MarkerSize', 30);
end

hold off;
