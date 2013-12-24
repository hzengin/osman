#include "note_import.h"
#include <QDebug>
note_import::note_import()
{
}

QStringList note_import::getList()
{
    QDir directory("./notes");
    QStringList result;
    result = directory.entryList();
    if(!result.isEmpty())
    {
        result.removeFirst();
        result.removeFirst();
    }

    if(result.isEmpty())
    {
        result.append("EMPTY");
    }
    return result;
}

QString note_import::getNote(int index)
{

    if(!(this->getList().at(0)== "EMPTY"))
    {
        QFile file("./notes/"+this->getList().at(index));
        file.open(QFile::ReadOnly);
        QString text=file.readAll();
        return text;
    }
    else
        return "EMPTY";
}
