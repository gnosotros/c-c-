Se necesita pasar cientos de datos de un archivo csv (comma separated values), y alimentar una base de datos sqlite que queremos crear,
queremos compilar nuestro proyecto sin tener que instalar interfaces de desarrollo complejas y hacerlo de manera rapida, para ello usamos 
gcc en su version 9.2.2 y scribimos un sencillo condigo que nos vale para la practica.

lo primero que hicimos fue bajar el source de sqlite.
1. opciones de compilacion:
	*a. bajamos la librerias preconpiladas de sqlite3.dll y sqlite3.def de la pagina*
	b. compilamos con el codigo gcc -shared sqlite3.c -o sqlite3.dll
	*c. creamos la libreria libsqlite3.a asi en cmd dlltool --def sqlite3.def --dllname sqlite3.dll --output-lib libsqlite3.a de para enlazarla a mi codigo  con g++*
	d. en caso de tener solo la dll creamos asi dlltool --dllname sqlite3.dll --output-lib libsqlite3.a
2. copiamos sqlite3.dll y libsqlite3.a
