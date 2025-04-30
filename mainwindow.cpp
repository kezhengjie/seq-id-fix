#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, &QPushButton::clicked, [&]() -> void {
        this->OnPushButtonClicked();
    });
}

void MainWindow::OnPushButtonClicked()
{
    this->ui->plainTextEdit_2->clear();
    const char *sql_template
        = "SELECT setval('{seq}', COALESCE((SELECT MAX(id) FROM {table}), 0) + 1);";
    auto content = this->ui->plainTextEdit->toPlainText();
    auto lines = content.split(QRegularExpression("\r?\n"));
    for (const auto &line : lines) {
        this->ui->plainTextEdit_2->appendPlainText(line);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
