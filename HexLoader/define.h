#ifndef DEFINE_H
#define DEFINE_H

#define ROW_DATA  0x0101
#define COL_DATA  0x0102
#define IS_UPDATE 0x0103
#define IS_ERROR  0x0104

#define FILENAME_NULL        0
#define FILE_EXIST_FALSE     1
#define FILE_BUFFER_NULL     2
#define FILE_POINTER_NULL    3
#define FILE_READ_ERROR      4

#define FILE_WRITE_ERROR     0xF0
#define FILE_WRITE_COMPLETED 0xF1
#define FILE_READ_COMPLETED  0xF2

#define __PRINT_DEBUGINFO__(TYPE) \
        do \
        { \
            switch (TYPE) \
            { \
            case FILENAME_NULL: \
                qDebug() << "FILENAME_NULL"; \
                break; \
            case FILE_EXIST_FALSE: \
                qDebug() << "FILE_EXIST_FALSE"; \
                break; \
            case FILE_BUFFER_NULL: \
                qDebug() << "FILE_BUFFER_NULL"; \
                break; \
            case FILE_POINTER_NULL: \
                qDebug() << "FILE_POINTER_NULL"; \
                break; \
            case FILE_READ_ERROR: \
                qDebug() << "FILE_READ_ERROR"; \
                break; \
            default: \
                break; \
            } \
        } while (0)

#define __STATUSBAR__(TYPE, STRING) \
        do \
        { \
        switch (TYPE) \
            { \
            case FILE_WRITE_ERROR: \
                ui.statusBar->showMessage("Console: [ Write buffer data to file error! ]"); \
                break; \
            case FILE_WRITE_COMPLETED: \
                ui.statusBar->showMessage("Console: [ Write buffer data to file completed! ]"); \
                break; \
            case FILE_READ_COMPLETED: \
                ui.statusBar->showMessage("Console: [ Read file data to buffer completed! ] { Size: " + STRING + " }"); \
                break; \
            default: \
                break; \
            } \
        } while (0)

typedef struct _tagHashAndItem
{
    QHash<QTableWidgetItem*, QString> hash;
    QTableWidgetItem* item;
} tagHashAndItem;

#endif