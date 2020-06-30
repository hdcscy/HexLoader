/********************************************************************************
** Form generated from reading UI file 'hexloader.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEXLOADER_H
#define UI_HEXLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HexLoaderClass
{
public:
    QAction *action_open;
    QAction *action_close;
    QAction *action_undo;
    QAction *action_redo;
    QAction *action_save;
    QAction *action_saveas;
    QAction *action_find;
    QAction *action_openfile;
    QAction *action_about;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget_hex;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuAbout;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *HexLoaderClass)
    {
        if (HexLoaderClass->objectName().isEmpty())
            HexLoaderClass->setObjectName(QStringLiteral("HexLoaderClass"));
        HexLoaderClass->resize(840, 768);
        HexLoaderClass->setMinimumSize(QSize(840, 0));
        HexLoaderClass->setMaximumSize(QSize(16777215, 16777215));
        HexLoaderClass->setStyleSheet(QStringLiteral(""));
        action_open = new QAction(HexLoaderClass);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_close = new QAction(HexLoaderClass);
        action_close->setObjectName(QStringLiteral("action_close"));
        action_undo = new QAction(HexLoaderClass);
        action_undo->setObjectName(QStringLiteral("action_undo"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/HexLoader/Resources/revoke.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_undo->setIcon(icon);
        action_redo = new QAction(HexLoaderClass);
        action_redo->setObjectName(QStringLiteral("action_redo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/HexLoader/Resources/revert.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_redo->setIcon(icon1);
        action_save = new QAction(HexLoaderClass);
        action_save->setObjectName(QStringLiteral("action_save"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/HexLoader/Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_save->setIcon(icon2);
        action_saveas = new QAction(HexLoaderClass);
        action_saveas->setObjectName(QStringLiteral("action_saveas"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/HexLoader/Resources/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_saveas->setIcon(icon3);
        action_find = new QAction(HexLoaderClass);
        action_find->setObjectName(QStringLiteral("action_find"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/HexLoader/Resources/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_find->setIcon(icon4);
        action_openfile = new QAction(HexLoaderClass);
        action_openfile->setObjectName(QStringLiteral("action_openfile"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/HexLoader/Resources/open_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_openfile->setIcon(icon5);
        action_about = new QAction(HexLoaderClass);
        action_about->setObjectName(QStringLiteral("action_about"));
        centralWidget = new QWidget(HexLoaderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableWidget_hex = new QTableWidget(centralWidget);
        tableWidget_hex->setObjectName(QStringLiteral("tableWidget_hex"));
        tableWidget_hex->setEditTriggers(QAbstractItemView::AnyKeyPressed);
        tableWidget_hex->setGridStyle(Qt::DashLine);

        horizontalLayout->addWidget(tableWidget_hex);

        HexLoaderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HexLoaderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 840, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        HexLoaderClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(HexLoaderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HexLoaderClass->setStatusBar(statusBar);
        toolBar = new QToolBar(HexLoaderClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        HexLoaderClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menu->addAction(action_open);
        menu->addAction(action_close);
        menuAbout->addAction(action_about);
        toolBar->addAction(action_openfile);
        toolBar->addSeparator();
        toolBar->addAction(action_save);
        toolBar->addAction(action_saveas);
        toolBar->addSeparator();
        toolBar->addAction(action_undo);
        toolBar->addAction(action_redo);
        toolBar->addSeparator();
        toolBar->addAction(action_find);

        retranslateUi(HexLoaderClass);

        QMetaObject::connectSlotsByName(HexLoaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *HexLoaderClass)
    {
        HexLoaderClass->setWindowTitle(QApplication::translate("HexLoaderClass", "HexLoader", 0));
        action_open->setText(QApplication::translate("HexLoaderClass", "Open", 0));
        action_close->setText(QApplication::translate("HexLoaderClass", "Close", 0));
        action_undo->setText(QApplication::translate("HexLoaderClass", "undo", 0));
#ifndef QT_NO_TOOLTIP
        action_undo->setToolTip(QApplication::translate("HexLoaderClass", "undo(ctrl+z)", 0));
#endif // QT_NO_TOOLTIP
        action_undo->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+Z", 0));
        action_redo->setText(QApplication::translate("HexLoaderClass", "redo", 0));
#ifndef QT_NO_TOOLTIP
        action_redo->setToolTip(QApplication::translate("HexLoaderClass", "redo(ctrl+y)", 0));
#endif // QT_NO_TOOLTIP
        action_redo->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+Y", 0));
        action_save->setText(QApplication::translate("HexLoaderClass", "save", 0));
#ifndef QT_NO_TOOLTIP
        action_save->setToolTip(QApplication::translate("HexLoaderClass", "save(ctrl+s)", 0));
#endif // QT_NO_TOOLTIP
        action_save->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+S", 0));
        action_saveas->setText(QApplication::translate("HexLoaderClass", "saveas", 0));
#ifndef QT_NO_TOOLTIP
        action_saveas->setToolTip(QApplication::translate("HexLoaderClass", "save as(ctrl+a)", 0));
#endif // QT_NO_TOOLTIP
        action_saveas->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+A", 0));
        action_find->setText(QApplication::translate("HexLoaderClass", "find", 0));
#ifndef QT_NO_TOOLTIP
        action_find->setToolTip(QApplication::translate("HexLoaderClass", "find(ctrl+f)", 0));
#endif // QT_NO_TOOLTIP
        action_find->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+F", 0));
        action_openfile->setText(QApplication::translate("HexLoaderClass", "openfile", 0));
#ifndef QT_NO_TOOLTIP
        action_openfile->setToolTip(QApplication::translate("HexLoaderClass", "open file(ctrl+o)", 0));
#endif // QT_NO_TOOLTIP
        action_openfile->setShortcut(QApplication::translate("HexLoaderClass", "Ctrl+O", 0));
        action_about->setText(QApplication::translate("HexLoaderClass", "About", 0));
        menu->setTitle(QApplication::translate("HexLoaderClass", "File", 0));
        menuAbout->setTitle(QApplication::translate("HexLoaderClass", "Other", 0));
        toolBar->setWindowTitle(QApplication::translate("HexLoaderClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class HexLoaderClass: public Ui_HexLoaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEXLOADER_H
