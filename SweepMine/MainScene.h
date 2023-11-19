#ifndef MAINSCENE_H
#define MAINSCENE_H

#include<LevelData.h>

class MainScene : public QMainWindow,LevelData
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
};
#endif // MAINSCENE_H
