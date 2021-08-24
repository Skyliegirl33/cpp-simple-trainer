#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "zelda_trainer.h"

#include <memory>
#include <string>

ZeldaTrainer trainer(L"RetroArch bsnes 115");
std::wstring modules[] = { L"bsnes_libretro.dll" };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void populate_ui(Ui::MainWindow* ui) {
    ui->itemList->addItem("Bombs");
    ui->itemList->addItem("Arrows");

    ui->rupeeAmount->setText(QString::number(trainer.consumables.rupees));
}

void MainWindow::on_pushButton_clicked() {
    // Scan for process and modules
    trainer.scan_process_mem(1, modules);
    // Populate item consumables
    trainer.populate_consumables();

    populate_ui(ui);
}

void MainWindow::on_itemList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
    ui->itemName->setText(current->text());

    if (current->text() == "Bombs") {
        ui->itemQt->setText(QString::number(trainer.consumables.bombs));
    } else if (current->text() == "Arrows") {
        ui->itemQt->setText(QString::number(trainer.consumables.arrows));
    }
}

