# MapAdjuster

Goal of this program is to adjust an incoming source map (EU4 for example) to geographically match target map (Vic2 for example) by distorting it, while retaining province spacing and location.

Unfortuately, ShepardsDistortion of Imagemagick doesn't allow us to do this, as it stretches points with radial AoE, affecting pizels via inverse square law (1/r^2), whereas what we need is a 
mesh-approach that affects them linearly.

There is no Mesh in Imagemagick. There is selective cutting and distorting of individual triangles, a process a bit too involved for what we need, and which is supposed to be used
on the same image, not to map one image to another.

So, this project is on hiatus until Imagemagick supports meshes/grids natively.