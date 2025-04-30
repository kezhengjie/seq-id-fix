#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, &QPushButton::clicked, [&]() -> void {
        this->OnPushButtonClicked();
    });
}

QStringList splitlines(const QString& str)
{
    return str.split(QRegularExpression("\r?\n"));
}

void MainWindow::OnPushButtonClicked()
{
    this->ui->plainTextEdit_2->clear();
    QString sql_template
        = "SELECT setval('%1', COALESCE((SELECT MAX(id) FROM %2), 0) + 1);";
    auto content = this->ui->plainTextEdit->toPlainText();
    auto lines = splitlines(content);
    for (const auto& line : lines) {
        auto seq = line.simplified();
        if (seq.indexOf("_id_seq") == -1) {
            continue;
        }
        auto table = seq.section("_id_seq", 0, 0).simplified();
        qDebug() << seq;
        qDebug() << table;
        this->ui->plainTextEdit_2->appendPlainText(sql_template.arg(seq, table));
        this->ui->plainTextEdit_2->selectAll();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
