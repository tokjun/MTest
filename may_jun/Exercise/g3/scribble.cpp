#include <fx.h>
#include "scribble.h"

// Define a message map for the MYScribble Window class
FXDEFMAP(MYScribbleWindow) MYScribbleWindowMap[] = {
  //_____Message_Type__________ID__________Message_Handler_____
  FXMAPFUNC(SEL_PAINT, MYScribbleWindow::ID_CANVAS, MYScribbleWindow::onPaint),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS, MYScribbleWindow::ID_CANVAS, MYScribbleWindow::onMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE, MYScribbleWindow::ID_CANVAS,MYScribbleWindow::onMouseUp),
  FXMAPFUNC(SEL_MOTION, MYScribbleWindow::ID_CANVAS, MYScribbleWindow::onMouseMove),
  FXMAPFUNC(SEL_COMMAND, MYScribbleWindow::ID_CLEAR, MYScribbleWindow::onCmdClear),
  FXMAPFUNC(SEL_UPDATE, MYScribbleWindow::ID_CLEAR, MYScribbleWindow::onUpdClear),
};


FXIMPLEMENT(MYScribbleWindow, FXMainWindow, MYScribbleWindowMap, ARRAYNUMBER(MYScribbleWindowMap))


// Construct a ScribbleWindow
MYScribbleWindow::MYScribbleWindow(FXApp* a):FXMainWindow(a, "Scribble Applictation Title", NULL, NULL, DECOR_ALL, 0, 0, 800, 600){
 
  contents = new FXHorizontalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0);

  canvasFrame = new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT,0, 0, 0, 0, 10, 10, 10, 10);
  
  new FXLabel(canvasFrame, "Canvas Frame", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);
  
  canvas = new FXCanvas(canvasFrame, this, ID_CANVAS, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_COLUMN);
  
  // Horizontal divider line
  new FXHorizontalSeparator(canvasFrame, SEPARATOR_GROOVE|LAYOUT_FILL_X);


  buttonFrame = new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

  new FXLabel(buttonFrame, "Button Frame", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);

  new FXHorizontalSeparator(buttonFrame, SEPARATOR_RIDGE|LAYOUT_FILL_X);

  new FXButton(buttonFrame, "&Clear", NULL, this, ID_CLEAR, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 5, 5);

  new FXButton(buttonFrame, "&Exit", NULL, getApp(), FXApp::ID_QUIT, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 5, 5);

  
  // Initialize private variables
  drawColor = FXRGB(255, 0, 0);
  mdflag = 0;
  dirty =0; 
}


// Create and initialize
void MYScribbleWindow::create(){
  // Create the window
  FXMainWindow::create();

  // Make the main window appear
  show(PLACEMENT_SCREEN);
}



// Handle the message
long MYScribbleWindow::onMouseDown(FXObject *, FXSelector, void *){
  canvas->grab();
  mdflag = 1;
  return 1;
}

long MYScribbleWindow::onMouseMove(FXObject *, FXSelector, void * ptr){
  FXEvent *ev = (FXEvent *)ptr;

  if(mdflag)
    {
      FXDCWindow dc(canvas);

      dc.setForeground(drawColor);
      dc.drawLine(ev->last_x, ev->last_y, ev->win_x, ev->win_y);
      dirty = 1;
    }
  
  return 1;
}

long MYScribbleWindow::onMouseUp(FXObject *, FXSelector, void *ptr){
  FXEvent *ev = (FXEvent*) ptr;
  canvas->ungrab();
  
  if(mdflag){
    FXDCWindow dc(canvas);

    dc.setForeground(drawColor);
    dc.drawLine(ev->last_x, ev->last_y, ev->win_x, ev->win_y);

    dirty = 1;
    mdflag = 0;
  }
  
  return 1;
}

long MYScribbleWindow::onPaint(FXObject *, FXSelector, void *ptr){
  FXEvent *ev = (FXEvent*) ptr;
  FXDCWindow dc(canvas, ev);

  dc.setForeground(canvas->getBackColor());
  dc.fillRectangle(ev->rect.x, ev->rect.y, ev->rect.w, ev->rect.h);

  return 1;
}


// Handle the clear message
long MYScribbleWindow::onCmdClear(FXObject *, FXSelector, void *){
  FXDCWindow dc(canvas);

  dc.setForeground(canvas->getBackColor());
  dc.fillRectangle(0, 0, canvas->getWidth(), canvas->getHeight());

  dirty = 0;
  return 1;
}


long MYScribbleWindow::onUpdClear(FXObject *sender, FXSelector, void *){
  if(dirty)
    sender->handle(this, FXSEL(SEL_COMMAND, FXWindow::ID_ENABLE), NULL);
  else
    sender->handle(this, FXSEL(SEL_COMMAND, FXWindow::ID_DISABLE), NULL);

  return 1;
}
