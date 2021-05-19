# PPM-Editor
Editor of .ppm files that can perform several functions and also represent 3D objects (.obj) in a 2D image.

# Some Functions

__3D Object in 2D image__

<img src="/img/README/3d2d.jpg" alt="3d2d"/>

__Blur__

<img src="/img/README/blur.jpg" alt="Blur"/>

__Negative Image__

<img src="/img/README/negative.jpg" alt="negative"/>

__Glut__ (You can move the camera on the stage using the keys (W, A, S, D, Q and E))

<img src="/img/README/glut.jpg" alt="Glut1"/>

<img src="/img/README/glut2.jpg" alt="Glut2"/>

__Stamping__

<img src="/img/README/stamping.jpg" alt="Stamping"/>

# Dependencies

sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev mesa-utils freeglut3 libglew-dev


# Execute:

1- ./make

2- 

./make run   

OR

cd bin && ./output

# TO CONVERT .jpeg,.png,etc in .PPM:

1-Sudo apt-get install imagemagick

2-convert image.jpg out.ppm

# TO REMOVE COLOR, TEXTURES AND NORMALS FROM THE OBJECT .obj:

1- sudo apt-get install openctm-tools

2- ctmconv input.obj output.obj --no-normals --no-texcoords --no-colors

3- Open file and replace all occurrences of "//" with nothing ""
