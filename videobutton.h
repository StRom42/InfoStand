#ifndef VIDEOBUTTON_H
#define VIDEOBUTTON_H

#include <QPushButton>

class VideoButton : public QPushButton {
public:
    VideoButton(QWidget* parent = nullptr)
        : QPushButton(parent){};

    const QString &getVideoPath() const;
    void setVideoPath(const QString &newVideoPath);

private:
    QString videoPath;
};

inline const QString &VideoButton::getVideoPath() const
{
    return videoPath;
}

inline void VideoButton::setVideoPath(const QString &newVideoPath)
{
    videoPath = newVideoPath;
}

#endif // VIDEOBUTTON_H
