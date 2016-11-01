#include <iostream>
#include <QApplication>
#include <QString>
#include <string.h>
#include <getopt.h>
#include "mygui.hpp"

using namespace mynamespace;

int help(int code) {
  std::cout << "BLOCKS - The Game!\n";
  std::cout << "Developed by Santiago Pagola in Oct. 2016\n";
  std::cout << "USAGE: blocks [OPTIONS]\n";
  std::cout << "OPTIONS:\n";
  std::cout << "-a <name>  First player's name\n";
  std::cout << "-b <name>  Second player's name\n";
  std::cout << "-d\t\t     Enable debug messages\n";
  std::cout << "-h\t\t     Print this help and exit\n";
  std::cout << "-m <level> Play against the machine (let's have fun!)\n";
  std::cout << "    level: easy, hard\n";
  std::cout << "-t\t\t     Timer enabled (10 sec.)\n";
  if (code == 0) {
    return 0;
  } else {
    return -1;
  }
}

int main(int argc, char* argv[]) {
  std::system("clear");
  QApplication app(argc, argc + argv);
  MyGui *gui;
  if (argc==1) {
    gui = new MyGui();
  } else {
    bool debug = false;
    bool machine = false;
    bool timer = false;
    QString player,player_B,level;
    QStringList levels;
    levels << "easy" << "hard";
    int c;
    while ((c = getopt(argc, argv, "dhta:b:m:")) != -1) {
      switch (c) {
      case 'a':
	player = QString::fromStdString(optarg);
	break;
      case 'b':
	player_B = QString::fromStdString(optarg);
	break;
      case 'd':
	debug = true;
	break;
      case 'h':
	return help(0);
      case 'm':
	machine = true;
	level = QString::fromStdString(optarg);
	if (!levels.contains(level)) {
	  std::cerr << "Wrong level: \"" << optarg << "\". Returning\n";
	  return help(1);
	}
	break;
      case 't':
	timer = true;
	break;
      default:
	std::cerr << "Wrong arg. Returning\n";      
	return help(1);
      }
    }
    gui = new MyGui(debug,
		    machine,
		    level,
		    timer,
		    player,
		    player_B);
  }
  return app.exec();
}
