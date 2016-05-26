function mesh = createTestSurface(type, N)
% mesh = createTestSurface(type, N, baseMesh)
% type='sphere', 'torus', 'helicoid', 'saddle', 'cylinder'
% N is grid resolution in the parameter shape (grid will be NxN)

if nargin ~= 2
    error('you have to provide the type of surface and [u,v] grid resolution as input to the function');
end

[u v] = meshgrid(0:1/N:1, 0:1/N:1);
X = u;
Y = v;
Z = zeros( size(u) );
[f,v] = (surf2patch(surf(X, Y, Z)));
%close;
plane.V = v';
plane.V(4,:) = 1;
plane.F = [f(:,1:3)', f(:,[3:4,1])'];

if strcmp( type, 'torus' )
    b = 1;
    a = 4;

    mesh.V(1, :) = (a + b * cos( plane.V(2, :) * (2*pi) )) .* cos( plane.V(1, :) * (2 * pi) );
    mesh.V(2, :) = (a + b * cos( plane.V(2, :) * (2*pi) )) .* sin( plane.V(1, :) * (2 * pi) );
    mesh.V(3, :) = b * sin( plane.V(2, :) * (2 * pi) );
    mesh.F = plane.F;
    mesh = removeRepeatedVerts(mesh);
    u = ones( 1, size(mesh.V, 2) );
    pos = find( mesh.V(1, :) >= 0);
    neg = find( mesh.V(1, :) < 0);
    u(pos) = atan( mesh.V(2, pos) ./ mesh.V(1, pos) );
    u(neg) = atan( mesh.V(2, neg) ./ mesh.V(1, neg) ) + pi;
    cosv = ((mesh.V(1, :) ./ cos(u)) - a) / b;
    mesh.CK1 = (1 / b) .* ones(1, size(mesh.V,2));
    mesh.CK2 = cosv ./ (a + b * cosv);    
    mesh.CMK = 0.5 * (mesh.CK1 + mesh.CK2);
    mesh.CGK = mesh.CK1 .* mesh.CK2;
elseif strcmp( type, 'cylinder' )
    mesh.V(1, :) = cos( plane.V(1, :) * (2 * pi) );
    mesh.V(2, :) = sin( plane.V(1, :) * (2 * pi) );
    mesh.V(3, :) = (1/4) * ( plane.V(2, :) * (2 * pi) );
    mesh.F = plane.F;
    
    mesh.CK1 = ones(1, size(mesh.V, 2) );
    mesh.CK2 = zeros(1, size(mesh.V, 2) );
    mesh.CMK = ones(1, size(mesh.V, 2) ) / 2;
    mesh.CGK = zeros(1, size(mesh.V, 2) );    
elseif strcmp( type, 'saddle' )
    mesh.V(1, :) = 2 * plane.V(1, :) - 1;
    mesh.V(2, :) = 2 * plane.V(2, :) - 1;
    mesh.V(3, :) = mesh.V(1, :).^3 - 3 * mesh.V(1, :).*mesh.V(2, :).^2;
    mesh.F = plane.F;

    for i=1:size(mesh.V, 2)
        u = mesh.V(1, i);
        v = mesh.V(2, i);
        K = (-36 * (u^2 + v^2)) / ((1 + 9 * (u^2 + v^2) ^ 2 ) ^ 2);
        H = (27 * u) * (-u ^ 4 + 2 * (u ^ 2) * (v ^ 2) + 3 * v ^ 4) / ((1 + 9 * (u^2 + v^2) ^ 2 ) ^ (3/2) );
        mesh.CK1(i) = H + sqrt(H^2 - K);
        mesh.CK2(i) = H - sqrt(H^2 - K);
        mesh.CMK(i) = H;
        mesh.CGK(i) =  mesh.CK1(i) * mesh.CK2(i);
    end
elseif strcmp( type, 'helicoid' )
    mesh.V(1, :) = plane.V(1, :) * (2 * pi) .* cos( plane.V(2, :) * (2 * pi) );
    mesh.V(2, :) = plane.V(1, :) * (2 * pi) .* sin( plane.V(2, :) * (2 * pi) );
    mesh.V(3, :) = plane.V(2, :) * (2 * pi);
    mesh.F = plane.F;
    
    v = mesh.V(3, :);
    u = mesh.V(1, :) ./ cos(v);
    mesh.CMK = zeros(1, size(mesh.V, 2) );
    mesh.CGK = -1 ./ ((1 + u.^2).^2);
    mesh.CK1 = sqrt(-mesh.CGK);
    mesh.CK2 = -mesh.CK1;
end

