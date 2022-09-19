#include "imagelabel.h"
#include <QEventLoop>
#include <QSslSocket>

ImageLabel::ImageLabel(QWidget* parent)
    : QLabel(parent) {
}

void ImageLabel::setSource(QString path) {
    if (path.startsWith("https") || path.startsWith("http")) {
        QUrl url(path);
        QNetworkAccessManager manager;
        QEventLoop loop;

        QNetworkReply* reply = manager.get(QNetworkRequest(url));
        QObject::connect(reply, &QNetworkReply::finished, &loop,
                         [&reply, this, &loop]() {
                             if (reply->error() == QNetworkReply::NoError) {
                                 QByteArray jpegData = reply->readAll();
                                 QPixmap pixmap;
                                 pixmap.loadFromData(jpegData);
                                 if (!pixmap.isNull()) {
                                     this->clear();
                                     this->setPixmap(pixmap);
                                 }
                             }
                             loop.quit();
                         });

        loop.exec();
    } else {
        setPixmap(QPixmap(path));
    }
}
