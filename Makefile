CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fPIC -Wshadow

INCLUDES = -I$(HOME)/qmodule/segment/include \
           -I$(JAVA_HOME)/include \
           -I$(JAVA_HOME)/include/linux \
           -I$(HOME)/qmodule/qcommon/include \
           -I$(HOME)/qmodule/transcode/include

LIBS = $(HOME)/qmodule/segment/lib/libsegment.a $(HOME)/qmodule/transcode/lib/libtranscode.a

COMMON_OBJS = SegmenterJniImp.o
BINS = libsegmenterjni.so
all : $(BINS)

libsegmenterjni.so: $(COMMON_OBJS)
        $(CXX) $(CFLAGS) -shared -o $@ $^ $(LIBS)

.cpp.o:
        $(CXX) $(CFLAGS) $(INCLUDES) -c $? -o $@

.cc.o:
        $(CXX) $(CFLAGS) $(INCLUDES) -c $? -o $@

.c.o:
        $(CC) $(CFLAGS) $(INCLUDES) -c $? -o $@

clean:
        rm -f *.o $(BINS)
