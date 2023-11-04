# GUI with Dear ImGUI framework 

GUI app example in C++ and Dear ImGui Framework

## Build

TODO: Review dependencies:

    $ sudo apt-get update
    $ sudo apt-get install cmake pkg-config
    $ sudo apt-get install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
    $ sudo apt-get install libao-dev libmpg123-dev
    $ sudo apt-get install libsdl2-dev
    $ sudo apt-get install libsdl2-image-dev
    
    $ sudo apt-get install libglew-dev libglfw3-dev libglm-dev


# Libraries

## Catch2

[Link] https://github.com/catchorg/Catch2.git

## Libstudxml

$ wget https://www.codesynthesis.com/download/libstudxml/1.0/libstudxml-1.0.1.tar.gz

$ tar -xvf libstudxml-1.0.1.tar.gz

$ mv libstudxml-1.0.1 libstudxml

$ cd libstudxml

### HOST 

$ ./configure --prefix=INSTALL_FOLDER

$ make -j$(nproc)

$ sudo make install

### TARGET

$ ./configure --host=COMPILER --prefix=INSTALL_FOLDER

$ make -j$(nproc)

$ sudo make install

## Dear IMGui

[Link] https://github.com/ocornut/imgui.git

## SDL

[Link] https://github.com/libsdl-org/SDL.git

[Link] https://github.com/libsdl-org/SDL_image.git

## GLFW

[Link] https://github.com/glfw/glfw.git

