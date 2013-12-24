#ifndef FLUID_MENU_H
#define FLUID_MENU_H
#include <QtGui>
#include <QTimer>
#include <QStringRef>
#include "fluid/menu_item.h"
#include "fluid/pictureflow.h"

class fluid_menu : public QStackedWidget
{
    Q_OBJECT

public:
    fluid_menu(osman *oss);
    ~fluid_menu();
    int w;
    int h;

public slots:
    void showThat(int index);
    void switchToMenu();
    void aniSlide();
protected:
    void changeEvent(QEvent *event);
private:
    PictureFlow* pictureFlowWidget;
    QList<menu_item*> menu_items;
    void populatePictureFlow();
    void switchToSlideshow();
    void addMenuItems(osman *oss);
    void addIntroItems();
    void introFinished();
    osman *oss;
    QTimer introAni;

};


#endif
