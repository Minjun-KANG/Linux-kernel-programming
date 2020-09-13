.SUFFIXES : .c .o

TARGET = main
OBJS = main.o reverse.o  

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
.c .o :
	$(CC) -c $<
dep :
	$(CC) -M $(OBJS.o=.c)
clean:
	rm -r *.o

