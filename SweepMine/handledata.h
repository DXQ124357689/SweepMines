#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include<QVector>
#include<QPair>
#include<ctime>
#include<cstdlib>
#include<QPoint>
#include<QSet>

class HandleData
{
public:
    HandleData();

    QVector<QVector<QPair<int,int>>>* addBomb(int n, int bombNum, QVector<QVector<QPair<int,int>>>*& Val);

    QVector<QVector<QPair<int,int>>>* reData(int n,QVector<QVector<QPair<int,int>>>*& Val);

    QPoint computePos(int x, int y);

    int recursiveSearch(int x,int y,int n,int& unNum, QVector<QVector<QPair<int,int>>>*& Val);

    int Check(int x, int y,int n,int& unNum,int& gameStatus, QVector<QVector<QPair<int,int>>>*& Val);
};

#endif // HANDLEDATA_H
