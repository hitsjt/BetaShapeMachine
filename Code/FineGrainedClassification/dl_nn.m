function dl_nn(data_path)
% dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/airplane_gt_new');
% dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/chair_large');
% dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/bike_large');
% dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/helicopters_large');

X = load( sprintf('%s/descriptor.txt', data_path) );

map_from_class_name_to_class_ids = containers.Map();
map_from_class_ids_to_class_name = {};
Y = [];
filenames = {};

classifications_file = fopen( sprintf('%s/classification_data.txt', data_path), 'rt' );
while true    
    filename = fscanf(classifications_file, '%s', 1);
    if feof(classifications_file)
        break;
    end
    filenames{end+1} = filename;
    
    label = fscanf(classifications_file, '%s', 1);
    if feof(classifications_file)
        break;
    end    
    if strcmp( label, 'other')
        Y(end+1) = -1;
    else  
        if ~isKey(map_from_class_name_to_class_ids, label)
            map_from_class_name_to_class_ids(label) = map_from_class_name_to_class_ids.Count + 1;
            map_from_class_ids_to_class_name{end+1} = label;
        end        
        Y(end+1) = map_from_class_name_to_class_ids(label);
    end
    
%    is_train(end+1) = fscanf(classifications_file, '%d', 1) == 1;
end
fclose( classifications_file );


N = size( X, 1);
is_train = zeros(N, 1);
best_is_train = is_train;
best_accuracy = 0;

for iter=1:10
    is_train = zeros(N, 1);
    shuffled_ids = randperm(N);
    is_train( shuffled_ids(1:10) ) = 1;    
    if any( Y( find(is_train) ) == -1 )
        continue;
    end
    
    save( sprintf('%s/split.txt', data_path)  ,'is_train', '-ascii');    
    accuracy = dl_nn_internal(data_path, X, Y);
    if ( accuracy > best_accuracy )
        best_accuracy = accuracy;
        best_is_train = is_train;
    end
end

save( sprintf('%s/split.txt', data_path)  ,'best_is_train', '-ascii');    
[accuracy Ypred] = dl_nn_internal(data_path, X, Y);



%% create output dirs
for c=1:length(map_from_class_ids_to_class_name)
    if exist( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}), 'dir')
        rmdir( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}), 's' );
    end
    mkdir( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}) );
end

for m=1:length(filenames)
    if Y(m) == -1
        continue;
    end
    if Y(m) ~= Ypred(m)
        fprintf('%s\n', filenames{m});
    end
    label = map_from_class_ids_to_class_name{ Ypred(m) };
    if exist( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), 'file' )
        copyfile( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), sprintf('%s/classification/%s/%s.png', data_path, label, filenames{m} ) );
    end
end

end








function [accuracy Ypred] = dl_nn_internal(data_path, X, Y)
is_train = load( sprintf('%s/split.txt', data_path ) ) == 1;

classifier_model = ClassificationKNN.fit(X(find(is_train), :),Y(find(is_train)), 'Distance', 'cityblock');
Ypred = predict(classifier_model, X)';

keep_indices = setdiff( find(~is_train), find(Y==-1) );
accuracy = sum( Ypred(keep_indices) == Y(keep_indices) ) / length(keep_indices);

fprintf('Classification accuracy: %f\n', accuracy );

end






























% function dl_nn(data_path)
% % dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/airplane_gt_new');
% % dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/chair_large');
% % dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/bike_large');
% % dl_nn('C:/Users/V/Desktop/BetaShapeMachine/Data/helicopters_large');
% 
% N = size( load( sprintf('%s/descriptor.txt', data_path) ), 1);
% is_train = zeros(N, 1);
% best_is_train = is_train;
% best_accuracy = 0;
% 
% for iter=1:100
%     shuffled_ids = randperm(N);
%     is_train( shuffled_ids(1:10) ) = 1;
%     save( sprintf('%s/split.txt', data_path)  ,'is_train', '-ascii');    
%     accuracy = dl_nn_internal(data_path, 0);
%     if ( accuracy > best_accuracy )
%         best_accuracy = accuracy;
%         best_is_train = is_train;
%     end
% end
% 
% save( sprintf('%s/split.txt', data_path)  ,'best_is_train', '-ascii');    
% dl_nn_internal(data_path, 1);
% 
% end
% 
% function accuracy = dl_nn_internal(data_path, final)
% 
% X = load( sprintf('%s/descriptor.txt', data_path) );
% 
% map_from_class_name_to_class_ids = containers.Map();
% map_from_class_ids_to_class_name = {};
% %is_train = [];
% is_train = load( sprintf('%s/split.txt', data_path ) );
% Y = [];
% filenames = {};
% 
% classifications_file = fopen( sprintf('%s/classification_data.txt', data_path), 'rt' );
% while true    
%     filename = fscanf(classifications_file, '%s', 1);
%     if feof(classifications_file)
%         break;
%     end
%     filenames{end+1} = filename;
%     
%     label = fscanf(classifications_file, '%s', 1);
%     if feof(classifications_file)
%         break;
%     end    
%     if strcmp( label, 'other')
%         Y(end+1) = -1;
%     else  
%         if ~isKey(map_from_class_name_to_class_ids, label)
%             map_from_class_name_to_class_ids(label) = map_from_class_name_to_class_ids.Count + 1;
%             map_from_class_ids_to_class_name{end+1} = label;
%         end        
%         Y(end+1) = map_from_class_name_to_class_ids(label);
%     end
%     
% %    is_train(end+1) = fscanf(classifications_file, '%d', 1) == 1;
% end
% fclose( classifications_file );
% 
% classifier_model = ClassificationKNN.fit(X(find(is_train), :),Y(find(is_train)), 'Distance', 'cityblock');
% Ypred = predict(classifier_model, X)';
% 
% keep_indices = setdiff( find(~is_train), find(Y==-1) );
% accuracy = sum( Ypred(keep_indices) == Y(keep_indices) ) / length(keep_indices);
% fprintf('Classification accuracy: %f\n', accuracy );
% 
% if final == 1
%     for c=1:length(map_from_class_ids_to_class_name)
%         if exist( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}), 'dir')
%             rmdir( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}), 's' );
%         end
%         mkdir( sprintf('%s/classification/%s', data_path, map_from_class_ids_to_class_name{c}) );
%     end
%     
%     for m=1:length(filenames)
%         % debugging
%         if Y(m) == -1
%             continue;
%         end
%         if Y(m) ~= Ypred(m)
%             fprintf('%s\n', filenames{m});
%         end
%         label = map_from_class_ids_to_class_name{ Ypred(m) };
%         if exist( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), 'file' )
%             copyfile( sprintf('%s/meshes/%s.png', data_path, filenames{m} ), sprintf('%s/classification/%s/%s.png', data_path, label, filenames{m} ) );
%         end
%     end
% end
% 
% end