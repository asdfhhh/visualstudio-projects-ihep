
CC = g++
CPPFLAGS += -I`root-config --incdir`
LDLIBS += `root-config --glibs`
Objects = menu_setup.o viewer.o gui.o about.o main.o daq.o

all: $(Objects) lsi

main.o: main.cc gui.h viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

daq.o: daq.cc daq.h gui.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

gui.o: gui.cc gui.h daq.h about.h menu_setup.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

menu_setup.o: menu_setup.cc daq.h gui.h menu_setup.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

viewer.o: viewer.cc viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

about.o: about.cc about.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

lsi: $(Objects)
	$(CC) $(LDLIBS) $(CPPFLAGS) -o lsi $(Objects) 

clean:
	rm -f lsi *.o
dataclean:
	rm -f *.txt *.root
