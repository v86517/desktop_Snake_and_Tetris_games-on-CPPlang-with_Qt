/**
 * @file tetrisWidget.cc
 * @brief Файл интерфейса игры Tetris с использованием Qt.
 */
#include "tetrisWidget.h"

tetrisQTClass::tetrisQTClass() {
  setWindowTitle("Tetris");
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, Qt::black);
  setAutoFillBackground(true);
  setPalette(pal);
  setStyleSheet("color : white");
  resize(pix_size * COLSS * 2, pix_size * (ROWS) + 2);
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &tetrisQTClass::updatePrint);
  startState();
  layout();
}

tetrisQTClass::~tetrisQTClass() {
  killTimer(timer_val);
  freeMemory(&game_info);
  delete timer;
}

void tetrisQTClass::addLabel(QVBoxLayout *info, QLabel *label,
                             const QFont &font) {
  info->addWidget(label);
  label->setFont(font);
}

void tetrisQTClass::layout() {
  QFont label_font("Arial", 14, QFont::Bold);
  QHBoxLayout *layout = new QHBoxLayout(this);
  QWidget *infoWidget = new QWidget(this);
  QVBoxLayout *info = new QVBoxLayout(infoWidget);
  level_label = new QLabel(this);
  score_label = new QLabel(this);
  // score_label->setStyleSheet("QLabel { background-color : red; color : blue;
  // }");
  high_score_Label = new QLabel(this);
  next = new QLabel(this);
  test1 = new QLabel(this);
  test2 = new QLabel(this);

  addLabel(info, level_label, label_font);
  addLabel(info, score_label, label_font);
  addLabel(info, high_score_Label, label_font);
  addLabel(info, next, label_font);
  addLabel(info, test1, label_font);
  addLabel(info, test2, label_font);

  layout->addWidget(infoWidget);
}
void tetrisQTClass::startState() {
  initState(&game_info);
  state = START;
  act = NOSIG;
  if (timer_val > 0) {
    killTimer(timer_val);
  }
  speed_val = game_info.speed / 1000;
  timer_val = startTimer(speed_val);
}

void tetrisQTClass::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)

  QPainter p(this);
  printFieldState(&p);
  if (game_info.pause == 1) {
    printStateBanner(Qt::white, e, &p,
                     "               PAUSEd\n\n\n            p - continue");
  } else if (state == START) {
    printStateBanner(
        Qt::white, e, &p,
        "           NEW GAME\n\n    ENTER - start game\n            "
        "  ESC - exit");
  } else if (state == GAMEOVER && game_info.level > LAST_LEVEL) {
    printStateBanner(
        Qt::white, e, &p,
        "              YOU WON\n\n      ENTER - new game\n            "
        "  ESC - exit");
  } else if (state == GAMEOVER) {
    printStateBanner(
        Qt::white, e, &p,
        "            GAME OVER\n\n      ENTER - new game\n            "
        "  ESC - exit");
  }
  printGameInfo();
}

void tetrisQTClass::chooseColor(int color, QPainter *p) {
  switch (color) {
    case 1:
      p->setBrush(Qt::darkYellow);
      break;
    case 2:
      p->setBrush(Qt::yellow);
      break;
    case 3:
      p->setBrush(Qt::magenta);
      break;
    case 4:
      p->setBrush(Qt::green);
      break;
    case 5:
      p->setBrush(Qt::blue);
      break;
    case 6:
      p->setBrush(Qt::darkMagenta);
      break;
    case 8:
      p->setBrush(Qt::red);
      break;

    default:
      break;
  }
}

void tetrisQTClass::printFieldState(QPainter *p) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLSS; j++) {
      if (game_info.field[i][j]) {
        chooseColor(game_info.field[i][j], p);
      } else {
        p->setPen(Qt::black);
        p->setBrush(Qt::black);
      }
      p->drawRect(pix_size * j, pix_size * i, pix_size, pix_size);
    }
  }
  p->setBrush(Qt::black);
  p->setPen(Qt::white);
  p->drawRect(315, 1, 283, 600);
  p->drawLine(0, 1, 301, 1);
  p->drawLine(0, 600, 301, 600);
  p->drawLine(0, 1, 0, 600);
  p->drawLine(301, 1, 301, 600);

  for (int i = 0; i < NEXT_WIDTH; i++) {
    for (int j = 0; j < NEXT_WIDTH; j++) {
      if (game_info.next[i][j]) {
        chooseColor(game_info.next[i][j], p);
        p->setPen(Qt::black);
        p->drawRect((COLSS + 2 + j) * pix_size, (6 + i) * pix_size, pix_size,
                    pix_size);
      }
    }
  }
}

void tetrisQTClass::printGameInfo() {
  high_score_Label->setGeometry(COLSS * pix_size + 25, 0, 190, 40);
  score_label->setGeometry(COLSS * pix_size + 25, 40, 150, 40);
  level_label->setGeometry(COLSS * pix_size + 25, 80, 150, 40);
  next->setGeometry(COLSS * pix_size + 25, 120, 150, 40);
  test1->setGeometry(COLSS * pix_size + 25, 340, 150, 40);
  test2->setGeometry(COLSS * pix_size + 25, 380, 150, 40);

  high_score_Label->setText(QString("Highscore: %1").arg(game_info.high_score));
  score_label->setText(QString("Score: %1").arg(game_info.score));
  level_label->setText(QString("Level: %1").arg(game_info.level));
  next->setText(QString("Next:"));
  test1->setText(QString("act: %1").arg((int(act))));
  test2->setText(QString("state: %1").arg((int(state))));
}

void tetrisQTClass::updatePrint(void) {
  update();
  if (game_info.pause == 1) {
    killTimer(timer_val);
  }
}

void tetrisQTClass::timerEvent(QTimerEvent *event) {
  Q_UNUSED(event);
  if (state != MOVING || game_info.pause == 1) {
    userInput(&game_info, &currentFigure, act = NOSIG, &state);
  }
  if (state == MOVING && game_info.pause == 0) {
    userInput(&game_info, &currentFigure, act = Down, &state);
  }

  if (speed_val != game_info.speed / 1000) {
    killTimer(timer_val);
    speed_val = game_info.speed / 1000;
    timer_val = startTimer(speed_val);
  }
  repaint();
}

void tetrisQTClass::keyPressEvent(QKeyEvent *e) {
  act = NOSIG;
  if (e->key() == Qt::Key_Down) {
    act = Down;
  } else if (e->key() == Qt::Key_Up) {
    act = Up;
  } else if (e->key() == Qt::Key_Left) {
    act = Left;
  } else if (e->key() == Qt::Key_Right) {
    act = Right;
  } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    act = Start;
  } else if (e->key() == Qt::Key_Escape) {
    act = Terminate;
  } else if (e->key() == Qt::Key_P) {
    act = Pause;
  } else if (e->key() == Qt::Key_Space) {
    act = Action;
  }

  if (act == Pause && state == MOVING) {
    game_info.pause = game_info.pause == 1 ? 0 : 1;
    act = NOSIG;
  }

  if (game_info.pause == 0) {
    userInput(&game_info, &currentFigure, act, &state);
  }
  if (act == Down) {
    killTimer(timer_val);
    timer_val = startTimer(speed_val);
  }
  if (state != EXIT_STATE) repaint();
  if (state == EXIT_STATE && act == Terminate) {
    QWidget::close();
  }
}

void tetrisQTClass::printStateBanner(QColor color, QPaintEvent *e,
                                     QPainter *painter, const QString &text) {
  QFont font = painter->font();
  font.setPointSize(20);
  font.setBold(true);
  painter->setFont(font);
  QRect rect = e->rect();
  QRect textRect = rect;
  textRect.moveTop(textRect.top() - font.pointSize() / 2);
  painter->setPen(color);
  painter->drawText(textRect, Qt::AlignVCenter, text);
}