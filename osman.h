#ifndef OSMAN_H
#define OSMAN_H
#include "classes.h"
#include "note_import.h"
#include <QWidget>
namespace Ui {
    class osman;
}

class osman : public QWidget {
    Q_OBJECT
public:
    osman(QWidget *parent = 0);
    ~osman();
    void prepareNotesUI();
    void prepareTodosUI();
    void prepareLessonsUI();
    void prepareScheduleUI();
    void prepareGradesUI();
    void prepareExamsUI();
    void prepareTodayUI();
    void prepareAllUIs();
    void setIndex(int index); // This function sets the stacked_widget's currnet index. This will call if the program running under Symbian60.
  signals:
    void showMenu(); // This signal connected to menu's show slot.
protected:
    void changeEvent(QEvent *e);

private:
    Ui::osman *ui;
    todos tdo;
    lessons lsn;
    schedule sch;
    sections sct;
    exams exm;
    note_import importer;
    QSqlDatabase db;
    QSqlTableModel *tableModel;

private slots:
    void on_pushButton_delete_exam_clicked();
    /* Main Menu */
    void on_pushButton_menu_clicked();
    /* Lessons Screen */
    void on_pushButton_cr_lesson_clicked();
    void on_pushButton_del_lesson_clicked();
    /* Schedule Screen */
    void on_pushButton_rm_lesson_clicked();
    void on_pushButton_remove_todo_clicked();
    void on_pushButton_add_exam_clicked();
    void on_comboBox_lesson_currentIndexChanged(QString lesson);
    void on_pushButton_add_todo_clicked();
    void on_comboBox_days_currentIndexChanged();
    
    void on_pushButton_backNotes_clicked();
    void on_pushButton_showNote_clicked();
    void on_pushButton_add_lesson_clicked();


};

#endif // OSMAN_H
