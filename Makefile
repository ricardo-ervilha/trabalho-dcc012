all: libed myapps

libed:
	gcc -c .\src\ProductReview.cpp -I .\include -o .\obj\ProductReview.o 

myapps:
	g++ .\apps\main.cpp .\obj\ProductReview.o -I .\include -o .\bin\main

run:
	.\bin\main

clean:
	del .\bin\*
	del .\obj\*

