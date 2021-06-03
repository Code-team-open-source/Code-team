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
    ui->sl1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->sl2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->sl3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->sl4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->bt1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->bt2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->cmd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);





    ui->pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->create->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->cm2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->ln2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->label->setFont(QFont("Times", 20));
    ui->label_2->setFont(QFont("Times", 20));
    ui->label_3->setFont(QFont("Times", 20));
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
    ui->bt1->hide();
    ui->bt2->hide();
    ui->cmd->hide();
    ui->sl1->hide();
    ui->sl2->hide();
    ui->sl3->hide();
    ui->sl4->hide();
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
    ui->bt1->hide();
    ui->bt2->hide();
    ui->cmd->hide();
    ui->sl1->hide();
    ui->sl2->hide();
    ui->sl3->hide();
    ui->sl4->hide();
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
    if (arg1 == "Cmd") {
        ui->cmd->show();
    }
}

void Creator_of_tasks::on_create_clicked()
{
    std::vector<std::pair<std::string, std::string>> a;
    if(ui->comboBox->currentText() == "Button") {
        if(ui->bt1->text() != "") {
            a.push_back({"ON", ui->bt1->text().toStdString()});
        }
        if(ui->bt2->text() != "") {
            a.push_back({"OFF", ui->bt2->text().toStdString()});
        }
        if (a.size() > 1) {
            cr_ts.push_back({{"Button", ui->lineEdit->text().toStdString()}, a});
        }
    }
    if(ui->comboBox->currentText() == "Slider") {
        if(ui->sl1->text() != "") {
            a.push_back({"1", ui->sl1->text().toStdString()});
        }
        if(ui->sl2->text() != "") {
            a.push_back({"2", ui->sl2->text().toStdString()});
        }
        if(ui->sl3->text() != "") {
            a.push_back({"3", ui->sl3->text().toStdString()});
        }
        if(ui->sl4->text() != "") {
            a.push_back({"4", ui->sl4->text().toStdString()});
        }
        if (a.size() > 1) {
            cr_ts.push_back({{"Slider", ui->lineEdit->text().toStdString()}, a});
        }
    }
    if(ui->comboBox->currentText() == "Cmd") {
        a.push_back({ui->ln2->text().toStdString(), ui->cmd->text().toStdString()});
        cr_ts.push_back({{"Cmd", ui->lineEdit->text().toStdString()}, a});
    }

    ui->bt1->clear();
    ui->bt2->clear();
    ui->cmd->clear();
    ui->sl1->clear();
    ui->sl2->clear();
    ui->sl3->clear();
    ui->sl4->clear();
    ui->lineEdit->clear();
    ui->ln2->clear();
}

void Creator_of_tasks::on_cm2_activated(const QString &arg1)
{
    ui->bt1->hide();
    ui->bt2->hide();
    ui->cmd->hide();
    ui->sl1->hide();
    ui->sl2->hide();
    ui->sl3->hide();
    ui->sl4->hide();
    if (arg1 == "1") {
        ui->sl1->show();
    }
    if (arg1 == "2") {
        ui->sl2->show();
    }
    if (arg1 == "3") {
        ui->sl3->show();
    }
    if (arg1 == "4") {
        ui->sl4->show();
    }
    if (arg1 == "ON") {
        ui->bt1->show();
    }
    if (arg1 == "OFF") {
        ui->bt2->show();
    }
}
