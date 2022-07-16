<h1 align="center">PPM and 3D Object (.obj) Editor</h1>

<p align="center"> 🚀 Editor of .ppm files that can perform several functions and also represent 3D objects (.obj) in a 2D image. </p>

Table of Contents

===================

<!--ts-->

- [Examples](#Examples)
- [Environment](#Environment)
- [Prerequisites](#Prerequisites)
- [Convert .jpeg,.png,etc in .ppm](#Convert)
- [Remove color, textures and normals from the object (.obj)](#Remove)
- [Execute](#Execute)

<!--te-->

===================

# Examples

**3D Object in 2D image**

<img src="/img/README/3d2d.jpg" alt="3d2d"/>

**Blur**

<img src="/img/README/blur.jpg" alt="Blur"/>

**Negative Image**

<img src="/img/README/negative.jpg" alt="negative"/>

**Glut** (You can move the camera on the stage using the keys (W, A, S, D, Q and E))

<img src="/img/README/glut.jpg" alt="Glut1"/>

<img src="/img/README/glut2.jpg" alt="Glut2"/>

**Stamping**

<img src="/img/README/stamping.jpg" alt="Stamping"/>

# Environment

Execution environment used and tested:

**SO**: Ubuntu 20.04 **Kernel**: 5.8.0-63-generic

# Prerequisites

Before starting, you will need to have the following tools installed on your machine:

- [OpenGL](https://www.opengl.org/)

```bash
#Install Dependencies
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev mesa-utils freeglut3 libglew-dev
```

# Convert .jpeg,.png,etc in .ppm

To convert .jpeg,.png,etc in .PPM

```bash
$ sudo apt-get install imagemagick

$ convert image.jpg out.ppm
```

# Remove color, textures and normals from the object (.obj)

```bash
$ sudo apt-get install openctm-tools

$ ctmconv input.obj output.obj --no-normals --no-texcoords --no-colors
```

Open file and replace all occurrences of "//" with nothing ""

# Execute

```bash
$ make

$ make run
```
