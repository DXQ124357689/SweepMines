#ifndef LEVEL2_H
#define LEVEL2_H

#include"level1.h"
#include"level3.h"
#include"LevelData.h"

class Level2 : public QMainWindow,LevelData
{
    Q_OBJECT
public:
    explicit Level2(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

signals:

};

#endif // LEVEL2_H
