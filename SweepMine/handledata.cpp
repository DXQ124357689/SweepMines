#include "handledata.h"

HandleData::HandleData()
{

}

int HandleData::recursiveSearch(int x, int y, int n,int& unNum, QVector<QVector<QPair<int,int>>>*& Val)
{
    if((*Val)[x][y].second != 0){
        return unNum;
    }
    else{
        if(y-1 >= 0){
            if(x-1 >= 0 && (*Val)[x-1][y-1].first == 0){
                (*Val)[x-1][y-1].first = 2;
                unNum--;
                recursiveSearch(x-1,y-1,n,unNum,Val);
            }
            if(x+1 < n && (*Val)[x+1][y-1].first == 0){
                (*Val)[x+1][y-1].first = 2;
                unNum--;
                recursiveSearch(x+1,y-1,n,unNum,Val);
            }
            if((*Val)[x][y-1].first == 0){
                (*Val)[x][y-1].first = 2;
                unNum--;
                recursiveSearch(x,y-1,n,unNum,Val);
            }
        }
        if(y+1 < n){
            if(x-1 >= 0 && (*Val)[x-1][y+1].first == 0){
                (*Val)[x-1][y+1].first = 2;
                unNum--;
                recursiveSearch(x-1,y+1,n,unNum,Val);
            }
            if(x+1 < n && (*Val)[x+1][y+1].first == 0){
                (*Val)[x+1][y+1].first = 2;
                unNum--;
                recursiveSearch(x+1,y+1,n,unNum,Val);
            }
            if((*Val)[x][y+1].first == 0){
                (*Val)[x][y+1].first = 2;
                unNum--;
                recursiveSearch(x,y+1,n,unNum,Val);
            }
        }
        if(x-1 >= 0 && (*Val)[x-1][y].first == 0) {
            (*Val)[x-1][y].first = 2;
            unNum--;
            recursiveSearch(x-1,y,n,unNum,Val);
        }
        if(x+1 < n && (*Val)[x+1][y].first == 0) {
            (*Val)[x+1][y].first = 2;
            unNum--;
            recursiveSearch(x+1,y,n,unNum,Val);
        }
    }
    return unNum;
}

int HandleData::Check(int x, int y, int n, int &unNum,int& gameStatus, QVector<QVector<QPair<int, int> > > *&Val){

    int total = (*Val)[x][y].second, num = 0, un = 0;
    QVector<QPair<int,int>> *temVal = new QVector<QPair<int,int>>();
    temVal->resize(8);
    if(y-1 >= 0){
        if(x-1 >= 0){
            if((*Val)[x-1][y-1].first == 1){
                num++;
            }
            else if((*Val)[x-1][y-1].first == 0){
                (*temVal)[un++] = QPair<int,int>(x-1,y-1);
            }
        }
        if(x+1 < n){
            if((*Val)[x+1][y-1].first == 1){
                num++;
            }
            else if((*Val)[x+1][y-1].first == 0){
                (*temVal)[un++] = QPair<int,int>(x+1,y-1);
            }
        }
        if((*Val)[x][y-1].first == 1){
            num++;
        }
        else if((*Val)[x][y-1].first == 0){
            (*temVal)[un++] = QPair<int,int>(x,y-1);
        }
    }
    if(y+1 < n){
        if(x-1 >= 0){
            if((*Val)[x-1][y+1].first == 1){
                num++;
            }
            else if((*Val)[x-1][y+1].first == 0){
                (*temVal)[un++] = QPair<int,int>(x-1,y+1);
            }
        }
        if(x+1 < n){
            if((*Val)[x+1][y+1].first == 1){
                num++;
            }
            else if((*Val)[x+1][y+1].first == 0){
                (*temVal)[un++] = QPair<int,int>(x+1,y+1);
            }
        }
        if((*Val)[x][y+1].first == 1){
            num++;
        }
        else if((*Val)[x][y+1].first == 0){
            (*temVal)[un++] = QPair<int,int>(x,y+1);
        }
    }
    if(x-1 >= 0){
        if((*Val)[x-1][y].first == 1){
            num++;
        }
        else if((*Val)[x-1][y].first == 0){
            (*temVal)[un++] = QPair<int,int>(x-1,y);
        }
    }
    if(x+1 < n){
        if((*Val)[x+1][y].first == 1){
            num++;
        }
        else if((*Val)[x+1][y].first == 0){
            (*temVal)[un++] = QPair<int,int>(x+1,y);
        }
    }

    if(num == total&& un != 0){

        temVal->resize(un);
        un =0 ;
        for(int i =0;i<temVal->size();i++){

            if((*Val)[(*temVal)[i].first][(*temVal)[i].second].second == -1){
                gameStatus = -1;
            }
            else if((*Val)[(*temVal)[i].first][(*temVal)[i].second].second == 0){
                recursiveSearch((*temVal)[i].first,(*temVal)[i].second,n,unNum,Val);
            }
            if((*Val)[(*temVal)[i].first][(*temVal)[i].second].first != 2){
                un++;
            }
            (*Val)[(*temVal)[i].first][(*temVal)[i].second].first = 2;
        }
        unNum -= un;

        delete temVal;
    }

    return unNum;
}

QPoint HandleData::computePos(int x, int y)
{
    int gridX = (x - 74) / 40 + 1;
    int gridY = (y - 150) / 40 + 1;

    return QPoint(gridX,gridY);
}

QVector<QVector<QPair<int,int>>>* HandleData::addBomb(int n, int bombNum, QVector<QVector<QPair<int,int>>>*& Val){

    srand((unsigned int)time(NULL));

    //数据初始化
    Val->resize(n);
    for(int i = 0;i < n;i++) {
        (*Val)[i].resize(n);
        for(int j = 0;j<n;j++){
            (*Val)[i][j] = QPair<int, int>(0, 0);
        }
    }

    //添加炸弹
    //for(int i = 0;i < bombNum;i++) { (*Val)[rand()%9][rand()%9].second = -1; } 有重复

    QSet<QPair<int, int>> randomPositions;
    while (randomPositions.size() < bombNum) {
        int row = rand() % n;
        int col = rand() % n;
        randomPositions.insert(QPair<int, int>(row, col));
    }

    // 将这10个位置对应的 second 值修改为 -1
    for (const auto& pos : randomPositions) {
        (*Val)[pos.first][pos.second].second = -1;
    }

    //遍历添加数字
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if((*Val)[i][j].second != -1){
                if(i-1 >= 0){
                    if(j-1 >= 0&&(*Val)[i-1][j-1].second == -1){ (*Val)[i][j].second++; }
                    if((*Val)[i-1][j].second == -1){ (*Val)[i][j].second++; }
                    if(j+1 < n&&(*Val)[i-1][j+1].second == -1){ (*Val)[i][j].second++; }
                }
                if(j-1 >= 0&&(*Val)[i][j-1].second == -1){ (*Val)[i][j].second++; }
                if(j+1 < n&&(*Val)[i][j+1].second == -1){ (*Val)[i][j].second++; }
                if(i+1 < n){
                    if(j-1 >= 0&&(*Val)[i+1][j-1].second == -1){ (*Val)[i][j].second++; }
                    if((*Val)[i+1][j].second == -1){ (*Val)[i][j].second++; }
                    if(j+1 < n&&(*Val)[i+1][j+1].second == -1){ (*Val)[i][j].second++; }
                }
            }
        }
    }

    return Val;
}

QVector<QVector<QPair<int,int>>>* HandleData::reData(int n,QVector<QVector<QPair<int,int>>>*& Val){

    for(int i = 0;i < n;i++) {
        for(int j = 0;j<n;j++){
            (*Val)[i][j].first = 0;
        }
    }
    return Val;
}
