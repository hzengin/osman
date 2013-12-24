#ifndef CLASSES_H
#define CLASSES_H
#include <QStringList>
#include <QSqlDatabase>
#include <QTextDocument>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QDir>
#include <QFile>


class lessons
{
public:
    lessons(QSqlDatabase &db); // Note: db is a pointer of a QSqlDatabase which is our main data store.
    lessons();
    QSqlDatabase db; // This is our SQLite database.
    QStringList lessonList(); // This function returns a list of lessons.
    QSqlTableModel *lessonsTable(); /* This function returns a QSqlTableModel. This model shows our lessons table which is in our database.
    In main class (osman) we will use this for preparing UI. */
    bool addLesson(QString lessonName, QString teacherName); // This function executes a SQL query for adding a lesson to database's lessons table.
    bool deleteLesson(QModelIndex index); // This function executes a SQL query for removing a lesson to database's lessons table.
};

class sections
{
public:
    sections(QSqlDatabase &db); //  Note: db is a pointer of a QSqlDatabase which is our main data store.
    sections();
    QSqlDatabase db; // This is our SQLite database.   
    QStringList getSections(QString lessonName); // This one returns a list of sections of given lesson.
};

class schedule
{
public:
    schedule(QSqlDatabase &db); //  Note: db is a pointer of a QSqlDatabase which is our main data store.
    schedule();
    QSqlDatabase db; // This is our SQLite database.
    QSqlQueryModel* daysSchedule(int day); // This one returns a QSqlQueryModel which is a result of executed query. It contains the schedule of given day.
    void addToSchedule(QString lessonName, int day, QString startTime, QString endTime, QString classroom); // Executes a query to add an entry to schedule.
    void removeFromSchedule(int day, QModelIndex index); // Executes a query to delete an entry from schedule.
};

class todos
{
public:
    todos(QSqlDatabase &db); //  Note: db is a pointer of a QSqlDatabase which is our main data store.
    todos();
    QSqlDatabase db; // This is our SQLite database.
    QSqlTableModel *todosTable(); /* This function returns a QSqlTableModel. This model shows our todos table which is in our databse.
    In main class (osman) we will use this for preparing UI. */
    bool addTodo(QString todo, QString date); // Executes a query to add a todo.
    bool deleteTodo(QModelIndex index); // Executes a query to delete a todo.
};

class grades
{
public:
    grades(QSqlDatabase &db); //  Note: db is a pointer of a QSqlDatabase which is our main data store (a database of course).
    grades();
    QSqlDatabase db;
    bool addGrade(QString section, QString lesson, int value); // Executes a query to add a grade program to grades.
    bool addSection(QString name, QString lesson, int worth); // Executes a section to add a grade program to section.
    bool sectionExists(QString name, QString lesson); /* This function return true if there is a section which is given value (name).
    If not, function returns false of course. Osman uses this in main class (osman in osman.cpp) to decide what to do. Adding grade 
    in a section or adding a new section with a new worth and add a grade into it. */
    QStringList getGrades(QString section, QString lesson); /* Returns a list of grades in database. Osman uses this for filling
    combobox_grades which is under osman UI. */
    bool deleteGrade(QString section,QString lesson,int value); // Deletes a grade by given arguments.
    int getSectionWorth(QString lesson,QString section); // Returns worth value of given section. A worth shows a grade's effect on average.
};

class exams
{
public:
    exams(QSqlDatabase &db); //  Note: db is a pointer of a QSqlDatabase which is our main data store(a database of course)
    exams();
    QSqlDatabase db;
    QSqlTableModel* examsTable(); /* This function returns a QSqlTableModel. This model shows our exams table which is in our databse.
    In main class(osman) we will use this for preparing UI. */
    bool addExam(QString lesson, QString section, QString date);
    bool deleteExam(QModelIndex index);
};

void prepareSystemForS60();

#endif // CLASSES_H
