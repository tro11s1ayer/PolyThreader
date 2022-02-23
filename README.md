# PolyThreader
Polymorphic Thread PoC

Opens UDP port 137
![polyThreader-1](https://user-images.githubusercontent.com/98718914/155408887-30978a8e-679c-4e88-85e4-92ab74d97d5d.png)

Compile with:
x86_64-w64-mingw32-gcc workspace/scripts/thread.c -o thread.exe -lpthread -static-libgcc -Wint-conversion -Wimplicit-function-declaration -Wint-to-pointer-cast
