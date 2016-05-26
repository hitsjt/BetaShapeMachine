function  accuracy = getaccuracy(file_name)
accuracy  = load(file_name);
accuracy  = cumsum(accuracy );
[m,n] = size(accuracy );
accuracy  =accuracy/(accuracy(m*n));
accuracy (m*n)= accuracy (m*n - 1);