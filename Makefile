CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
# DEFS=-DDEBUG

OBJS=amazon.o book.o clothing.o mydatastore.o db_parser.o movie.o product_parser.o product.o user.o util.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h mydatastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp

book.o: book.cpp book.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp

clothing.o: clothing.cpp clothing.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp

mydatastore.o: mydatastore.cpp mydatastore.h datastore.h product.h product_parser.h user.h db_parser.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp

db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp

movie.o: movie.cpp movie.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp

product_parser.o: product_parser.cpp product_parser.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp

product.o: product.cpp product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp

clean:
	rm -f *.o amazon
