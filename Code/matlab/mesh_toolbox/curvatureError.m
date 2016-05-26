function [RMSK1 RMSK2 RMSMK RMSGK MAXK1 MAXK2 MAXMK MAXGK] = curvatureError(mesh)

K1 = mesh.GK1;
K2 = mesh.GK2;
MK = mesh.GMK;
GK = mesh.GGK;

N = length(mesh.CK1);


if ( isfield(mesh, 'CK1') )
    RMSK1 = (1/N) * sqrt( sum( ( K1 - mesh.CK1 ).^2 ) );
    MAXK1 = max( abs( K1 - mesh.CK1 ) );
end

if ( isfield(mesh, 'CK2') )
    RMSK2 = (1/N) * sqrt( sum( ( K2 - mesh.CK2 ).^2 ) );
    MAXK2 = max( abs( K2 - mesh.CK2 ) );
end

if ( isfield(mesh, 'CMK') )
    RMSMK = sqrt( (1/N) * sum( ( MK - mesh.CMK ).^2 ) );
    MAXMK = max( abs ( MK - mesh.CMK ) );
end


if ( isfield(mesh, 'CGK') )
    RMSGK = sqrt( (1/N) * sum( ( GK - mesh.CGK ).^2 ) );
    MAXGK = max( abs ( GK - mesh.CGK ) );
else
    RMSGK = Inf;
    MAXGK = Inf;
end
