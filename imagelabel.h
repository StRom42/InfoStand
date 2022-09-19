#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QUrl>

class ImageLabel : public QLabel {
public:
    ImageLabel(QWidget* parent = nullptr);

    void setSource(QString path);
};

#endif // IMAGELABEL_H
