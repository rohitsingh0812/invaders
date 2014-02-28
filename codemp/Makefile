#
# sample makefile
#

#
# The following directives let make know that you may be using files
# with a cpp extension.
#

.SUFFIXES: .cpp 

#
# You may have to set the directories so that are appropiate for
# your account.
#

CC       = g++

# EZWINDIR = /users/courses/cs101/public_html/Demos/EzWindows/EzWindows

# If you downloaded EzWindows to your local machine, use the following
# definition instead of the above; delete the above 
# definition of EZWINDIR, and uncomment the following line
#
EZWINDIR = ../../EzWindows

X11DIR   = /usr/X11R6

# The CPPFLAGS macro lets the compiler know where to find include files

CPPFLAGS=-I$(X11DIR)/include -I$(EZWINDIR)/include

# The LDFLAGS macro lets the linker know where to find library files

# LDFLAGS=-L$(X11DIR)/lib -lX11 -L$(EZWINDIR)/lib -lezwin  -lXpm
LDFLAGS=-L$(X11DIR)/lib -lX11 -L$(EZWINDIR)/lib -lezwin /usr/lib/libXpm.so.4 


# The OBJS macro tells the compiler which object files need to be present
# to link your program into an executable.
# For every C++ file you use in your program, add a file.o here.
#
# The following sequence of commands defines a target for the program
# executable.  Replace both occurrences of sample1 here by the name you 
# want to use for your executable program
#
#g1 : *.cpp *.h
#	$(CC) -c invaders.cpp $(CPPFLAGS) $(LDFLAGS)
#gameinvaders2: invaders.cpp functions.h variables.h extern.h inclusion.h classes.h inclusionparts.h startup.cpp
#	$(CC) -o gameinvaders2 invaders.cpp startup.cpp $(CPPFLAGS) $(LDFLAGS)
#g2 : *.cpp *.h
#	$(CC) -c startup.cpp $(CPPFLAGS) $(LDFLAGS)
#g3 : *.cpp *.h
#	$(CC) -c iofunctions.cpp $(CPPFLAGS) $(LDFLAGS)

game : *.cpp *.h
	$(CC) -c *.cpp $(CPPFLAGS)
gameinv : *.cpp *.h *.o
	$(CC) -o gameinv *.o $(LDFLAGS)
.cpp.o:
	$(CC) $(CPPFLAGS) -c $< 
clean:
	rm -f *.o *~
