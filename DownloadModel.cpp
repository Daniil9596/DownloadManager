#include "DownloadModel.h"

DownloadModel::DownloadModel(QObject *pobj/*= 0*/)
    : QObject(pobj)
{
    Manager = new QNetworkAccessManager(this);
    connect(Manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotFinished(QNetworkReply*)));
    MaxDownloads = 6;
}

void DownloadModel::NextDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = Manager->get(request);
    emit sendReply(reply);
    ReplyList.append(reply);
}

QString DownloadModel::SaveFileName(const QUrl &url)
{
    QString path = url.path();
    QString FileName = QFileInfo(path).fileName();
    if (FileName.isEmpty()){
        FileName = "download";
    }
    if (QFile::exists(FileName)) {
        // already exists, don't overwrite
        int i = 0;
        FileName += '.';
        while(QFile::exists(FileName + QString::number(i)))
            ++i;
        FileName += QString::number(i);
    }
    return FileName;
}

bool DownloadModel::SaveFile(const QString &FileName, QIODevice *reply)
{
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(reply->readAll());
    file.close();
    return true;
}

void DownloadModel::Execute()
{
    while(MaxDownloads > 0 && !UrlQueue.isEmpty()) {
        NextDownload(UrlQueue.dequeue());
        --MaxDownloads;
    }
}

void DownloadModel::AddUrls(QStringList &Url_list)
{
    if(Url_list.isEmpty()){
        return;
    }
    foreach (QString url, Url_list) {
        UrlQueue.enqueue(QUrl::fromEncoded(url.toLocal8Bit()));
    }
    Execute();
}

void DownloadModel::slotFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        emit Error(reply->errorString(), url.toString());
    } else {
        QString FileName = SaveFileName(url);
        if (SaveFile(FileName, reply))
            emit Success(url.toString());
    }
    ReplyList.removeAll(reply);
    reply->deleteLater();
    //signal for Quit console app or test
    if(UrlQueue.isEmpty() && ReplyList.isEmpty()){
        emit Finish();
    }
    //--------------------------
    ++MaxDownloads;
    Execute();
}
