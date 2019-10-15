SRCS=   main.cpp \
		room.cpp \
		player.cpp \
		misc.cpp \
		castleGen.cpp \
		data.cpp 

KingServent:
	g++ $(SRCS) -o king

.PHONY: KingServent