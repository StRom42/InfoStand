#include "mainwidget.h"

#include <QApplication>
#include <QDir>
#include <QtSql>

int main(int argc, char* argv[]) {
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.setValue("host", "127.0.0.1");
    settings.setValue("databaseName", QDir::currentPath() + "/InfoStand.db");
    settings.sync();

    QSettings treeSettings("treeSettings.ini", QSettings::IniFormat);
    treeSettings.beginGroup("Артефакты");
    treeSettings.setValue("1", "1");
    treeSettings.endGroup();

    treeSettings.beginGroup("Музыкальные инструменты");
    treeSettings.setValue("1", "2");
    treeSettings.endGroup();

    treeSettings.sync();

    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
