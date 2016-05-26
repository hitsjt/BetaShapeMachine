function [Label, parts] = getConnectedComponents(mesh)

if ~isfield(mesh,'FaceAdj')
    mesh = faceAdjacencyMatrix(mesh);
end

stack_elem = zeros(1,size(mesh.F,2));
stack_last = 0;

facesLeft = size(mesh.F,2);
Label = zeros(1,size(mesh.F,2));
current_label = 0;

    function depthFirstFlood(f)
        stack_elem(1) = f;
        stack_last = 1;
        while stack_last > 0
            f = stack_elem(stack_last);
            stack_last = stack_last - 1;
            if Label(f) == 0
                % add face to those found
                Label(f) = current_label;

                % remove it from those remaining
                facesLeft = facesLeft - 1;
                
                % recurse on all adjacent faces
                adj = find(mesh.FaceAdj(f,:));
                for k = 1:length(adj)
                    stack_last = stack_last + 1;
                    stack_elem(stack_last) = adj(k);                    
                end
            end
        end
    end

while facesLeft > 0
    current_label = current_label + 1;
    f = find(Label == 0, 1);
    depthFirstFlood(f);
end

if nargout > 1
    for k = 1:current_label
        parts(k).F = mesh.F(:,Label == k);
        parts(k).V = mesh.V(:,unique(parts(k).F(:)));
        [tf, parts(k).F] = ismember(parts(k).F,unique(parts(k).F(:)));
    end
end

end % getConnectedComponents