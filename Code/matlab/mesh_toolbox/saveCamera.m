function [cameraA cameraB cameraC cameraD] = saveCamera(filename)

cameraA = campos;
cameraB = camtarget;
cameraC = camup;
cameraD = camva;

if nargin == 0
    save('__camera__matlab.mat');
else
    save(filename)
end