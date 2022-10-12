all: libed myapps

libed:
	gcc -c .\src\ProductReview.cpp -I .\include -o .\obj\ProductReview.o 
	gcc -c .\src\ListaEncad.cpp -I .\include -o .\obj\ListaEncad.o

myapps:
	g++ .\apps\main.cpp .\obj\ProductReview.o .\obj\ListaEncad.o -I .\include -o .\bin\main_list

run:
	.\bin\main

clean:
	del .\bin\*
	del .\obj\*

