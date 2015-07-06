#include <fx.h>
#include "MConnectorWindow.h"

//
// ------------------ Declare and define subfunction ------------------ //
//
void m_Build4Matrix(FXComposite *comp, int textLen);

// build 4x4 matrix table
void m_Build4Matrix(FXComposite *comp, int textLen)
{  
  FXMatrix *mxData = new FXMatrix(comp, 4, MATRIX_BY_ROWS, FRAME_RIDGE);
 
  for(int i = 0; i < 16; i++)
  {
    new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  }
}


//
// ------------------ Map and Object implementation ------------------ //
// Message map
FXDEFMAP(MConnectorWindow) MConnectorWindowMap[] = {
  //_____Message_Type__________ID__________Message_Handler_____
  FXMAPFUNC(SEL_COMMAND, MConnectorWindow::ID_SUBMITVALUE, MConnectorWindow::onSubmitValue),

};

FXIMPLEMENT(MConnectorWindow, FXMainWindow, MConnectorWindowMap, ARRAYNUMBER(MConnectorWindowMap))


//
// ------------------ Class MConnectorWindow ------------------ //
//
MConnectorWindow::MConnectorWindow(FXApp* app):FXMainWindow(app, "MConnector Application", NULL, NULL, DECOR_ALL, 0, 0, 800, 600) 
{
  FXVerticalFrame *frMain = new FXVerticalFrame(this, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXHorizontalFrame *frIOPanel = new FXHorizontalFrame(frMain, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_BOTTOM);

  // Input panel
  FXVerticalFrame *frMainInt = new FXVerticalFrame(frIOPanel, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_LEFT);
  MCBuildIntUp(frMainInt);

  // Output panel
  FXVerticalFrame *frMainOut = new FXVerticalFrame(frIOPanel, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_RIGHT);
  MCBuildOutUp(frMainOut);
}


//
// ------------------ Private member functions ------------------ //
//
int MConnectorWindow::MCBuildIntUp(FXComposite *comp)
{
  FXVerticalFrame *frIntUp = new FXVerticalFrame(comp, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP);
  FXGroupBox *gb_1 = new FXGroupBox(frIntUp, "Connect parameters", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);

  FXMatrix *mxIntUp = new FXMatrix(gb_1, 2, MATRIX_BY_COLUMNS, FRAME_RIDGE);
  new FXLabel(mxIntUp, "Hostname: ");
 // FXTextField *hostText = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN); 
 //

  hostText = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);



 
  new FXLabel(mxIntUp, "Port: ");
  FXTextField *portText = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN); 

  new FXLabel(mxIntUp, "Y: ");
  FXTextField *yText = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN); 
 
  new FXButton(mxIntUp, "&Submit", NULL, this, ID_SUBMITVALUE, BUTTON_NORMAL);
  new FXButton(mxIntUp, "&Clear", NULL, NULL, 0, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X);
 
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
// ------------------ Message handler functions ------------------ //
//
long MConnectorWindow::onSubmitValue(FXObject *sender, FXSelector, void*)
{
  hostText->setText("hello");  
  return 1;
}




//
// ------------------ Create class ------------------ //
//
void MConnectorWindow::create(){
  FXMainWindow::create();
  show(PLACEMENT_SCREEN);
}

