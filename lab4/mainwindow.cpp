#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Теория принятия решений в условиях неопределенности. Лабораторная работа №4. Вычисление Конкордации");//Название программы
    m = 8;
    n = 9;
    Separator = ",";
    outListWidget = "Исх.данные";
    TextOnListWidget(outListWidget);
    QMenu *file = menuBar()->addMenu("Файл");
    QAction *loadfile = new QAction("Загрузить данные", this);
    run = new QAction("Выполнить вычисления", this);
    savefile = new QAction("Сохранить в файл",this);
    print = new QAction("Распечатать",this);
    QAction *clear = new QAction("Очистить",this);
    QAction *exit = new QAction("Выход",this);
    loadfile->setShortcut(tr("Ctrl+L"));
    run->setShortcut(tr("Ctrl+R"));
    savefile->setShortcut(tr("Ctrl+S"));
    print->setShortcut(tr("Ctrl+P"));
    clear->setShortcut(tr("Ctrl+C"));
    exit->setShortcut(tr("Ctrl+E"));

    file->addAction(loadfile);
    file->addAction(run);
    file->addAction(savefile);
    file->addAction(print);
    file->addAction(clear);
    file->addSeparator();
    file->addAction(exit);

    ui->mainToolBar->addAction(loadfile);
    ui->mainToolBar->addAction(run);
    ui->mainToolBar->addAction(savefile);
    ui->mainToolBar->addAction(print);
    ui->mainToolBar->addAction(clear);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(exit);


    ui->tableWidget->setRowCount(m);
    ui->tableWidget->setColumnCount(n);
    ui->tableWidget_2->setRowCount(1);
    ui->tableWidget_2->setColumnCount(n);
    ui->tableWidget_3->setRowCount(1);
    ui->tableWidget_3->setColumnCount(n);
    ui->tableWidget_5->setRowCount(1);
    ui->tableWidget_5->setColumnCount(n);
    ui->tableWidget_6->setRowCount(1);
    ui->tableWidget_6->setColumnCount(n);
    ui->tableWidget_7->setRowCount(1);
    ui->tableWidget_7->setColumnCount(n);
    ui->tableWidget_8->setRowCount(1);
    ui->tableWidget_8->setColumnCount(n);
    ui->tableWidget_9->setRowCount(1);
    ui->tableWidget_9->setColumnCount(n);
    ui->tableWidget_10->setRowCount(1);
    ui->tableWidget_10->setColumnCount(n);
    ui->tableWidget_11->setRowCount(1);
    ui->tableWidget_11->setColumnCount(n);
    ui->tableWidget_12->setRowCount(1);
    ui->tableWidget_12->setColumnCount(n);
    ui->tableWidget_13->setRowCount(1);
    ui->tableWidget_13->setColumnCount(n);
    ui->tableWidget_14->setRowCount(1);
    ui->tableWidget_14->setColumnCount(n);
    ui->tableWidget_15->setRowCount(1);
    ui->tableWidget_15->setColumnCount(n);
    ui->tableWidget_16->setRowCount(1);
    ui->tableWidget_16->setColumnCount(n);
    ui->tableWidget_17->setRowCount(1);
    ui->tableWidget_17->setColumnCount(n);
    ui->tableWidget_18->setRowCount(1);
    ui->tableWidget_18->setColumnCount(n);
    ui->tableWidget_19->setRowCount(1);
    ui->tableWidget_19->setColumnCount(n);
    ui->tableWidget_20->setRowCount(1);
    ui->tableWidget_20->setColumnCount(n);
    ui->tableWidget_4->setRowCount(m+1);
    ui->tableWidget_4->setColumnCount(2);
    int widthColumn = 35;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==0)
            {
                ui->tableWidget_2->setColumnWidth(j,widthColumn);
                ui->tableWidget_3->setColumnWidth(j,widthColumn);
                ui->tableWidget_5->setColumnWidth(j,widthColumn);
                ui->tableWidget_6->setColumnWidth(j,widthColumn);
                ui->tableWidget_7->setColumnWidth(j,widthColumn);
                ui->tableWidget_8->setColumnWidth(j,widthColumn);
                ui->tableWidget_9->setColumnWidth(j,widthColumn);
                ui->tableWidget_10->setColumnWidth(j,widthColumn);
                ui->tableWidget_11->setColumnWidth(j,widthColumn);
                ui->tableWidget_12->setColumnWidth(j,widthColumn);
                ui->tableWidget_13->setColumnWidth(j,widthColumn);
                ui->tableWidget_14->setColumnWidth(j,widthColumn);
                ui->tableWidget_15->setColumnWidth(j,widthColumn);
                ui->tableWidget_16->setColumnWidth(j,widthColumn);
                ui->tableWidget_17->setColumnWidth(j,widthColumn);
                ui->tableWidget_18->setColumnWidth(j,widthColumn);
                ui->tableWidget_19->setColumnWidth(j,widthColumn);
                ui->tableWidget_20->setColumnWidth(j,widthColumn);
            }
            ui->tableWidget->setColumnWidth(j,widthColumn);
        }
    }
    ui->tableWidget_4->setColumnWidth(1,widthColumn+20);

    ui->lineEdit->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->lineEdit->setHidden(true);
    run->setDisabled(true);
    savefile->setDisabled(true);
    print->setDisabled(true);

    QObject::connect(loadfile,SIGNAL(triggered(bool)),this,SLOT(Read()));
    QObject::connect(clear,SIGNAL(triggered()),this, SLOT(Clear()));
    QObject::connect(exit,SIGNAL(triggered()),this, SLOT(Exit()));
    QObject::connect(savefile,SIGNAL(triggered()),this,SLOT(Save()));
    QObject::connect(print,SIGNAL(triggered()),this,SLOT(Print()));
    QObject::connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    QObject::connect(loadfile,SIGNAL(triggered(bool)),run,SLOT(setDisabled(bool)));
    QObject::connect(run,SIGNAL(triggered(bool)),print,SLOT(setDisabled(bool)));
    QObject::connect(run,SIGNAL(triggered(bool)),savefile,SLOT(setDisabled(bool)));

    QObject::connect(run,SIGNAL(triggered(bool)),this,SLOT(mainfunction()));
}

MainWindow::~MainWindow()
{
    delete run;
    delete savefile;
    delete print;
    delete ui;
}

void MainWindow::init()
{
    data = new double*[m];
    for(int i=0;i<m;i++)
    {
        data[i]=new double[n];
        for(int j=0;j<n;j++)
        {
            data[i][j]=0;
        }
    }
}

double *MainWindow::SummaryRank(double **matrix, int row, int col, int experts)
{
    double ret = 0;
    double* vector = new double[col];
    for(int i=0;i<col;i++)
    {
        vector[i]=0;
    }
    for(int i=0;i<col;i++)
    {
        ret = 0;
        for(int j=0;j<row;j++)
        {
            if(j==experts)
            {
                continue;
            }
            else
            {
                ret += matrix[j][i];
            }
        }
        vector[i]=ret;
    }
    return vector;
}

double *MainWindow::SKO(double *sr, int size, int experts)
{
    double averangerank = AverangeRank(size);
    //qDebug()<<averangerank;
    double* vector=new double[size];
    for(int i=0;i<size;i++)
    {
        vector[i] = 0;
    }
    for(int i=0;i<size;i++)
    {
        vector[i]=sr[i]-averangerank*experts;
    }
    return vector;
}

double MainWindow::AverangeRank(int SizeColumn)
{
    double ret = 0;
    for(int i=1;i<=SizeColumn;i++)
    {
        ret +=i;
    }
    ret = ret/SizeColumn;
    return ret;
}

double MainWindow::concord(double *quadro, int size, int experts, int alternative)
{
    double coeff = 12;
    double res = 0;
    double outparametr = 0;
    for(int i=0;i<size;i++)
        res+=(quadro[i]*quadro[i]);
    outparametr=coeff*(res)/((experts*experts)*(alternative*alternative*alternative-alternative));
    return outparametr;
}

void MainWindow::OutTextEdit(QString info, int exc)
{
    if(exc==999)
    {
        ui->textEdit->append(QString("Общая"));
    }
    ui->textEdit->append(info);
}

void MainWindow::addStringToListWidget(QString string)
{
    ui->listWidget->clear();
    outListWidget = outListWidget + string;//добавление закладки в листвиджет
    TextOnListWidget(outListWidget);
}

QString MainWindow::Max(double *k, int size)
{
    double max = k[0];
    int index = 0;
    for(int i=0;i<size;i++)
    {
        if(max<k[i])
        {
            max=k[i];
            index = i;
        }
    }
    QString out = QString::number(max)+QString(" ")+QString::number(index);
    return out;
}

void MainWindow::mainfunction()
{
    double* sumrank;
    double* sko;
    double* concordance;
    sumrank = new double[m];
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
    }
    sko = new double[m];
    for(int i=0;i<m;i++)
    {
        sko[i]=0;
    }
    concordance = new double[m+1];
    for(int i=0;i<m+1;i++)
    {
        concordance[i]=0;
    }
    ui->listWidget->clear();
    ui->textEdit->clear();
    outListWidget = "Исх.данные";
    TextOnListWidget(outListWidget);
    ui->lineEdit->setHidden(true);
    init();
    QString TableNumber, ArrayOut;
    ui->textEdit->append(QString("Исходные данные:"));
    //заполнение массива
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            QTableWidgetItem* item = ui->tableWidget->item(i,j);
            //TableNumber = item->text();
            if(ui->tableWidget->item(i,j)==0)//если значение в ячейке 0 или она не заполнена
            {
                data[i][j]=0;
                TableNumber = QString::number(data[i][j]);//изменяем пустое значение на 0
                ArrayOut += TableNumber + QString(" ");
                QTableWidgetItem *item = new QTableWidgetItem(TableNumber);
                ui->tableWidget->setItem(i,j,item);
                //qDebug()<<TableNumber;
            }
            else
            {
                TableNumber = item->text();
                //qDebug()<<TableNumber;
                for(int k=0;k<TableNumber.length();k++)
                {
                    if(TableNumber.at(k)==',')
                    {
                        TableNumber = TableNumber.replace(QRegExp(","),".");
                    }
                }
                data[i][j]= TableNumber.toDouble();
                ArrayOut += TableNumber + QString(" ");
            }
        }
        ui->textEdit->append(ArrayOut);
        //qDebug()<<ArrayOut;
        ArrayOut.clear();
    }
    ui->textEdit->append(QString(""));
    exclude = 999;//не вычеркиваем
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(";Сум.рангов(все данные)");//добавление закладки в листвиджет
    QString DataString;
    QStringList l;
    QString d;
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    ui->textEdit->append(QString("По всем данным"));
    OutTextEdit(DataString,0);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_2->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m);
    addStringToListWidget(";Отклонение(все данные)");
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,0);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_3->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[0]=concord(sko,n,m,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }

    //без 1-ой строки
    exclude = 0;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,1);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_5->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,1);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_6->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 2-ой строки
    exclude = 1;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,2);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_7->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,2);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_8->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 3-ой строки
    exclude = 2;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,3);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_9->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,3);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_10->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 4-ой строки
    exclude = 3;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,4);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_11->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,4);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_12->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 5-ой строки
    exclude = 4;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,5);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_13->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,5);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_14->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 6-ой строки
    exclude = 5;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,6);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_15->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,6);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_16->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 7-ой строки
    exclude = 6;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,7);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_17->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,7);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_18->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    //без 8-ой строки
    exclude = 7;
    ui->textEdit->append(QString("Исключаем ")+QString::number(exclude+1)+QString(" строку"));
    sumrank = SummaryRank(data,m,n,exclude);//вычисление суммы рангов
    addStringToListWidget(QString(";Сум.рангов")+QString::number(exclude+1));//добавление закладки в листвиджет
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sumrank[i]);
        }
        else
        {
            DataString += DataString.number(sumrank[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,8);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_19->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();

    sko=SKO(sumrank,n,m-1);
    addStringToListWidget(QString(";Отклонение")+QString::number(exclude+1));
    for(int i=0;i<n;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(sko[i]);
        }
        else
        {
            DataString += DataString.number(sko[i])+QString(" ");
        }
    }
    OutTextEdit(DataString,8);
    l = DataString.split(" ");
    for(int i=0;i<n;i++)
    {
        d = l.at(i);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget_20->setItem(0,i,item);
    }
    DataString.clear();
    d.clear();
    l.clear();
    concordance[exclude+1]=concord(sko,n,m-1,n);
    for(int i=0;i<m;i++)
    {
        sumrank[i]=0;
        sko[i]=0;
    }


    for(int i=0;i<m+1;i++)
    {
        if(i==n-1)
        {
            DataString += DataString.number(concordance[i]);
        }
        else
        {
            DataString += DataString.number(concordance[i])+QString(" ");
        }
    }
    l=DataString.split(" ");
    DataString.clear();
    for(int i=0;i<l.length();i++)
    {
        d = l.at(i);
        if(i==0)
        {
            DataString+=QString("R = ")+d+QString("; ");
        }
        else
        {
            if(i==l.length()-1)
            {
                DataString+=QString("R")+QString::number(i)+QString(" = ")+d+QString(".");
            }
            else
            {
                DataString+=QString("R")+QString::number(i)+QString(" = ")+d+QString("; ");
            }

        }
    }
    ui->textEdit->append(QString(""));
    OutTextEdit(DataString,0);//вывод конкордации
    addStringToListWidget(";Конкордации");
    //вывод всех конкордаций в таблицу
    for(int j=0;j<2;j++)
    {
        for(int i=0;i<m+1;i++)
        {
            if(j==0)
            {
                if(i==0)
                {
                    QTableWidgetItem* item = new QTableWidgetItem(QString("Общая"));
                    ui->tableWidget_4->setItem(i,j,item);
                }
                else
                {
                    QTableWidgetItem* item = new QTableWidgetItem(QString("Без ")+QString::number(i)+QString(" строки"));
                    ui->tableWidget_4->setItem(i,j,item);
                }
            }
            else
            {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(concordance[i]));
                ui->tableWidget_4->setItem(i,j,item);
            }
        }
    }

    //формирование ответа в answer
    QString answer = Max(concordance,m+1);
    l = answer.split(" ");
    answer.clear();
    if("0"==l.at(1))
    {
        answer = QString("Ответ: ")+DataString+QString(" Max(R) = ")+l.at(0)+QString(" при учете всех данных.");
    }
    else
    {
        answer = QString("Ответ: ")+DataString+QString(" Max(R) = ")+l.at(0)+QString(" при исключении ")+QString::number(QString(l.at(1)).toDouble())+QString(" строки");
    }
    ui->lineEdit->setText(answer);
    OutTextEdit(answer,0);//вывод ответа
    answer.clear();
    DataString.clear();
    ui->lineEdit->setHidden(false);
}

void MainWindow::Read()
{
    int variant = 0;//инициализируем переменную под вариант
    var = 0;//глобальная переменная иниицализируем ее 0, т.к. пока вариант не выбран
    bool buttonOk;//флаг на кнопку
    int rows = 0;
    int columns = 0;
    //вызываем стандартный диалог. В нашем случае используем метод getInt()
    //параметры:
    //0 - указываем родителя, заголовок, сообщение, 1 - начальное значение, 1- мин значение, 30 - максимальное значение, 1- шаг увеличения, флаг на кнопку
    variant = QInputDialog::getInt(0,"Окно выбора варианта","Введите номер варианта в текстовое поле..",1,1,30,1,&buttonOk);
    if(!buttonOk)//кнопка не нажата
    {
        return;
    }
    else//нажата
    {
        QFile myFile(":/data.txt"); // переменная работы с файлами
        //загружаем из ресурсов
        if (!myFile.open(QFile::ReadOnly | QFile::Text))//открываем файл
            //QFile::ReadOnly - открытие только для чтения
        {
            QMessageBox::warning(0,"Предупреждение!", "Невозможно прочитать!");

            //если не удалось открыть файл, сообщение на экран
            return;
            //остановка выполнения функции
        }
        QTextStream myText(&myFile);// переменная для записи в файл и чтения из него
        //&myFile - аргумент передаем как ссылку на наш файл

        QString strText;//для наших данных
        QStringList data;//для приведения данных к нормальному виду

        int i=1;
        while (!myText.atEnd() && variant != i)//пока не пройдем до конца файла и вариант=i
        {
            strText = myText.readLine();//читаем строку
            ++i;
        }

        if(myText.atEnd())//не нашли выводим сообщение и завершаем работу
        {
            QMessageBox::information(0, "Предупреждение!", "Нет такого варианта!");
            myFile.close();
            return;
        }
        else//помещаем данные в строку
        {
            strText = myText.readLine();
            data = strText.split(" ");//приводим к нормальному виду данные
            //qDebug()<<strText;
            //qDebug()<<data.length();
            rows = 8;
            columns = 9;

            for(int i=0;i<data.length();)//отображаем данные в таблицу
            {
                for(int j=0;j<rows;j++)
                {
                    for(int k=0;k<columns;k++)
                    {
                        strText = data.at(i);
                        QTableWidgetItem *item = new QTableWidgetItem(strText);
                        ui->tableWidget->setItem(j,k,item);
                        i++;
                    }
                }
            }
            myFile.close();
        }
        data.clear();
        var = variant;//сохраняем вариант в глоб перем для функции сохранения
    }
}

void MainWindow::TextOnListWidget(QString text)
{
    QStringList R = text.split(";");
    ui->listWidget->addItems(R);
}

void MainWindow::Exit()
{
    QApplication::exit(0);
}

void MainWindow::Clear()
{
    ui->lineEdit->clear();
    ui->tableWidget->clear();
    ui->tableWidget_2->clear();
    ui->tableWidget_3->clear();    
    ui->tableWidget_4->clear();
    ui->tableWidget_5->clear();
    ui->tableWidget_6->clear();
    ui->tableWidget_7->clear();
    ui->tableWidget_8->clear();
    ui->tableWidget_9->clear();
    ui->tableWidget_10->clear();
    ui->tableWidget_11->clear();
    ui->tableWidget_12->clear();
    ui->tableWidget_13->clear();
    ui->tableWidget_14->clear();
    ui->tableWidget_15->clear();
    ui->tableWidget_16->clear();
    ui->tableWidget_17->clear();
    ui->tableWidget_18->clear();
    ui->tableWidget_19->clear();
    ui->tableWidget_20->clear();
    ui->lineEdit->setHidden(true);
    ui->textEdit->clear();
    ui->listWidget->clear();
    ui->listWidget->addItem("Исх.данные");
    run->setDisabled(true);
    savefile->setDisabled(true);
    print->setDisabled(true);
}
void MainWindow::Print()
{
    QString information = ui->textEdit->toPlainText();
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        QTextDocument document;
        document.setPlainText(information);
        document.setDefaultFont(QFont("Times",10,QFont::Bold));
        document.print(&printer);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(QString("Решение варианта №")+QString::number(var));
    }
}

void MainWindow::Save()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Сохранение в файл..");
    msgBox.setInformativeText("Выберите формат сохранения..");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *txt = msgBox.addButton(tr("Текстовый формат"), QMessageBox::ActionRole);
    QPushButton *pdf = msgBox.addButton(tr("PDF"), QMessageBox::ActionRole);
    msgBox.exec();
    if(msgBox.clickedButton()== txt)
    {
        QString stringWrite;//переменная для информации из textedit
        QString filename = QFileDialog::getSaveFileName(
                    this,
                    tr("Сохранить файл"),
                    QString("Решение варианта №")+QString::number(var),
                    tr("Формат файла (*.txt)") );//вызываем диалог сохранения файла и качестве имени предлагаем свое и запоминаем путь к файлу
        if(!filename.isNull())//если путь не пустой
        {
            QFile file(filename);
            if (!file.open(QIODevice::WriteOnly))//открываем только на запись
            {
                QMessageBox::critical(this,tr("Ошибка"),tr("Невозможно сохранить файл"));
                return;
            }
            else
            {
                QTextStream stream(&file);
                stringWrite = ui->textEdit->toPlainText();//вынимаем всю информацию из textedit-а как она есть
                stringWrite.replace(QRegExp("\n"),"\r\n");//заменяем \n на \r\n
                stream<<stringWrite;//записываем
                file.close();//закрываем файл
            }
        }
    }
    else if(msgBox.clickedButton()== pdf)
    {
        QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Сохранить файл"),QString("Решение варианта №")+QString::number(var),QObject::tr("PDF (*.pdf)"));
        QString information = ui->textEdit->toPlainText();
        //qDebug()<<information;
        QPrinter printer;
        QPainter painter;
        QStringList data = information.split("\n");
        //qDebug()<<data;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        if (!painter.begin(&printer))
            return;
        int width = 40;
        int height = 40;
        int pos = 0;
        for(int i=0;i<data.length();i++)
        {
            if(i==0)
            {
                pos=0;
                height = height+(pos*15);
                painter.drawText(width,height,data[i]);
            }
            else
            {
                pos = 1;
                height = height+(pos*15);
                painter.drawText(width,height,data[i]);
                //qDebug()<<height;
                pos++;
                if(height>=1050)
                {
                    printer.newPage();
                    height = 40;
                    pos=0;
                }
            }
        }
        painter.end();
    }
}
