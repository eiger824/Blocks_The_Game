#ifndef MY_GUI_HPP_
#define MY_GUI_HPP_

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QtCore>
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPair>

namespace mynamespace {

  const int MAX_ROWS = 4;
  const int MAX_COLS = 4;
  
  class MyGui : public QWidget {
    Q_OBJECT
  public:
    explicit MyGui(QWidget* parent=0);
    ~MyGui();
  protected:
    void keyPressEvent(QKeyEvent *event);
  private slots:
    void timerOut();
  private:
    void info(const int code, const QString& msg);
    void info();
    QString currentPair2String();
    bool canMove(const int key);
    void updateLabels();
    void machinePlays();
    void switchPlayer();
    bool checkIfWin();
    bool save2list();
    void updateCurrentCol(int opt);
    void updateCurrentRow(int opt);
    bool checkPos(unsigned int x, unsigned int y);
    bool isPosLocked(unsigned int x, unsigned int y);
    void printLocked();
    bool checkDiag();
    void resetGame();
  private:
    QVBoxLayout *m_main_layout;
    QHBoxLayout *m_first;
    QHBoxLayout *m_second;
    QHBoxLayout *m_third;
    QHBoxLayout *m_fourth;
    QPair<unsigned int,unsigned int> m_current;
    QPair<unsigned int,unsigned int> m_current_B;
    bool m_started;
    QTimer *m_timer;
    QLabel *m_block;
    QString m_current_player;
    QList<QPair<unsigned int,unsigned int> > m_locked_pos;
    QList<QPair<unsigned int,unsigned int> > m_locked_pos_B;
  };
  
} //mynamespace

#endif /*MY_GUI_HPP_*/
