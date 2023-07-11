#include "filetaskwidget.h"

FileTaskWidget::FileTaskWidget(QWidget *parent) : TaskWidget(parent) {
    path_to_check = new QLineEdit(this);
    label = new QLabel("Enter path",this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    //create the layout
    layout->addWidget(startButton);
    layout->addWidget(label);
    layout->addWidget(path_to_check);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    // Connect signals to slots
    connect(startButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void FileTaskWidget::startTask(){
    QString path = this->path_to_check->text();
    QDir dir(path);
    if(!dir.exists()) {
        qInfo() << "Il file path "<<path<<"non esiste.";
    }
}

