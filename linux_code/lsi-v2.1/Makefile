CC = g++
CPPFLAGS += -I`root-config --incdir`
LDLIBS += `root-config --glibs`
CCTFLAGS = -I/usr/local/linuxvmeen_util
CCTLIBS = /usr/local/linuxvmeen_util/libcctvmeen.a
Objects = viewer.o gui.o about.o main.o daq.o

lsi: $(Objects)
	$(CC) $(LDLIBS) $(CPPFLAGS) $(CCTFLAGS) -o lsi $(Objects) $(CCTLIBS) 

main.o: main.cpp gui.h viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

daq.o: daq.cpp daq.h gui.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

gui.o: gui.cpp gui.h daq.h about.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

timer.o: timer.cpp timer.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

viewer.o: viewer.cpp viewer.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

about.o: about.cpp about.h
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CCTFLAGS)

objclean:
	-rm $(Objects) 

.PHONY:clean dataclean
clean:
	rm -f lsi *.o
dataclean:
	rm -f *.txt *.root
