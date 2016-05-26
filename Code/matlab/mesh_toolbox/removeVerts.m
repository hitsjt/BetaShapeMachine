function mesh = removeVerts(mesh, Vind)

V = mesh.V;

D = sqdist(V,V);
D( logical(eye(size(D))) ) = Inf;
D( :, Vind) = Inf;

[tmp cv] = min(D, [], 2);

for v=1:length(Vind)
    mesh.F( mesh.F == Vind(v) ) = cv( Vind(v) );
end

verts = setdiff( 1:size(mesh.V, 2), Vind);
mesh.V = mesh.V(:,verts);
[tf, mesh.F] = ismember(mesh.F,verts);
