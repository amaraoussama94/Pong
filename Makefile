
Pong:Pong.o  Bat.o
	g++ Pong.o Bat.o -o Pong -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


Pong.o:Pong.cpp
	g++ -c Pong.cpp

Bat.o:Bat.cpp
	g++ -c Bat.cpp

clean:
#cleanup all object file
	  -rm *.o $(objects) 