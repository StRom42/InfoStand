/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include "TextWidget.h"
#include "imagelabel.h"
#include "treeview.h"
#include "videobutton.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget {
public:
    QGridLayout* gridLayout;
    //    QVBoxLayout* vboxLayout;
    TreeView* menu_view;
    QScrollArea* scrollArea;
    TextWidget* textWidget;
    ImageLabel* image_label;
    VideoButton* video_button;

    void setupUi(QWidget* MainWidget) {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(1185, 600);
        gridLayout = new QGridLayout(MainWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        menu_view = new TreeView(MainWidget);
        menu_view->setObjectName(QString::fromUtf8("menu_view"));

        gridLayout->addWidget(menu_view, 0, 0, 4, 3);

        scrollArea = new QScrollArea(MainWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        textWidget = new TextWidget();
        textWidget->setObjectName(QString::fromUtf8("textWidget"));
        scrollArea->setWidget(textWidget);
        scrollArea->setWidgetResizable(true);

        gridLayout->addWidget(scrollArea, 0, 3, 4, 4);

        image_label = new ImageLabel(MainWidget);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setPixmap(
            QPixmap(QString::fromUtf8(":/res/no-photo.png")));
        image_label->setScaledContents(true);
        image_label->setMaximumSize(QSize(512, 512));

        gridLayout->addWidget(image_label, 0, 7, 2, 2);

        video_button = new VideoButton(MainWidget);
        video_button->setObjectName(QString::fromUtf8("video_button"));

        gridLayout->addWidget(video_button, 2, 7, 2, 2);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget* MainWidget) {
        MainWidget->setWindowTitle(
            QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        image_label->setText(QString());
        video_button->setText(QCoreApplication::translate(
            "MainWidget",
            "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202"
            "\321\214 \320\262\320\270\320\264\320\265\320\276",
            nullptr));
    } // retranslateUi
};

namespace Ui {
class MainWidget : public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
