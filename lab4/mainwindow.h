#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QFileDialog>
#include <QPainter>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    double** data;
    int exclude;
    double* SummaryRank(double** matrix,int row,int col,int experts);//сумма рангов
    double* SKO(double* sr, int size, int experts);//отклонение sr - sumrank
    double AverangeRank(int SizeColumn);//средний ранг
    double concord(double* quadro,int size,int experts,int alternative);
    void OutTextEdit(QString info,int exc);
    void addStringToListWidget(QString string);
    QString Max(double* k, int size);//k-конкордация
private slots:
    void Read();
    void Exit();
    void Clear();
    void Save();
    void Print();
    void TextOnListWidget(QString text);
    void mainfunction();
private:
    Ui::MainWindow *ui;
    int var;
    int m,n;
    QString Separator;
    QString outListWidget;
    QAction* run;
    QAction* savefile;
    QAction* print;
};

#endif // MAINWINDOW_H
