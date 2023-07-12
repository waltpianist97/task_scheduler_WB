#include "scheduler.h"
#include <QSystemTrayIcon>
#include <QMessageBox>

Scheduler::Scheduler(QWidget *parent)
    : QMainWindow(parent)
    /** Costruttore dello scheduler **/

{
    //creazione del layout di base
    main_layout = new QVBoxLayout;
    main_layout->setSizeConstraint(QLayout::SetMinimumSize);

    QWidget *central_widget = new QWidget(this);
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
    this->setWindowTitle("Task Scheduler");

    //icona
    this->setWindowIcon(QIcon(":/myappico.png"));

    //system tray icon
    my_system_tray_icon = new QSystemTrayIcon(this);
    my_system_tray_icon->setIcon(QIcon(":/myappico.png"));
    my_system_tray_icon->setVisible(true);

    /*questi sono i task per stampare il testo in debug e controllare la presenza del file
    dopo aver inserito i campi nei rispettivi QLineEdit. I parametri indicano il tipo di widget
    e la durata del task singolo. Miglioramento possibile: creare per ogni tipo di task una sottoclasse del TaskWidget di base.*/
    TaskWidget *task_widget_text = new TaskWidget(this,1,1000);
    main_layout->addWidget(task_widget_text);
    TaskWidget *taskWidget_file = new TaskWidget(this,2,2000);
    main_layout->addWidget(taskWidget_file);

    //questo, a scopo puramente dimostrativo, è un bottone che aggiunge
    //un dummy task
    QPushButton *add_task_widget = new QPushButton("Add new task",this);
    main_layout->addWidget(add_task_widget);
    connect(add_task_widget, SIGNAL(clicked()), this, SLOT(add_task()));

}

Scheduler::~Scheduler()
{
    /** Metodo distruttore, che elimina i tasks dallo scheduler **/

    for (TaskWidget *task_widget : task_widgets) {
        delete task_widget;
    }

    task_widgets.clear();
}


void Scheduler::add_task(){
    /** Metodo che aggiunge un nuovo task alla GUI **/
    TaskWidget *task_widget = new TaskWidget(this);
    main_layout->addWidget(task_widget);
    task_widgets.append(task_widget);

    //esempio di notifica da parte del system tray icon
    my_system_tray_icon->showMessage(tr("Attenzione"),tr("E' stato inserito un nuovo task!"));
}


