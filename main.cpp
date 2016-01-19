#include <QApplication>
#include "DownloadModel.h"
#include "DownloadView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QStringList lst;
    lst << "http://img1.goodfon.ru/original/6495x4330/3/4a/mlechnyy-put-kosmos-zvezdy-3734.jpg"
           << "http://kvant.space/sites/default/files/images/artleo.com-45222_0.jpg";
    QStringList lst2;
    lst2 << "http://mynokiablog.com/wp-content/uploads/2012/02/Screen-Shot-2012-02-27-at-10.43.51-AM.jpg";
    DownloadModel model;
    QObject::connect(&model, SIGNAL(Finish()), &a, SLOT(quit()));//test without interface
    model.AddUrls(lst);
    model.AddUrls(lst2);
    */
    DownloadView view;

    return a.exec();
}
