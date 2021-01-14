#2017707007 Minjun_Kang

CC = gcc
TARGET = Producer
TARGET2 = Consumer
OBJS = Producer.o
OBJS2 = Consumer.o

all: $(TARGET) $(TARGET2)

$(TARGET): $(OBJS)
	$(CC) $(TARGET).c -o $(TARGET) -lrt

$(TARGET2): $(OBJS2)
	$(CC) $(TARGET2).c -o $(TARGET2) -lrt

.c:
	$(CC) -c $<
clean :
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(OBJS2)
	rm -f $(TARGET2)



