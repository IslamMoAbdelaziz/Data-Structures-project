#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCheck_Consistency_triggered();

    void on_actionSolve_Errors_triggered();

    void on_actionFormat_Prettify_triggered();
//    void formatting(string &data);

    void on_actionConvert_to_JSON_triggered();

    void on_actionMinify_triggered();

    void on_actionCompress_triggered();

private:
    Ui::MainWindow *ui;

     QString currentFile = "";
};
#endif // MAINWINDOW_H
