#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "menumodel.h"
#include "repository.h"
#include "videoplayer.h"
#include <QMessageBox>
#include <QScreen>
#include <QSettings>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    void startVideo();
    void showItem(const QItemSelection& selected,
                  const QItemSelection& deselected);

private:
    QScreen* screen{nullptr};
    Ui::MainWidget* ui{nullptr};
    QSettings* settings{nullptr};
    VideoPlayer* videoWidget{nullptr};
    std::shared_ptr<RepositoryFactory> repository{nullptr};
    MenuModel* menuModel{nullptr};
};
#endif // MAINWIDGET_H
