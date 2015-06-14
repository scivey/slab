CC=g++
CFLAGS=--std=c++11
INC=-I/usr/include/mysql -I./src
LINK=-lmysqlclient -lmysqlpp -lmicrohttpd

OBJ=$(addprefix ./src/, \
		main.o \
		models.o \
	)

app: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINK)

./src/%.o:./src/%.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

mysql:
	mysql -uroot -pF1b3rFl4k3s cppappdb
