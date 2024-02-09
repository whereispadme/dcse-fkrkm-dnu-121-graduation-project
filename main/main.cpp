#include "headers.h"
#include "mainwindow.h"

void setDarkPalleteApplication(QApplication &app)
{
    app.setWindowIcon(QIcon(":/icons/mainwindow.png"));
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window,QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Base,QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase,Qt::white);
    darkPalette.setColor(QPalette::ToolTipText,Qt::white);
    darkPalette.setColor(QPalette::Text,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
    darkPalette.setColor(QPalette::Button,QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText,Qt::red);
    darkPalette.setColor(QPalette::Link,QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText,Qt::white);
    darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));

    app.setPalette(darkPalette);
}

void setFontApplication(QString path)
{
    QFontDatabase fontDatabase;
    int fontId = fontDatabase.addApplicationFont(path);
    if (fontId == -1) qDebug() << "Помилка завантаження шрифта!";

    QStringList fontFamilies = fontDatabase.applicationFontFamilies(fontId);
    if (fontFamilies.isEmpty()) qDebug() << "Відсутні доступні сімейства шрифтів!";

    QFont customFont(fontFamilies.at(0));
    customFont.setPointSize(11);
    customFont.setBold(true);

    QApplication::setFont(customFont);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setDarkPalleteApplication(app);
    app.setStyleSheet("QTabWidget::tab-bar { background-color: rgb(42,42,42); } "
                      "QTabWidget { background-color: rgb(42,42,42); } "
                      "QLineEdit { border-radius: 4px; } "
                      "QLineEdit:hover { border: 1px solid rgb(64, 71, 88); } "
                      "QLineEdit:focus { border: 1px solid rgb(4, 217, 255); } "
                      "QDateEdit:hover { border: 1px solid rgb(64, 71, 88); } "
                      "QDateEdit:focus { border: 1px solid rgb(4, 217, 255); } "
                      "QTimeEdit:hover { border: 1px solid rgb(64, 71, 88); } "
                      "QTimeEdit:focus { border: 1px solid rgb(4, 217, 255); }");
    setFontApplication(":/fonts/Nunito-Bold.ttf");

    MainWindow mainWindow;

    return app.exec();
}
