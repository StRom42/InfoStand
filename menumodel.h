#ifndef MENUMODEL_H
#define MENUMODEL_H

#include "repository.h"
#include <QAbstractItemModel>
#include <QSettings>

class TreeItem {
public:
    explicit TreeItem(uint id, const QVector<QVariant>& data,
                      TreeItem* parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parentItem();

    uint getId() const;

private:
    uint id;
    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem* m_parentItem{nullptr};
};

class MenuModel : public QAbstractItemModel {
    Q_OBJECT
public:
    MenuModel(std::shared_ptr<ExhibitsRepository> repository,
              QObject* parent = nullptr);
    ~MenuModel();

    QModelIndex index(int row, int column,
                      const QModelIndex& parent) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    uint getItemId(const QModelIndex& index) const;

private:
    void setupModelData(TreeItem* parent);

private:
    TreeItem* rootItem{nullptr};
    QSettings treeSettings{"treeSettings.ini", QSettings::IniFormat};
    std::shared_ptr<ExhibitsRepository> repository;
};

#endif // MENUMODEL_H
