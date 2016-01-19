#ifndef DOWNLOADMODEL_H
#define DOWNLOADMODEL_H

//for use in console, you must do next:
//QStringList args = QCoreApplication::instance()->arguments();
//and skip the first argument, which is the program's name
//args.takeFirst();
//then call AddUrls(args);


#include <QObject>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class DownloadModel : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager   *Manager;  //manage of downloads in parallel
    int                     MaxDownloads;
    QQueue<QUrl>            UrlQueue; //queue of url for requests
    QList<QNetworkReply*>   ReplyList;//list of current downloads
public:
    DownloadModel(QObject *pobj = 0);
private:
    void NextDownload(const QUrl &url); //begin next download
    QString SaveFileName(const QUrl &url); //make file name from url
    bool SaveFile(const QString &FileName, QIODevice *reply); //save file in downloads
public slots:
    void Execute();                     //start of processing urls
    void AddUrls(QStringList &Url_list);//add urls in queue and start execute
private slots:
    void slotFinished(QNetworkReply *reply);//call, when download is done or error
signals:
    void Error(QString, QString);
    void Success(QString);
    void Finish();
    void sendReply(QNetworkReply*);
};

#endif // DOWNLOADMODEL_H
