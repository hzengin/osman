#ifndef SECTION_TEMPLATE_H
#define SECTION_TEMPLATE_H

#include <QWidget>
#include "classes.h"
#include "grade_template.h"
#include <QTableWidgetItem>

namespace Ui {
    class section_template;
}

class section_template : public QWidget {
    Q_OBJECT
public:
    section_template(QString section_name, QSqlDatabase &db, grade_template *parent);
    ~section_template();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::section_template *ui;
    grades grd;
    grade_template *parent;

private slots:
    void on_tableWidget_grades_itemClicked(QTableWidgetItem* item);
};

#endif // SECTION_TEMPLATE_H
