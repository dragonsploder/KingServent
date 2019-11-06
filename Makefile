SRCS=   main.cpp \
		room.cpp \
		player.cpp \
		misc.cpp \
		castleGen.cpp \
		data.cpp \
		parser.cpp \
		messages.cpp

KingServent:
	g++ $(SRCS) -o king

.PHONY: KingServent

countLines: 
	find . \( -name "*.cpp" -o -name "*.h" \) | xargs wc -l | sort