#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>

#include "../src/hardware/QTPaintDevice.h"
#include "../src/hardware/InputDevice.h"

#include "../src/gui/HighScore.h"
#include "../src/gui/MainMenu.h"
#include "../src/gui/Game.h"

#include "../src/misc/DataInfo.h"

constexpr double FRAMERATE = 120;

class GameWidget : public QWidget
{
    Q_OBJECT

private:
    QTimer *timer;

    QTPaintDevice paintDevice;
    HighScore highscores;
    MainMenu menu;

    DataInfo fpsInfo;

    Game *game = nullptr;

    bool shouldExit = false;
    bool showDebug = false;

public:
    explicit GameWidget(QWidget *parent = nullptr);
    virtual ~GameWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void exitGame();

private slots:
    void updateGame();


};

#endif // GAMEWIDGET_H
