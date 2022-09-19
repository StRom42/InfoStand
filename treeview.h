#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView {
    Q_OBJECT
public:
    TreeView(QWidget* parent = nullptr)
        : QTreeView(parent) {
    }

public:
    void setItemModel(QAbstractItemModel* model) {
        this->setModel(model);
        connect(this->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &TreeView::emitSelectedItemChanged);
    }

public slots:
    void emitSelectedItemChanged(const QItemSelection& selected,
                                 const QItemSelection& deselected) {
        emit selectedItemChanged(selected, deselected);
    }

signals:
    void selectedItemChanged(const QItemSelection& selected,
                             const QItemSelection& deselected);
};

#endif // TREEVIEW_H
