#include "section_template.h"
#include "ui_section_template.h"

section_template::section_template(QString section_name, QSqlDatabase &db, grade_template *parent) :
    QWidget(parent),
    ui(new Ui::section_template)
{
    ui->setupUi(this);
    this->parent = parent;
    grd = grades(db);
    QStringList grades = grd.getGrades(section_name, parent->lesson_name);
    ui->tableWidget_grades->setColumnCount(grades.count());

    for(int a = 0; a < grades.count(); a++)
    {
       QTableWidgetItem item(grades.at(a), 1);
       ui->tableWidget_grades->setItem(0, a, item.clone());
    }
}

section_template::~section_template()
{
    delete ui;
}

void section_template::changeEvent(QEvent *e)
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

void section_template::on_tableWidget_grades_itemClicked(QTableWidgetItem* item)
{
    int grade_value = item->text().toInt();
    parent->gradeClicked(grade_value);
}
