function mesh = MeyerCurvature(mesh)

if ~isfield(mesh, 'EFM1') || ~isfield(mesh, 'EFM2')
    disp('Computing Edge-Face Matrix...')
    mesh = getEdgeFaceMatrix(mesh);
end

if ~isfield(mesh, 'Nv')
    disp('Computing vertex normals...');
    mesh = vertexNormals(mesh);
end

if ~isfield(mesh, 'Adj')
    disp('Computing vertex adjacency...');
    mesh = adjacencyMatrix(mesh);
end

if ~isfield(mesh, 'Fa')
    disp('Computing face areas...');
    mesh = faceAreas(mesh);
end

K = zeros(4,size(mesh.V,2));

disp('Computing cot of alpha/beta face angles...');
[cot_alpha, cot_beta] = getAlphaBetas(mesh);

disp('Computing A_mixed...');
[A_mixed GK] = getAreas(mesh, cot_alpha, cot_beta);

disp('Computing K...');
for i = 1:size(mesh.V,2)
    js = find(mesh.Adj(i,:));
    for k = 1:length(js)
        j = js(k);        
        x_ij = mesh.V(:,i) - mesh.V(:,j);        
        K(:,i) = K(:,i) + (cot_alpha(i,j) + cot_beta(i,j))*x_ij;
    end
end

K = scale_cols(K,1./(2*A_mixed));

mesh.MMK = norms(K)'/2;
mesh.MMK = mesh.MMK .* sign(dot(K(1:3, :), mesh.Nv(1:3, :) )');
mesh.MMK = -mesh.MMK';

BEF_SQ = mesh.MMK.^2 - GK;
BEF_SQ( find( BEF_SQ < 0 ) ) = 0;

mesh.MK1 = mesh.MMK + sqrt( BEF_SQ );
mesh.MK2 = mesh.MMK - sqrt( BEF_SQ );
mesh.MGK = mesh.MK1 .* mesh.MK2;

disp('Done.');


%--------------------------------------------------------------------------
function [cot_alpha, cot_beta] = getAlphaBetas(mesh)

cot_alpha = sparse(size(mesh.V,2), size(mesh.V,2));
cot_beta  = sparse(size(mesh.V,2), size(mesh.V,2));

Edges = find((mesh.EFM1(:) ~= 0) & (mesh.EFM2(:) ~= 0));


for k = 1:length(Edges)

    e = Edges(k);
    
    i = mod(e, size(mesh.V,2));
    j = floor(e/size(mesh.V,2)) + 1;    
        
    f1 = mesh.EFM1(e);
    a = setdiff(mesh.F(:,f1), [i;j]);
    v1 = normalize(mesh.V(:,i) - mesh.V(:,a));
    v2 = normalize(mesh.V(:,j) - mesh.V(:,a));        
    cos_alpha = dot(v1,v2);
    cot_alpha(e) = cos_alpha/sqrt(1 - cos_alpha^2);
    
    f2 = mesh.EFM2(e);
    b = setdiff(mesh.F(:,f2), [i;j]);
    v1 = normalize(mesh.V(:,i) - mesh.V(:,b));
    v2 = normalize(mesh.V(:,j) - mesh.V(:,b));
    cos_beta = dot(v1,v2);
    cot_beta(e) = cos_beta/sqrt(1 - cos_beta^2);

end

cot_alpha = cot_alpha + cot_alpha';
cot_beta = cot_beta + cot_beta';

%--------------------------------------------------------------------------
function [A_mixed GK] = getAreas(mesh, cot_alpha, cot_beta);

A_mixed = zeros(1,size(mesh.V,2));
GK = 2*pi*ones(1,size(mesh.V,2));

for i = 1:size(mesh.V,2)
    
    js = find(mesh.Adj(i,:));
    
    %if xor(any(mesh.EFM1(i,js) == 0), any(mesh.EFM2(i,js) == 0))
    %    A_mixed(i) = NaN;
    %else
    
        % get triangles
        Ts = [];
        for k = 1:length(js)
            j = js(k);
            Ts = [Ts, mesh.EFM1(min(i,j),max(i,j))];
            Ts = [Ts, mesh.EFM2(min(i,j),max(i,j))];
        end
        Ts = setdiff(unique(Ts),0);
        
        for k = 1:length(Ts)
            T = Ts(k);
            
            F = mesh.F(:,T);
            
            % put i as the first index
            F = [i;setdiff(F,i)];
            
            n12 = normalize(mesh.V(:,F(2)) - mesh.V(:,F(1)));
            n13 = normalize(mesh.V(:,F(3)) - mesh.V(:,F(1)));
            n23 = normalize(mesh.V(:,F(3)) - mesh.V(:,F(2)));
            
            inner_cos(1) = dot(n12,n13);
            GK(i) = GK(i) - acos(inner_cos(1));
            
            inner_cos(2) = dot(-n12,n23);
            inner_cos(3) = dot(-n13,-n23);
            
            % if T is non-obtuse
            if all(inner_cos > 0)
                
                % use voronoi area
                PR = mesh.V(:,F(2)) - mesh.V(:,F(1));
                PQ = mesh.V(:,F(3)) - mesh.V(:,F(1));
                cot_Q = inner_cos(3)/sqrt(1 - inner_cos(3)^2);
                cot_R = inner_cos(2)/sqrt(1 - inner_cos(2)^2);
                
                A_vor = (dot(PR,PR)*cot_Q + dot(PQ,PQ)*cot_R)/8;
                
                A_mixed(i) = A_mixed(i) + A_vor;
                
            else
                % if T is obtuse at x
                if inner_cos(1) <= 0
                    A_mixed(i) = A_mixed(i) + mesh.Fa(T)/2;
                else
                    A_mixed(i) = A_mixed(i) + mesh.Fa(T)/4;
                end
            end
        end
        
        GK(i) = GK(i) / A_mixed(i);
        %end
end
