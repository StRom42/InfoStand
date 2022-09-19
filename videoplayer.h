#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
#include <QVideoWidget>

class VideoPlayer : public QVideoWidget {
public:
    VideoPlayer();
    ~VideoPlayer();

    void playVideo(QString source);

private:
    void startPlayingVideo();

private:
    QThread* thread{nullptr};
    QMediaPlayer* player{nullptr};
};

#endif // VIDEOPLAYER_H
