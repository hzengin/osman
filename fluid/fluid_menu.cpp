#include "fluid_menu.h"
#include <QTextItem>

#define DEFAULT_INPUT_TIMEOUT 10000
#define SIZING_FACTOR_HEIGHT 4/8
#define SIZING_FACTOR_WIDTH 4/8

fluid_menu::fluid_menu(osman *oss)
{
    pictureFlowWidget = new PictureFlow();
    pictureFlowWidget->setFocus();
    addWidget(pictureFlowWidget);
    setCurrentWidget(pictureFlowWidget);
    pictureFlowWidget->setFocus();
    QRect screen_size = QApplication::desktop()->screenGeometry();
    introAni.setInterval(250);
    this->oss=oss;
    QObject::connect(&introAni,SIGNAL(timeout()),this,SLOT(aniSlide()));
    QObject::connect(pictureFlowWidget, SIGNAL(itemActivated(int)), this, SLOT(showThat(int)));
	QObject::connect(oss,SIGNAL(showMenu()),this,SLOT(showFullScreen()));
	QObject::connect(oss,SIGNAL(showMenu()),oss,SLOT(hide()));
    h = screen_size.height() * SIZING_FACTOR_HEIGHT;
    w = screen_size.width() * SIZING_FACTOR_WIDTH;

    const int hh = qMin(h, w);
    const int ww = hh;
    pictureFlowWidget->setSlideSize(QSize(ww, hh));
    addIntroItems();
    populatePictureFlow();
    pictureFlowWidget->setCurrentSlide(0);
    pictureFlowWidget->isIntroRunning=true;
    introAni.start();
 

}

void fluid_menu::aniSlide()
{
    static int wait=5;
    if(pictureFlowWidget->currentSlide()<4&&wait==0)
    {
        introAni.setInterval(333);
        pictureFlowWidget->showNext();
    }
    else
    {
        if(wait==0)
        {
        introAni.stop();
        pictureFlowWidget->isIntroRunning=false;
        introFinished();
        }
        else
            wait--;
    }
}


void fluid_menu::addMenuItems(osman *oss)
{
    /*We are appending the menu items*/
    menu_item* today = new menu_item(7,"Today's Schedule",":/logos/today",oss);
    menu_item* exams = new menu_item(3,"Exams",":/logos/exams",oss);
    menu_item* grades = new menu_item(2,"Grades",":/logos/grades",oss);
    menu_item* todo = new menu_item(4,"Todos",":/logos/todos",oss);
    menu_item* notes = new menu_item(5,"Notes",":/logos/notes",oss);
    menu_item* schedule = new menu_item(1,"Schedule",":/logos/schedule",oss);
    menu_item* lessons = new menu_item(0,"Lessons",":/logos/lessons",oss);

    
    menu_items.append(notes);
    menu_items.append(todo);
    menu_items.append(exams);
    menu_items.append(lessons);
    menu_items.append(today);
    menu_items.append(schedule);
    menu_items.append(grades);
    oss->prepareAllUIs();
    // Append an exit Item
    menu_item* exitItem = new menu_item(-1,"Exit OSMAN",":/logos/exit",oss);
    menu_items.append(exitItem);
}

void fluid_menu::addIntroItems()
{
    menu_item *o=new menu_item(":/logos/o");
    menu_item *s=new menu_item(":/logos/s");
    menu_item *m=new menu_item(":/logos/m");
    menu_item *a=new menu_item(":/logos/a");
    menu_item *n=new menu_item(":/logos/n");
    menu_items.append(o);
    menu_items.append(s);
    menu_items.append(m);
    menu_items.append(a);
    menu_items.append(n);
    populatePictureFlow();
}

void fluid_menu::introFinished()
{
    menu_items.clear();
    addMenuItems(oss);
    populatePictureFlow();
}

void fluid_menu::populatePictureFlow()
{
    pictureFlowWidget->setSlideCount(menu_items.count());

    for (int i=menu_items.count()-1; i>=0; --i) {
        pictureFlowWidget->setSlide(i, *(menu_items[i]->getItem_image()));
        pictureFlowWidget->setSlideCaption(i, menu_items[i]->getCaption());
    }

    pictureFlowWidget->setCurrentSlide(menu_items.count()/2);
}

void fluid_menu::showThat(int index)
{
    //the exit item's action
    if (index == menu_items.size() -1) {
        qApp->quit();
        return;
    }
    menu_items[index]->showPage();
	this->showFullScreen();
}

void fluid_menu::switchToMenu()
{
    setCurrentWidget(pictureFlowWidget);
}

void fluid_menu::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (isActiveWindow()) {
            if(currentWidget() == pictureFlowWidget) {
            } else {
            }
        } else {
        }
    }
    QStackedWidget::changeEvent(event);
}


fluid_menu::~fluid_menu()
{
    delete pictureFlowWidget;
}
