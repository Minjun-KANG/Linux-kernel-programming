

CC = gcc
TARGET = mytxt
OBJS = mytxt.o data_MGT.o locks.o

OBJS2 =f_lock.o locks.o
TARGET2 = f_lock


all: $(TARGET) $(TARGET2)


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
mytxt.o : mytxt.c Myheader.h
	$(CC) -c mytxt.c Myheader.h
data_MGT.o : data_MGT.c Myheader.h
	$(CC) -c data_MGT.c Myheader.h
locks.o : locks.c Myheader.h
	$(CC) -c locks.c Myheader.h


$(TARGET2) : $(OBJS2)
	$(CC) -o $@ $(OBJS2)
f_lock.o : f_lock.c Myheader.h
	$(CC) -c f_lock.c Myheader.h

clean :
	rm -r *.o $(TARGET)
	rm -r $(TARGET2)



