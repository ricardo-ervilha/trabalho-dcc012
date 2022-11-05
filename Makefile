ifdef ComSpec
    RM=del /F /Q
	AUXPS=\\
	PS=$(strip $(AUXPS))
else
    RM=rm -f
	PS=/
endif

pre:
	mkdir -p obj
	mkdir -p bin

libed:
	g++ -c .$(PS)src$(PS)ProductReview.cpp -I .$(PS)include -o .$(PS)obj$(PS)ProductReview.o 
	g++ -c .$(PS)src$(PS)ListaEncad.cpp -I .$(PS)include -o .$(PS)obj$(PS)ListaEncad.o
	g++ -c .$(PS)src$(PS)List.cpp -I .$(PS)include -o .$(PS)obj$(PS)List.o
	g++ -c .$(PS)src$(PS)Hash.cpp -I .$(PS)include -o .$(PS)obj$(PS)Hash.o
	g++ -c .$(PS)src$(PS)File.cpp -I .$(PS)include -o .$(PS)obj$(PS)File.o
	g++ -c .$(PS)src$(PS)BucketSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)BucketSort.o
	g++ -c .$(PS)src$(PS)MergeSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)MergeSort.o
	g++ -c .$(PS)src$(PS)QuickSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)QuickSort.o
	g++ -c .$(PS)src$(PS)HashProduct.cpp -I .$(PS)include -o .$(PS)obj$(PS)HashProduct.o

myapps_import:
	g++ .$(PS)apps$(PS)main_import.cpp .$(PS)obj$(PS)List.o .$(PS)obj$(PS)File.o .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)Hash.o -I .$(PS)include -o .$(PS)bin$(PS)main_import

myapps_bin:
	g++ .$(PS)apps$(PS)main_bin.cpp .$(PS)obj$(PS)List.o .$(PS)obj$(PS)File.o .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)Hash.o .$(PS)obj$(PS)BucketSort.o .$(PS)obj$(PS)MergeSort.o .$(PS)obj$(PS)HashProduct.o .$(PS)obj$(PS)QuickSort.o  -I .$(PS)include -o .$(PS)bin$(PS)main_bin

clean:
	$(RM) .$(PS)bin$(PS)*
	$(RM) .$(PS)obj$(PS)*

