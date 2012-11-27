#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "minimaxAgent.hpp"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *keyEvent);
private:
    void gameInit();
    void gameDraw();
    void gameLoop();
    MinimaxAgent minimax_;
    State state_;
    Action pacmanAction;
};

#endif // GLWIDGET_H
