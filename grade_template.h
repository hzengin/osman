#ifndef GRADE_TEMPLATE_H
#define GRADE_TEMPLATE_H
#include <QWidget>
#include "classes.h"
#include "osman.h"

namespace Ui {
    class grade_template;
}

class grade_template : public QWidget {
    Q_OBJECT
public:
    grade_template(QString lesson_name, QSqlDatabase &db, osman *parent);
    grade_template();
    ~grade_template();
    QSqlDatabase db; // This is our database
    QString lesson_name; // Grades will be used at this template.
    sections sec;
    grades grd;
    void gradeClicked(int grade);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::grade_template *ui;
    osman *parent; // To reach main OSMAN class this is required. This is a pointer which pointing the main UI.
    int currentGrade;


private slots:
    void on_pushButton_average_clicked();
    void on_comboBox_section_editTextChanged(QString );
    void on_comboBox_section_currentIndexChanged();
    void on_pushButton_deleteGrade_clicked();
    void on_pushButton_addGrade_clicked();
};

#endif // GRADE_TEMPLATE_H
