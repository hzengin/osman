#ifndef NOTE_IMPORT_H
#define NOTE_IMPORT_H
#include <QTextDocument>
#include <QFile>
#include <QDir>
#include <QStringList>


class note_import
{
public:
    note_import();
    QStringList getList(); // Gets a list of files in notes folder.
    QString getNote(int index); // Returns a note data in HTML style. It uses given index to select note file.
};

#endif // NOTE_IMPORT_H
