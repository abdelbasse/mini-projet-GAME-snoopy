@echo off
gcc src\main.c cJSON/cJSON.c -o bin\prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lm

cd bin
.\prog
cd ..
