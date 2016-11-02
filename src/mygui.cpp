#include <iostream>
#include <QFont>
#include <QMessageBox>
#include "mygui.hpp"
#include "keyvalues.hpp"

namespace mynamespace {

  MyGui::MyGui(bool debug,
	       bool machine,
	       QString level,
	       bool timer,
	       QString player,
	       QString player_B,
	       QWidget* parent): QWidget(parent),
				 m_started(false),
				 m_my_turn(true),
				 m_debug(debug),
				 m_machine(machine),
				 m_level(level),
				 m_timer_enabled(timer),
				 m_cnt(0),
				 m_cnt_B(0),
				 m_rem_secs(10),
				 m_wins(0),
				 m_wins_B(0) {
    setFixedSize(650,750);
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
    connect(m_player_edit, SIGNAL(textChanged()), this, SLOT(limitChar()));
    m_player_edit->setFixedHeight(30);
    m_player_edit->setStyleSheet("background-color: white; color: black;");
    m_player_edit->setTabChangesFocus(true);
    if (!player.isEmpty())
      m_player_edit->setText(player);
    m_player_edit_B = new QTextEdit();
    connect(m_player_edit_B, SIGNAL(textChanged()), this, SLOT(limitChar()));
    m_player_edit_B->setFixedHeight(30);
    m_player_edit_B->setStyleSheet("background-color: white; color: black;");
    m_player_edit_B->setTabChangesFocus(true);
    if (!player_B.isEmpty())
      m_player_edit_B->setText(player_B);
    if (m_machine) {
      m_player_edit_B->setEnabled(false);
      m_player_edit_B->setStyleSheet("background-color: grey; color: white;");
      m_player_edit_B->setText("Machine. Level: " + m_level);
      info(0, "Selected level: " + m_level);
    }
    /***************************************************/
    
    if (blockimage.load(YELLOW)) {
      block2->setPixmap(blockimage);
      info(0, "Loaded initial block");
    }
    if (blockimage.load(PREFIX+QString::fromStdString("blue.png"))) {
      block1->setPixmap(blockimage);
      block3->setPixmap(blockimage);
      block4->setPixmap(blockimage);
      block5->setPixmap(blockimage);
      block6->setPixmap(blockimage);
      block7->setPixmap(blockimage);
      block8->setPixmap(blockimage);
      block9->setPixmap(blockimage);
      block10->setPixmap(blockimage);
      block11->setPixmap(blockimage);
      block12->setPixmap(blockimage);
      block13->setPixmap(blockimage);
      block14->setPixmap(blockimage);
      block15->setPixmap(blockimage);
      block16->setPixmap(blockimage);
      info(0, "Loaded ordinary blocks");
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
    //animation timer
    m_animation_timer = new QTimer();
    connect(m_animation_timer, SIGNAL(timeout()), this, SLOT(animationTimerOut()));
    m_animation_timer->start(1000 / 3);
    setWindowTitle(tr("Blocks 1.1 - Santi Pagola 2016"));
    show();
  }
  MyGui::~MyGui() {
    delete m_block;
    delete m_timer;
    delete m_animation_timer;
    delete m_main_layout;
    delete m_intro;
    delete m_first;
    delete m_second;
    delete m_third;
    delete m_fourth;
    delete m_move_count;
    delete m_move_count_B;
    delete m_restart;
    delete m_remaining;
    delete m_debug_opt;
    delete m_timer_opt;
    delete m_scores;
    delete m_player;
    delete m_player_B;
    delete m_player_edit;
    delete m_player_edit_B;
  }

  void MyGui::keyPressEvent(QKeyEvent *event) {
    if (m_machine && !m_my_turn) return;
    if (m_animation_timer->isActive()) {
      if (!BLACKLIST.contains(event->key())) {
	m_animation_timer->stop();
	resetGame();
	return;
      } else {
	info(1, "Wrong key. Returning.");
      }
    } else {
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
	  
	    if (!m_animation_timer->isActive()) {
	      m_animation_timer->start(1000 / 3);
	    }
	  
	    QMessageBox::information(this, player + " wins!!",
				     "Close this dialog and press any key to start playing again.");
	    if (m_current_player == YELLOW) {
	      ++m_wins;
	    } else {
	      ++m_wins_B;
	    }
	    //update scores label
	    m_scores->setText("Scores\n" + QString::number(m_wins) +
			      "-" + QString::number(m_wins_B));
	    m_rem_secs = 10;
	    m_remaining->setText(m_secs + QString::number(m_rem_secs));
	    m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
	  } else {
	    //switch player and reset position
	    switchPlayer();
	    if (m_machine) {
	      info(0, "Machine is playing.");
	      m_my_turn = false;
	      machinePlays();
	    }
	  }
	}
      }
    }
  }

  bool MyGui::save2list() {
    QPixmap target;
    if (m_current_player == YELLOW) {
      if (!m_locked_pos.contains(m_current) &&
	  !m_locked_pos_B.contains(m_current)) {
	m_locked_pos << m_current;
	//substitute "selected" view with normal view
	if (target.load(PREFIX+"yellow.png")) {
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(m_current.first+1)->layout())
				->itemAt(m_current.second)->widget())->setPixmap(target);
	}
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
	info(1, "Position locked.");
	return false;
      }
    } else {
      if (!m_locked_pos.contains(m_current_B) &&
	  !m_locked_pos_B.contains(m_current_B)) {
	m_locked_pos_B << m_current_B;
	if (target.load(PREFIX+"red.png")) {
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(m_current_B.first+1)->layout())
				->itemAt(m_current_B.second)->widget())->setPixmap(target);
	}
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
    // fill all blue
    for (unsigned i=0; i < MAX_ROWS; ++i) {
      for (unsigned j=0; j < MAX_COLS; ++j) {
	if (target.load(PREFIX+QString::fromStdString("blue.png"))) {
	  QLabel *target_block =
	    qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i+1)->layout())->itemAt(j)->widget());
	  target_block->setPixmap(target);
	}
      }
    }
    // fill yellow positions
    for (unsigned i=0; i < m_locked_pos.size(); ++i) {
      if (target.load(PREFIX+"yellow.png")) {
	QLabel *target_block =
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(m_locked_pos.at(i).first+1)->layout())->itemAt(m_locked_pos.at(i).second)->widget());
	target_block->setPixmap(target);
      }
    }
    //fill red positions
    for (unsigned i=0; i < m_locked_pos_B.size(); ++i) {
      if (target.load(PREFIX+"red.png")) {
	QLabel *target_block =
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(m_locked_pos_B.at(i).first+1)->layout())->itemAt(m_locked_pos_B.at(i).second)->widget());
	target_block->setPixmap(target);
      }
    }
    //and fill the current one
    for (unsigned i=0; i < MAX_ROWS; ++i) {
      for (unsigned j=0; j < MAX_COLS; ++j) {
	if (checkPos(i,j)) { //position indicated by m_current(_B), THAT color is different
	  if (target.load(m_current_player)) {
	    QLabel *target_block =
	      qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i+1)->layout())->itemAt(j)->widget());
	    target_block->setPixmap(target);
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
    /*
     Two things must be taken into consideration:
       1.) Ruin your oponent! 
       2.) Make your move
    */
    //first, check one available position
    unsigned int x = 0;
    unsigned int y = 0;
    bool found;
    int which;
    unsigned int n;
    if (m_level == EASY) {
      do {
	x = rand() % 4;
	y = rand() % 4;
      } while (isPosLocked(x,y));
    } else {
      found = false;
      //1.) Ruin your oponent
      //See if player1 is about/on the way to make a win-move
      if (isPossibleWin(which,n)) { //possible win for yellow
	info(0, "*** POSSIBLE WIN ON ***[YELLOW]\n -> Diag(2)/Col(1)/Row(0): "
	     + QString::number(which));
	info(0, " -> Nr.: " + QString::number(n) + "\n***********************");
	if (which == 1) {
	  //machine will cut the column 'n'
	  for (unsigned i=0; i < MAX_ROWS; ++i) {
	    if (!isPosLocked(i,n)) {
	      x = i;
	      y = n;
	      found = true;
	      break;
	    }
	  }
	} else if (which == 0) {
	  //machine will cut the row 'n'
	  for (unsigned i=0; i < MAX_COLS; ++i) {
	    if (!isPosLocked(n,i)) {
	      x = n;
	      y = i;
	      found = true;
	      break;
	    }
	  }
	} else { //2
	  //machine will cut the diagonal +/- according to 'n'
	  if (n == 0) {
	    for (unsigned i=0; i< MAX_ROWS; ++i) {
	      if (!isPosLocked(i,i)) {
		x = i;
		y = i;
		found = true;
		break;
	      }
	    }
	  } else {
	    for (unsigned i=0; i< MAX_ROWS; ++i) {
	      if (!isPosLocked(i,MAX_ROWS-1-i)) {
		x = i;
		y = MAX_ROWS-1-i;
		found = true;
		break;
	      }
	    }
	  }
	}
      } else {
	//2.) Make your move
	if (isPossibleWin(which,n,true)) { //possible win for machine
	  info(0, "*** POSSIBLE WIN ON ***[machine]\n -> Diag(2)/Col(1)/Row(0): "
	       + QString::number(which));
	  info(0, " -> Nr.: " + QString::number(n) + "\n***********************");
	  if (which == 1) {
	    for (unsigned i=0; i < MAX_ROWS; ++i) {
	      if (!isPosLocked(i,n)) {
		x = i;
		y = n;
		found = true;
		break;
	      }
	    }
	  } else if (which == 0) {
	    for (unsigned i=0; i < MAX_COLS; ++i) {
	      if (!isPosLocked(n,i)) {
		x = n;
		y = i;
		found = true;
		break;
	      }
	    }
	  } else {
	    //machine will cut the diagonal +/- according to 'n'
	    if (n == 0) {
	      for (unsigned i=0; i< MAX_ROWS; ++i) {
		if (!isPosLocked(i,i)) {
		  x = i;
		  y = i;
		  found = true;
		  break;
		}
	      }
	    } else {
	      for (unsigned i=0; i< MAX_ROWS; ++i) {
		if (!isPosLocked(i,MAX_ROWS-1-i)) {
		  x = i;
		  y = MAX_ROWS-1-i;
		  found = true;
		  break;
		}
	      }
	    }
	  }
	} else {
	  //First try edges
	  for (unsigned i=0; i<= MAX_ROWS; i+= 3) {
	    for (unsigned j=0; j<=MAX_COLS; j+=3) {
	      if (!isPosLocked(i,j)) {
		x = i;
		y = j;
		found = true;
		break;
	      }
	    }
	  }
	  //Retrieve last pair from oponent
	  QPair<unsigned int, unsigned int>pair = m_locked_pos.last();
	  if ( !found) {
	    //check if there are some free places in current column/row
	    //first check row
	    for (unsigned i=0; i<MAX_ROWS; ++i) {
	      if (!isPosLocked(pair.first,i)) {
		x = pair.first;
		y = i;
		found = true;
		break;
	      }
	    }
	  }
	  if (!found) {
	    //then check col
	    for (unsigned i=0; i<MAX_COLS; ++i) {
	      if (!isPosLocked(i, pair.second)) {
		x = i;
		y = pair.second;
		found = true;
		break;
	      }
	    }
	  }
	  //if none of the above possible, just find any of the available
	  if ((m_locked_pos.size() +
	       m_locked_pos_B.size()) < (MAX_ROWS * MAX_COLS)) {
	    for (unsigned i=0; i<MAX_COLS; ++i) {
	      for (unsigned j=0; j<MAX_ROWS; ++j) {
		if (!isPosLocked(i,j)) {
		  x = i ;
		  y = j;
		  found = true;
		  break;
		}
	      }
	    }
	  } else {
	    //stop timer
	    if (m_timer->isActive())
	      m_timer->stop();
	    //and reset game
	    resetGame();
	  }
	}
      }
    }
    info(0, "[machine]Going to try position: ["
	 + QString::number(x) + ","
	 + QString::number(y) + "]");
    //Extra check
    if (isPosLocked(x,y)) {
      info(1, "Position was already locked.\nReturning.");
      switchPlayer();
      return;
    }
    //update coordinates
    m_current_B.first = x;
    m_current_B.second = y;
    //set block there
    QPixmap target;
    if (target.load(m_current_player)) {
      qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(x+1)->layout())
			    ->itemAt(y)->widget())->setPixmap(target);
    }
    info(0, "Locking position (" + m_current_player + "): "
	 + QString::number(x) + ","
	 + QString::number(y));
    //save position
    if (m_current_player == YELLOW) {
      m_locked_pos.append(qMakePair(x,y));
      ++m_cnt;
      m_move_count->setText(m_info + QString::number(m_cnt));
    } else {
      m_locked_pos_B.append(qMakePair(x,y));
      ++m_cnt_B;
      m_move_count_B->setText(m_info + QString::number(m_cnt_B));
    }

    if (checkIfWin()) {
      QString player;
      if (m_current_player == YELLOW)
	player = m_player_edit->toPlainText();
      else
	player = m_player_edit_B->toPlainText();
      if (!m_animation_timer->isActive()) {
	m_animation_timer->start(1000 / 3);
      }
      QMessageBox::information(this, player + " wins!!",
			       "Close this dialog and press any key to start playing again.");
      if (m_current_player == YELLOW) {
	++m_wins;
      } else {
	++m_wins_B;
      }
      //update scores label
      m_scores->setText("Scores\n" + QString::number(m_wins) +
			"-" + QString::number(m_wins_B));
      if (m_timer->isActive())
	m_timer->stop();
      
      m_rem_secs = 10;
      m_remaining->setText(m_secs + QString::number(m_rem_secs));
      m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
    } else {
      //and return control to user
      switchPlayer();
      m_my_turn = true;
      //if max reached, reset
      unsigned int nr = m_locked_pos.size()
	+ m_locked_pos_B.size();
      if (nr == MAX_ROWS * MAX_COLS) {
	//stop timer
	if (m_timer->isActive())
	  m_timer->stop();
	//and reset game
	resetGame();
      }
    }
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
      m_my_turn = true;
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
    for (unsigned i=i; i <= MAX_ROWS; ++i) {
      for (unsigned j=0; j< MAX_COLS; ++j) {
	if (target.load(PREFIX+QString::fromStdString("blue.png"))) {
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i)->layout())->itemAt(j)->widget())->setPixmap(target);
	}
      }
    }
    update();
    //reset positions for both
    m_current.first = 0;
    m_current.second = 0;
    m_current_B.first = 0;
    m_current_B.second = 0;

    //empty locked positions
    m_locked_pos.clear();
    m_locked_pos_B.clear();

    //stop animation timer
    if (m_animation_timer->isActive()) {
      m_animation_timer->stop();
      //disconnect(m_animation_timer, SIGNAL(timeout()), this, SLOT(animationTimerOut()));
    }
    
    //start timer if timer support is enabled
    if (m_timer_enabled) {
      info(0, "timer started");
      m_timer->start(1000);
    }
    //remove focus to edits
    m_player_edit->setEnabled(false);
    m_player_edit_B->setEnabled(false);
    //my turn again
    m_my_turn = true;
    //reset counter
    m_rem_secs = 10;
    m_remaining->setText(m_secs + QString::number(m_rem_secs));
    m_remaining->setStyleSheet("background-color: white; color: black; font: arial 12px;");
    //change user to YELLOW
    m_current_player = YELLOW;
    //reset move count
    m_cnt = 0;
    m_cnt_B = 0;
    m_move_count->setText(m_info + QString::number(m_cnt));
    m_move_count_B->setText(m_info + QString::number(m_cnt_B));

    //and update labels
    updateLabels();
  }

  bool MyGui::isPossibleWin(int &which, unsigned int &nr, bool me) {
    //function that will check if players YELLOW or machine are on the way to win
    /* 
       "which" will be assigned either:
          0: if possible win on row
	  1: if possible win on column
	  2: if possible win on diagonal
     */
    //check columns
    unsigned cnt=0;
    if (!me) { //possible win for YELLOW player
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	for (unsigned j=0; j<MAX_COLS; ++j) {
	  if (m_locked_pos.contains(qMakePair(j,i))) {
	    ++cnt;
	  } else if (m_locked_pos_B.contains(qMakePair(j,i))) {
	    info(0, "[warning]Column "
		 + QString::number(i)
		 + " already taken by machine, skipping line...");
	    cnt = 0;
	    break;
	  }
	} //--> end of column 
	//when column i is completed, compute counter
	if (cnt > 1) {
	  which = 1;
	  nr = i;
	  return true;
	}
	cnt = 0;
      }
      //check rows
      for (unsigned j=0; j<MAX_COLS; ++j) {
	for (unsigned i=0; i<MAX_ROWS; ++i) {
	  if (m_locked_pos.contains(qMakePair(j,i))) {
	    ++cnt;
	  } else if (m_locked_pos_B.contains(qMakePair(j,i))) {
	    info(0, "[warning]Row "
		 + QString::number(j)
		 + " already taken by machine, skipping...");
	    cnt = 0;
	    break;
	  }
	}
	//when row j is completed, compute counter
	if (cnt > 1) {
	  which = 0;
	  nr = j;
	  return true;
	}
	cnt = 0;
      }
      cnt = 0;
      //check diagonal +
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	if (m_locked_pos.contains(qMakePair(i,i))) {
	  ++cnt;
	} else if (m_locked_pos_B.contains(qMakePair(i,i))) {
	  info(0, "[warning]Diagonal already taken by machine, skipping...");
	  cnt = 0;
	  break;
	}
      }
      if (cnt > 1) {
	which = 2;
	nr = 0; //indicates + diagonal
	return true;
      }
      cnt = 0;
      //check diagonal -
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	if (m_locked_pos.contains(qMakePair(i,MAX_ROWS-1-i))) {
	  ++cnt;
	} else if (m_locked_pos_B.contains(qMakePair(i,MAX_ROWS-1-i))) {
	  info(0, "[warning]Diagonal already taken by machine, skipping...");
	  cnt = 0;
	  break;
	}
      }
      if (cnt > 1) {
	which = 2;
	nr = 1; //indicates + diagonal
	return true;
      }
      cnt = 0;
      info(0, "Yellow player is no threat now. Retuning false");
    } else { //possible win for machine
      //check columns
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	for (unsigned j=0; j<MAX_COLS; ++j) {
	  if (m_locked_pos_B.contains(qMakePair(j,i))) {
	    ++cnt;
	  }
	  if (m_locked_pos.contains(qMakePair(j,i))) {
	    cnt = 0;
	    break;
	  }
	}
	if (cnt > 1) {
	  which = 1;
	  nr = i;
	  return true;
	}
	cnt = 0;
      }
      //check rows
      for (unsigned j=0; j<MAX_COLS; ++j) {
	for (unsigned i=0; i<MAX_ROWS; ++i) {
	  if (m_locked_pos_B.contains(qMakePair(j,i))) {
	    ++cnt;
	  }
	  if (m_locked_pos.contains(qMakePair(j,i))) {
	    cnt = 0;
	    break;
	  }
	}
	if (cnt > 1) {
	  which = 0;
	  nr = j;
	  return true;
	}
	cnt = 0;
      }
      //check diagonal +
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	if (m_locked_pos_B.contains(qMakePair(i,i))) {
	  ++cnt;
	} else if (m_locked_pos.contains(qMakePair(i,i))) {
	  info(0, "[warning]Diagonal already taken by YELLOW player, skipping...");
	  cnt = 0;
	  break;
	}
      }
      if (cnt > 1) {
	which = 2;
	nr = 0; //indicates + diagonal
	return true;
      }
      cnt = 0;
      //check diagonal -
      for (unsigned i=0; i<MAX_ROWS; ++i) {
	if (m_locked_pos_B.contains(qMakePair(i,MAX_ROWS-1-i))) {
	  ++cnt;
	} else if (m_locked_pos.contains(qMakePair(i,MAX_ROWS-1-i))) {
	  info(0, "[warning]Diagonal already taken by YELLOW player, skipping...");
	  cnt = 0;
	  break;
	}
      }
      if (cnt > 1) {
	which = 2;
	nr = 1; //indicates + diagonal
	return true;
      }
      cnt = 0;
    }
    return false;
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

  void MyGui::limitChar() {
    QString text,textB;
    if (m_machine) {
      text = m_player_edit->toPlainText();
      if (text.at(text.size()-1) == 10) {
	text.chop(1);
	m_player_edit->setText(text);
	disconnect(m_player_edit, SIGNAL(textChanged()), this, SLOT(limitChar()));
	resetGame();
      } else if (text.size() > 40) {
	text.chop(1);
	m_player_edit->setText(text);
      }
    } else {
      text = m_player_edit->toPlainText();
      textB = m_player_edit_B->toPlainText();
      if (textB.at(textB.size()-1) == 40) {
	textB.chop(1);
	m_player_edit_B->setText(textB);
	disconnect(m_player_edit, SIGNAL(textChanged()), this, SLOT(limitChar()));
	disconnect(m_player_edit_B, SIGNAL(textChanged()), this, SLOT(limitChar()));
	resetGame();
	return;
      }
      if (textB.size() > 40) {
	textB.chop(1);
	m_player_edit_B->setText(textB);
      }
      if (text.size() > 40) {
	text.chop(1);
	m_player_edit->setText(text);
      }
    }
  }
  void MyGui::animationTimerOut() {
    QPixmap target;
    for (unsigned i=1; i<=MAX_ROWS; ++i) {
      for (unsigned j=0; j<MAX_COLS; ++j) {
	if (target.load(PREFIX+COLORS.at(rand() % COLORS.size()))) {
	  qobject_cast<QLabel*>(qobject_cast<QLayout*>(m_main_layout->itemAt(i)->layout())->itemAt(j)->widget())->setPixmap(target);
	}
      }
    }
  }
} //mynamespace
