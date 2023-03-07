#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QTextEdit>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    setStyleSheet(QString{"border-left: 2px solid gray;"
                          "border-right: 2px solid gray;"
                          "border-top: 2px solid gray;"
                          "border-bottom: 2px solid gray;"
                          "border-radius : 10px;"});
    setFixedSize(400, 400);
    QVBoxLayout *mainLayout = new QVBoxLayout();

    _label = new QLabel();
    _label->setAlignment(Qt::AlignCenter);
    _label->setPixmap(QPixmap(":/res/icon.svg"));

    QTextEdit *edit = new QTextEdit();
    edit->setStyleSheet(QString{"border-width: 1px;"
                               "border-style: solid;"
                               "margin-top: 0.5ex;"});
    mainLayout->addWidget(edit);
    QObject::connect(edit, &QTextEdit::textChanged, [=]{
        QString tx = edit->toPlainText();
        qDebug() << "text:" << tx;
        QPixmap pix;
        pix.loadFromData(tx.toUtf8());
        _label->setPixmap(pix);
    });
    mainLayout->addWidget(_label, Qt::AlignCenter);

    ui->centralwidget->setLayout(mainLayout);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
   if(!event->mimeData()->urls()[0].fileName().right(3).compare("svg")
           || !event->mimeData()->urls()[0].fileName().right(3).compare("json"))
       event->acceptProposedAction();
    else
       event->ignore();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    const QMimeData*qm = event->mimeData();
    _label->setPixmap(QPixmap(qm->urls()[0].toLocalFile()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

