#include "grade_template.h"
#include "ui_grade_template.h"
#include "section_template.h"
#include <QMessageBox>

grade_template::grade_template(QString lesson_name, QSqlDatabase &db, osman *parent) :
    QWidget(parent),
    ui(new Ui::grade_template)
{
    this->db = db;
    this->lesson_name = lesson_name;
    this->parent=parent;
    ui->setupUi(this);
    sec = sections();
    QStringList sections = sec.getSections(lesson_name);
    if(sections.isEmpty())
        return;

    ui->comboBox_section->clear();
    ui->comboBox_section->addItems(sections);
    ui->tabWidget->removeTab(0);
    for(int index = 0; index < sections.count(); index++)
    {
        ui->tabWidget->addTab(new section_template(sections.at(index), db, this), sections.at(index));
        /*
          This loop adding tabs using section_template.
        */
    }
}

grade_template::~grade_template()
{
    delete ui;
}

void grade_template::changeEvent(QEvent *e)
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

void grade_template::on_pushButton_addGrade_clicked()
{
    QString worth=ui->lineEdit_worth->text();
    worth=worth.replace("Worth: ","");
    worth=worth.replace("%","");
    /*
      We have to check if there is a section which have same name with given name.
    */
    if(!grd.sectionExists(ui->comboBox_section->currentText(), this->lesson_name))
    {
        /*
          If there is; we should add given grade into it. If not we adding a new section.
        */
        grd.addSection(ui->comboBox_section->currentText(), this->lesson_name,worth.toInt());
    }

    grd.addGrade(ui->comboBox_section->currentText(), this->lesson_name, ui->lineEdit_grade->text().toInt());
    parent->prepareGradesUI();
    /*We updates the ui for changes.*/
    return;
}

void grade_template::gradeClicked(int grade)
{
    this->currentGrade = grade;
}

void grade_template::on_pushButton_deleteGrade_clicked()
{
    grd.deleteGrade(ui->comboBox_section->currentText(), this->lesson_name, this->currentGrade);
    parent->prepareGradesUI();
    /*We deletes the current grade and we updates the ui for changes.*/

}

void grade_template::on_comboBox_section_currentIndexChanged()
{
    int worth=grd.getSectionWorth(this->lesson_name,ui->comboBox_section->currentText());
    //Gets new section's worth.This will use to set linedit_worth's text.
    ui->lineEdit_worth->setText(QString::number(worth));
    ui->lineEdit_worth->setEnabled(false);
}

void grade_template::on_comboBox_section_editTextChanged(QString )
{
    ui->lineEdit_worth->clear();
    ui->lineEdit_worth->setEnabled(true);
}

void grade_template::on_pushButton_average_clicked()
{
     float lesson_total;
     /*
     This loop making same work with all sections
     */
     for(int section_index = 0; section_index < ui->tabWidget->count(); section_index++)
     {
         QString section_name = ui->tabWidget->tabText(section_index);
         int section_worth = grd.getSectionWorth(this->lesson_name, section_name);
         QStringList grades = grd.getGrades(section_name,this->lesson_name);
         int section_total = 0;
         /*Getting grades,current section's worth, it's name*/
         /*!
            This loop working with all grades and sum up them with section's total grade.
         */
         for(int grade_index = 0; grade_index<grades.count(); grade_index++)
         {
                QString grade = grades.at(grade_index);
                section_total += grade.toInt();

         }
         /*!
           OSMAN calculating the average using sections worth
         */
        lesson_total += ((float)section_total / grades.count()) * ((float)section_worth  / (float)100);
     }
     QMessageBox::information(0, "Average", "Average of " + this-> lesson_name + " is: " + QString::number(lesson_total));
}
