#include "osman.h"
#include "ui_osman.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <grade_template.h>
#include <section_template.h>

osman::osman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::osman)
{
    // Database connection.
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./osman.database");

    ui->setupUi(this);

    lsn = lessons(db);
    sch = schedule(db);
    tdo = todos(db);
    sct = sections(db);
    exm = exams(db);

    prepareAllUIs();

}

osman::~osman()
{
    delete ui;
}

void osman::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void osman::prepareGradesUI()
{
    int lessonTabIndex=ui->tabWidget_lessons->currentIndex();
    ui->tabWidget_lessons->clear();
    QStringList lessons = lsn.lessonList();
    if(lessons.isEmpty())
        return;

    for(int index = ui->tabWidget_lessons->count(); index < lessons.count(); index++)
        ui->tabWidget_lessons->addTab(new grade_template(lessons.at(index), db, this), lessons.at(index));
    ui->tabWidget_lessons->setCurrentIndex(lessonTabIndex);

}

void osman::prepareLessonsUI()
{
    this->tableModel = lsn.lessonsTable();
    ui->tableView_lessons->setModel(this->tableModel);
    ui->tableView_lessons->setColumnHidden(0, true);
}

void osman::prepareScheduleUI()
{
    QSqlQueryModel *days_lessons = sch.daysSchedule(ui->comboBox_days->currentIndex());
    ui->tableView_the_day->setModel(days_lessons);
    QStringList lessons = lsn.lessonList();
    if(lessons.isEmpty())
        return;
    ui->comboBox_lessons->clear();
    ui->comboBox_lessons->addItems(lessons);
}

void osman::prepareNotesUI()
{
    ui->listWidget_Notes->clear();
    int rowCount=importer.getList().count();
    for(int index=0;index<rowCount;index++)
    {
        QListWidgetItem item(importer.getList().at(index),ui->listWidget_Notes);
        ui->listWidget_Notes->addItem(item.clone());
    }
}

void osman::prepareTodosUI()
{
    QSqlQueryModel *todo_table = tdo.todosTable();
    ui->tableView_todos->setModel(todo_table);
    ui->tableView_todos->setColumnHidden(0, true);
}

void osman::prepareExamsUI()
{
    QStringList lessons = lsn.lessonList();
    ui->comboBox_lesson->clear();
    ui->comboBox_lesson->addItems(lessons);
    ui->tableView_exams->setModel(exm.examsTable());
    ui->tableView_exams->setColumnHidden(0, true);
}

void osman::prepareTodayUI()
{
    QDate date = QDate::currentDate();
    int day = date.dayOfWeek();

    QSqlQueryModel *todays_lessons = sch.daysSchedule(day - 1);
    this->ui->tableView_todays_sch->setModel(todays_lessons);
}

void osman::prepareAllUIs()
{
    prepareExamsUI();
    prepareGradesUI();
    prepareLessonsUI();
    prepareNotesUI();
    prepareScheduleUI();
    prepareTodayUI();
    prepareTodosUI();
}

// We use QStackedWidget to display different interfaces and its setCurrentIndex method to switch between them.
void osman::on_pushButton_menu_clicked()        { /*ui->stackedWidget->setCurrentIndex(0);*/ emit showMenu(); }
void osman::on_pushButton_backNotes_clicked()   { ui->stackedWidget->setCurrentIndex(5); }

void osman::on_pushButton_showNote_clicked()
{
    note_import importer;
    int index = ui->listWidget_Notes->currentIndex().row();
    qDebug()<<index;
    if(index==-1)
    {
        return;
    }
    QString text = importer.getNote(index);
    // Display the note.
    ui->textBrowser_note->setHtml(text);
    ui->stackedWidget->setCurrentIndex(6);
}

/* Lesson Page */
void osman::on_pushButton_cr_lesson_clicked()
{
    QString lesson = ui->lineEdit_lesson_name->text();
    QString teacher = ui->lineEdit_teacher_name->text();

    lsn.addLesson(lesson, teacher);
    this->prepareLessonsUI(); // Update the lessons table.
}

void osman::on_pushButton_del_lesson_clicked()
{
    lsn.deleteLesson(ui->tableView_lessons->currentIndex());
    this->prepareLessonsUI();
}

/* Schedule Page */
void osman::on_comboBox_days_currentIndexChanged()
{
	this->prepareScheduleUI();
}

void osman::on_pushButton_add_lesson_clicked()
{
    int day = ui->comboBox_days->currentIndex();
    QString lessonName = ui->comboBox_lessons->currentText();
    QString startTime = ui->timeEdit_from->text();
    QString endTime = ui->timeEdit_to->text();
    QString classroom = ui->lineEdit_classroom->text();
    sch.addToSchedule(lessonName, day, startTime, endTime, classroom);
	this->prepareScheduleUI();
}

/* Todos UI */
void osman::on_pushButton_add_todo_clicked()
{
    QString todo = ui->lineEdit_todo->text();
    QString date = ui->todo_date->text();
    tdo.addTodo(todo, date);
	this->prepareTodosUI();
}

void osman::on_pushButton_remove_todo_clicked()
{
    tdo.deleteTodo(ui->tableView_todos->currentIndex());
	this->prepareTodosUI();
}

/* Exams UI */
void osman::on_comboBox_lesson_currentIndexChanged(QString lesson)
{
    QStringList sections = sct.getSections(lesson);
    ui->comboBox_section->clear();
    ui->comboBox_section->addItems(sections);
}

void osman::on_pushButton_add_exam_clicked()
{
    QString lesson = ui->comboBox_lesson->currentText();
    QString section = ui->comboBox_section->currentText();
    QString date = ui->dateTimeEdit->text();
    exm.addExam(lesson, section, date);
    this->prepareExamsUI();
}

void osman::on_pushButton_delete_exam_clicked()
{
    exm.deleteExam(ui->tableView_exams->currentIndex());
    this->prepareExamsUI();
}

void osman::on_pushButton_rm_lesson_clicked()
{
    QModelIndex index = ui->tableView_the_day->currentIndex();
    int day = ui->comboBox_days->currentIndex();
    sch.removeFromSchedule(day, index);
    this->prepareScheduleUI();
}

void osman::setIndex(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
