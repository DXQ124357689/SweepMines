#ifndef LEVEL1_H
#define LEVEL1_H

#include"LevelData.h"
#include"level2.h"
#include"level3.h"

class Level1 : public QMainWindow,LevelData
{
    Q_OBJECT
public:
    explicit Level1(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

signals:

};

#endif // LEVEL1_H
