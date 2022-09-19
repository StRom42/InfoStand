#include "repository.h"

void ExhibitsRepository::insert(const Exhibit& object) {
    QString command =
        QString("INSERT INTO %1 (%2, %3, %4, %5) "
                "VALUES (:name, :description, :imagePath, :videoPath, :name)")
            .arg(tableName, descriptionField, imagepathField, videopathField,
                 nameField);
    query->prepare(command);
    query->bindValue(":description", object.getDescription());
    query->bindValue(":imagePath", object.getImagePath());
    query->bindValue(":videoPath", object.getVideoPath());
    query->bindValue(":name", object.getName());
    query->exec();
}

Exhibit ExhibitsRepository::getById(uint id) {
    QString command =
        QString("SELECT * FROM %1 WHERE %2 = :id").arg(tableName, idFieldName);
    query->prepare(command);
    query->bindValue(":id", id);
    query->exec();
    QSqlRecord record = query->record();

    Exhibit exhibit(id);
    if (query->next()) {
        int descriptionIndex = record.indexOf(descriptionField);
        exhibit.setDescription(query->value(descriptionIndex).toString());
        int imageIndex = record.indexOf(imagepathField);
        exhibit.setImagePath(query->value(imageIndex).toString());
        int videoIndex = record.indexOf(videopathField);
        exhibit.setVideoPath(query->value(videoIndex).toString());
        int nameIndex = record.indexOf(nameField);
        exhibit.setName(query->value(nameIndex).toString());
    }

    return exhibit;
}

void ExhibitsRepository::update(const Exhibit& object) {
    QString command =
        QString("UPDATE %1 SET %2 = :description, %3 = "
                ":imagePath, %4 = :videoPath, %5 = :name WHERE %6 = :id")
            .arg(tableName, descriptionField, imagepathField, videopathField,
                 nameField, idFieldName);
    query->prepare(command);
    query->bindValue(":description", object.getDescription());
    query->bindValue(":imagePath", object.getImagePath());
    query->bindValue(":videoPath", object.getVideoPath());
    query->bindValue(":name", object.getName());
    query->bindValue(":id", object.getId());
    query->exec();
}

void ExhibitsRepository::removeById(uint id) {
    QString command =
        QString("DELETE FROM %1 WHERE %2 = :id").arg(tableName, idFieldName);
    query->prepare(command);
    query->bindValue(":id", id);
    query->exec();
}

RepositoryFactory::RepositoryFactory(QString hostname, QString user,
                                     QString password, QString databaseName) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setHostName(hostname);
    database.setDatabaseName(databaseName);
    database.setUserName(user);
    database.setPassword(password);
    bool ok = database.open();
    if (!ok) {
        throw std::logic_error("Database opening connection error");
    }

    exhibitsRep = std::make_shared<ExhibitsRepository>(database);
}

std::shared_ptr<ExhibitsRepository> RepositoryFactory::getExhibitsRepository() {
    return exhibitsRep;
}
