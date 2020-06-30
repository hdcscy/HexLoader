#include "hexloader.h"

HexLoader::HexLoader(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setStyleSheet("QTableView::item:selected{color:white;background:gray;}"); 
    ui.statusBar->setStyleSheet("color:white;background-color:gray");
    ui.statusBar->setFont(QFont("Consolas", 9, QFont::Normal));
    ui.statusBar->showMessage("Console: [ None ]");

    _pFileBuffer = nullptr;
    _pFileName = nullptr;
    _fp = nullptr;

    _dlgAbout = new QDialog(this);
    _lbAbout = new QLabel(_dlgAbout);

    _dlgFind = new QDialog(this);
    _lbFind = new QLabel(_dlgFind);
    _btFindAscii = new QPushButton(_dlgFind);
    _btFindChar = new QPushButton(_dlgFind);
    _editFind = new QLineEdit(_dlgFind);
    _vLayoutFind = new QVBoxLayout(_dlgFind);
    _hLayoutFind = new QHBoxLayout(_dlgFind);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;

    _lbAbout->setText("\r\n        HexLoader v1.0.0");
    _dlgAbout->setFixedSize(200, 50);
    _dlgAbout->setWindowTitle("HexLoader - About");
    _dlgAbout->setWindowFlags(flags);

    _lbFind->setText("What to find?");
    _btFindAscii->setText("Hex");
    _btFindChar->setText("Text");
    _dlgFind->setFixedSize(200, 100);
    _vLayoutFind->addWidget(_lbFind);
    _vLayoutFind->addWidget(_editFind);
    _vLayoutFind->addLayout(_hLayoutFind);
    _hLayoutFind->addWidget(_btFindAscii);
    _hLayoutFind->addWidget(_btFindChar);
    _dlgFind->setWindowFlags(flags);

    _listItemAddrInfo.clear();
    _hashAsciiKey.clear();
    _hashCharKey.clear();
    _queueSave.clear();
    _stackUndo.clear();
    _stackUndoAddr.clear();
    _stackRedo.clear();
    _stackRedoAddr.clear();

    _nFromAscii = 0;
    _nFromChar = 0;
    _nScrollAsciiValue = 0;
    _nScrollCharValue = 0;
    _nFileSize = 0;

    _color.setRgb(246, 246, 246);

    funcGenerateHashAsciiKey();
    funcGenerateHashCharKey();
    
    connect(ui.action_open, SIGNAL(triggered()), this, SLOT(slotOpenDialog()));
    connect(ui.action_openfile, SIGNAL(triggered()), this, SLOT(slotOpenDialog()));
    connect(ui.action_close, SIGNAL(triggered()), this, SLOT(slotCloseProgram()));
    connect(ui.action_save, SIGNAL(triggered()), this, SLOT(slotSaveData()));
    connect(ui.action_saveas, SIGNAL(triggered()), this, SLOT(slotSaveAsData()));
    connect(ui.action_undo, SIGNAL(triggered()), this, SLOT(slotUndo()));
    connect(ui.action_redo, SIGNAL(triggered()), this, SLOT(slotRedo()));
    connect(ui.action_find, SIGNAL(triggered()), this, SLOT(slotFind()));
    connect(ui.action_about, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(_btFindAscii, SIGNAL(clicked()), this, SLOT(slotFindAsciiPushButton()));
    connect(_btFindChar, SIGNAL(clicked()), this, SLOT(slotFindCharPushButton()));
    connect(ui.tableWidget_hex->verticalScrollBar(), SIGNAL(sliderMoved(int)),
            this, SLOT(slotScroll(int)));
}

HexLoader::~HexLoader()
{
    g_funcFreeResrc(_lbAbout);
    g_funcFreeResrc(_dlgAbout);

    g_funcFreeResrc(_lbFind);
    g_funcFreeResrc(_btFindAscii);
    g_funcFreeResrc(_btFindChar);
    g_funcFreeResrc(_editFind);
    g_funcFreeResrc(_hLayoutFind);
    g_funcFreeResrc(_vLayoutFind);
    g_funcFreeResrc(_dlgFind);

    funcFreeResrc();
}

void HexLoader::funcFreeResrc()
{
    g_funcFreeResrcArr(_pFileName);
    g_funcFreeResrcArr(_pFileBuffer);

    if (nullptr != _fp)
    {
        fclose(_fp);
        _fp = nullptr;
    }

    _listItemAddrInfo.clear();
    _queueSave.clear();
    _stackUndo.clear();
    _stackUndoAddr.clear();
    _stackRedo.clear();
    _stackRedoAddr.clear();

    _nFromAscii = 0;
    _nFromChar = 0;
    _nScrollAsciiValue = 0;
    _nScrollCharValue = 0;
    _nFileSize = 0;

    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
               this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));
    disconnect(ui.tableWidget_hex, SIGNAL(itemSelectionChanged()), 
               this, SLOT(slotSelectionItemBackGround()));
}

void HexLoader::funcFreeResrc(const int nType)
{
#ifdef __DEBUG__
    __PRINT_DEBUGINFO__(nType);
#endif
    funcFreeResrc();
    exit(0);
}

void HexLoader::slotOpenDialog()
{
    QString str = QFileDialog::getOpenFileName(this, "Open File Dialog", QDir::rootPath(), "All(*)");
    QByteArray byte = str.toLocal8Bit();
    if (byte.isEmpty())
    {
        return;
    }
    funcFreeResrc();
    _pFileName = new char[byte.size() + 1];
    if (nullptr == _pFileName)
    {
        funcFreeResrc(FILENAME_NULL);
    }
    memset(_pFileName, 0, byte.size() + 1);
    memcpy(_pFileName, byte.data(), byte.size());
    funcTotalLoadOp();
}

void HexLoader::funcLoadResrc()
{
    _fp = fopen(_pFileName, "rb+");
    if (nullptr == _fp)
    {
        funcFreeResrc(FILE_POINTER_NULL);
    }

    fseek(_fp, 0L, SEEK_END);
    _nFileSize = ftell(_fp);
    fseek(_fp, 0L, SEEK_SET);

    _pFileBuffer = new char[_nFileSize + 1];
    if (nullptr == _pFileBuffer)
    {
        funcFreeResrc(FILE_BUFFER_NULL);
    }

    memset(_pFileBuffer, 0, _nFileSize + 1);
    fread(_pFileBuffer, _nFileSize, 1, _fp);
    if (ferror(_fp))
    {
        funcFreeResrc(FILE_READ_ERROR);
    }
}

void HexLoader::funcGenerateTable()
{
    unsigned int nColCount = 16;
    unsigned int nAsciiColLoopCnt = 0;
    unsigned int nAsciiRowLoopCnt = 0;
    unsigned int nRowRount = _nFileSize / nColCount + 1;
    QStringList headerHor;
    QStringList headerVer;

    for (unsigned int i = 0; i < nColCount; ++i)
    {
        QString str = QString::number(i, 16);
        headerHor << str.toUpper();
    }

    for (unsigned int i = 0; i < nRowRount; ++i)
    {
        QString str = QString::number(i * 16, 10);
        QString strDup = QString("%1%2").arg(str.toUInt(), 8, 16, QLatin1Char('0')).arg("(H)");
        headerVer << strDup.toUpper();
    }

    ui.tableWidget_hex->clear();
    ui.tableWidget_hex->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui.tableWidget_hex->setColumnCount(nColCount);
    ui.tableWidget_hex->setRowCount(nRowRount);
    ui.tableWidget_hex->setHorizontalHeaderLabels(headerHor);
    ui.tableWidget_hex->setVerticalHeaderLabels(headerVer);
    ui.tableWidget_hex->horizontalHeader()->setFont(QFont("Consolas", 9, QFont::Normal));
    ui.tableWidget_hex->verticalHeader()->setFont(QFont("Consolas", 9, QFont::Normal));
    ui.tableWidget_hex->horizontalHeader()->setDefaultSectionSize(21);
    ui.tableWidget_hex->verticalHeader()->setDefaultSectionSize(21);
    ui.tableWidget_hex->setAlternatingRowColors(true);
    ui.tableWidget_hex->horizontalHeader()->setStyleSheet("QHeaderView::section{background:gray;color:white;}");
    ui.tableWidget_hex->verticalHeader()->setStyleSheet("QHeaderView::section{background:gray;color:white;}");

    for (unsigned int i = 0; i < nRowRount; ++i)
    {
        for (unsigned int j = 0; j < nColCount; ++j)
        {
            QTableWidgetItem* item = nullptr;
            if (i * 16 + j < _nFileSize)
            {
                QString str = QString::number(_pFileBuffer[i * 16 + j], 10);
                int nTemp = 0xFF;
                nTemp = nTemp & str.toInt();
                QString strDup = QString("%1").arg(nTemp, 2, 16, QLatin1Char('0'));

                item = new QTableWidgetItem(strDup.toUpper());
                item->setTextAlignment(Qt::AlignCenter);
                item->setFont(QFont("Consolas", 9, QFont::Normal));
                item->setData(ROW_DATA, i);
                item->setData(COL_DATA, j);
                item->setData(IS_UPDATE, false);
                item->setData(IS_ERROR, false);

                ui.tableWidget_hex->setItem(i, j, item);
            }
            else
            {
                item = new QTableWidgetItem(" ");
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
                ui.tableWidget_hex->setItem(i, j, item);
            }    
        }
    }

    headerHor << " ";
    for (unsigned int i = nColCount + 1; i < nColCount + 17; ++i)
    {
        QString str = QString::number(nAsciiRowLoopCnt++, 16);
        headerHor << str.toUpper();
    }

    nAsciiRowLoopCnt = 0;

    ui.tableWidget_hex->setColumnCount(nColCount + 17);
    ui.tableWidget_hex->setHorizontalHeaderLabels(headerHor);

    for (unsigned int i = 0; i < nRowRount; ++i)
    {
        for (unsigned int j = nColCount + 1; j < nColCount + 17; ++j)
        {
            QTableWidgetItem* item = nullptr;
            if (i * 16 + j - 17 < _nFileSize)
            {
                unsigned int nTemp = nAsciiRowLoopCnt * 16 + nAsciiColLoopCnt;
                char str[2] = { 0 };
                str[0] = _pFileBuffer[nTemp];

                item = new QTableWidgetItem(str);
                item->setTextAlignment(Qt::AlignCenter);
                item->setFont(QFont("Consolas", 9, QFont::Normal));
                item->setData(ROW_DATA, i);
                item->setData(COL_DATA, j);
                item->setData(IS_UPDATE, false);
                item->setData(IS_ERROR, false);

                ui.tableWidget_hex->setItem(i, j, item);
                ++nAsciiColLoopCnt;
            }
            else
            {
                item = new QTableWidgetItem(" ");
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
                ui.tableWidget_hex->setItem(i, j, item);
            }
        }
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setBackgroundColor(Qt::white);
        item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
        ui.tableWidget_hex->setItem(i, nColCount, item);
        ++nAsciiRowLoopCnt;
        nAsciiColLoopCnt = 0;
    }
}

void HexLoader::slotCloseProgram()
{
    funcFreeResrc();
    exit(0);
}

void HexLoader::funcTotalLoadOp()
{
    funcLoadResrc();
    funcGenerateTable();
    funcSetTitleIsEdit(false);
    
    QString strDup = QString::number(_nFileSize, 10);
    __STATUSBAR__(FILE_READ_COMPLETED, strDup);

    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
            this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));
    connect(ui.tableWidget_hex, SIGNAL(itemSelectionChanged()), 
            this, SLOT(slotSelectionItemBackGround()));
}

bool HexLoader::funcCheckItemText(const QString& str)
{
    char* pTemp = new char[str.size() + 1];
    memcpy(pTemp, str.toStdString().c_str(), str.size());

    for (int i = 0; i < str.size(); ++i)
    {
        if (pTemp[i] >= '0' && pTemp[i] <= '9')
        {
            continue;
        }
        if (pTemp[i] >= 'a' && pTemp[i] <= 'z')
        {
            pTemp[i] = pTemp[i] - 32;
        }
        if (pTemp[i] > 'F' || pTemp[i] < 'A')
        {
            if (nullptr != pTemp)
            {
                delete[] pTemp;
                pTemp = nullptr;
            }
            return false;
        }
    }

    if (nullptr != pTemp)
    {
        delete[] pTemp;
        pTemp = nullptr;
    }

    return true;
}

void HexLoader::funcModifyDstItemData(QTableWidgetItem* itemSrc, const bool isUpdate, const bool isError)
{
    unsigned int nRow = itemSrc->data(ROW_DATA).toUInt();
    unsigned int nColumn = itemSrc->data(COL_DATA).toUInt();
    QTableWidgetItem* itemDst;

    if (nColumn < 17)
    {
        itemDst = ui.tableWidget_hex->item(nRow, nColumn + 17);      
    }
    else
    {
        itemDst = ui.tableWidget_hex->item(nRow, nColumn - 17);
    }

    itemDst->setData(IS_UPDATE, isUpdate);
    itemDst->setData(IS_ERROR, isError);

    if (isUpdate)
    { 
        itemDst->setBackgroundColor(Qt::green);
    }
    else
    {
        itemDst->setBackgroundColor(Qt::red);
    }
}

void HexLoader::funcSetUpdationItemRG(QTableWidgetItem* itemSrc, const bool isUpdate, const bool isError)
{
    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
               this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    itemSrc->setData(IS_UPDATE, isUpdate);
    itemSrc->setData(IS_ERROR, isError);
    if (isUpdate)
    {
        itemSrc->setBackgroundColor(Qt::green);
    }
    else
    {
        itemSrc->setBackgroundColor(Qt::red);
    }  

    funcModifyDstItemData(itemSrc, isUpdate, isError);

    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
            this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    slotSelectionItemBackGround();
}

void HexLoader::slotUpdationItemBackGround(QTableWidgetItem* item)
{
    unsigned int nColumn = item->data(COL_DATA).toUInt();
    if (nColumn < 17)
    {
        bool bCheck = funcCheckItemText(item->text());
        if (item->text().size() > 2 || !bCheck)
        {
            funcSetUpdationItemRG(item, false, true);
            return;
        }
    }
    else
    {
        if (item->text().size() >= 2)
        {
            funcSetUpdationItemRG(item, false, true);
            return;
        }
    }

    _queueSave.enqueue(item);

    funcSetUpdationItemRG(item, true, false);
    funcSetTitleIsEdit(true);
}

bool HexLoader::funcRecoveryBgOfAsciiOrHex(const int nLoopCount, const int nDif)
{
    int nRow = _listItemAddrInfo[nLoopCount]->row();
    int nColDst = _listItemAddrInfo[nLoopCount]->column() + nDif;
    int nColSrc = _listItemAddrInfo[nLoopCount]->column();
    QTableWidgetItem* itemDst = ui.tableWidget_hex->item(nRow, nColDst);
    QTableWidgetItem* itemSrc = ui.tableWidget_hex->item(nRow, nColSrc);

    if (itemSrc->data(IS_UPDATE).toBool())
    {
        itemDst->setBackgroundColor(Qt::green);
        return false;
    }

    if (itemSrc->data(IS_ERROR).toBool())
    {
        itemDst->setBackgroundColor(Qt::red);
        return false;
    }

    if (0 == _listItemAddrInfo[nLoopCount]->row() % 2)
    {
        itemDst->setBackgroundColor(Qt::white);
    }
    else
    {
        itemDst->setBackgroundColor(_color);
    }

    return true;
}

void HexLoader::funcClearListAndRecoveryBg()
{
    if (!_listItemAddrInfo.isEmpty())
    {
        for (unsigned int i = 0; i < _listItemAddrInfo.size(); ++i)
        {
            if (_listItemAddrInfo[i]->column() < 17)
            {
                if (!funcRecoveryBgOfAsciiOrHex(i, 17))
                {
                    continue;
                }
            }
            else
            {
                if (!funcRecoveryBgOfAsciiOrHex(i, -17))
                {
                    continue;
                }
            }
        }

        _listItemAddrInfo.clear();
    }
}

void HexLoader::funcGenarateSelectionBg(const int nRow, const int nColumn, const int nDif)
{
    QTableWidgetItem* itemSrc = ui.tableWidget_hex->item(nRow, nColumn);
    QTableWidgetItem* itemDst = ui.tableWidget_hex->item(nRow, nColumn + nDif);
    if (itemSrc->data(IS_UPDATE).toBool())
    {
        if (nDif < 0)
        {
            funcSetAsciiToItem(itemDst, itemSrc->text());
        }
        else
        {
            funcSetCharToItem(itemDst, itemSrc->text());
        }

        itemDst->setBackgroundColor(Qt::green);
    }
    else if (itemSrc->data(IS_ERROR).toBool())
    {
        itemDst->setBackgroundColor(Qt::red);
    }
    else
    {
        itemDst->setBackgroundColor(Qt::yellow);  
    }
    
    _listItemAddrInfo.append(itemSrc);
}

void HexLoader::slotSelectionItemBackGround()
{
    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
               this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    funcClearListAndRecoveryBg();

    QModelIndexList indexes = ui.tableWidget_hex->selectionModel()->selectedIndexes();
    for (unsigned int i = 0; i < indexes.size(); ++i)
    {
        if (indexes[i].column() < 17)
        {
            funcGenarateSelectionBg(indexes[i].row(), indexes[i].column(), 17);
        }
        else
        {
            funcGenarateSelectionBg(indexes[i].row(), indexes[i].column(), -17);
        }
    }

    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
            this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));
}

void HexLoader::funcGenerateHashAsciiKey()
{
     char szTemp[128][2] = 
     {
         " ", " ", " ", " ", " ", " ", " ", " ",
         " ", " ", " ", " ", " ", " ", " ", " ",
         " ", " ", " ", " ", " ", " ", " ", " ",
         " ", " ", " ", " ", " ", " ", " ", " ",
         " ", "!", "\"", "#", "$", "%", "&", "'",
         "(", ")", "*", "+", ",", "-", ".", "/",
         "0", "1", "2", "3", "4", "5", "6", "7",
         "8", "9", ":", ";", "<", "=", ">", "?",
         "@", "A", "B", "C", "D", "E", "F", "G",
         "H", "I", "J", "K", "L", "M", "N", "O",
         "P", "Q", "R", "S", "T", "U", "V", "W",
         "X", "Y", "Z", "[", "\\", "]", "^", "_",
         "`", "a", "b", "c", "d", "e", "f", "g",
         "h", "i", "j", "k", "l", "m", "n", "o",
         "p", "q", "r", "s", "t", "u", "v", "w",
         "x", "y", "z", "{", "|", "}", "~", " "
     };

     for (int i = 0; i < 128; ++i)
     {
         _hashAsciiKey.insert(i, QString("%1").arg(szTemp[i]));
     }
}

void HexLoader::funcGenerateHashCharKey()
{
    for (int i = 0; i < _hashAsciiKey.size(); ++i)
    {
        QString szKey = _hashAsciiKey.value(i);
        _hashCharKey.insert(szKey, i);
    }
}

void HexLoader::funcWriteDataToFile(FILE* fp)
{
    QString str;
    if (!_queueSave.isEmpty())
    {
        QTableWidgetItem* item = nullptr;
        unsigned int nColumn = 0;
        unsigned int nRow = 0;
        unsigned int nLoop = _queueSave.size();
        QString value;
        QString text;
        bool ok;
        for (unsigned int i = 0; i < nLoop; ++i)
        {
            item = _queueSave.dequeue();
            nColumn = item->column();
            nRow = item->row();
            text = item->text();
            if (nColumn < 17)
            {
                _pFileBuffer[nRow * 16 + nColumn] = text.toInt(&ok, 16);
            }
            else
            {       
                _pFileBuffer[nRow * 16 + nColumn - 17] = text.toStdString().c_str()[0];
            }
        }
    }

    fseek(fp, 0L, SEEK_SET);
    fwrite(_pFileBuffer, _nFileSize, 1, fp);
    if (ferror(fp))
    {
        __STATUSBAR__(FILE_WRITE_ERROR, str);
    }

    fflush(fp);
    __STATUSBAR__(FILE_WRITE_COMPLETED, str);

    funcSetTitleIsEdit(false);
}

void HexLoader::slotSaveData()
{
    if (nullptr == _pFileName || nullptr == _pFileBuffer)
    {
        return;
    }
    funcWriteDataToFile(_fp);
}

void HexLoader::slotSaveAsData()
{
    if (nullptr == _pFileName || nullptr == _pFileBuffer)
    {
        return;
    }

    std::string fileName = _pFileName;
    std::string suffix = fileName.substr(fileName.find_last_of(".") + 1);
    QString format = "File(*.";
    format = format + suffix.c_str() + ")";
    QString str = QFileDialog::getSaveFileName(this, "Save As Dialog", QDir::homePath(), format);
    if (str.isEmpty())
    {
        return;
    }

    FILE* fp = fopen(str.toStdString().c_str(), "w");
    if (nullptr == fp)
    {
        __STATUSBAR__(FILE_WRITE_ERROR, str);
        return;
    }

    funcWriteDataToFile(fp);

    if (nullptr != fp)
    {
        fclose(fp);
        fp = nullptr;
    }
}

void HexLoader::funcSetTitleIsEdit(const bool isEdit)
{
    QString str;
    if (isEdit)
    {
        str = "HexLoader - ";
        str = str + QString::fromLocal8Bit(_pFileName) + "*"; 
    }
    else
    {
        str = "HexLoader - ";
        str = str + QString::fromLocal8Bit(_pFileName); 
    }
    this->setWindowTitle(str);
}

void HexLoader::funcSetCharToItem(QTableWidgetItem* itemDst, const QString& str)
{
    bool ok;
    int nKey = str.toUInt(&ok, 16);
    QString value = _hashAsciiKey.value(nKey);
    itemDst->setText(value);
}

void HexLoader::funcSetAsciiToItem(QTableWidgetItem* itemDst, const QString& str)
{
    int nValue = _hashCharKey.value(str);
    QString strDup = QString("%1").arg(nValue, 2, 16, QLatin1Char('0'));
    itemDst->setText(strDup.toUpper());
}

QTableWidgetItem* HexLoader::funcStackWriteDataToBuffer(QStack<QHash<QTableWidgetItem*, QString>>& stack, 
                                                        QStack<QTableWidgetItem*>& stackAddr,
                                                        QStack<QHash<QTableWidgetItem*, QString>>& stackReverse,
                                                        QStack<QTableWidgetItem*>& stackAddrReverse)
{
    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
                                          this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    QHash<QTableWidgetItem*, QString> hash = stack.pop();
    QTableWidgetItem* itemSrc = stackAddr.pop();
    QTableWidgetItem* itemDst = nullptr;
    unsigned int nColumn = itemSrc->column();
    unsigned int nRow = itemSrc->row();
    QString text = hash.value(itemSrc);
    bool ok;

    if (nColumn < 17)
    {
        _pFileBuffer[nRow * 16 + nColumn] = text.toInt(&ok, 16);
        itemDst = ui.tableWidget_hex->item(nRow, nColumn + 17);
        funcSetCharToItem(itemDst, text);
    }
    else
    {
        _pFileBuffer[nRow * 16 + nColumn - 17] = text.toStdString().c_str()[0];
        itemDst = ui.tableWidget_hex->item(nRow, nColumn - 17);
        funcSetAsciiToItem(itemDst, text);
    } 

    QHash<QTableWidgetItem*, QString> hashDup;
    hashDup.insert(itemSrc, itemSrc->text());
    stackReverse.push(hashDup);
    stackAddrReverse.push(itemSrc);

    itemSrc->setText(text);
    itemSrc->setBackgroundColor(Qt::magenta);
    itemDst->setBackgroundColor(Qt::magenta);

    funcSetTitleIsEdit(true);

    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
                                       this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    return itemSrc;
}

void HexLoader::slotRedo()
{
    if (_stackRedo.isEmpty())
    {
        return;
    }

    QTableWidgetItem* itemSrc = funcStackWriteDataToBuffer(_stackRedo, _stackRedoAddr, 
                                                           _stackUndo, _stackUndoAddr);
    _queueSave.enqueue(itemSrc); 
}

void HexLoader::slotUndo()
{
    if (_stackUndo.isEmpty())
    {
        return;
    }

    funcStackWriteDataToBuffer(_stackUndo, _stackUndoAddr,
                               _stackRedo, _stackRedoAddr);

    if (!_queueSave.isEmpty())
    {
        _queueSave.pop_back();
    }
}

void HexLoader::funcPushDataToUndoStack(QTableWidgetItem* item)
{
    QHash<QTableWidgetItem*, QString> hash;
    hash.insert(item, item->text());
    _stackUndo.push(hash);
    _stackUndoAddr.push(item);
}

void HexLoader::keyPressEvent(QKeyEvent* evnt)
{
    if (evnt->key() == Qt::Key_Tab        || evnt->key() == Qt::Key_CapsLock ||
        evnt->key() == Qt::Key_Shift      || evnt->key() == Qt::Key_Control  ||
        evnt->key() == Qt::Key_Alt        || evnt->key() == Qt::Key_Enter    ||
        evnt->key() == Qt::Key_NumLock    || evnt->key() == Qt::Key_Print    ||
        evnt->key() == Qt::Key_ScrollLock || evnt->key() == Qt::Key_Pause    ||
        evnt->key() == Qt::Key_Escape     || evnt->key() == Qt::Key_Insert   ||
        evnt->key() == Qt::Key_Home       || evnt->key() == Qt::Key_PageUp   ||
        evnt->key() == Qt::Key_PageDown   || evnt->key() == Qt::Key_Delete   ||
        evnt->key() == Qt::Key_End        || evnt->key() == Qt::Key_HomePage ||
        evnt->key() == Qt::Key_F1         || evnt->key() == Qt::Key_F2       ||
        evnt->key() == Qt::Key_F3         || evnt->key() == Qt::Key_F4       ||
        evnt->key() == Qt::Key_F5         || evnt->key() == Qt::Key_F6       ||
        evnt->key() == Qt::Key_F7         || evnt->key() == Qt::Key_F8       ||
        evnt->key() == Qt::Key_F9         || evnt->key() == Qt::Key_F10      ||
        evnt->key() == Qt::Key_F11        || evnt->key() == Qt::Key_F12      ||
        evnt->key() == Qt::Key_SysReq     || evnt->key() == Qt::Key_Clear    ||
        evnt->key() == Qt::Key_Return     || evnt->key() == Qt::Key_Backtab  ||
        evnt->key() == Qt::Key_Left       || evnt->key() == Qt::Key_Up       ||
        evnt->key() == Qt::Key_Right      || evnt->key() == Qt::Key_Down     ||
        evnt->key() == Qt::Key_AltGr)
    {
        return;
    }
    
    QTableWidgetItem* item = ui.tableWidget_hex->currentItem();
    funcPushDataToUndoStack(item);
}

void HexLoader::slotScroll(int nValue)
{
    _nScrollAsciiValue = nValue;
    _nScrollCharValue = nValue;
    _nFromAscii = nValue * 16;
    _nFromChar = nValue * 16;
}

void HexLoader::slotFindAsciiPushButton()
{
    if (nullptr == _pFileBuffer)
    {
        return;
    }

    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
                                          this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    QScrollBar* vScrollBar = ui.tableWidget_hex->verticalScrollBar();
    QString text = _editFind->text();
    QString buffer = _pFileBuffer;
    bool ok;
    int nValue = text.toInt(&ok, 16);
    int nAddr = 0;
    int nCount = 0;
    int nDif = 0;
    
    for (unsigned int i = _nFromAscii; i < buffer.size(); ++i)
    {
        nAddr = reinterpret_cast<int>(&_pFileBuffer[i]);
        if (nValue == _pFileBuffer[i])
        {
            nDif = nAddr - reinterpret_cast<int>(_pFileBuffer);
            _nFromAscii = nDif + 1;
            nCount = i;
            break;
        }
    }

    if (nAddr >= reinterpret_cast<int>(_pFileBuffer + buffer.size() - 1))
    {
        _nFromAscii = 0;
        _nScrollAsciiValue = 0;
        for (unsigned int i = _nFromAscii; i < buffer.size(); ++i)
        {
            nAddr = reinterpret_cast<int>(&_pFileBuffer[i]);
            if (nValue == _pFileBuffer[i])
            {
                nDif = nAddr - reinterpret_cast<int>(_pFileBuffer);
                _nFromAscii = nDif + 1;
                nCount = i;
                break;
            }
        }
    }

    if (nullptr != vScrollBar)
    {
        vScrollBar->setValue(nCount / 16);
    }

    unsigned int nRow = 0;
    unsigned int nColumn = 0;
    if (nCount < 16)
    {
        nColumn = nCount;
    }
    else
    {
        nColumn = nCount % 16;
        nRow = nCount / 16;
    }

    QTableWidgetItem* item = ui.tableWidget_hex->item(nRow, nColumn + 17);
    ui.tableWidget_hex->setItemSelected(item, true);
    slotSelectionItemBackGround();
    
    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
                                       this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));
}

void HexLoader::slotFindCharPushButton()
{
    if (nullptr == _pFileBuffer)
    {
        return;
    }

    disconnect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)), 
                                          this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));

    QString text = _editFind->text();
    QString buffer = _pFileBuffer;

    int nAddr = buffer.indexOf(text, _nFromChar);
    if (nAddr < 0xFFFFFFFF)
    {
        _nFromChar = nAddr + 1;
    }
    else
    {
        nAddr = buffer.indexOf(text);
        _nFromChar = nAddr + 1;
        _nScrollCharValue = 0;
    }

    QScrollBar* vScrollBar = ui.tableWidget_hex->verticalScrollBar();
    if (nullptr != vScrollBar)
    {
        vScrollBar->setValue(nAddr / 16);
    }

    unsigned int nRow = 0;
    unsigned int nColumn = 0;
    if (nAddr < 16)
    {
        nColumn = nAddr;
    }
    else
    {
        nColumn = nAddr % 16;
        nRow = nAddr / 16;
    }

    QTableWidgetItem* item = nullptr;
    for (unsigned int i = 0; i < text.size(); ++i)
    {
        item = ui.tableWidget_hex->item(nRow, nColumn + i);
        ui.tableWidget_hex->setItemSelected(item, true);
        slotSelectionItemBackGround();
    }

    connect(ui.tableWidget_hex, SIGNAL(itemChanged(QTableWidgetItem*)),
                                       this, SLOT(slotUpdationItemBackGround(QTableWidgetItem*)));
}

void HexLoader::slotFind()
{
    _dlgFind->show();
}

void HexLoader::slotAbout()
{
    _dlgAbout->show();
}
