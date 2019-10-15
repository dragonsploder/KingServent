SRCS=   main.cpp \
		room.cpp \
		player.cpp \
		misc.cpp \
		castleGen.cpp \
		data.cpp \
		parser.cpp

KingServent:
	g++ $(SRCS) -o king

.PHONY: KingServent