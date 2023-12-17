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
First for any modification u want to do u need, or u want to be inspired from this project u nned first a [VScode](https://code.visualstudio.com/download)