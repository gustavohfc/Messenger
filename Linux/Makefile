all: main.cpp ../multi_platform/Engine.cpp ../multi_platform/Engine.h ../multi_platform/Funcionalidades.cpp ../multi_platform/Funcionalidades.h
	g++ -o obj/main.o -c main.cpp -Wall
	g++ -o obj/engine.o -c ../multi_platform/Engine.cpp -Wall
	g++ -o obj/funcionalidades.o -c ../multi_platform/Funcionalidades.cpp -Wall
	g++ -o Messenger obj/main.o obj/engine.o obj/funcionalidades.o