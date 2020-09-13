#2017707007 Minjun_Kang

CC = gcc
TARGET = MyShell
OBJS = MyShell.o UserCmd.o getType.o exe_cmd.o std_DC.o opt_scan.o print.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
.c.o:
	$(CC) -c $<
clean :
	rm -f $(OBJS)
	rm -f $(TARGET)



