#include "menu_item.h"
#include <QLayout>
menu_item::menu_item(int page_index, QString caption, QString image_name, osman *app)
{
    itemImagePath = image_name;
    itemCaption = caption;
    this->page_index=page_index;
    this->app=app;
}

menu_item::menu_item(QString image_name)
{
    itemImagePath = image_name;
}

void menu_item::showPage()
{
    app->setIndex(page_index);
	switch(this->page_index)
	{
	case 0:
		app->prepareLessonsUI();
		break;
	case 1:
		app->prepareScheduleUI();
		break;
	case 2:
		app->prepareGradesUI();
		break;
	case 3:
		app->prepareExamsUI();
		break;
	case 4:
		app->prepareTodosUI();
		break;
	case 5:
		app->prepareNotesUI();
		break;
	case 7:
		app->prepareTodayUI();
		break;
	}
	app->showFullScreen();
}

QImage* menu_item::getItem_image()
{
    return new QImage(itemImagePath);
}

QString menu_item::getCaption()
{
    return itemCaption;
}
