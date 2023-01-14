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
	g++ -c .$(PS)src$(PS)ListaEncadProductReview.cpp -I .$(PS)include -o .$(PS)obj$(PS)ListaEncadProductReview.o
	g++ -c .$(PS)src$(PS)List.cpp -I .$(PS)include -o .$(PS)obj$(PS)List.o
	g++ -c .$(PS)src$(PS)Hash.cpp -I .$(PS)include -o .$(PS)obj$(PS)Hash.o
	g++ -c .$(PS)src$(PS)File.cpp -I .$(PS)include -o .$(PS)obj$(PS)File.o
	g++ -c .$(PS)src$(PS)BucketSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)BucketSort.o
	g++ -c .$(PS)src$(PS)MergeSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)MergeSort.o
	g++ -c .$(PS)src$(PS)QuickSort.cpp -I .$(PS)include -o .$(PS)obj$(PS)QuickSort.o
	g++ -c .$(PS)src$(PS)HashProduct.cpp -I .$(PS)include -o .$(PS)obj$(PS)HashProduct.o
	g++ -c .$(PS)src$(PS)ArvoreVP.cpp -I .$(PS)include -o .$(PS)obj$(PS)ArvoreVP.o
	g++ -c .$(PS)src$(PS)HuffmanCoding.cpp -I .$(PS)include -o .$(PS)obj$(PS)HuffmanCoding.o
	g++ -c .$(PS)src$(PS)LZ77Coding.cpp -I .$(PS)include -o .$(PS)obj$(PS)LZ77Coding.o

depB:
	g++ -c .$(PS)src$(PS)ProductReview.cpp -I .$(PS)include -o .$(PS)obj$(PS)ProductReview.o
	g++ -c .$(PS)src$(PS)NoB.cpp -I .$(PS)include -o .$(PS)obj$(PS)NoB.o
	g++ -c .$(PS)src$(PS)ArvoreB.cpp -I .$(PS)include -o .$(PS)obj$(PS)ArvoreB.o

extends:
	g++ .$(PS)apps$(PS)extends_main.cpp .$(PS)obj$(PS)List.o .$(PS)obj$(PS)File.o .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)Hash.o .$(PS)obj$(PS)MergeSort.o	.$(PS)obj$(PS)QuickSort.o .$(PS)obj$(PS)BucketSort.o .$(PS)obj$(PS)ListaEncadProductReview.o .$(PS)obj$(PS)HashProduct.o .$(PS)obj$(PS)HuffmanCoding.o .$(PS)obj$(PS)LZ77Coding.o -I .$(PS)include -o .$(PS)bin$(PS)extends_main		

myapps:
	g++ .$(PS)apps$(PS)main.cpp .$(PS)obj$(PS)List.o .$(PS)obj$(PS)File.o .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)Hash.o .$(PS)obj$(PS)MergeSort.o	.$(PS)obj$(PS)QuickSort.o .$(PS)obj$(PS)BucketSort.o .$(PS)obj$(PS)ListaEncadProductReview.o .$(PS)obj$(PS)HashProduct.o .$(PS)obj$(PS)HuffmanCoding.o .$(PS)obj$(PS)LZ77Coding.o -I .$(PS)include -o .$(PS)bin$(PS)main		

vp:
	g++ .$(PS)apps$(PS)mainVP.cpp .$(PS)obj$(PS)List.o .$(PS)obj$(PS)File.o .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)Hash.o .$(PS)obj$(PS)MergeSort.o	.$(PS)obj$(PS)QuickSort.o .$(PS)obj$(PS)BucketSort.o .$(PS)obj$(PS)ListaEncadProductReview.o .$(PS)obj$(PS)HashProduct.o .$(PS)obj$(PS)ArvoreVP.o .$(PS)obj$(PS)HuffmanCoding.o -I .$(PS)obj$(PS)LZ77Coding.o -I .$(PS)include -o .$(PS)bin$(PS)mainVP		

ab:
	g++ .$(PS)apps$(PS)mainB.cpp .$(PS)obj$(PS)ProductReview.o .$(PS)obj$(PS)NoB.o .$(PS)obj$(PS)ArvoreB.o -I .$(PS)include -o .$(PS)bin$(PS)mainB		

clean:
	$(RM) .$(PS)bin$(PS)*
	$(RM) .$(PS)obj$(PS)*

