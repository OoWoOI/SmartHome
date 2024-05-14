.PHONY: clean

OBJ=./bin/svr.o ./bin/svrconf.o ./bin/network.o ./bin/svrlog.o ./bin/log.o ./bin/conf.o ./bin/ioctl.o

all : svr.o svrlog.o svrconf.o log.o conf.o ioctl.o network.o 
	gcc main.c ${OBJ} -o ./bin/server

svr.o : svrconf.o svrlog.o 
	gcc -c ./src/Server.c  -o ./bin/svr.o

svrconf.o: conf.o
	gcc -c ./src/ServerConf.c  -o ./bin/svrconf.o

conf.o : 
	gcc -c ./common/src/Conf.c  -o ./bin/conf.o

svrlog.o: log.o 
	gcc -c ./src/ServerLog.c  -o ./bin/svrlog.o

log.o : 
	gcc -c ./common/src/Log.c -o ./bin/log.o

ioctl.o: 
	gcc -c ./common/src/IoCtl.c -o ./bin/ioctl.o

network.o :
	gcc -c ./common/src/NetWork.c -o ./bin/network.o
	
clean:
	rm -rf ./bin/*.o ./bin/server 

