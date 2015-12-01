#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationVersion("1.0.0.52");

    QCommandLineParser parser;
    parser.addPositionalArgument("source", "Scource File");
    parser.process(application);

    QString initialFilePath;
    const QStringList argsuments = parser.positionalArguments();
    if(argsuments.size() > 0)
        initialFilePath = argsuments.at(0);


    MainWindow w(initialFilePath);
    w.show();

    return application.exec();
}
