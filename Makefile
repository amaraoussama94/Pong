#main app
Pong:Pong.o  Bat.o Ball.o
	g++ Pong.o Bat.o Ball.o -o Pong -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


Pong.o:Pong.cpp
	g++ -c Pong.cpp

#Bat class 
Bat.o:Bat.cpp
	g++ -c Bat.cpp

#Ball class 
Ball.o:Ball.cpp
	g++ -c Ball.cpp

clean:
#cleanup all object file
	  -rm *.o $(objects) 