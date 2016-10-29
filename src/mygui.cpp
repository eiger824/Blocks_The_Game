#include <iostream>
#include <QFont>
#include "mygui.hpp"
#include "keyvalues.hpp"

namespace mynamespace {

  MyGui::MyGui(QWidget* parent): QWidget(parent),
				 m_started(false) {
    setFixedSize(600,600);
    setStyleSheet("background-color: grey;");
    
    m_main_layout = new QVBoxLayout;
    m_main_layout->setAlignment(Qt::AlignCenter);

    m_first = new QHBoxLayout;
    m_second = new QHBoxLayout;
    m_third = new QHBoxLayout;
    m_fourth = new QHBoxLayout;

    QPixmap blockimage;
    QLabel *block1 = new QLabel;
    QLabel *block2 = new QLabel;
    QLabel *block3 = new QLabel;
    QLabel *block4 = new QLabel;
    QLabel *block5 = new QLabel;
    QLabel *block6 = new QLabel;
    QLabel *block7 = new QLabel;
    QLabel *block8 = new QLabel;
    QLabel *block9 = new QLabel;
    QLabel *block10 = new QLabel;
    QLabel *block11 = new QLabel;
    QLabel *block12 = new QLabel;
    QLabel *block13 = new QLabel;
    QLabel *block14 = new QLabel;
    QLabel *block15 = new QLabel;
    QLabel *block16 = new QLabel;
    
    if (blockimage.load(YELLOW)) {
      block2->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block1->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block3->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block4->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block5->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block6->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block7->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block8->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block9->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block10->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block11->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block12->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block13->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block14->setPixmap(blockimage);
      info(0, "Loaded block");
    } if (blockimage.load(QString::fromStdString("blue.png"))) {
      block15->setPixmap(blockimage);
      info(0, "Loaded block");
    }
    if (blockimage.load(QString::fromStdString("blue.png"))) {
      block16->setPixmap(blockimage);
      info(0, "Loaded block");
    }
   
    //init current position
    m_current.first = 0;
    m_current.second = 0;

    m_current_B.first = 0;
    m_current_B.second = 0;

    m_first->addWidget(block2);
    m_first->addWidget(block1);
    m_first->addWidget(block3);
    m_first->addWidget(block4);
    
    m_second->addWidget(block5);
    m_second->addWidget(block6);
    m_second->addWidget(block7);
    m_second->addWidget(block8);

    m_third->addWidget(block9);
    m_third->addWidget(block10);
    m_third->addWidget(block11);
    m_third->addWidget(block12);
    
    m_fourth->addWidget(block13);
    m_fourth->addWidget(block14);
    m_fourth->addWidget(block15);
    m_fourth->addWidget(block16);
    
    //add widgets to layout
    m_main_layout->addLayout(m_first);
    m_main_layout->addLayout(m_second);
    m_main_layout->addLayout(m_third);
    m_main_layout->addLayout(m_fourth);

    //set layout
    setLayout(m_main_layout);

    //start player
    m_current_player = YELLOW;
    //timer
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    //m_timer->start(10000);
    info(0, "Timer started.");

    show();
  }
  MyGui::~MyGui() {
    delete m_timer;
    delete m_main_layout;
  }

  void MyGui::keyPressEvent(QKeyEvent *event) {
    if (event->key() == LEFT) {
      //move left
      if (canMove(LEFT)) {
	updateCurrentRow(0);
	info();
	updateLabels();
      }
    } else if (event->key() == RIGHT) {
      //move right
      if (canMove(RIGHT)) {
        updateCurrentRow(1);
	info();
	updateLabels();
      }
    } else if (event->key() == UP) {
      //move up
      if (canMove(UP)) {
	updateCurrentCol(0);
	info();
	updateLabels();
      }
    } else if (event->key() == DOWN) {
      //move down
      if (canMove(DOWN)) {
	updateCurrentCol(1);
	info();
	updateLabels();
      }
    } else if (event->key() == ESC) {
      //save locket pos of current player to list
      save2list();
      info(0, "Locking position (" + m_current_player + "): " + currentPair2String());
      switchPlayer();
    }
  }

  void MyGui::save2list() {
    if (m_current_player == YELLOW) {
      m_locked_pos << m_current;
    } else {
      m_locked_pos_B << m_current_B;
    }
    printLocked();
    info(0, "Nr locked positions: "
	 + QString::number(m_locked_pos.size()
			   + m_locked_pos_B.size()));
  }

  void MyGui::updateCurrentCol(int opt) {
    if (m_current_player == YELLOW) {
      if (opt == 1)
	++m_current.first;
      else
	--m_current.first;
    } else {
      if (opt == 1)
	++m_current_B.first;
      else
	--m_current_B.first;
    }
  }

  void MyGui::updateCurrentRow(int opt) {
    if (m_current_player == YELLOW) {
      if (opt == 1)
	++m_current.second;
      else
	--m_current.second;
    } else {
      if (opt == 1)
	++m_current_B.second;
      else
	--m_current_B.second;
    }
  }

  bool MyGui::checkPos(unsigned int x, unsigned int y) {
    if (m_current_player == YELLOW) {
      if (m_current.first == x &&
	  m_current.second == y) {
	return true;
      } else return false;
    } else {
      if (m_current_B.first == x &&
	  m_current_B.second == y) {
	return true;
      } else return false;
    }
  }

  void MyGui::updateLabels() {
    //switch labels
    QPixmap target;
    for (unsigned i=0; i < MAX_COLS; ++i) {
      for (unsigned j=0; j< MAX_ROWS; ++j) {
	if (!isPosLocked(i,j)) { //see if position is free
	  if (checkPos(j,i)) { //position indicated by m_current(_B), THAT color is different
	    if (target.load(m_current_player)) {
	      qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(j)->layout())->itemAt(i)->widget())->setPixmap(target);
	    }
	  } else {
	    if (target.load(QString::fromStdString("blue.png"))) {
	      qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(j)->layout())->itemAt(i)->widget())->setPixmap(target);
	    }
	  }
	} //end of if (!isPosLocked(i,j))
      }
    }
  }

  void MyGui::timerOut() {
    info(0, "Timeout");
    switchPlayer();
  }

  bool MyGui::canMove(const int key) {
    switch (key) {
    case LEFT:
      if (m_current_player == YELLOW) {
	if (m_current.second == 0) return false;
	else return true;
      } else {
	if (m_current_B.second == 0) return false;
	else return true;
      }
    case RIGHT:
      if (m_current_player == YELLOW) {
	if (m_current.second == MAX_COLS-1) return false;
	else return true;
      } else {
	if (m_current_B.second == MAX_COLS-1) return false;
	else return true;
      }
    case UP:
      if (m_current_player == YELLOW) {
	if (m_current.first == 0) return false;
	else return true;
      } else {
	if (m_current_B.first == 0) return false;
	else return true;
      }    
    case DOWN:
      if (m_current_player == YELLOW) {
	if (m_current.first == MAX_ROWS-1) return false;
	else return true;
      } else {
	if (m_current_B.first == MAX_ROWS-1) return false;
	else return true;
      }
    default:
      return false;
    }
  }
  
  void MyGui::info(const int code, const QString& msg) {
    if (code == 0)
      std::cout << msg.toStdString() << std::endl;
    else
      std::cerr << msg.toStdString() << std::endl;
  }

  void MyGui::info() {
    if (m_current_player == YELLOW)
      std::cout << "Yellow: (" << m_current.first << "," <<
	m_current.second << ")" << std::endl;
    else
      std::cout << "Red: (" << m_current_B.first << "," <<
	m_current_B.second << ")" << std::endl;
  }

  QString MyGui::currentPair2String() {
    if (m_current_player == YELLOW) {
      return QString("(" +
		     QString::number(m_current.first) +
		     "," +
		     QString::number(m_current.second) +
		     ")");
    } else {
      return QString("(" +
		     QString::number(m_current_B.first) +
		     "," +
		     QString::number(m_current_B.second) +
		     ")");
    }
  }
  
  void MyGui::machinePlays() {
    
    //and return control to user
    switchPlayer();
  }

  void MyGui::switchPlayer() {
    if (m_current_player == YELLOW) {
      m_current_player = RED;
      m_current.first = 0;
      m_current.second = 0;
    } else {
      m_current_player = YELLOW;
      m_current_B.first = 0;
      m_current_B.second = 0;
    }
    info(0, "Switching player: " + m_current_player);
  }

  bool MyGui::isPosLocked(unsigned int x, unsigned int y) {
    if (m_locked_pos.contains(qMakePair(x,y)) ||
	m_locked_pos_B.contains(qMakePair(x,y))) {
      info(0, "Returning true, position found");
      return true;
    }
    else return false;
  }

  bool MyGui::checkIfWin() {
    /*
      Three "scenarios" must be tested:
      1.) column fill?
      2.) row fill?
      3.) diagonal fill?
    */
    return true;
  }

  void MyGui::printLocked() {
    std::cout << "\tYELLOW PLAYER: \n";
    for (unsigned i=0; i<m_locked_pos.size(); ++i) {
      std::cout << "\t(" << m_locked_pos.at(i).first << ","
		<< m_locked_pos.at(i).second << ")" << std::endl;
    }
    std::cout << "\tRED PLAYER: \n";
    for (unsigned j=0; j<m_locked_pos_B.size();++j) {
      std::cout << "\t(" << m_locked_pos_B.at(j).first << ","
		<< m_locked_pos_B.at(j).second << ")" << std::endl;
    }
  }
} //mynamespace
