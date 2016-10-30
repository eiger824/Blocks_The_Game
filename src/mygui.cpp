#include <iostream>
#include <QFont>
#include <QMessageBox>
#include "mygui.hpp"
#include "keyvalues.hpp"

namespace mynamespace {

  MyGui::MyGui(bool debug,
	       bool machine,
	       bool timer,
	       QString player,
	       QString player_B,
	       QWidget* parent): QWidget(parent),
				 m_started(false),
				 m_debug(debug),
				 m_machine(machine),
				 m_timer_enabled(timer),
				 m_cnt(0),
				 m_cnt_B(0),
				 m_rem_secs(10),
				 m_wins(0),
				 m_wins_B(0) {
    setFixedSize(600,750);
    setStyleSheet("background-color: grey;");

    m_main_layout = new QVBoxLayout;
    m_main_layout->setAlignment(Qt::AlignCenter);

    m_intro = new QVBoxLayout;
    m_first = new QHBoxLayout;
    m_second = new QHBoxLayout;
    m_third = new QHBoxLayout;
    m_fourth = new QHBoxLayout;

    QPixmap blockimage;
    QLabel *block1  = new QLabel;
    QLabel *block2  = new QLabel;
    QLabel *block3  = new QLabel;
    QLabel *block4  = new QLabel;
    QLabel *block5  = new QLabel;
    QLabel *block6  = new QLabel;
    QLabel *block7  = new QLabel;
    QLabel *block8  = new QLabel;
    QLabel *block9  = new QLabel;
    QLabel *block10 = new QLabel;
    QLabel *block11 = new QLabel;
    QLabel *block12 = new QLabel;
    QLabel *block13 = new QLabel;
    QLabel *block14 = new QLabel;
    QLabel *block15 = new QLabel;
    QLabel *block16 = new QLabel;


    /****************** INFO PANEL  ********************/
    m_info = "Move count: ";
    m_secs = "Remaning: 00:";
    m_move_count = new QLabel(m_info + QString::number(m_cnt));
    m_move_count->setStyleSheet("background-color: yellow; font: arial 8px; color: black;");
    m_move_count->setAlignment(Qt::AlignCenter);
    m_move_count_B = new QLabel(m_info + QString::number(m_cnt_B));
    m_move_count_B->setStyleSheet("background-color: red; font: arial 8px; color: black;");
    m_move_count_B->setAlignment(Qt::AlignCenter);
    m_restart = new QPushButton("Start");
    m_restart->setFocusPolicy(Qt::NoFocus);
    m_restart->setStyleSheet("background-color: white; color: black; font: arial 8px; margin: 2px solid black;");
    m_restart->setFixedWidth(120);
    connect(m_restart, SIGNAL(clicked()), this, SLOT(resetGame()));
    m_remaining = new QLabel(m_secs + QString::number(m_rem_secs));
    m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
    m_remaining->setFixedHeight(50);
    m_remaining->setAlignment(Qt::AlignCenter);
    m_debug_opt = new QCheckBox("Debug enabled");
    m_debug_opt->setFocusPolicy(Qt::NoFocus);
    if (m_debug)
      m_debug_opt->setChecked(true);
    m_timer_opt = new QCheckBox("Timer enabled");
    m_timer_opt->setFocusPolicy(Qt::NoFocus);
    if (m_timer_enabled)
      m_timer_opt->setChecked(true);
    connect(m_debug_opt, SIGNAL(stateChanged(int)), this, SLOT(enableDebug(int)));
    connect(m_timer_opt, SIGNAL(stateChanged(int)), this, SLOT(enableTimer(int)));
    m_scores = new QLabel("Scores\n0\t-\t0");
    m_scores->setStyleSheet("color: white; font: arial 70px;");
    m_scores->setFixedHeight(100);
    m_scores->setAlignment(Qt::AlignCenter);
    m_player = new QLabel("Player 1:");
    m_player_B = new QLabel("Player 2:");
    m_player_edit = new QTextEdit();
    m_player_edit->setFixedHeight(30);
    m_player_edit->setStyleSheet("background-color: white; color: black;");
    m_player_edit->setTabChangesFocus(true);
    if (!player.isEmpty())
      m_player_edit->setText(player);
    m_player_edit_B = new QTextEdit();
    m_player_edit_B->setFixedHeight(30);
    m_player_edit_B->setStyleSheet("background-color: white; color: black;");
    m_player_edit_B->setTabChangesFocus(true);
    if (!player_B.isEmpty())
      m_player_edit_B->setText(player_B);
    /***************************************************/
    
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
    m_first->setSpacing(7);
    
    m_second->addWidget(block5);
    m_second->addWidget(block6);
    m_second->addWidget(block7);
    m_second->addWidget(block8);
    m_second->setSpacing(7);

    m_third->addWidget(block9);
    m_third->addWidget(block10);
    m_third->addWidget(block11);
    m_third->addWidget(block12);
    m_third->setSpacing(7);
    
    m_fourth->addWidget(block13);
    m_fourth->addWidget(block14);
    m_fourth->addWidget(block15);
    m_fourth->addWidget(block16);
    m_fourth->setSpacing(7);

    QHBoxLayout *temp = new QHBoxLayout;
    QHBoxLayout *names = new QHBoxLayout;
    QHBoxLayout *names_B = new QHBoxLayout;
    names->addWidget(m_player);
    names->addWidget(m_player_edit);
    names_B->addWidget(m_player_B);
    names_B->addWidget(m_player_edit_B);
    temp->addWidget(m_move_count);
    temp->addWidget(m_move_count_B);
    m_intro->addWidget(m_scores);
    m_intro->addLayout(names);
    m_intro->addLayout(names_B);
    m_intro->addLayout(temp);
    m_intro->addWidget(m_debug_opt);
    m_intro->addWidget(m_timer_opt);
    m_intro->addWidget(m_remaining);
    m_intro->addWidget(m_restart);
    
    //add widgets to layout
    m_main_layout->addLayout(m_intro);
    m_main_layout->addLayout(m_first);
    m_main_layout->addLayout(m_second);
    m_main_layout->addLayout(m_third);
    m_main_layout->addLayout(m_fourth);
    m_main_layout->setSpacing(10);

    //set layout
    setLayout(m_main_layout);

    //start player
    m_current_player = YELLOW;
    //timer
    m_timer = new QTimer();
    if (m_timer_enabled) {
      connect(m_timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    }
    setWindowTitle(tr("Blocks 1.1 - Santi Pagola 2016"));
    show();
  }
  MyGui::~MyGui() {
    delete m_timer;
    delete m_main_layout;
  }

  void MyGui::keyPressEvent(QKeyEvent *event) {
    if (event->key() == LEFT) {
      //move left
      updateCurrentRow(0);
      info();
      updateLabels();
    } else if (event->key() == RIGHT) {
      //move right
      updateCurrentRow(1);
      info();
      updateLabels();
    } else if (event->key() == UP) {
      //move up
      updateCurrentCol(0);
      info();
      updateLabels();
    } else if (event->key() == DOWN) {
      //move down
      updateCurrentCol(1);
      info();
      updateLabels();
    } else if (event->key() == ESC ||
	       event->key() == ENTER) {
      //stop timer
      if (m_timer_enabled) {
	if (m_timer->isActive()) {
	  m_timer->stop();
	}
      }
      //save locket pos of current player to list
      if (save2list()) {
	if (m_current_player == YELLOW) {
	  ++m_cnt;
	  m_move_count->setText(m_info + QString::number(m_cnt));
	} else {
	  ++m_cnt_B;
	  m_move_count_B->setText(m_info + QString::number(m_cnt_B));
	} 
	info(0, "Locking position (" + m_current_player + "): " + currentPair2String());
	//check if win
	if (checkIfWin()) {
	  QString player;
	  if (m_current_player == YELLOW)
	    player = m_player_edit->toPlainText();
	  else
	    player = m_player_edit_B->toPlainText();
	  QMessageBox::information(this, player + " wins!!",
				   "Close this dialog to start playing again.");
	  if (m_current_player == YELLOW) {
	    ++m_wins;
	  } else {
	    ++m_wins_B;
	  }
	  //update scores label
	  m_scores->setText("Scores\n" + QString::number(m_wins) +
			    "-" + QString::number(m_wins_B));
	  resetGame();
	} else {
	  //switch player and reset position
	  switchPlayer();
	}
      }
    }
  }

  bool MyGui::save2list() {
    if (m_current_player == YELLOW) {
      if (!m_locked_pos.contains(m_current) &&
	  !m_locked_pos_B.contains(m_current)) {
	m_locked_pos << m_current;
	printLocked();
	unsigned int nr = m_locked_pos.size()
	  + m_locked_pos_B.size();
	info(0, "Nr locked positions: "
	     + QString::number(nr));
	if (nr == MAX_ROWS * MAX_COLS) {
	  //stop timer
	  if (m_timer->isActive())
	    m_timer->stop();
	  //reset counter
	  m_rem_secs = 10;
	  m_remaining->setText(m_secs + QString::number(m_rem_secs));
	  m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
	  //and reset game
	  resetGame();
	}
	return true;
      } else {
	QMessageBox::information(this, "Wrong move",
				 "Position is already locked.\nSelect another free position.");
	info(1, "Position exists!!");
	return false;
      }
    } else {

      if (!m_locked_pos.contains(m_current_B) &&
	  !m_locked_pos_B.contains(m_current_B)) {
	m_locked_pos_B << m_current_B;
	printLocked();
	info(0, "Nr locked positions: "
	     + QString::number(m_locked_pos.size()
			       + m_locked_pos_B.size()));
	return true;
      } else {
	info(1, "Position locked.");
	return false;
      }
    }
  }

  void MyGui::updateCurrentCol(int opt) {
    if (m_current_player == YELLOW) {
      if (opt == 1) {
	++m_current.first;
	if (m_current.first == MAX_ROWS)
	  m_current.first = 0;
      } else {
	if (m_current.first > 0)
	  --m_current.first;
	else
	  m_current.first = MAX_ROWS-1;
      }
    } else {
      if (opt == 1) {
	++m_current_B.first;
	if (m_current_B.first == MAX_ROWS)
	  m_current_B.first = 0;
      } else {
	if (m_current_B.first > 0)
	  --m_current_B.first;
	else
	  m_current_B.first = MAX_ROWS-1;
      }
    }
  }

  void MyGui::updateCurrentRow(int opt) {
    if (m_current_player == YELLOW) {
      if (opt == 1) {
	++m_current.second;
	if (m_current.second == MAX_COLS)
	  m_current.second = 0;
      } else {
	if (m_current.second > 0)
	  --m_current.second;
	else
	  m_current.second = MAX_COLS-1;
      }
    } else {
      if (opt == 1) {
	++m_current_B.second;
	if (m_current_B.second == MAX_COLS)
	  m_current_B.second = 0;
      } else {
	if (m_current_B.second > 0)
	  --m_current_B.second;
	else
	  m_current_B.second = MAX_COLS-1;
      }
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
    for (unsigned i=1; i <= MAX_ROWS; ++i) {
      for (unsigned j=0; j< MAX_COLS; ++j) {
	if (!isPosLocked(i-1,j)) { //see if position is free
	  if (checkPos(i-1,j)) { //position indicated by m_current(_B), THAT color is different
	    if (target.load(m_current_player)) {
	      QLabel *target_block =
		qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i)->layout())->itemAt(j)->widget());
	      target_block->setPixmap(target);
	    }
	  } else {
	    if (target.load(QString::fromStdString("blue.png"))) {
	      QLabel *target_block =
		qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i)->layout())->itemAt(j)->widget());
	      target_block->setPixmap(target);
	    }
	  }  
	}
      }
    }
  }

  void MyGui::timerOut() {
    if (m_rem_secs == 1) {
      info(0, "Timeout");
      switchPlayer();
      //reset label
      m_rem_secs = 10;
      m_remaining->setText(m_secs + QString::number(m_rem_secs));
      m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
    } else {
      --m_rem_secs;
      m_remaining->setText(m_secs + "0" + QString::number(m_rem_secs));
      if (m_rem_secs < 5) {
	m_remaining->setStyleSheet("background-color: white; color: red; font: arial 12px;");
      } else {
	m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
      }
    }
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
    if (!m_debug) return;
    if (code == 0)
      std::cout << msg.toStdString() << std::endl;
    else
      std::cerr << msg.toStdString() << std::endl;
  }

  void MyGui::info() {
    if (!m_debug) return;
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
    if (m_timer_enabled) {
      m_rem_secs = 10;
      m_remaining->setText(m_secs + QString::number(m_rem_secs));
      m_timer->start(1000);
      info(0, "Timer started.");
    }
  }

  bool MyGui::isPosLocked(unsigned int x, unsigned int y) {
    if (m_locked_pos.contains(qMakePair(x,y)) ||
	m_locked_pos_B.contains(qMakePair(x,y))) {
      info(0, "Returning true, position found: (" +
	   QString::number(x) + "," + QString::number(y) + ")");
      return true;
    }
    else return false;
  }

  bool MyGui::checkIfWin() {
    /*
      Three "scenarios" must be tested:
      1.) column fill?
      2.) row fill?
      3.) diagonal fill? (iif (i==j || i==3-j))
    */
    unsigned int cnt=0;
    if (m_current_player == YELLOW) {
      //first check column fill
      if (m_locked_pos.contains(qMakePair(m_current.first,(unsigned int)0))) ++cnt;
      if (m_locked_pos.contains(qMakePair(m_current.first,(unsigned int)1))) ++cnt;
      if (m_locked_pos.contains(qMakePair(m_current.first,(unsigned int)2))) ++cnt;
      if (m_locked_pos.contains(qMakePair(m_current.first,(unsigned int)3))) ++cnt;
      info(0, "Column cnt was: " + QString::number(cnt));
      if (cnt==4) return true;
      //reset cnt
      cnt=0;
      //check row fill
      if (m_locked_pos.contains(qMakePair((unsigned int)0, m_current.second))) ++cnt;
      if (m_locked_pos.contains(qMakePair((unsigned int)1, m_current.second))) ++cnt;
      if (m_locked_pos.contains(qMakePair((unsigned int)2, m_current.second))) ++cnt;
      if (m_locked_pos.contains(qMakePair((unsigned int)3, m_current.second))) ++cnt;
      info(0, "Row cnt was: " + QString::number(cnt));
      if (cnt==4) return true;
      //reset cnt
      cnt=0;
      //Now check if diagonal fill is possible
      if (!checkDiag()) {
	return false;
      } else {
	if (m_locked_pos.contains(qMakePair((unsigned int)0, (unsigned int)0))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)1, (unsigned int)1))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)2, (unsigned int)2))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)3, (unsigned int)3))) ++cnt;
	info(0, "Cnt was: " + QString::number(cnt));
	if (cnt==4) return true;
	//reset cnt
	cnt=0;
	//or inverted
	if (m_locked_pos.contains(qMakePair((unsigned int)0, (unsigned int)3))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)1, (unsigned int)2))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)2, (unsigned int)1))) ++cnt;
	if (m_locked_pos.contains(qMakePair((unsigned int)3, (unsigned int)0))) ++cnt;
	info(0, "Cnt was: " + QString::number(cnt));
	if (cnt==4) return true;
	//reset cnt
	cnt=0;
      }
      return false;
    } else {
      //first check column fill
      if (m_locked_pos_B.contains(qMakePair(m_current_B.first,(unsigned int)0))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair(m_current_B.first,(unsigned int)1))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair(m_current_B.first,(unsigned int)2))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair(m_current_B.first,(unsigned int)3))) ++cnt;
      if (cnt==4) return true;
      //reset cnt
      cnt=0;
      //check row fill
      if (m_locked_pos_B.contains(qMakePair((unsigned int)0, m_current_B.second))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair((unsigned int)1, m_current_B.second))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair((unsigned int)2, m_current_B.second))) ++cnt;
      if (m_locked_pos_B.contains(qMakePair((unsigned int)3, m_current_B.second))) ++cnt;
      if (cnt==4) return true;
      //reset cnt
      cnt=0;
      //Now check if diagonal fill is possible
      if (!checkDiag()) {
	return false;
      } else {
	if (m_locked_pos_B.contains(qMakePair((unsigned int)0, (unsigned int)0))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)1, (unsigned int)1))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)2, (unsigned int)2))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)3, (unsigned int)3))) ++cnt;
	info(0, "Cnt was: " + QString::number(cnt));
	if (cnt==4) return true;
	//reset cnt
	cnt=0;
	//or inverted
	if (m_locked_pos_B.contains(qMakePair((unsigned int)0, (unsigned int)3))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)1, (unsigned int)2))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)2, (unsigned int)1))) ++cnt;
	if (m_locked_pos_B.contains(qMakePair((unsigned int)3, (unsigned int)0))) ++cnt;
	if (cnt==4) return true;
	//reset cnt
	cnt=0;
      }
      return false;
    }
  }

  bool MyGui::checkDiag() {
    if (m_current_player == YELLOW) {
      if (m_current.first == m_current.second ||
	  m_current.first == 3 - m_current.second)
	return true;
      else return false;
    } else {
      if (m_current_B.first == m_current_B.second ||
	  m_current_B.first == 3 - m_current_B.second)
	return true;
      else return false;
    }
  }

  void MyGui::printLocked() {
    if (!m_debug) return;
    std::cout << "------------------------\n\tYELLOW PLAYER: \n";
    for (unsigned i=0; i<m_locked_pos.size(); ++i) {
      std::cout << "\t(" << m_locked_pos.at(i).first << ","
		<< m_locked_pos.at(i).second << ")" << std::endl;
    }
    std::cout << "\tRED PLAYER: \n";
    for (unsigned j=0; j<m_locked_pos_B.size();++j) {
      std::cout << "\t(" << m_locked_pos_B.at(j).first << ","
		<< m_locked_pos_B.at(j).second << ")" << std::endl;
    }
    std::cout <<"------------------------\n";
  }

  void MyGui::resetGame() {
    info(0, "Resetting game.");
    QPixmap target;
    for (unsigned i=2; i <= MAX_ROWS; ++i) {
      for (unsigned j=0; j< MAX_COLS; ++j) {
	if (target.load(QString::fromStdString("blue.png"))) {
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i)->layout())->itemAt(j)->widget())->setPixmap(target);
	}
      }
    }
    //reset positions for both
    m_current.first = 0;
    m_current.second = 0;
    m_current_B.first = 0;
    m_current_B.second = 0;

    //empty locked positions
    m_locked_pos.clear();
    m_locked_pos_B.clear();

    //start timer if timer support is enabled
    if (m_timer_enabled) {
      info(0, "timer started");
      m_timer->start(1000);
    }
    //remove focus to edits
    m_player_edit->setEnabled(false);
    m_player_edit_B->setEnabled(false);
  }

  void MyGui::enableDebug(int opt) {
    m_debug = opt;
    info(0, "Debug is: " + QString::number(m_debug));
  }

  void MyGui::enableTimer(int opt) {
    m_timer_enabled = opt;
    if (opt) {
      connect(m_timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    } else {
      disconnect(m_timer, SIGNAL(timeout()), this, SLOT(timerOut()));
      m_rem_secs = 10;
      m_remaining->setText(m_secs + "10");
    }
    info(0, "Timer is: " + QString::number(m_timer_enabled));
  }

} //mynamespace
