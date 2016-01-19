#include "DownloadView.h"

DownloadView::DownloadView(QWidget *pwgt/*= 0*/) : QWidget(pwgt)
{
    QLabel *lbl = new QLabel("Set Urls:");

    Download_model = new DownloadModel(this);
    connect(Download_model, SIGNAL(sendReply(QNetworkReply*)), this, SLOT(addRow(QNetworkReply*)));
    connect(Download_model, SIGNAL(Success(QString)), this, SLOT(delRow(QString)));
    connect(Download_model, SIGNAL(Error(QString, QString)), this, SLOT(Error(QString, QString)));
    Url_edit = new QTextEdit;
    Url_edit->append("http://img1.goodfon.ru/original/6495x4330/3/4a/mlechnyy-put-kosmos-zvezdy-3734.jpg");
    Url_edit->append("http://kvant.space/sites/default/files/images/artleo.com-45222_0.jpg");

    QPushButton *cmd_run = new QPushButton("&Download");
    connect(cmd_run, SIGNAL(clicked()), this, SLOT(slotRun()));

    QStringList header;
    header << "FileName" << "Progress";
    Tbl_wgt = new QTableWidget(0, 2);
    QHeaderView *hv = new QHeaderView(Qt::Horizontal);
    hv->setSectionResizeMode(QHeaderView::Stretch);
    Tbl_wgt->setHorizontalHeader(hv);
    Tbl_wgt->setHorizontalHeaderLabels(header);

    QVBoxLayout *V_layout = new QVBoxLayout;
    V_layout->addWidget(lbl);
    V_layout->addWidget(Url_edit);
    V_layout->addWidget(cmd_run);
    V_layout->addWidget(Tbl_wgt);

    setLayout(V_layout);
    show();
}

void DownloadView::slotRun()
{
    QString tmp = Url_edit->toPlainText();
    QStringList urls(tmp.split("\n", QString::SkipEmptyParts));
    Download_model->AddUrls(urls);
    Url_edit->clear();
}

void DownloadView::addRow(QNetworkReply *reply)
{
    QString FileName = reply->url().path().section('/', -1);
    ProgressBar *progress = new ProgressBar;
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), progress, SLOT(downloadProgress(qint64, qint64)));
    Tbl_wgt->setRowCount(Tbl_wgt->rowCount() + 1);
    Tbl_wgt->setItem(Tbl_wgt->rowCount() - 1, 0, new QTableWidgetItem(FileName));
    Tbl_wgt->setCellWidget(Tbl_wgt->rowCount() - 1, 1, progress);
}

void DownloadView::delRow(QString url)
{
    for(int i = 0; i < Tbl_wgt->rowCount(); ++i){
        if(Tbl_wgt->item(i, 0)->text() == url.section('/', -1)){
            Tbl_wgt->removeRow(i);
            return;
        }
    }
}

void DownloadView::Error(QString err, QString url)
{
    QMessageBox::critical(0, tr("Error!"), err);
    for(int i = 0; i < Tbl_wgt->rowCount(); ++i){
        if(Tbl_wgt->item(i, 0)->text() == url.section('/', -1)){
            Tbl_wgt->removeRow(i);
            return;
        }
    }
}
