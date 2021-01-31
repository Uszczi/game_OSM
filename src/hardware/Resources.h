#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

#include <QApplication>
#include <QDir>

static const std::string HIGH_SCORE_FILE = "highscore.txt";

static const std::string FONT_PIXMAP = "font.ppm";
static const std::string MAZE_PIXMAP = "maze.ppm";
static const std::string CLYDE_PIXMAP = "clyde.ppm";

static const std::string PACMAN_LEFT = "pacman_left.ppm";
static const std::string PACMAN_RIGHT = "pacman_right.ppm";
static const std::string PACMAN_UP = "pacman_up.ppm";
static const std::string PACMAN_DOWN = "pacman_down.ppm";

namespace res
{
    static std::string getResourcePath()
    {
        return qApp->applicationDirPath().toStdString() + "/static/";
    }

    static std::string resource(std::string name)
    {
        return getResourcePath() + name;
    }
}

#endif // RESOURCES_H
