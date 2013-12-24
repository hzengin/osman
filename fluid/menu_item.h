#ifndef MENU_ITEM_H
#define MENU_ITEM_H
#include "osman.h"
#include <QObject>
#include <QImage>
class menu_item : public QObject
{
public:
    menu_item(int page_index,QString caption,QString image_name,osman *app);
    menu_item(QString image_name);
    /*
    This function shows the OSMAN UI and hides fluid main menu and changes the stacked_widgets current index
    which is in OSMAN's main UI"
    */
    void showPage();

    QImage* getItem_image();
    /*
    This function returns a ui
    */
    QString getCaption();

private:
    QString itemImagePath;
    QString itemCaption;
    QString itemInfo;
    int page_index;
    osman *app;
};

#endif // MENU_ITEM_H
