#include "menumodel.h"

TreeItem::TreeItem(uint id, const QVector<QVariant>& data, TreeItem* parentItem)
    : id(id),
      m_itemData(data),
      m_parentItem(parentItem) {
}

TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem* item) {
    m_childItems.append(item);
}

TreeItem* TreeItem::child(int row) {
    if (row < 0 || row >= m_childItems.size()) return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const {
    return m_childItems.count();
}

int TreeItem::row() const {
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const {
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const {
    if (column < 0 || column >= m_itemData.size()) return QVariant();
    return m_itemData.at(column);
}

TreeItem* TreeItem::parentItem() {
    return m_parentItem;
}

uint TreeItem::getId() const {
    return id;
}

MenuModel::MenuModel(std::shared_ptr<ExhibitsRepository> repository,
                     QObject* parent)
    : QAbstractItemModel(parent),
      repository(repository) {

    rootItem = new TreeItem(-1, {""});
    setupModelData(rootItem);
}

MenuModel::~MenuModel() {
    delete rootItem;
}

QModelIndex MenuModel::index(int row, int column,
                             const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) return QModelIndex();

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);
    if (childItem) return createIndex(row, column, childItem);
    return QModelIndex();
}

Qt::ItemFlags MenuModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant MenuModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex MenuModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->parentItem();

    if (parentItem == rootItem) return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int MenuModel::rowCount(const QModelIndex& parent) const {
    TreeItem* parentItem;
    if (parent.column() > 0) return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int MenuModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant MenuModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    if (role != Qt::DisplayRole) return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

uint MenuModel::getItemId(const QModelIndex& index) const {
    if (!index.isValid()) return 0;

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    return item->getId();
}

void MenuModel::setupModelData(TreeItem* parent) {
    for (QString& group : treeSettings.childGroups()) {
        treeSettings.beginGroup(group);
        TreeItem* item = new TreeItem(0, {group}, parent);
        parent->appendChild(item);
        setupModelData(item);
        treeSettings.endGroup();
    }
    for (QString& key : treeSettings.childKeys()) {
        int itemId = treeSettings.value(key).toInt();
        Exhibit object = repository->getById(itemId);
        QString itemName = object.getName();
        TreeItem* item = new TreeItem(itemId, {itemName}, parent);
        parent->appendChild(item);
    }
}
