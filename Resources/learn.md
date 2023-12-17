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
First for any modification you want to do you need, or you want to be inspired from this project you nned first a [VScode](https://code.visualstudio.com/download).
### SDL Installation ###
You need to Visit the Official website of [SDL](https://www.libsdl.org/) , then. and go to Downsload option.
if they still using github . then select [SDL2-devel-2.28.5-VC.zip](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5) you might still find it in the link.(*Only For C Programming*)

Now, u only need some file inside [include] directory,which are :
- SDL2.dll
- SDL2.lib
- SDL2main.dll
- SDL.h



