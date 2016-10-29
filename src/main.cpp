#include <iostream>
#include <QApplication>

#include "mygui.hpp"

using namespace mynamespace;

int main(int argc, char* argv[]) {
  QApplication app(argc, argc + argv);
  MyGui *gui = new MyGui();
  return app.exec();
}
