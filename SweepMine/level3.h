#ifndef LEVEL3_H
#define LEVEL3_H

#include"level1.h"
#include"level2.h"
#include"LevelData.h"


class Level3 : public QMainWindow,LevelData
{
    Q_OBJECT
public:
    explicit Level3(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);

signals:

};

#endif // LEVEL3_H
