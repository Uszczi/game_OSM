#include "GameWidget.h"

#include "../src/hardware/KeyMapping.h"
#include "../src/hardware/Resources.h"

#include <QApplication>
#include <QPainter>
#include <QKeyEvent>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    paintDevice(this, res::resource(FONT_PIXMAP)),
    highscores(res::resource(HIGH_SCORE_FILE)),
    menu(highscores),
    fpsInfo(16)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    game = new Game;

    menu.setExitCallback([&](){
        shouldExit = true;
    });

    menu.setContinueCallback([&](){
        game->setPlaying(true);
    });

    menu.setNewGameCallback([&](){
        delete game;
        game = new Game;
        game->setPlaying(true);
    });

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame);
    timer->start(1000/FRAMERATE);
}

GameWidget::~GameWidget()
{
    delete game;
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    game->drawTo(paintDevice);

    if(!game->isPlaying())
        menu.drawTo(paintDevice);

    paintDevice.drawText("FPS: "+ std::to_string((unsigned)fpsInfo.averange()), 0, 0);
    paintDevice.swapBuffers();

    QWidget::paintEvent(event);
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if(!game->isPlaying())
        menu.processInput(key);
    else
        game->processInput(key);

    if(key == KEY_SPACE) {
        showDebug = !showDebug;
        game->setDebugMode(showDebug);
    }

    QWidget::keyPressEvent(event);
}

void GameWidget::updateGame()
{
    if(shouldExit) {
        exitGame();
        return;
    }

    double dt_s = timer->interval()/1000.0;

    if(game->isPlaying())
    {
        game->update(dt_s);

        if(game->isGameLost())
        {
            game->setPlaying(false);
            highscores.addEntry(game->getPoints());

            delete game;
            game = new Game;
        }
        else if (game->isGameWon())
        {
            int score = game->getPoints();

            delete game;
            game = new Game(score);
        }
    }

    fpsInfo.add(1.0/dt_s);
    update();
}

void GameWidget::exitGame()
{
    timer->stop();

    if(game)
    {
        highscores.addEntry(game->getPoints());
        highscores.save();
        delete game;
    }

    QApplication::quit();
}
