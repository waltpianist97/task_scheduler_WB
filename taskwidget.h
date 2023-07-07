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
class TaskWidget : public QWidget {
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr,int type=0);
    int type_of_task;

private:
    QPushButton *startButton;
    QProgressBar *progressBar;
    QLineEdit *text_to_print;
    QLineEdit *path_to_check;
    QPushButton *deleteWidgetButton;
    QLabel *label;
    void startTask();

private slots:
    void on_button_clicked();
    //void re_enable_button();
    //void updateProgressBar(int value);
    void remove_task();


signals:
    void progressUpdated(int progress);
    void finished();

};

#endif // TASKWIDGET_H
