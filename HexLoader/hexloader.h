#ifndef HEXLOADER_H
#define HEXLOADER_H

#ifndef __DEBUG__
#define __DEBUG__
#endif

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QList>
#include <QHash>
#include <QStack>
#include <QQueue>
#include <QByteArray>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QScrollBar>
#include <algorithm>
#include <stdio.h>
#include "ui_hexloader.h"
#include "define.h"

template <typename T>
inline void g_funcFreeResrc(T* &pointer)
{
    if (nullptr != pointer)
    {
        delete pointer;
        pointer = nullptr;
    }
}

template <typename T>
inline void g_funcFreeResrcArr(T* &pointer)
{
    if (nullptr != pointer)
    {
        delete[] pointer;
        pointer = nullptr;
    }
}

class HexLoader : public QMainWindow
{
    Q_OBJECT

public:
    HexLoader(QWidget *parent = 0);
    ~HexLoader();

    void funcLoadResrc();
    void funcGenerateTable();
    void funcFreeResrc();
    void funcFreeResrc(const int nType);
    void funcTotalLoadOp();
    void funcClearListAndRecoveryBg();
    void funcGenerateHashAsciiKey();
    void funcGenerateHashCharKey();
    bool funcCheckItemText(const QString& str);
    void funcGenarateSelectionBg(const int nRow, const int nColumn, const int nDif);
    bool funcRecoveryBgOfAsciiOrHex(const int nLoopCount, const int nDif);
    void funcModifyDstItemData(QTableWidgetItem* itemSrc, const bool isUpdate, const bool isError);
    void funcSetUpdationItemRG(QTableWidgetItem* itemSrc, const bool isUpdate, const bool isError);
    void funcWriteDataToFile(FILE* fp);
    void funcSetTitleIsEdit(const bool isEdit);
    void funcSetCharToItem(QTableWidgetItem* itemDst, const QString& str);
    void funcSetAsciiToItem(QTableWidgetItem* itemDst, const QString& str);
    void funcPushDataToUndoStack(QTableWidgetItem* item);
    QTableWidgetItem* funcStackWriteDataToBuffer(QStack<QHash<QTableWidgetItem*, QString>>& stack, 
                                                 QStack<QTableWidgetItem*>& stackAddr,
                                                 QStack<QHash<QTableWidgetItem*, QString>>& stackReverse,
                                                 QStack<QTableWidgetItem*>& stackAddrReverse);

protected:
    virtual void keyPressEvent(QKeyEvent* evnt);

private slots:
    void slotOpenDialog();
    void slotCloseProgram();
    void slotSaveData();
    void slotSaveAsData();
    void slotUndo();
    void slotRedo();
    void slotFind();
    void slotAbout(); 
    
    void slotUpdationItemBackGround(QTableWidgetItem*);
    void slotSelectionItemBackGround();
    void slotScroll(int);

    void slotFindAsciiPushButton();
    void slotFindCharPushButton();

private:
    Ui::HexLoaderClass ui;

    char* _pFileBuffer;
    char* _pFileName;
    unsigned int _nFileSize;
    FILE* _fp;
    QColor _color;
    bool _isKeyPress;

    QDialog* _dlgAbout;
    QLabel* _lbAbout;

    QLineEdit* _editFind;
    QDialog* _dlgFind;
    QLabel* _lbFind;
    QPushButton* _btFindAscii;
    QPushButton* _btFindChar;
    QVBoxLayout* _vLayoutFind;
    QHBoxLayout* _hLayoutFind;
    int _nFromAscii;
    int _nFromChar;
    int _nScrollAsciiValue;
    int _nScrollCharValue;

    QList<QTableWidgetItem*> _listItemAddrInfo;
    QHash<int, QString> _hashAsciiKey;
    QHash<QString, int> _hashCharKey;
    QQueue<QTableWidgetItem*> _queueSave;
    QStack<QHash<QTableWidgetItem*, QString>> _stackUndo;
    QStack<QTableWidgetItem*> _stackUndoAddr;
    QStack<QHash<QTableWidgetItem*, QString>> _stackRedo;
    QStack<QTableWidgetItem*> _stackRedoAddr;
};

#endif // HEXLOADER_H
