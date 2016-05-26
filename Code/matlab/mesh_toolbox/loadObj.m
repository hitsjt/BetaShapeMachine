function mesh = loadObj(filestr, flipaxes, disable_output)

if nargin < 2
    flipaxes = false;
    disable_output = false;
end
if nargin < 3
    disable_output = false;
end

file = fopen(filestr);

mesh.V = zeros(4, 200000, 'single');
mesh.Nv = zeros(3, 200000, 'single');
mesh.F = zeros(3, 400000, 'uint32');

v = [0;0;0;1];
nv = [0;0;0];
f = [0;0;0];
i = 0;
numfaces = 0;
numverts = 0;
numvertns = 0;

while ~feof(file)
    i = i + 1;
    if mod(i, 1000) == 0
        if ~disable_output
            fprintf(1, '%d lines read\n', i)
        end
    end   
    line = strtrim(fgetl(file));
    if isempty(line)
        continue
    end
    [toks pos] = textscan(line, '%s',1);
    token = char(toks{1});
    line = line(pos+1:end);
    
    if strcmp(token, 'v')
        numverts = numverts + 1;
        k = 0;
        while k < 3 && ~isempty(line)
            k = k + 1;
            [toks pos] = textscan(line, '%s',1);
            token = char(toks{1});
            line = line(pos+1:end);
            v(k) = eval(token);
        end
        if k > 3
            error('Read vertex with more than 3 coordinates.');
        end
        mesh.V(:, numverts) = v;
    elseif strcmp(token, 'vn')
        numvertns = numvertns + 1;
        k = 0;
        while k < 3 && ~isempty(line)
            k = k + 1;
            [toks pos] = textscan(line, '%s',1);
            token = char(toks{1});
            line = line(pos+1:end);
            nv(k) = eval(token);
        end        
        if k > 3
            error('Read vertex normal with more than 3 coordinates.');
        end
        mesh.Nv(1:3, numvertns) = nv;
    elseif strcmp(token, 'f')
        numfaces = numfaces + 1;
        k = 0;
        while ~isempty(line)
            k = k + 1;            
            [toks pos] = textscan(line, '%s', 1);
            token = char(toks{1});
            line = line(pos+1:end);
            toks = textscan(token, '%s', 1, 'delimiter', '/');            
            token = char(toks{1});
            f(k) = eval(token);
        end
%        if k > 3
%            error('Read face with more than 3 indices.');
%        end
        for l=1:k        
            mesh.F(l, numfaces) = f(l);            
        end
    end
    
end
fclose(file);

mesh.V = mesh.V(:, 1:numverts);
mesh.Nv = mesh.Nv(:, 1:numverts);
mesh.F = mesh.F(:, 1:numfaces);

if flipaxes
    mesh.V = mesh.V([1,3,2,4],:);
    mesh.V(2,:) = -mesh.V(2,:);
end