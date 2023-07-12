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
    QHBoxLayout *layout;
protected:

    QPushButton *start_button;
    QProgressBar *progress_bar;
    QLineEdit *text_to_print;
    QLineEdit *path_to_check;
    QPushButton *delete_widget_button;
    QLabel *label;



private slots:
    void on_button_clicked();
    void remove_task();
    void do_task();
    void create_default_task();
    void create_text_print_task();
    void create_check_file_task();
    void start_task();
};

#endif // TASKWIDGET_H
