@echo off
gcc src\main.c -o bin\prog -I include -L lib -lmingw32 -lSDL2main -lSDL2

cd bin
.\prog
cd ..
