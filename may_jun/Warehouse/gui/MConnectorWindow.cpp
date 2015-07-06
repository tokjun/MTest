#include "MConnectorWindow.h"

//
// ------------------ Declare and define subfunction ------------------ //
//
void m_Build4Matrix(FXComposite *comp, int textLen);

// build 4x4 matrix table
void m_Build4Matrix(FXComposite *comp, int textLen)
{  
  FXMatrix *mxData = new FXMatrix(comp, 4, MATRIX_BY_ROWS, FRAME_RIDGE);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN); 
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30); 
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);

  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30); 
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);

  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30); 
  new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN, 0, 0, 30,30);
}


//
// ------------------ Map and Object implementation ------------------ //
//
FXDEFMAP(MConnectorWindow) MConnectorWindowMap[] = {
  //_____Message_Type__________ID__________Message_Handler_____
  //  FXMAPFUNC(SEL_TIMEOUT, MConnectorWindow::ID_ANIMATION, MConnectorWindow::onAnimation),
};

FXIMPLEMENT(MConnectorWindow, FXMainWindow, MConnectorWindowMap, ARRAYNUMBER(MConnectorWindowMap))


//
// ------------------ Class MConnectorWindow ------------------ //
//
MConnectorWindow::MConnectorWindow(FXApp* app):FXMainWindow(app, "MConnector Application", NULL, NULL, DECOR_ALL, 0, 0, 800, 600) 
{
  FXVerticalFrame *frMain = new FXVerticalFrame(this, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // Information panel
  FXHorizontalFrame *frInforPanel = new FXHorizontalFrame(frMain, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);
  MCBuildInfor(frInforPanel);

  FXHorizontalFrame *frIOPanel = new FXHorizontalFrame(frMain, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_BOTTOM);

  // Input panel
  FXVerticalFrame *frMainInt = new FXVerticalFrame(frIOPanel, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_LEFT);
  MCBuildIntUp(frMainInt);
  MCBuildIntDown(frMainInt);

  // Output panel
  FXVerticalFrame *frMainOut = new FXVerticalFrame(frIOPanel, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_RIGHT);
  MCBuildOutUp(frMainOut);
  MCBuildOutDown(frMainOut);
}


//
// ------------------ Private member functions ------------------ //
//
int MConnectorWindow::MCBuildInfor(FXComposite *comp)
{
  FXHorizontalFrame *frInfor = new FXHorizontalFrame(comp, FRAME_RIDGE|LAYOUT_TOP);
  FXGroupBox *gbInfor = new FXGroupBox(frInfor, "I'm Information", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  new FXLabel(gbInfor, "lb1");
  new FXLabel(gbInfor, "lb2");

  return 1;
}


//
//
int MConnectorWindow::MCBuildIntUp(FXComposite *comp)
{
  FXVerticalFrame *frIntUp = new FXVerticalFrame(comp, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP);
  FXGroupBox *gb_1 = new FXGroupBox(frIntUp, "gb_1", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);

  new FXButton(gb_1, "1", NULL, NULL, 0, BUTTON_NORMAL|LAYOUT_FILL_X|LAYOUT_TOP);
  new FXButton(gb_1, "2", NULL, NULL, 0, BUTTON_NORMAL|LAYOUT_FILL_Y|LAYOUT_SIDE_LEFT);
  new FXButton(gb_1, "3", NULL, NULL, 0, BUTTON_NORMAL|LAYOUT_FILL_Y|LAYOUT_SIDE_RIGHT);
  new FXButton(gb_1, "4", NULL, NULL, 0, BUTTON_NORMAL|LAYOUT_FILL_Y|LAYOUT_CENTER_X);

  FXGroupBox *gb_2 = new FXGroupBox(frIntUp, "gb_2", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_BOTTOM);
 
  return 1;
}


//
int MConnectorWindow::MCBuildIntDown(FXComposite *comp)
{
  FXHorizontalFrame *frPower = new FXHorizontalFrame(comp, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_BOTTOM);

  FXGroupBox *gbPower = new FXGroupBox(frPower, "I'm POWER!", FRAME_GROOVE|LAYOUT_FILL_X|LAYOUT_BOTTOM);  
  FXMatrix *mxPower = new FXMatrix(gbPower, 3, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_CENTER_X);

  new FXLabel(mxPower, "label");
  new FXButton(mxPower, "OFF");
  new FXButton(mxPower, "ON");

  return 1;
}


//
// 
int MConnectorWindow::MCBuildOutUp(FXComposite *comp)
{
  mainTab = new FXTabBook(comp, NULL, 0, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  // ------------------ Tab1 tab ------------------ //
  FXTabItem *tabTab_1 = new FXTabItem(mainTab, "tabTab_1\t", 0, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);
  FXVerticalFrame *frTab_1 = new FXVerticalFrame(mainTab, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 0, 0, 0, 0);

  //// Tab1-Data
  FXGroupBox *gbData = new FXGroupBox(frTab_1, "gbData", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);
  FXHorizontalFrame *frData = new FXHorizontalFrame(gbData, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frData, 10);


  //// Tab1-Image
  FXGroupBox *gbImage = new FXGroupBox(frTab_1, "gbImage", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_CENTER_Y);
  FXHorizontalFrame *frImage = new FXHorizontalFrame(gbImage,FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  new FXCanvas(frImage, this, ID_CANVAS, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_COLUMN);
  new FXCanvas(frImage, this, ID_CANVAS, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_COLUMN); 
  new FXCanvas(frImage, this, ID_CANVAS, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_COLUMN);


  // ------------------ Tab2 tab ------------------ //
  FXTabItem *tabTab_2 = new FXTabItem(mainTab, "tab_2\t", 0, LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);
  FXVerticalFrame *frTab_2 = new FXVerticalFrame(mainTab, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 0, 0, 0, 0);

  //// Tab2 Up
  FXHorizontalFrame *frTab_2Up = new FXHorizontalFrame(frTab_2, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP);

  FXGroupBox *gb_1 = new FXGroupBox(frTab_2Up, "gb_1", FRAME_RIDGE|LAYOUT_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXHorizontalFrame *frGb_1 = new FXHorizontalFrame(gb_1, FRAME_RIDGE|LAYOUT_CENTER_X|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frGb_1, 5);

  FXGroupBox *gb_2 = new FXGroupBox(frTab_2Up, "gb_2", FRAME_RIDGE|LAYOUT_RIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXHorizontalFrame *frGb_2 = new FXHorizontalFrame(gb_2, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frGb_2, 5);


  //// Tab2 down
  FXHorizontalFrame *frTab_2Down = new FXHorizontalFrame(frTab_2, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_BOTTOM);

  FXGroupBox *gb_3 = new FXGroupBox(frTab_2Down, "gb_3", FRAME_RIDGE|LAYOUT_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXHorizontalFrame *frGb_3 = new FXHorizontalFrame(gb_3, FRAME_RIDGE|LAYOUT_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frGb_3, 5);

  FXGroupBox *gb_4 = new FXGroupBox(frTab_2Down, "gb_4", FRAME_RIDGE|LAYOUT_RIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXHorizontalFrame *frGb_4 = new FXHorizontalFrame(gb_4, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frGb_4, 5);

  return 1;
}


//
int MConnectorWindow::MCBuildOutDown(FXComposite *comp)
{
  FXHorizontalFrame *frOutDown = new FXHorizontalFrame(comp, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_BOTTOM);
  
  FXButton *btn_1 = new FXButton(frOutDown, "btn_1", NULL, NULL, 0, BUTTON_NORMAL|LAYOUT_LEFT);
  FXButton *btn_2 = new FXButton(frOutDown, "btn_2", NULL, NULL, 0, BUTTON_NORMAL);
  
  return 1;
}



//
// ------------------ Create class ------------------ //
//
void MConnectorWindow::create(){
  FXMainWindow::create();
  show(PLACEMENT_SCREEN);
}

