#include "console.h"

#include <QApplication>

#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Mwars mwars;            // instantiate mwars as class Mwars (should be capitalised)
    mwars.show();

    return app.exec();
}
