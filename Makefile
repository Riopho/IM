demo:main.o network.o
	g++ -o demo -g main.o network.o

main.o:main.cpp network.cpp network.h
	g++ -c -g main.cpp

network.o:network.cpp network.h
	g++ -c -g network.cpp

clean:
	rm ./*.o demo
