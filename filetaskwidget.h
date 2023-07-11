#ifndef FILETASKWIDGET_H
#define FILETASKWIDGET_H
#include "taskwidget.h"
#include <QDir>

class FileTaskWidget : public TaskWidget {
    Q_OBJECT
public:
    FileTaskWidget(QWidget *parent = nullptr);

private:
    QLineEdit *path_to_check;
    QLabel *label;
    void startTask();



};

#endif // FILETASKWIDGET_H
