CC = gcc
OBJS = main.o data_MGT.o
TARGET = test

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o : main.c
	$(CC) -c main.c 

data_MGT.o : data_MGT.c
	gcc -c data_MGT.c

clean :
	rm -r *.o $(TARGET)

