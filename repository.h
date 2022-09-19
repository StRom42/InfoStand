#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "entities.h"
#include <QImage>
#include <QString>
#include <QtSql>
#include <memory>

template <typename T>
class BaseRepository {
public:
    BaseRepository(const QSqlDatabase& db)
        : query(new QSqlQuery(db)) {
    }

    virtual void insert(const T& object){};
    virtual T getById(uint id){};
    virtual void update(const T& object){};
    virtual void removeById(uint id){};

protected:
    QSqlQuery* query{nullptr};
};

class ExhibitsRepository : public BaseRepository<Exhibit> {
public:
    ExhibitsRepository(const QSqlDatabase& db)
        : BaseRepository<Exhibit>(db){};

    void insert(const Exhibit& object) override;
    Exhibit getById(uint id) override;
    void update(const Exhibit& object) override;
    void removeById(uint id) override;

private:
    QString tableName{"ExhibitsTable"};
    QString idFieldName{"ExhibitId"};
    QString nameField{"Name"};
    QString descriptionField{"Description"};
    QString imagepathField{"ImagePath"};
    QString videopathField{"VideoPath"};
};

class RepositoryFactory {
public:
    RepositoryFactory(QString hostname, QString user, QString password,
                      QString databaseName);

    std::shared_ptr<ExhibitsRepository> getExhibitsRepository();

private:
    QSqlDatabase database;
    std::shared_ptr<ExhibitsRepository> exhibitsRep;
};

#endif // REPOSITORY_H
