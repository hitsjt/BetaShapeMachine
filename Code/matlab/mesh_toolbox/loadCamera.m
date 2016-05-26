function loadCamera(filename, A, B, C, D)
if nargin == 0
    load('__camera__matlab.mat');
end
if nargin == 1 && ~isempty(filename)
    load(filename);
end

if nargin <= 1
    campos(cameraA);
    camtarget(cameraB);
    camup(cameraC);
    camva(cameraD);
else
    
    campos(A);
    %camtarget(B);
    camup(C);
    camva(D);
end