function plotPointsAndNormals(X)

V = X(:, 1:3);
N = X(:, 4:6);

scatter3( V(:, 1), V(:, 2), V(:, 3) );
hold on;
quiver3(V(:, 1), V(:, 2), V(:, 3), N(:, 1), N(:, 2), N(:, 3));
hold off;
set(gcf, 'Color', 'w');
set(gca, 'Projection', 'perspective');
axis equal
axis tight
axis off