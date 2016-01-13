CPPFLAGS = -std=c++11 -Wall -Wextra -Wvla -pthread -O -DNDEBUG
HEADERS = DimensionsMismatchException.hpp NonSquareMatrixException.hpp MatrixException.hpp


TARNAME=ex3.tar
TARFILES=Matrix.hpp Makefile README

.SUFFIXES:

Matrix: Matrix.hpp.gch

Matrix.hpp.gch:Matrix.hpp $(HEADERS)
	$(CXX) $(CPPFLAGS) -x c++-header $<

tar: 
	tar cvf ex3.tar Matrix.hpp NotCompatibleDimensionsException.hpp \
	NotSquareMatrixException.hpp OutOfMatrixLimitsException.hpp README Makefile
	

clean:
	rm -rf *.gch $(TARNAME)

.PHONY: clean
	
.DEFAULT_GOAL := Matrix.hpp.gch
