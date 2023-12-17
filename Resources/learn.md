# CDL my documentation #
## Introduction ##
### Learning how Game Engin works ###
each game engin have 3 main function , **Setup** , **Update** , **Drow**
in engines the code will look like this 
```c
void Setup(){
    //code that execute one time at the begining
}
void Update(){
    //code execute every frame 
}
void Drow(){
    //code execute to render
}
```

### What happen in the Main ###
 - the [Update] function is a function that loop every frame and every frame it have a render the and read user data.
 - for [Setup] is just a simple function before the loop start to set up some data or function needed after.

```c
Setup();
while (true){
    read_input();
    Update();
    //for generation design and graphiques
    drow();
}
```

## Instalation for Windows ##
### Vscode Installation ###
    First for any modification you want to do you need, or you want to be inspired from this project you need first a [VScode](https://code.visualstudio.com/download).
### C compiler Installation ###
    To use the GNU Compiler Collection (GCC) on Windows, you can use the MinGW-w64 distribution. Follow these steps:

1. **Download MinGW-w64 Installer:**
   - Visit the [MinGW-w64 download page](https://mingw-w64.org/doku.php) and download the installer appropriate for your system (32-bit or 64-bit).

2. **Run the Installer:**
   - Execute the downloaded installer.
   - During installation, choose the architecture, threads, and exceptions according to your preferences.

3. **Add MinGW-w64 to System Path:**
   - After installation, add the MinGW-w64 binaries to your system's PATH environment variable. This allows you to run GCC from any command prompt.
   
4. **Verify Installation:**
   - Open a new command prompt and type `gcc --version` to verify that GCC is installed correctly. You should see information about the installed GCC version.

Now, you have GCC installed on your Windows system and can use it to compile C and C++ programs.

For more detailed instructions or troubleshooting, refer to the [MinGW-w64 documentation](https://mingw-w64.org/doku.php).
### SDL Installation ###
    You need to Visit the Official website of [SDL](https://www.libsdl.org/) , then. and go to Downsload option.
    if they still using github . then select [SDL2-devel-2.28.5-VC.zip](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) you might still find it in the link.(*Only For C Programming*)

    Now, you only need to use some files inside **./include** directory,which are :
     - SDL2.dll
     - SDL2.lib
     - SDL2main.dll
     - SDL.h

    After that you need to include it in your progamme : 
    ```c
    #include <stdlib.h>
    #include <stdin.h>
    #include "SDL.h"

    int main(){
        ...
    }
    ```
**Note :** you need to add this file in your project :
    ```
    - Project Dir
    | - main.c
    | - SDL2.dll
    | - SDL2.lib
    | - SDL2main.dll
    | - SDL.h

    ```

And try :
    ```bash
    gcc main.c -o myprogram
    ```
    **or**
    ```bash
    gcc main.c library.c -o myprogram
    ```
To run it do :
    ```bash
    ./myprogram
    ```

For information about this library [Click me](https://wiki.libsdl.org/SDL2/FrontPage)



