# c-c++
algoritmos en código c y c++

opciones de compilacion:
    - escribir en lenguaje batch
      1. ruta del compilador mingw por ejemplo c:\mingw
        set PATH=c:\mingw\bin;%PATH%
      2. podemos agregar la compilacion en c o c++ asi
         gcc -c scrip.c 
         g++ -g -std=c++11 scrip.cpp
      3. ademas podemos enlazar las librerias en c o c++ con la salida scrip.o
         g++  scrip.o libreria.a  -o nombre_nombre_del_archivo
  
