#include "taskwidget.h"
#include <QDebug>
#include <QLabel>
#include <QDir>
#include <QDirIterator>
#include <unistd.h>
#define TOT_DURATION 20000 // in ms, durata complessiva dell'esecuzione del task


void TaskWidget::create_default_task()
{
    progress_bar = new QProgressBar(this);
    progress_bar->setRange(0, 100);
    delete_widget_button = new QPushButton("X",this);
    //layout
    layout->addWidget(start_button);
    layout->addWidget(progress_bar);
    layout->addWidget(delete_widget_button);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    // Connessione segnali e slots
    connect(delete_widget_button, SIGNAL(clicked()), this, SLOT(remove_task()));
}

void TaskWidget::create_text_print_task()
{
    label = new QLabel("Enter text",this);
    text_to_print = new QLineEdit(this);

    //layout
    layout->addWidget(start_button);
    layout->addWidget(label);
    layout->addWidget(text_to_print);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Connessione segnali e slots
    connect(start_button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void TaskWidget::create_check_file_task()
{
    path_to_check = new QLineEdit(this);
    label = new QLabel("Enter path",this);

    //create the layout
    layout->addWidget(start_button);
    layout->addWidget(label);
    layout->addWidget(path_to_check);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Connect signals to slots
    connect(start_button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

TaskWidget::TaskWidget(QWidget *parent,int type,int duration) : QWidget(parent) {
    /** metodo costruttore del task widget **/

    start_button = new QPushButton("Start", this);
    type_of_task = type;
    task_duration = duration;
    layout = new QHBoxLayout(this);

    //Questo widget rappressenta un "default task", giusto per far vedere come aggiungere/togliere task nuovi
    if(type_of_task==0){
        create_default_task();

    }

    //Task che stampa una stringa su linea di comando
    if(type_of_task==1){

        create_text_print_task();

    }

    //Task che controlla se un certo path esiste. Se non esiste, stampa un messaggio di debug
    if(type_of_task==2){
        create_check_file_task();

    }

}

void TaskWidget::do_task() {
    /** metodo che gestisce il task **/
    if(this->type_of_task==1){
       qInfo()<<this->text_to_print->text();
    }

    if(this->type_of_task==2){
        QString path = this->path_to_check->text();
        QDir dir(path);
        if(!dir.exists()) {
            qInfo() << "Il file path "<<path<<"non esiste.";
        }

    }
}

void TaskWidget::start_task()
{
    int total_duration = TOT_DURATION;
    int dt = this->task_duration;   // intervallo in ms basato sul "Clock" del singolo task
    int num_iterations = total_duration / dt;

    int iteration = 0;
    while(iteration<num_iterations){
        this->do_task();
        usleep(dt*1000);
        iteration++;
    }
}

void TaskWidget::on_button_clicked()
{
    /** Questo metodo viene invocato quando il task viene avviato.
    Fa partire un ciclo while che esegue per una certa durata il task indicato. Se per caso
    un task viene invocato mentre ne viene eseguito un altro, l'applicazione non risponde, in quanto
    il suo main thread è già occupato dall'esecuzione del task corrente. Non appena finisce, parte quello
    successivo. Non sono definiti altri thread al di fuori di quello dell'applicazione. In alternativa il task
    può essere aggiunto ad una QQueue.**/

    // Calcolo del numero totale di iterazioni in base alla durata complessiva e a quella del
    // singolo task
    start_task();

}


void TaskWidget::remove_task(){
    /** Questo metodo rimuove un certo widget/task **/
    deleteLater();

}

