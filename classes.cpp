#include "classes.h"
#include <QMessageBox>
sections::sections(){}
lessons::lessons(){}
schedule::schedule(){}
todos::todos(){}
grades::grades(){}
exams::exams(){}

// Here, we pass the database connection to our classes.
lessons::lessons(QSqlDatabase &db)   { this->db = db; }
sections::sections(QSqlDatabase &db) { this->db = db; }
schedule::schedule(QSqlDatabase &db) { this->db = db; }
todos::todos(QSqlDatabase &db)       { this->db = db; }
grades::grades(QSqlDatabase &db)     { this->db = db; }
exams::exams(QSqlDatabase &db)       { this->db = db; }

/* Lessons Class */
QStringList lessons::lessonList()
{
    QStringList returnValue; // Lesson names in our database.
    QString query = "SELECT name FROM lessons";
    QSqlQuery tempResult = db.exec(query);

    tempResult.first(); // Go to the first value
    returnValue.append(tempResult.value(0).toString());
    while(tempResult.next())
        returnValue.append(tempResult.value(0).toString());
    if(returnValue.isEmpty())
        returnValue.append("Lesson list is empty!");
    return returnValue;
}

QSqlTableModel* lessons::lessonsTable()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("lessons");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Teacher");
    return model;
}

bool lessons::addLesson(QString lessonName, QString teacherName)
{
    if(lessonName.isEmpty() || teacherName.isEmpty())
        return false;
    QSqlQuery query;
    query.prepare("INSERT INTO lessons VALUES(NULL, :lessonName, :teacherName)");
    query.bindValue(":lessonName", lessonName);
    query.bindValue(":teacherName", teacherName);
    query.exec();
    return true;
}

bool lessons::deleteLesson(QModelIndex index)
{
    QSqlTableModel *model = this->lessonsTable();
    model->removeRow(index.row());
    model->submitAll();
    return true;
}

/* Sections Class */
QStringList sections::getSections(QString lessonName)
{
    QStringList result;
    QSqlQuery query(db);
    query.prepare("SELECT name FROM sections WHERE lesson=:lesson");
    query.bindValue(":lesson", lessonName);
    query.exec();
    query.first();
    result.append(query.value(0).toString());
    while(query.next())
        result.append(query.value(0).toString());
    if(result.isEmpty())
        result.append("EMPTY");
    return result;
}

/* Schedule Class */
QSqlQueryModel* schedule::daysSchedule(int day)
{

    QString query("SELECT start, end, lesson, classroom FROM schedule WHERE day=:replaceme ORDER BY start");
    QString theday;
    query.replace(":replaceme", theday.setNum(day));
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "Start");
    model->setHeaderData(1, Qt::Horizontal, "End");
    model->setHeaderData(2, Qt::Horizontal, "Lesson");
    model->setHeaderData(3, Qt::Horizontal, "Classroom");
    return model;
}

void schedule::addToSchedule(QString lessonName, int day, QString startTime, QString endTime, QString classroom)
{
    if(lessonName.isEmpty() || startTime.isEmpty() || endTime.isEmpty() || classroom.isEmpty())
        return;

    QSqlQuery query;
    query.prepare("INSERT INTO schedule VALUES(NULL, :lessonName, :day, :startTime, :endTime, :classroom)");
    query.bindValue(":lessonName", lessonName);
    query.bindValue(":day", day);
    query.bindValue(":startTime", startTime);
    query.bindValue(":endTime", endTime);
    query.bindValue(":classroom", classroom);
    query.exec();
}

void schedule::removeFromSchedule(int day, QModelIndex index)
{
    QSqlQueryModel *model = this->daysSchedule(day);
    QString start = model->record(index.row()).value(0).toString();

    QString text;
    text = "DELETE FROM schedule WHERE day=':day' AND start=':start'";
    text.replace(":day", QString::number(day));
    text.replace(":start", start);

    QSqlQuery query;
    query.exec(text);
}

/* Todo Class */
QSqlTableModel* todos::todosTable()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("todos");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Todo");
    model->setHeaderData(2, Qt::Horizontal, "Date");
    return model;
}

bool todos::addTodo(QString todo, QString date)
{
    if(todo.isEmpty() || date.isEmpty())
        return false;

    QSqlQuery query;
    query.prepare("INSERT INTO todos VALUES(NULL, :todo, :date)");
    query.bindValue(":todo", todo);
    query.bindValue(":date", date);
    query.exec();
    return true;
}

bool todos::deleteTodo(QModelIndex index)
{
    QSqlTableModel *model = this->todosTable();
    model->removeRow(index.row());
    model->submitAll();
    return true;
}

/* Grades Class */
bool grades::addGrade(QString section, QString lesson, int value)
{
    if(section.isEmpty())
        return false;

    QSqlQuery query;
    query.prepare("INSERT INTO grades VALUES(NULL, :lesson, :section, :value)");
    query.bindValue(":lesson", lesson);
    query.bindValue(":section", section);
    query.bindValue(":value", value);
    query.exec();
    return true;
}

bool grades::addSection(QString name, QString lesson, int worth)
{
    QSqlQuery query;
    query.prepare("INSERT INTO sections VALUES(NULL, :name, :lesson, :worth)");
    query.bindValue(":name", name);
    query.bindValue(":lesson", lesson);
    query.bindValue(":worth", worth);
    query.exec();
    return true;
}

bool grades::sectionExists(QString name, QString lesson)
{
    QString text;
    text = "SELECT COUNT(*) FROM sections WHERE name=':name' AND lesson=':lesson'";
    text.replace(":name", name);
    text.replace(":lesson", lesson);
    QSqlQuery query;
    query.exec(text);

    query.first();
    if(query.value(0).toInt() > 0)
        return true;
    else
        return false;

}

QStringList grades::getGrades(QString section, QString lesson)
{
    QStringList result;
    QString text;
    text = "SELECT value FROM grades WHERE section=':section' AND lesson=':lesson'";
    text.replace(":section", section);
    text.replace(":lesson", lesson);
    QSqlQuery query(db);
    query.exec(text);
    query.first();
    result.append(query.value(0).toString());
    while(query.next())
        result.append(query.value(0).toString());

    if (result.isEmpty())
        result.append("0");
    return result;
}

bool grades::deleteGrade(QString section, QString lesson, int value)
{
    QString text;
    text = "DELETE FROM grades WHERE section=':section' AND lesson=':lesson' AND value=':value'";
    text.replace(":section",section);
    text.replace(":lesson",lesson);
    text.replace(":value",QString::number(value));
    QSqlQuery query(db);
    return query.exec(text);
}

int grades::getSectionWorth(QString lesson, QString section)
{
    QString text;
    text = "SELECT worth FROM sections WHERE name=':name' AND lesson=':lesson'";
    text.replace(":name",section);
    text.replace(":lesson",lesson);;
    QSqlQuery query(db);
    query.exec(text);
    query.first();
    return query.value(0).toInt();
}

/* Exams Class */
QSqlTableModel* exams::examsTable()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("exams");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Lesson");
    model->setHeaderData(2, Qt::Horizontal, "Section");
    model->setHeaderData(3, Qt::Horizontal, "Date");
    return model;
}

bool exams::addExam(QString lesson, QString section, QString date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO exams VALUES(NULL, :todo, :section, :date)");
    query.bindValue(":lesson", lesson);
    query.bindValue(":section", section);
    query.bindValue(":date", date);
    query.exec();
    return true;
}

bool exams::deleteExam(QModelIndex index)
{
    QSqlTableModel *model = this->examsTable();
    model->removeRow(index.row());
    model->submitAll();
    return true;
}


