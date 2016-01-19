#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QtWidgets>

class ProgressBar : public QProgressBar {
    Q_OBJECT
public:
    ProgressBar(QWidget *pwgt = 0) : QProgressBar(pwgt) {}
private slots:
    void downloadProgress(qint64 nRecieved, qint64 nTotal) {
        if(nTotal > 0){
            setValue(100 * nRecieved / nTotal);
        }
    }
};

#endif // PROGRESSBAR_H
