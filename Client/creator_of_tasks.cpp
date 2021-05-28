#include "creator_of_tasks.h"
#include "ui_creator_of_tasks.h"
#include "tool.h"

Creator_of_tasks::Creator_of_tasks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Creator_of_tasks)
{
    ui->setupUi(this);
    ui->cm2->hide();
    ui->ln2->hide();
    ui->label_2->hide();
    ui->task_text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->create->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->cm2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->ln2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->box->setStyleSheet("QGroupBox { font-size: 20px; font-weight: bold; border: 1px solid grey}");
    ui->create->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");
    ui->pushButton->setStyleSheet("QPushButton{background: grey; border: 2px solid black; font: bold 40px;}"
                     "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 white, stop:0.5 grey, stop:1 white); border:1px solid black;}");

    n_player = new QMediaPlayer();
    n_playlist = new QMediaPlaylist(n_player);

    n_player->setPlaylist(n_playlist);
    n_playlist->addMedia(QUrl("qrc:/sound/but1.wav"));
    n_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

Creator_of_tasks::~Creator_of_tasks()
{
    delete ui;
}

void Creator_of_tasks::on_pushButton_clicked()
{
    n_player->play();
    m->showFullScreen();
    this->hide();
}

void Creator_of_tasks::on_comboBox_activated(const QString &arg1)
{
    ui->label_2->show();
    if(arg1 == "Button") {
        ui->ln2->hide();
        ui->cm2->clear();
        ui->cm2->show();
        ui->cm2->addItem("ON");
        ui->cm2->addItem("OFF");
    } else if(arg1 == "Slider" or arg1 == "Dial"){
        int n = 4;
        if (arg1 == "Dial") {
            n = 10;
        }
        ui->ln2->hide();
        ui->cm2->clear();
        ui->cm2->show();
        for (int i = 1; i <= n; ++i) {
            ui->cm2->addItem(QString::number(i));
        }
    } else {
        ui->cm2->hide();
        ui->ln2->clear();
        ui->ln2->show();
    }
}

void Creator_of_tasks::on_create_clicked()
{
    n_player->play();
    //cr_ts.push_back({ui->comboBox->currentText()})
}
