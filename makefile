main: ObjektinisProgramavimas2.o Funkcijos.o
    g++ -o main ObjektinisProgramavimas2.o Funkcijos.o
ObjektinisProgramavimas.o: ObjektinisProgramavimas2.cpp
    g++ -c ObjektinisProgramavimas2.cpp
Funkcijos.o: Funkcijos.cpp
    g++ -c Funkcijos.cpp
clean:
    rm *.o main
