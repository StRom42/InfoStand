#include "entities.h"

const QString& Exhibit::getDescription() const {
    return description;
}

void Exhibit::setDescription(const QString& newDescription) {
    description = newDescription;
}

const QString& Exhibit::getImagePath() const {
    return imagePath;
}

void Exhibit::setImagePath(const QString& newImagePath) {
    imagePath = newImagePath;
}

const QString& Exhibit::getVideoPath() const {
    return videoPath;
}

void Exhibit::setVideoPath(const QString& newVideoPath) {
    videoPath = newVideoPath;
}

uint Exhibit::getId() const {
    return id;
}

const QString &Exhibit::getName() const
{
    return name;
}

void Exhibit::setName(const QString &newName)
{
    name = newName;
}
