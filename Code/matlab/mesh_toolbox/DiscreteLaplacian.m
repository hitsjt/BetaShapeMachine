function mesh = DiscreteLaplacian(mesh)

if ~isfield(mesh, 'EFM1') || ~isfield(mesh, 'EFM2')
    disp('Computing Edge-Face Matrix...')
    mesh = getEdgeFaceMatrix(mesh);
end

%Edges = find((mesh.EFM1(:) ~= 0) & (mesh.EFM2(:) ~= 0));
Edges = zeros(1,6*size(mesh.V,2));
EFM1 = mesh.EFM1;
EFM2 = mesh.EFM2;
e = 0;
for k = 1:prod( size(EFM1) )
   if (EFM1(k) ~= 0) & (EFM2(k) ~= 0)
       e = e + 1;
       Edges(e) = k;
   end
end
Edges = Edges(1:e);


L = sparse(size(mesh.V,2), size(mesh.V,2), 10 * size(mesh.V,2));

for k = 1:length(Edges)
    e = Edges(k);
    
    i = mod(e, size(mesh.V,2));
    j = floor(e/size(mesh.V,2)) + 1;    
        
    f1 = mesh.EFM1(e);
    a = setdiff(mesh.F(:,f1), [i;j]);
    v1 = normalize(mesh.V(:,i) - mesh.V(:,a));
    v2 = normalize(mesh.V(:,j) - mesh.V(:,a));        
    cos_alpha = dot(v1,v2);
    cot_alpha = cos_alpha/sqrt(1 - cos_alpha^2);
    
    f2 = mesh.EFM2(e);
    b = setdiff(mesh.F(:,f2), [i;j]);
    v1 = normalize(mesh.V(:,i) - mesh.V(:,b));
    v2 = normalize(mesh.V(:,j) - mesh.V(:,b));
    cos_beta = dot(v1,v2);
    cot_beta = cos_beta/sqrt(1 - cos_beta^2);
    
    L(i, j) = -.5 * (cot_alpha + cot_beta);    
    L(j, i) = L(i, j);
end

for i=1:size(mesh.V, 2)
    L(i, i) = -sum( L(i, :) );
end

mesh.L = L;