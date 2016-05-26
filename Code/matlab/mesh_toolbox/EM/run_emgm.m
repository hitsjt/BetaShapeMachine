function [label, model, llh] = run_emgm(X)
c = 1; % k represents the number of clusters
kfold = 10; % k-fold cross validation (number of folds)

X_kfold_train = {}; % will hold the training subsets for each fold of cross-validation
X_kfold_test = {}; % will hold the test subsets for each fold of cross-validation

r = randperm( size(X, 2) );
for k=1:kfold % 10-fold cross validation
    X_kfold_test{k} = X(:, r(1: floor(size(X, 2)/kfold)) );
    X_kfold_train{k} = X(:, r(ceil(size(X, 2)/kfold + 1):end) );
end
    
best_validation_llh = -Inf;
validation_llh = -Inf;
while true    
    prev_validation_llh = validation_llh;
    validation_llh = 0; % validation log likelihood
    
    for k=1:kfold
      init = kmeans(X_kfold_train{k}', c, 'Replicates', 1000 )';
      [label, model, llh] = emgm( X_kfold_train{k}, init, 100 ); % em for 1000 iterations and c clusters - initialize with k-means
      [label, model, llh] = emgm( X_kfold_test{k} , [], -1, model ); % just measure likelihood for the whole dataset
      validation_llh = validation_llh + llh;
    end
       
    fprintf('*** Cross-validation average log-likelihood for %d clusters is %s \n', c, sprintf('%.5f', validation_llh)  );    
    if validation_llh > best_validation_llh
        best_validation_llh = validation_llh;
        fprintf('*** Optimal number of clusters is currently: %d \n', c );    
    end
    if validation_llh < prev_validation_llh
        fprintf('Cross-validation average log-likelihood increased. Breaking. Best number of clusters was: %d ', c-1 ); 
        c = c - 1;
        break;
    end
    
    c = c + 1; % increase number of clusters in the next iteration
end

fprintf('Final model training...\n');
[label, model, llh] = emgm( X, c, 1000 );