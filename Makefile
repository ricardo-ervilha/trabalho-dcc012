
libed:
	gcc -c .\src\ProductReview.cpp -I .\include -o .\obj\ProductReview.o 
	gcc -c .\src\ListaEncad.cpp -I .\include -o .\obj\ListaEncad.o
	gcc -c .\src\List.cpp -I .\include -o .\obj\List.o
	gcc -c .\src\Hash.cpp -I .\include -o .\obj\Hash.o
	gcc -c .\src\File.cpp -I .\include -o .\obj\File.o

myapps_import:
	g++ .\apps\main_import.cpp .\obj\List.o .\obj\File.o .\obj\ProductReview.o .\obj\Hash.o -I .\include -o .\bin\main_import

myapps_bin:
	g++ .\apps\main_bin.cpp .\obj\List.o .\obj\File.o .\obj\ProductReview.o .\obj\Hash.o -I .\include -o .\bin\main_bin

clean:
	del .\bin\*
	del .\obj\*

