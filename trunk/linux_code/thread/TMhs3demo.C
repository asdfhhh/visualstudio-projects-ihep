{
// root macro creating an instance of class TMhs3
//		23.02.2000 J.A.
// usage:   	1) start root session;
//		2) execute this macro ".x TMhs3demo.C"; a Canvas opens,
//		the threads start and histograms are drawn
//		3) during the running example,
//   		"threadclass.Threadstart();" and "threadclass.Threadstop()" 
//		may be called interactively from  root interpreter
//		to stop example and restart it again many times
//		4) change instantiation of class to "TThreadframe threadclass;"
//		to see thread actions of base class TThreadframe
//		5) derive your own class from TThreadframe (overwrite
//		methods Func0...Func1) and test it...  

gSystem->Load("/usr/lib/libpthread.so");
gSystem->Load("libThread.so");
gSystem->Load("libTThreadframe.so");
gSystem->Load("libTMhs3.so");
cout << "shared libraries loaded\n"<<endl; 

//TThreadframe threadclass; // instance of thread framework base class
TMhs3 threadclass; // instance of derived thread class runnint mhs3 demo
threadclass.Threadstart();

}

