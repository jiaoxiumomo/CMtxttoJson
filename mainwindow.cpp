#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
      mainWidget=new QWidget;
      open=new QPushButton;
      open->setText(tr("打开"));
      save=new QPushButton;
      save->setText(tr("保存"));
      CMtableView=new QTableView;
      CMtableView->horizontalHeader()->setStretchLastSection(true);
      //CMtableView->set
      //CMtableView->resize(1000,mainWidget->height());
      mainLayout=new QGridLayout;
      mainLayout->addWidget(open,0,0,1,1);
      mainLayout->addWidget(save,0,1,1,1);
      mainLayout->addWidget(CMtableView,1,0,1,2);
      mainWidget->setLayout(mainLayout);
      setUpModel();

      setCentralWidget(mainWidget);
      resize(400,500);

      //this->setLayout(mainLayout);
      this->setWindowTitle(tr("julab控存转json"));
      //this->setFixedWidth(400);

      connect(open,&QPushButton::clicked,this,&MainWindow::openFile);
      connect(save,&QPushButton::clicked,this,&MainWindow::savFlie);

}

void MainWindow::setUpModel()
{
    ctlModel=new QStandardItemModel(1,3,this);
    ctlModel->setHeaderData(0,Qt::Horizontal,tr("微地址"));
    ctlModel->setHeaderData(1,Qt::Horizontal,tr("微指令"));
    ctlModel->setHeaderData(2,Qt::Horizontal,tr("微命令"));
}

void MainWindow::openFile()
{
    fileName=QFileDialog::getOpenFileName(this,tr("打开控存文件"),filePath,tr("早期控存文件 (*.csv)"));//同时打开多个面板文件
    if(!(fileName.isEmpty()))
   {
        QFile ctldata(fileName);
        if(ctldata.open(QFile::ReadOnly|QFile::Text))
          {
             QTextStream in(&ctldata);
             QString line;
             ctlModel->removeRows(0,ctlModel->rowCount(QModelIndex()),QModelIndex());
             int row=0;
             do
              {
                line=in.readLine();
                if(!line.isEmpty())
                {
                    QStringList list=line.split("\"",QString::KeepEmptyParts);
                    QStringList pieces=line.split(",",QString::KeepEmptyParts); //SkipEmptyParts
                    if(pieces.value(1)!=NULL){
                        ctlModel->insertRows(row,1,QModelIndex());
                        ctlModel->setData(ctlModel->index(row,0,QModelIndex()),pieces.value(0));
                        ctlModel->setData(ctlModel->index(row,1,QModelIndex()),pieces.value(1));
                        ctlModel->setData(ctlModel->index(row,2,QModelIndex()),list.value(1));
                        row++;
                    }
                }
              }while(!line.isEmpty());
             ctldata.close();
          }
        CMtableView->setModel(ctlModel);
   }


}
void MainWindow::savFlie(){
    QString fiName=QFileDialog::getSaveFileName(this,tr("保存控存文件"),"json",tr("控存文件 (*.json)"));
    if(fiName!=NULL){
     QFile data(fiName);
     QJsonObject ctlInfoArray[ctlModel->rowCount()];
     for(int i=0;i<ctlModel->rowCount();i++){
         QModelIndex key=ctlModel->index(i,0,QModelIndex());
         QModelIndex instruction=ctlModel->index(i,1,QModelIndex());
         QModelIndex command=ctlModel->index(i,2,QModelIndex());
             ctlInfoArray[i].insert("key",(key.data().toString()).toInt(NULL,16));
             ctlInfoArray[i].insert("instruction",instruction.data().toString());
             ctlInfoArray[i].insert("command",command.data().toString());

       }
     QJsonArray array;
     for(int i=0;i<ctlModel->rowCount();i++){
             array.insert(i,ctlInfoArray[i]);
}
     QJsonDocument document;
      if(data.open(QFile::ReadWrite|QFile::Truncate|QIODevice::Text)){
     document.setArray(array);
     data.write(document.toJson());
      }
    }

}


MainWindow::~MainWindow()
{
  delete open;
    delete save;
    delete CMtableView;
    delete mainLayout;
    delete mainWidget;
    delete ctlModel;

}
