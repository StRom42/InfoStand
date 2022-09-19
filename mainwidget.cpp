#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::MainWidget) {

    ui->setupUi(this);

    settings = new QSettings("settings.ini", QSettings::IniFormat);

    QString host = settings->value("host", "127.0.0.1").toString();
    QString databaseName =
        settings->value("databaseName", "InfoStand.db").toString();
    QString user = settings->value("user", "").toString();
    QString password = settings->value("password", "").toString();

    try {
        repository = std::make_shared<RepositoryFactory>(host, user, password,
                                                         databaseName);
    } catch (std::logic_error) {
        QMessageBox::warning(this, "Ошибка базы данных",
                             "Не удается подключиться к базе данных");
    }

    if (QGuiApplication::screens().size() < 2) {
        QMessageBox::warning(this, "Ошибка подключения второго экрана",
                             "Второй экран не подключен!");
    } else {
        screen = QGuiApplication::screens()[1];
        videoWidget = new VideoPlayer;
        videoWidget->move(screen->geometry().x(), screen->geometry().y());
        videoWidget->resize(screen->geometry().width(),
                            screen->geometry().height());
        videoWidget->showFullScreen();
    }

    menuModel = new MenuModel(repository->getExhibitsRepository());
    this->ui->menu_view->setItemModel(menuModel);

    connect(ui->menu_view, &TreeView::selectedItemChanged, this,
            &MainWidget::showItem);

    connect(ui->video_button, &QPushButton::clicked, this,
            &MainWidget::startVideo);
}

MainWidget::~MainWidget() {
    delete ui;
    delete screen;
    delete settings;
    delete videoWidget;
    delete menuModel;
}

void MainWidget::startVideo() {
    QString videoPath = ui->video_button->getVideoPath();
    if (!videoPath.isEmpty()) {
        try {
            videoWidget->playVideo(videoPath);
        } catch (...) {
            QMessageBox::warning(
                this, "Ошибка воспроизведения видео",
                "Не подключен второй экран или видео не найдено");
        }
    }
}

void MainWidget::showItem(const QItemSelection& selected,
                          const QItemSelection& deselected) {
    Q_UNUSED(deselected);
    auto indexes = selected.indexes();
    if (!indexes.isEmpty()) {
        uint id = menuModel->getItemId(indexes[0]);
        if (id != 0) {
            Exhibit object = repository->getExhibitsRepository()->getById(id);
            ui->textWidget->setText(object.getDescription());
            ui->image_label->setSource(object.getImagePath());
            ui->video_button->setVideoPath(object.getVideoPath());
        }
    }
}
