
EXEC = tinyXmlExample
OBJS = tinyXmlExample.o
LDFLAGS = -L$(ROOTDIR)/lib/libtinyxml
EXTERN_LIBS += -ltinyxml
CXXFLAGS += -g $(CFLAGS) -I$(ROOTDIR)/lib/libtinyxml
INCLUDE=-I$(ROOTDIR)/lib/libtinyxml


all: $(EXEC)


$(EXEC): $(OBJS)
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC) $(OBJS) $(EXTERN_LIBS) $(STD_LIBS)


myparser: myparser.o
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -o myparser myparser.o $(EXTERN_LIBS) $(STD_LIBS)
