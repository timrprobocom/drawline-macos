# This is a GNU make Makefile.  It's not generally possible to have a single
# makefile work in GNU make and nmake.
#

DEBUG = 1
INCS = 
CPPFLAGS = 

ifndef windir

# Linux and MacOS

UNAME = $(shell uname -s)
INCS += -I/usr/local/include  
LIBS = 
ifeq ($(UNAME),Linux)
INCS +=
LIBS += 
XTRA = Linux
else
LIBS := $(LIBS)
endif

ifdef DEBUG
CPPFLAGS += -g
endif
CPPFLAGS += --std=c++11 $(shell wx-config --cppflags)
ifeq ($(shell uname),Linux)
LDFLAGS = 
else
LDFLAGS = -lc++
CPPFLAGS += -Wno-potentially-evaluated-expression
endif
LIBS += $(shell wx-config --libs) 
LDFLAGS += -Wl,-rpath,$(IPPROOT)/lib
OUTPUT_OPTION = -o $@
LINK = g++ -o 

EXE = 
O = o

else

# Windows

WX = C:\Data\wx\wxWidgets
INCS += /I$(WX)\include /I$(WX)\include\msvc
LIBS = advapi32.lib 
CPPFLAGS := $(CPPFLAGS) /EHsc /DUNICODE /D_UNICODE /D_WIN32_WINNT=0x0600 $(INCS)
LDFLAGS = /libpath:$(WX)\lib\vc_x64_lib
OUTPUT_OPTION = /c /Fo$@
ifdef DEBUG
CPPFLAGS += /MDd /Od /Zi
LDFLAGS += /debug
else
CPPFLAGS += /MD
endif
CXX = cl
LINK = link /out:

EXE = .exe
O = obj

%.$O: %.cpp
	cl $(CPPFLAGS) $(OUTPUT_OPTION) $<

endif

CPPFLAGS := $(INCS) $(CPPFLAGS)
OBJS = \
	MainFrame.$O

all:    Example$(EXE)

Example$(EXE):      $(OBJS)
	$(LINK)$@ $(LDFLAGS) $(OBJS) $(LIBS)


clean:
	rm -f $(OBJS) Example$(EXE)

