
Timber:Pong.o
	g++ Pong.o -o Pong -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system  


Timber.o:Pong.cpp
	g++ -c Pong.cpp
clean:
#cleanup all object file
	  -rm *.o $(objects) 