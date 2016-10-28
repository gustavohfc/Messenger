CC = g++
CFLAGS = -Wall

Messenger: obj/main.o obj/Engine.o obj/Funcionalidades.o obj/Conexao.o obj/Peer.o obj/Linux_UI.o obj/UI_selector.o
	$(CC) obj/* -o Messenger

obj/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o obj/main.o

obj/Engine.o: ../multi_platform/Engine/Engine.cpp ../multi_platform/Engine/Engine.h
	$(CC) $(CFLAGS) -c ../multi_platform/Engine/Engine.cpp -o obj/Engine.o

obj/Funcionalidades.o: ../multi_platform/Funcionalidades/Funcionalidades.cpp ../multi_platform/Funcionalidades/Funcionalidades.h
	$(CC) $(CFLAGS) -c ../multi_platform/Funcionalidades/Funcionalidades.cpp -o obj/Funcionalidades.o

obj/Conexao.o: ../multi_platform/Conexao/Conexao.cpp ../multi_platform/Conexao/Conexao.h
	$(CC) $(CFLAGS) -c ../multi_platform/Conexao/Conexao.cpp -o obj/Conexao.o

obj/Peer.o: ../multi_platform/Peer/Peer.cpp ../multi_platform/Peer/Peer.h
	$(CC) $(CFLAGS) -c ../multi_platform/Peer/Peer.cpp -o obj/Peer.o

obj/Linux_UI.o: Linux_UI/Linux_UI.cpp Linux_UI/Linux_UI.h
	$(CC) $(CFLAGS) -c Linux_UI/Linux_UI.cpp -o obj/Linux_UI.o

obj/UI_selector.o: ../multi_platform/Interfaces/UI_selector/UI_selector.cpp ../multi_platform/Interfaces/UI_selector/UI_selector.h
	$(CC) $(CFLAGS) -c ../multi_platform/Interfaces/UI_selector/UI_selector.cpp -o obj/UI_selector.o





r: clean Messenger

clean:
	rm obj/*