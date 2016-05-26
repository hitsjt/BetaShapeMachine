function mesh = removeRepeatedFaces(mesh)

disp('Removing repeated faces...');
dispPercent(0);
i = 1;
tic;

F = sort(mesh.F,1);
numfaces = size(F,2);

del = false(1,size(F,2));

for i = 1:numfaces
    if ~del(i)
        for j = (i+1):numfaces
            if ~del(j) && F(1,i) == F(1,j) && F(2,i) == F(2,j) && F(3,i) == F(3,j)
                del(j) = true;
            end
        end
    end
end

mesh.F(:,del) = [];
disp(sprintf('%d faces removed', sum(del)));