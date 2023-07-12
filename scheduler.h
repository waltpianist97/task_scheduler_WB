#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include "taskwidget.h"
#include <QDebug>
class QSystemTrayIcon;

class Scheduler : public QMainWindow
{
    Q_OBJECT

public:
    Scheduler(QWidget *parent = nullptr);
    ~Scheduler();

private slots:
    void add_task();
private:
    QVBoxLayout *main_layout;
    QVector<TaskWidget*> task_widgets;
    QSystemTrayIcon *my_system_tray_icon;
};


#endif // SCHEDULER_H
