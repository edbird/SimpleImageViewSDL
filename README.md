# SimpleImageViewSDL
SDL Version of Simple Image View

# Keybindings
a = fix window to image size

q = quit

LEFT / RIGHT = select image from current working directory

# Why this software?
It's simple: Windows lacks a simple application to view image files. This is one of the most basic programs which would be expected to be included with any operating system. Instead of including a simple program which the user can use to view images, Microsoft has chosen to include pozzed bloatware with their operating systems. New versions of Microsoft paint take several seconds to open and load an image, which is simply not an acceptable situation for the end user.

In contrast, Simple Image View is just that - simple.

# Why SDL?
SDL probably isn't an ideal framework to use to build this kind of application, but it happened to be something that I knew how to use, and it is cross platform. Since I am a Linux developer and avoid using Windows unless absolutly necessary, I don't really know what options are available for Windows other than cross platform solutions.

Feel free to make suggestions and I can perhaps implement this differently if there is a better way.

# Requirements

SDL2 and SDL2 Image library (see include directives in main.cpp)

# Thread from elsewhere...
I've written a non-pozzed image viewer, intended to be used with Windows, but it is cross platform as it uses SDL.

If this is something you are interested in please check it out and let me know if you need help to compile it etc

It uses SDL2, so should just work cross platform, provided you have a C++ 17 compliant compiler on Windows

There is no menu or anything like that it's literally just a window which displays images. There are 4 keybindings. Q to quit, A to re-scale the window to the image, and LEFT/RIGHT to move between images in the current WD. I'm aware it needs some kind of GUI to be able to open images, but I've not got time to work on that at the moment

You will need to run it from a working dir which contains images. I'm also aware that's retarded and it's not something I've got around to sorting yet
