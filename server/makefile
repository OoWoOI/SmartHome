.PHONY: all clean

OBJ= ./bin/main.o ./bin/svr.o ./bin/svrConf.o ./bin/svrLog.o ./bin/conf.o ./bin/log.o ./bin/network.o
TARGET= ./bin/server
CFLAGS= -lpthread 

all: $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(OBJ) -o $(TARGET) 

./bin/main.o: 
	gcc -c main.c  -o ./bin/main.o $(CFLAGS)
./bin/svr.o: 
	gcc -c ./src/server.c -o ./bin/svr.o $(CFLAGS)
./bin/svrConf.o: 
	gcc -c ./src/svrConf.c -o ./bin/svrConf.o $(CFLAGS)
./bin/conf.o:
	gcc -c ../common/src/conf.c -o ./bin/conf.o $(CFLAGS)
./bin/svrLog.o: 
	gcc -c ./src/svrLog.c -o ./bin/svrLog.o $(CFLAGS)
./bin/log.o:
	gcc -c ../common/src/log.c -o ./bin/log.o $(CFLAGS)
./bin/network.o:
	gcc -c ../common/src/network.c -o ./bin/network.o $(CFLAGS)
clean:
	rm $(OBJ) $(TARGET)
