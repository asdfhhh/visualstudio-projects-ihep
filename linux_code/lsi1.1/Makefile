CC = g++
CPPFLAGS += -I`root-config --incdir`
LDLIBS += `root-config --glibs`
CCTFLAGS = -I/usr/local/linuxvmeen_util
CCTLIBS = /usr/local/linuxvmeen_util/libcctvmeen.a
Objects = menu_setup.o viewer.o gui.o about.o main.o daq.o

all: $(Objects) lsi objclean

main.o: main.cc gui.h viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

daq.o: daq.cc daq.h gui.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

gui.o: gui.cc gui.h daq.h about.h menu_setup.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

menu_setup.o: menu_setup.cc daq.h gui.h menu_setup.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

viewer.o: viewer.cc viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

about.o: about.cc about.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

lsi: $(Objects)
	$(CC) $(LDLIBS) $(CPPFLAGS) $(CCTFLAGS) -o lsi $(Objects) $(CCTLIBS) 

objclean:
	-rm -f *.o
clean:
	rm -f lsi *.o
dataclean:
	rm -f *.txt *.root
