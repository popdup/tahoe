
ARCH = arm

CROSS_DIR =
CROSS_COMPILE	= $(CROSS_DIR)

CC =  $(CROSS_COMPILE)g++
CCP= $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
STRIP=$(CROSS_COMPILE)strip
AR = $(CROSS_COMPILE)ar
AS = $(CROSS_COMPILE)as


SRCS+= \
	main.cpp \
	MyThread.cpp \
	BaseJob.cpp \
	DetailJob.cpp \
	MyWorkThread.cpp \
	MyThreadPool.cpp
		


OBJS = $(SRCS:.cpp=.o)



TARGET=operation

$(TARGET):$(OBJS)
	@echo "Makeing $(TARGET)..."
	$(CC) $(OBJS) -o $(TARGET) $(LIB) -lpthread -D_DEBUG


%.o:%.cpp
	@echo "=======>>Makeing $(CC) -w -c -o $<"
	@$(CC) $(CFLAGS) -c $< -w -o $@


clean:
	rm -f *.o
	
