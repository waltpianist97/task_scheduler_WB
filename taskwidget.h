/*Al fine di rendere l'ampliamento del set di task possibile, ho pensato
 di creare un widget che riesca a gestire un task. Nella main window sara' possibile aggiungerne altri*/

#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

class TaskWidget : public QWidget {
    Q_OBJECT
public:
    TaskWidget(QWidget *parent = nullptr,int type = 0,int duration = 1000);
    int type_of_task;
    int task_duration;

protected:
    QPushButton *startButton;
    QProgressBar *progressBar;
    QLineEdit *text_to_print;
    QLineEdit *path_to_check;
    QPushButton *deleteWidgetButton;
    QLabel *label;
    void startTask();

private slots:
    void on_button_clicked();
    void remove_task();


signals:
    void progressUpdated(int progress);
    void finished();

};

#endif // TASKWIDGET_H
