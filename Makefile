# C compiler
CC=gcc

# compile-time flags
CFLAGS=-Wall -g

# target exe names
TARGET1=SJF
TARGET2=RR

# build the exes
all:$(TARGET1)
all:$(TARGET2)

# link files into the exes
$(TARGET1): $(TARGET1).c
		$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c 
$(TARGET2): $(TARGET2).c
		$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c 