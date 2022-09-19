#ifndef ENTITIES_H
#define ENTITIES_H

#include <QString>

class Exhibit {
public:
    Exhibit(uint id = 0, QString name = "", QString description = "",
            QString imagePath = "", QString videoPath = "")
        : id(id),
          name(name),
          description(description),
          imagePath(imagePath),
          videoPath(videoPath){};

    const QString& getDescription() const;
    void setDescription(const QString& newDescription);

    const QString& getImagePath() const;
    void setImagePath(const QString& newImagePath);

    const QString& getVideoPath() const;
    void setVideoPath(const QString& newVideoPath);

    uint getId() const;

    const QString& getName() const;
    void setName(const QString& newName);

private:
    uint id;
    QString name;
    QString description;
    QString imagePath;
    QString videoPath;
};

#endif // ENTITIES_H
