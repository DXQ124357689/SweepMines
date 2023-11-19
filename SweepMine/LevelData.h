#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QMainWindow>
#include<QMenuBar>
#include<QPushButton>
#include<QLabel>
#include<QFrame>
#include<QPainter>
#include<QHoverEvent>
#include<QTimer>
#include<QDebug>
#include<QMessageBox>
#include<QSound>
#include"handledata.h"

class LevelData{

public:

    QMenuBar *menu;
    QMenu *game = new QMenu("游戏");
    QMenu *help = new QMenu("帮助");
    QMenu *selectLevel = new QMenu("关卡选择");

    QAction *Level01 = new QAction("简单");
    QAction *Level02 = new QAction("一般");
    QAction *Level03 = new QAction("困难");
    QAction *about = new QAction("关于");
    QAction *restart = new QAction("重新开始");
    QAction *exitGame = new QAction("退出");

    QLabel *timeLabel;
    QLabel *bombLabel;

    QSound *boom = new QSound(":/res/boom.wav");

    QFrame *frame;//框架对象

    HandleData *hd;//数据处理类对象

    //数据 指针数据切记要初始化
    QVector<QVector<QPair<int,int>>> *Data = new QVector<QVector<QPair<int,int>>>();
    //第一个存储状态 1为有旗子 0为没有按下 2为按下了 第二个存储数字    //指针数据切记要初始化

    int rows;//行列数

    int bombNum;//炸弹数

    int unPressNum;//未按下的个数

    int gameStatus = 0;//游戏状态：-1表示失败 0表示进行中 1表示胜利

    int numCount;//记录剩余炸弹数

    int currentTime = 0;//记录当前时间 单位为秒

    int dialogFlag = 0;

    int forbidFlag = 0;

    QPoint hoverPoint;//记录悬浮时的坐标

    QPoint leftPoint;//记录左键点击时的坐标

    QPoint rightPoint;//记录右键点击时的坐标

    QTimer *gameTime;//计时器
};

#endif // LEVELDATA_H
