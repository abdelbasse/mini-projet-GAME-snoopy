# CDL my documentation #
### Learning API ###
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

### Simple traduction ###
-the [Update] function is a function that loop every frame and every frame it have a render the and read user data.
-for [Setup] is just a simple function before the loop start to set up some data or function needed after.
```c
Setup();
while (true){
    read_input();
    Update();
    //for generation design and graphiques
    drow();
}
```