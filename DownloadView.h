#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include <QtWidgets>
#include <QNetworkReply>
#include "ProgressBar.h"
#include "DownloadModel.h"

class DownloadView : public QWidget {
    Q_OBJECT
private:
    QTextEdit           *Url_edit;
    QTableWidget        *Tbl_wgt;
    DownloadModel       *Download_model;
public:
    DownloadView(QWidget *pwgt = 0);
private slots:
    void slotRun();
    void addRow(QNetworkReply *reply);
    void delRow(QString url);
    void Error(QString err, QString url);
};

#endif // DOWNLOADVIEW_H
