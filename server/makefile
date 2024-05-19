.PHONY: all clean

OBJ= ./bin/main.o ./bin/svr.o ./bin/svrconf.o ./bin/svrlog.o ./bin/conf.o ./bin/log.o ./bin/network.o
TARGET= ./bin/server
CFLAGS= -lpthread 

all: $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(OBJ) -o $(TARGET) 

./bin/main.o: 
	gcc -c main.c  -o ./bin/main.o $(CFLAGS)
./bin/svr.o: 
	gcc -c ./src/server.c -o ./bin/svr.o $(CFLAGS)
./bin/svrconf.o: 
	gcc -c ./src/svrconf.c -o ./bin/svrconf.o $(CFLAGS)
./bin/conf.o:
	gcc -c ../common/src/conf.c -o ./bin/conf.o $(CFLAGS)
./bin/svrlog.o: 
	gcc -c ./src/svrlog.c -o ./bin/svrlog.o $(CFLAGS)
./bin/log.o:
	gcc -c ../common/src/log.c -o ./bin/log.o $(CFLAGS)
./bin/network.o:
	gcc -c ../common/src/network.c -o ./bin/network.o $(CFLAGS)
clean:
	rm $(OBJ) $(TARGET)
