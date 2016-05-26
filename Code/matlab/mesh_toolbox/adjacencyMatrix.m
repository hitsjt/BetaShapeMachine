function mesh = adjacencyMatrix(mesh)

s = size(mesh.V,2);
Adj = logical(sparse(s,s));
F = mesh.F;

for f = 1:size(F,2)
	Adj(F(1,f), F(2,f)) = true;
	Adj(F(2,f), F(3,f)) = true;
	Adj(F(1,f), F(3,f)) = true;
end

mesh.Adj = Adj | Adj';