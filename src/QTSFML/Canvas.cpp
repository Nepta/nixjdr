#include <QMdiSubWindow>
#include "Canvas.h"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

Canvas::Canvas(QWidget* Parent, const QPoint& Position,
	 const QSize& Size, unsigned int FrameTime) : QMdiSubWindow(Parent),
    myInitialized (false)
{
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
    myTimer.setInterval(FrameTime);
}

Canvas::~Canvas(){

}

void Canvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif


        Window::create(this->winId());
        // Let the derived class do its specific stuff
        onInit();
        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(sfmlPaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* Canvas::paintEngine() const
{
    return 0;
}

void Canvas::sfmlPaint() {
    // Let the derived class do its specific stuff
    onUpdate();
    // Display on screen
    RenderWindow::display();
    //RenderWindow::clear();
}
