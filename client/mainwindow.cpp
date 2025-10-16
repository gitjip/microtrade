#include "mainwindow.h"
#include "commander.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPalette>
#include <QStyleFactory>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupMenuTheme();
    Commander::instance()->publicUpdate();
    connect(ui->actionPublicRefresh, &QAction::triggered, Commander::instance(),
            &Commander::publicUpdate);
    connect(ui->actionPrivateRefresh, &QAction::triggered, Commander::instance(),
            &Commander::privateUpdate);
    connect(ui->actionSync, &QAction::triggered, Commander::instance(),
            &Commander::synchronous);
    connect(Commander::instance(), &Commander::readySetDarkTheme, this,
            [=]() { applyDarkTheme(); });
    connect(Commander::instance(), &Commander::readySetLightTheme, this,
            [=]() { applyLightTheme(); });
    Commander::instance()->setAutoTheme(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::applyLightTheme() {
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::WindowText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::AlternateBase, QColor(245, 245, 245));
    lightPalette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
    lightPalette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::Text, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    lightPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    lightPalette.setColor(QPalette::Link, QColor(0, 100, 200));
    lightPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    lightPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));

    lightPalette.setColor(QPalette::Disabled, QPalette::WindowText,
                          QColor(128, 128, 128));
    lightPalette.setColor(QPalette::Disabled, QPalette::Text,
                          QColor(128, 128, 128));
    lightPalette.setColor(QPalette::Disabled, QPalette::ButtonText,
                          QColor(128, 128, 128));
    lightPalette.setColor(QPalette::Disabled, QPalette::Highlight,
                          QColor(200, 200, 200));

    qApp->setPalette(lightPalette);

    qApp->setStyleSheet(R"(
        /* 主窗口和对话框 */
        QMainWindow, QDialog {
            background-color: #f0f0f0;
            color: #000000;
        }

        /* 按钮 */
        QPushButton {
            background-color: #e0e0e0;
            border: 1px solid #cccccc;
            color: #000000;
            padding: 6px 12px;
            border-radius: 4px;
            font-weight: normal;
        }
        QPushButton:hover {
            background-color: #d0d0d0;
            border: 1px solid #bbbbbb;
        }
        QPushButton:pressed {
            background-color: #c0c0c0;
            border: 1px solid #aaaaaa;
        }
        QPushButton:disabled {
            background-color: #f0f0f0;
            border: 1px solid #dddddd;
            color: #888888;
        }

        /* 输入框 */
        QLineEdit, QTextEdit, QPlainTextEdit {
            background-color: #ffffff;
            border: 1px solid #cccccc;
            color: #000000;
            padding: 5px 8px;
            border-radius: 3px;
            selection-background-color: #0078d7;
            selection-color: white;
        }
        QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
            border: 1px solid #0078d7;
        }
        QLineEdit:disabled, QTextEdit:disabled, QPlainTextEdit:disabled {
            background-color: #f8f8f8;
            border: 1px solid #e0e0e0;
            color: #888888;
        }

        /* 占位符文本 */
        QLineEdit::placeholder, QTextEdit::placeholder-text, QPlainTextEdit::placeholder-text {
            color: #888888;
            font-style: italic;
        }

        /* 标签 */
        QLabel {
            color: #000000;
            background-color: transparent;
        }
        QLabel:disabled {
            color: #888888;
        }

        /* 复选框 */
        QCheckBox {
            color: #000000;
            spacing: 5px;
        }
        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }
        QCheckBox::indicator:unchecked {
            background-color: #ffffff;
            border: 1px solid #cccccc;
            border-radius: 2px;
        }
        QCheckBox::indicator:unchecked:hover {
            border: 1px solid #bbbbbb;
        }
        QCheckBox::indicator:checked {
            background-color: #0078d7;
            border: 1px solid #0066b4;
            border-radius: 2px;
            image: url(:/icons/check_white.svg);
        }
        QCheckBox:disabled {
            color: #888888;
        }
        QCheckBox::indicator:disabled {
            background-color: #f0f0f0;
            border: 1px solid #dddddd;
        }

        /* 单选框 */
        QRadioButton {
            color: #000000;
            spacing: 5px;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 8px;
        }
        QRadioButton::indicator:unchecked {
            background-color: #ffffff;
            border: 1px solid #cccccc;
        }
        QRadioButton::indicator:unchecked:hover {
            border: 1px solid #bbbbbb;
        }
        QRadioButton::indicator:checked {
            background-color: #0078d7;
            border: 1px solid #0066b4;
        }
        QRadioButton:disabled {
            color: #888888;
        }
        QRadioButton::indicator:disabled {
            background-color: #f0f0f0;
            border: 1px solid #dddddd;
        }

        /* 组合框 */
        QComboBox {
            background-color: #ffffff;
            border: 1px solid #cccccc;
            color: #000000;
            padding: 5px 8px;
            border-radius: 3px;
            min-width: 6em;
        }
        QComboBox:focus {
            border: 1px solid #0078d7;
        }
        QComboBox:disabled {
            background-color: #f8f8f8;
            border: 1px solid #e0e0e0;
            color: #888888;
        }
        QComboBox::drop-down {
            border: none;
            width: 20px;
        }
        QComboBox::down-arrow {
            image: url(:/icons/arrow_down.svg);
            width: 12px;
            height: 12px;
        }
        QComboBox QAbstractItemView {
            background-color: #ffffff;
            border: 1px solid #cccccc;
            color: #000000;
            selection-background-color: #0078d7;
            selection-color: white;
        }

        /* 菜单栏 */
        QMenuBar {
            background-color: #f0f0f0;
            color: #000000;
            border-bottom: 1px solid #cccccc;
        }
        QMenuBar::item {
            background-color: transparent;
            padding: 4px 8px;
        }
        QMenuBar::item:selected {
            background-color: #e0e0e0;
            border-radius: 2px;
        }
        QMenuBar::item:pressed {
            background-color: #d0d0d0;
        }

        /* 菜单 */
        QMenu {
            background-color: #ffffff;
            color: #000000;
            border: 1px solid #cccccc;
            padding: 4px;
        }
        QMenu::item {
            background-color: transparent;
            padding: 4px 24px 4px 8px;
        }
        QMenu::item:selected {
            background-color: #0078d7;
            color: white;
        }
        QMenu::item:disabled {
            color: #888888;
        }
        QMenu::separator {
            height: 1px;
            background-color: #e0e0e0;
            margin: 4px 8px;
        }
        QMenu::indicator {
            width: 16px;
            height: 16px;
        }

        /* 工具栏 */
        QToolBar {
            background-color: #f5f5f5;
            border: 1px solid #cccccc;
            spacing: 3px;
            padding: 2px;
        }
        QToolBar::handle {
            image: url(:/icons/grip_dots.svg);
        }
        QToolBar QToolButton {
            background-color: transparent;
            border: 1px solid transparent;
            border-radius: 3px;
            padding: 4px;
        }
        QToolBar QToolButton:hover {
            background-color: #e0e0e0;
            border: 1px solid #cccccc;
        }
        QToolBar QToolButton:pressed {
            background-color: #d0d0d0;
        }
        QToolBar QToolButton:disabled {
            background-color: transparent;
            color: #888888;
        }

        /* 进度条 */
        QProgressBar {
            border: 1px solid #cccccc;
            background-color: #f0f0f0;
            text-align: center;
            color: #000000;
            border-radius: 3px;
        }
        QProgressBar::chunk {
            background-color: #0078d7;
            border-radius: 2px;
        }
        QProgressBar:disabled {
            color: #888888;
        }
        QProgressBar::chunk:disabled {
            background-color: #a0a0a0;
        }

        /* 滚动条 */
        QScrollBar:vertical {
            background-color: #f0f0f0;
            width: 15px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background-color: #c0c0c0;
            border-radius: 7px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: #a0a0a0;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }

        /* 滑块 */
        QSlider::groove:horizontal {
            background-color: #e0e0e0;
            height: 4px;
            border-radius: 2px;
        }
        QSlider::handle:horizontal {
            background-color: #0078d7;
            width: 16px;
            height: 16px;
            border-radius: 8px;
            margin: -6px 0;
        }
        QSlider::handle:horizontal:hover {
            background-color: #0066b4;
        }

        /* 分组框 */
        QGroupBox {
            color: #000000;
            border: 1px solid #cccccc;
            border-radius: 4px;
            margin-top: 1ex;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            padding: 0 5px;
            background-color: #f0f0f0;
        }

        /* 选项卡 */
        QTabWidget::pane {
            border: 1px solid #cccccc;
            background-color: #ffffff;
        }
        QTabBar::tab {
            background-color: #e0e0e0;
            color: #000000;
            padding: 6px 12px;
            border: 1px solid #cccccc;
            border-bottom: none;
            border-top-left-radius: 3px;
            border-top-right-radius: 3px;
        }
        QTabBar::tab:selected {
            background-color: #ffffff;
            border-color: #cccccc;
        }
        QTabBar::tab:hover:!selected {
            background-color: #f0f0f0;
        }

        /* 工具提示 */
        QToolTip {
            background-color: #ffffdc;
            color: #000000;
            border: 1px solid #cccccc;
            padding: 2px 4px;
            border-radius: 2px;
        }

        /* 表格 */
        QTableView, QTableWidget {
            background-color: #ffffff;
            color: #000000;
            gridline-color: #e0e0e0;
            selection-background-color: #0078d7;
            selection-color: white;
        }
        QHeaderView::section {
            background-color: #f0f0f0;
            color: #000000;
            padding: 4px 8px;
            border: 1px solid #cccccc;
        }

        /* 树视图 */
        QTreeView, QTreeWidget {
            background-color: #ffffff;
            color: #000000;
            selection-background-color: #0078d7;
            selection-color: white;
        }
    )");
}

void MainWindow::applyDarkTheme() {
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(43, 43, 43));
    darkPalette.setColor(QPalette::WindowText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(60, 60, 60));
    darkPalette.setColor(QPalette::ToolTipText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Text, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, QColor(240, 240, 240));
    darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));

    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText,
                         QColor(128, 128, 128));
    darkPalette.setColor(QPalette::Disabled, QPalette::Text,
                         QColor(128, 128, 128));
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText,
                         QColor(128, 128, 128));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight,
                         QColor(80, 80, 80));

    qApp->setPalette(darkPalette);

    qApp->setStyleSheet(R"(
        /* 主窗口和对话框 */
        QMainWindow, QDialog {
            background-color: #2b2b2b;
            color: #e0e0e0;
        }

        /* 按钮 */
        QPushButton {
            background-color: #404040;
            border: 1px solid #555555;
            color: #e0e0e0;
            padding: 6px 12px;
            border-radius: 4px;
            font-weight: normal;
        }
        QPushButton:hover {
            background-color: #505050;
            border: 1px solid #666666;
        }
        QPushButton:pressed {
            background-color: #606060;
            border: 1px solid #777777;
        }
        QPushButton:disabled {
            background-color: #353535;
            border: 1px solid #454545;
            color: #888888;
        }

        /* 输入框 */
        QLineEdit, QTextEdit, QPlainTextEdit {
            background-color: #353535;
            border: 1px solid #555555;
            color: #e0e0e0;
            padding: 5px 8px;
            border-radius: 3px;
            selection-background-color: #2a82da;
            selection-color: white;
        }
        QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus {
            border: 1px solid #2a82da;
        }
        QLineEdit:disabled, QTextEdit:disabled, QPlainTextEdit:disabled {
            background-color: #2b2b2b;
            border: 1px solid #444444;
            color: #888888;
        }

        /* 占位符文本 */
        QLineEdit::placeholder, QTextEdit::placeholder-text, QPlainTextEdit::placeholder-text {
            color: #888888;
            font-style: italic;
        }

        /* 标签 */
        QLabel {
            color: #e0e0e0;
            background-color: transparent;
        }
        QLabel:disabled {
            color: #888888;
        }

        /* 复选框 */
        QCheckBox {
            color: #e0e0e0;
            spacing: 5px;
        }
        QCheckBox::indicator {
            width: 16px;
            height: 16px;
        }
        QCheckBox::indicator:unchecked {
            background-color: #353535;
            border: 1px solid #555555;
            border-radius: 2px;
        }
        QCheckBox::indicator:unchecked:hover {
            border: 1px solid #666666;
        }
        QCheckBox::indicator:checked {
            background-color: #2a82da;
            border: 1px solid #1e72ca;
            border-radius: 2px;
            image: url(:/icons/check_white.svg);
        }
        QCheckBox:disabled {
            color: #888888;
        }
        QCheckBox::indicator:disabled {
            background-color: #2b2b2b;
            border: 1px solid #444444;
        }

        /* 单选框 */
        QRadioButton {
            color: #e0e0e0;
            spacing: 5px;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 8px;
        }
        QRadioButton::indicator:unchecked {
            background-color: #353535;
            border: 1px solid #555555;
        }
        QRadioButton::indicator:unchecked:hover {
            border: 1px solid #666666;
        }
        QRadioButton::indicator:checked {
            background-color: #2a82da;
            border: 1px solid #1e72ca;
        }
        QRadioButton:disabled {
            color: #888888;
        }
        QRadioButton::indicator:disabled {
            background-color: #2b2b2b;
            border: 1px solid #444444;
        }

        /* 组合框 */
        QComboBox {
            background-color: #353535;
            border: 1px solid #555555;
            color: #e0e0e0;
            padding: 5px 8px;
            border-radius: 3px;
            min-width: 6em;
        }
        QComboBox:focus {
            border: 1px solid #2a82da;
        }
        QComboBox:disabled {
            background-color: #2b2b2b;
            border: 1px solid #444444;
            color: #888888;
        }
        QComboBox::drop-down {
            border: none;
            width: 20px;
        }
        QComboBox::down-arrow {
            image: url(:/icons/arrow_down_white.svg);
            width: 12px;
            height: 12px;
        }
        QComboBox QAbstractItemView {
            background-color: #353535;
            border: 1px solid #555555;
            color: #e0e0e0;
            selection-background-color: #2a82da;
            selection-color: white;
        }

        /* 菜单栏 */
        QMenuBar {
            background-color: #2b2b2b;
            color: #e0e0e0;
            border-bottom: 1px solid #444444;
        }
        QMenuBar::item {
            background-color: transparent;
            padding: 4px 8px;
        }
        QMenuBar::item:selected {
            background-color: #404040;
            border-radius: 2px;
        }
        QMenuBar::item:pressed {
            background-color: #505050;
        }

        /* 菜单 */
        QMenu {
            background-color: #353535;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 4px;
        }
        QMenu::item {
            background-color: transparent;
            padding: 4px 24px 4px 8px;
        }
        QMenu::item:selected {
            background-color: #2a82da;
            color: white;
        }
        QMenu::item:disabled {
            color: #888888;
        }
        QMenu::separator {
            height: 1px;
            background-color: #444444;
            margin: 4px 8px;
        }
        QMenu::indicator {
            width: 16px;
            height: 16px;
        }

        /* 工具栏 */
        QToolBar {
            background-color: #323232;
            border: 1px solid #444444;
            spacing: 3px;
            padding: 2px;
        }
        QToolBar::handle {
            image: url(:/icons/grip_dots_white.svg);
        }
        QToolBar QToolButton {
            background-color: transparent;
            border: 1px solid transparent;
            border-radius: 3px;
            padding: 4px;
        }
        QToolBar QToolButton:hover {
            background-color: #404040;
            border: 1px solid #555555;
        }
        QToolBar QToolButton:pressed {
            background-color: #505050;
        }
        QToolBar QToolButton:disabled {
            background-color: transparent;
            color: #888888;
        }

        /* 进度条 */
        QProgressBar {
            border: 1px solid #555555;
            background-color: #2b2b2b;
            text-align: center;
            color: #e0e0e0;
            border-radius: 3px;
        }
        QProgressBar::chunk {
            background-color: #2a82da;
            border-radius: 2px;
        }
        QProgressBar:disabled {
            color: #888888;
        }
        QProgressBar::chunk:disabled {
            background-color: #606060;
        }

        /* 滚动条 */
        QScrollBar:vertical {
            background-color: #2b2b2b;
            width: 15px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background-color: #606060;
            border-radius: 7px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background-color: #707070;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }

        /* 滑块 */
        QSlider::groove:horizontal {
            background-color: #404040;
            height: 4px;
            border-radius: 2px;
        }
        QSlider::handle:horizontal {
            background-color: #2a82da;
            width: 16px;
            height: 16px;
            border-radius: 8px;
            margin: -6px 0;
        }
        QSlider::handle:horizontal:hover {
            background-color: #1e72ca;
        }

        /* 分组框 */
        QGroupBox {
            color: #e0e0e0;
            border: 1px solid #555555;
            border-radius: 4px;
            margin-top: 1ex;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            padding: 0 5px;
            background-color: #2b2b2b;
        }

        /* 选项卡 */
        QTabWidget::pane {
            border: 1px solid #555555;
            background-color: #353535;
        }
        QTabBar::tab {
            background-color: #404040;
            color: #e0e0e0;
            padding: 6px 12px;
            border: 1px solid #555555;
            border-bottom: none;
            border-top-left-radius: 3px;
            border-top-right-radius: 3px;
        }
        QTabBar::tab:selected {
            background-color: #353535;
            border-color: #555555;
        }
        QTabBar::tab:hover:!selected {
            background-color: #484848;
        }

        /* 工具提示 */
        QToolTip {
            background-color: #404040;
            color: #e0e0e0;
            border: 1px solid #555555;
            padding: 2px 4px;
            border-radius: 2px;
        }

        /* 表格 */
        QTableView, QTableWidget {
            background-color: #353535;
            color: #e0e0e0;
            gridline-color: #444444;
            selection-background-color: #2a82da;
            selection-color: white;
        }
        QHeaderView::section {
            background-color: #404040;
            color: #e0e0e0;
            padding: 4px 8px;
            border: 1px solid #555555;
        }

        /* 树视图 */
        QTreeView, QTreeWidget {
            background-color: #353535;
            color: #e0e0e0;
            selection-background-color: #2a82da;
            selection-color: white;
        }
    )");
}

void MainWindow::setupMenuTheme() {
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionAutoTheme);
    actionGroup->addAction(ui->actionLightTheme);
    actionGroup->addAction(ui->actionDarkTheme);
    actionGroup->setExclusive(true);
    connect(ui->actionAutoTheme, &QAction::triggered, Commander::instance(),
            &Commander::setAutoTheme);
    connect(ui->actionDarkTheme, &QAction::triggered, Commander::instance(),
            &Commander::setDarkTheme);
    connect(ui->actionLightTheme, &QAction::triggered, Commander::instance(),
            &Commander::setLightTheme);
}

void MainWindow::closeEvent(QCloseEvent *e) {
    if (Commander::instance()->isLoggedin()) {
        e->ignore();
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Are you sure to quit?",
            "We will try to make you logout before you run away.");
        if (reply == QMessageBox::Yes) {
            ui->welcomeTab->tryToLogout();
            connect(ui->welcomeTab, &WelcomeWidget::aboutToLogout, this,
                    &MainWindow::close);
            QTimer::singleShot(1000, this, [=]() {
                qDebug() << "The server break down, cannot logout.";
                qApp->exit(0);
            });
        }
    } else {
        e->accept();
    }
}
