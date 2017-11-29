all: OLList_test.exe

OLList_test.exe: OLList_test.o OLList.o
	g++ -o OLList_test.exe OLList_test.o OLList.o

OLList_test.o: OLList_test.cpp
	g++ -c -g -O0 -std=c++11 OLList_test.cpp

OLList.o: OLList.cpp
	g++ -c -g -O0 -std=c++11 OLList.cpp

clean: 
	rm -rf ./*.o ./*.exe ./*.stackdump