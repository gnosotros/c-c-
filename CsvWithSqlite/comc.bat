echo off
set PATH=%CD%\mingw\bin;%PATH%
REM el orden del codigo debe ser las estenciones .o primero y luego las librerias.a
REM en caso de que desee compilar su propia version de sqlite.
REM gcc -Wall -c sqlite3.c 

gcc -c  csvSqlite.c
g++  csvSqlite.o libsqlite3.a  -o csv




