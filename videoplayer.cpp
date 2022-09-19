#include "videoplayer.h"

VideoPlayer::VideoPlayer() {
    player = new QMediaPlayer;
    player->setVideoOutput(this);
}

VideoPlayer::~VideoPlayer() {
    //    if (thread != nullptr) {
    //        thread->exit();
    //        delete thread;
    //    }
    delete player;
}

void VideoPlayer::playVideo(QString source) {
    //    if (thread != nullptr) {
    //        player->stop();
    //        thread->exit();
    //        delete thread;
    //    }

    if (source.startsWith("https") || source.startsWith("http")) {
        player->setMedia(QUrl(source));
    } else {
        player->setMedia(QUrl::fromLocalFile(source));
    }

    //    thread = QThread::create(&VideoPlayer::startPlayingVideo);
    //    thread->start();
    startPlayingVideo();
}

void VideoPlayer::startPlayingVideo() {
    player->play();
}
