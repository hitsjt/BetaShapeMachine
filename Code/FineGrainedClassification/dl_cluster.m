function dl_cluster(data_path, num_clusters)
% dl_cluster('C:/Users/V/Desktop/BetaShapeMachine/Data/airplane_gt_new', 10);
% fighter jets: 1-2
% second world war: 1
% commercial  (engines wing): 1
% commercial  (engines back): 1
% commercial  (prop. engines wing): 1
% UAVs: 1
% other: 1-2

% dl_cluster('C:/Users/V/Desktop/BetaShapeMachine/Data/chair_large', 5);

% dl_cluster('C:/Users/V/Desktop/BetaShapeMachine/Data/bike_large', 5);

% dl_cluster('C:/Users/V/Desktop/BetaShapeMachine/Data/helicopters_large', 5);


filenames_file = sprintf('%s/names.txt', data_path);
filenames = {};
f = fopen(filenames_file, 'rt');
while ~feof(f)
    filenames{end+1} = fgets(f);
    filenames{end}(end) = '';
end
fclose(f);

X = load( sprintf('%s/descriptor.txt', data_path) );

[idx, C] = kmeans(X, num_clusters, 'Start', 'cluster', 'Distance', 'cityblock', 'Replicates', 1000, 'EmptyAction', 'singleton');

for c=1:max(idx)
    if exist( sprintf('%s/cluster%d', data_path, c), 'dir')
        rmdir( sprintf('%s/cluster%d', data_path, c), 's' );
    end
    mkdir( sprintf('%s/cluster%d/', data_path, c) );
end

for m=1:length(idx)
    % debugging
    if exist( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), 'file' )
        copyfile( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), sprintf('%s/cluster%d/%s.png', data_path, idx(m), filenames{m} ) );
    end
%     im = imread( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), 'BackgroundColor', [1 1 1]);
%     im = cropImages(im);
%     imwrite( im, sprintf('%s/cluster%d/%s.jpg', data_path, c, filenames{m} ) ); 
end


end

function im = cropImages(im)
if length(size(im)) == 3
    imgray = rgb2gray(im);
    [x y] = find( imgray < 255);
    im = im( min(x):max(x), min(y):max(y), : );
else
    [x y] = find( im < 255);
    im = im( min(x):max(x), min(y):max(y));
end

end
