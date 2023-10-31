#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileSystemModel>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::homePath());  // Початкова директорія
    ui->treeView->setModel(model);
    ui->listView->setModel(model);

    QString sourcePath;  // Оголошення глобальної змінної

    connect(ui->selectDirButton, &QPushButton::clicked, [this]() {
        QString dirPath = QFileDialog::getExistingDirectory(this, tr("Виберіть директорію"), QDir::homePath());
        if (!dirPath.isEmpty()) {
            QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
            if (model) {
                model->setRootPath(dirPath);
                ui->treeView->setRootIndex(model->index(dirPath));
                ui->listView->setRootIndex(model->index(dirPath));
            }
        }
    });
    connect(ui->listView, &QListView::clicked, [this](const QModelIndex &index) {
        if (index.isValid() && index.model() == ui->listView->model()) {
            QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
            if (model) {
                QString dirPath = model->fileInfo(index).absoluteFilePath();
                model->setRootPath(dirPath);
                ui->treeView->setRootIndex(model->index(dirPath));
            }
        }
    });

    connect(ui->copyButton, &QPushButton::clicked, [this]() {
        QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
        QModelIndex currentIndex = ui->treeView->currentIndex();

        if (currentIndex.isValid() && !model->isDir(currentIndex)) {
            // Отримання поточного шляху та імені файлу
            QString currentPath = model->filePath(currentIndex);
            QFileInfo fileInfo(currentPath);
            QString currentName = fileInfo.fileName();
            QString currentExtension = fileInfo.suffix();

            // Створення ім'я для копії файлу
            QString copyName = currentName + "_copy";
            QString copyPath = fileInfo.absolutePath() + "/" + copyName + "." + currentExtension;

            // Перевірка, чи існують інші копії файлу
            int copyCount = 1;
            while (QFile::exists(copyPath)) {
                copyName = currentName + "_copy_" + QString::number(copyCount);
                copyPath = fileInfo.absolutePath() + "/" + copyName + "." + currentExtension;
                copyCount++;
            }

            // Створення копії файлу з новим іменем
            if (QFile::copy(currentPath, copyPath)) {

                model->setRootPath(fileInfo.absolutePath());
                ui->treeView->setRootIndex(model->index(fileInfo.absolutePath()));
                ui->listView->setRootIndex(model->index(fileInfo.absolutePath()));
            }
        }
    });


    connect(ui->pasteButton, &QPushButton::clicked, [this, &sourcePath]() {
        QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());

        // Вибер файлу, який потрібно вставити
        QString filePathToPaste = QFileDialog::getOpenFileName(this, tr("Виберіть файл для вставки"), QDir::homePath());

        if (!filePathToPaste.isEmpty() && !sourcePath.isEmpty()) {
            QFileInfo sourceInfo(sourcePath);
            QString newFileName = sourceInfo.fileName();


            QFileInfo destInfo(filePathToPaste);
            QString destPath = destInfo.absolutePath();

            // Перевірка, чи обраною директорією є тека
            if (destInfo.isDir()) {
                QString newFilePath = destPath + QDir::separator() + newFileName;
                if (QFile::copy(sourcePath, newFilePath)) {

                    model->setRootPath(destPath);
                    ui->treeView->setRootIndex(model->index(destPath));
                    ui->listView->setRootIndex(model->index(destPath));
                }
            }
        }
    });

connect(ui->renameButton, &QPushButton::clicked, [this]() {
    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
    QModelIndex currentIndex = ui->treeView->currentIndex();

    if (currentIndex.isValid()) {

        QString currentName = model->fileName(currentIndex);


        QString currentPath = model->filePath(currentIndex);
        QString currentExtension = model->isDir(currentIndex) ? "" : QFileInfo(currentPath).completeSuffix();

        // Запит користувача на нове ім'я
        bool ok;
        QString newName = QInputDialog::getText(this, tr("Змінити ім'я"), tr("Введіть нове ім'я:"), QLineEdit::Normal, currentName, &ok);

        if (ok && !newName.isEmpty() && newName != currentName) {
            // Перейменовання файлу або текии зі збереженням розширення (якщо це файл)
            QString newPath;
            if (model->isDir(currentIndex)) {
                newPath = model->filePath(currentIndex).section("/", 0, -2) + "/" + newName;
            } else {
                newPath = model->filePath(currentIndex).section("/", 0, -2) + "/" + newName + "." + currentExtension;
            }

            if (QFile::rename(currentPath, newPath)) {
                model->setRootPath(model->filePath(currentIndex).section("/", 0, -2));
            }
        }
    }
});
    connect(ui->deleteButton, &QPushButton::clicked, [this]() {
        QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
        QModelIndex currentIndex = ui->treeView->currentIndex();

        if (currentIndex.isValid()) {
            QString currentPath = model->filePath(currentIndex);
            QString currentName = model->fileName(currentIndex);

            // Запит користувача про підтвердження видалення
            int result = QMessageBox::question(this, tr("Підтвердження видалення"),
            tr("Ви впевнені, що бажаєте видалити %1?").arg(currentName),
                                               QMessageBox::Yes | QMessageBox::No);

            if (result == QMessageBox::Yes) {
                // Видалення файлу або теки
                if (model->remove(currentIndex)) {

                    model->setRootPath(currentPath.section("/", 0, -2));
                    ui->treeView->setRootIndex(model->index(currentPath.section("/", 0, -2)));
                    ui->listView->setRootIndex(model->index(currentPath.section("/", 0, -2)));
                }
            }
        }
    });

connect(ui->privDirButton, &QPushButton::clicked, [this]() {
    QFileSystemModel *model = qobject_cast<QFileSystemModel*>(ui->treeView->model());
    QModelIndex currentIndex = ui->treeView->currentIndex();

    if (currentIndex.isValid()) {
        QString currentPath = model->filePath(currentIndex);
        QString parentPath = currentPath.section("/", 0, -2); // Отримати батьківську теку

        // Перевірка, чи тека вище існує
        if (!parentPath.isEmpty()) {
            model->setRootPath(parentPath);
            ui->treeView->setRootIndex(model->index(parentPath));
            ui->listView->setRootIndex(model->index(parentPath));
        }
    }
});




}


MainWindow::~MainWindow()
{




    delete ui;
}
