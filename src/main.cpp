#include <iostream>
#include <QApplication>
#include <string.h>
#include "mygui.hpp"

using namespace mynamespace;

int help(int code) {
  std::cout << "BLOCKS - The Game!\n";
  std::cout << "Developed by Santiago Pagola in Oct. 2016\n";
  std::cout << "USAGE:\n";
  std::cout << "\t-d\tEnable debug messages\n";
  std::cout << "\t-h\tPrint this help and exit\n";
  std::cout << "\t-m\tPlay agains the machine (let's have fun!)\n";
  std::cout << "\t-t\tTimer enabled (10 sec.)\n";
  if (code == 0) {
    return 0;
  } else {
    return -1;
  }
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argc + argv);
  MyGui *gui;
  if (argc==1) {
    gui = new MyGui();
  } else {
    bool debug = false;
    bool machine = false;
    bool timer = false;
    for (unsigned i=1; i < argc; ++i) {
      if (!strcmp(argv[i],"-d")) {
	debug = true;
      } else if (!strcmp(argv[i],"-h")) {
	return help(0);
      } else if (!strcmp(argv[i],"-m")) {
	machine = true;
      } else if (!strcmp(argv[i],"-t")) {
	timer = true;
      } else {
	std::cerr << "Wrong arg. Returning\n";      
	return help(1);
      }
    }
    gui = new MyGui(debug,
		    machine,
		    timer);
  }
  return app.exec();
}
