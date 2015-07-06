#include "MConnectorWindow.h"


//
// ------------------ Declare and define subfunction ------------------ //
//
// void m_Build4Matrix(FXComposite *comp, int textLen);

// build 4x4 matrix table
int MConnectorWindow::m_Build4Matrix(FXComposite *comp, int textLen)
{  
  FXMatrix *mxData = new FXMatrix(comp, 4, MATRIX_BY_COLUMNS, FRAME_RIDGE);

  mat0 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat1 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat2 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat3 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  mat4 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat5 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat6 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat7 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  mat8 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat9 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat10 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat11 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  mat12 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat13 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat14 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
  mat15 = new FXTextField(mxData, textLen, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);
}


//
// ------------------ Map and Object implementation ------------------ //
// Message map
FXDEFMAP(MConnectorWindow) MConnectorWindowMap[] = {
  //_____Message_Type__________ID__________Message_Handler_____
  FXMAPFUNC(SEL_COMMAND, MConnectorWindow::ID_SUBMITVALUE, MConnectorWindow::onSubmitValue),
  FXMAPFUNC(SEL_COMMAND, FXDataTarget::ID_OPTION, MConnectorWindow::onChooseReceive),
  FXMAPFUNC(SEL_COMMAND, FXDataTarget::ID_OPTION+1, MConnectorWindow::onChooseClient),
  
  FXMAPFUNC(SEL_TIMEOUT, MConnectorWindow::ID_UPDATEMATRIX, MConnectorWindow::onUpdateMatrix),
};

FXIMPLEMENT(MConnectorWindow, FXMainWindow, MConnectorWindowMap, ARRAYNUMBER(MConnectorWindowMap))


//
// ------------------ Class MConnectorWindow ------------------ //
//
MConnectorWindow::MConnectorWindow(FXApp* app):FXMainWindow(app, "MConnector Application", NULL, NULL, DECOR_ALL, 0, 0, 630, 225) 
{
  application = app;
  FXHorizontalFrame *frMain = new FXHorizontalFrame(this, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // Input panel
  FXVerticalFrame *frMainInt = new FXVerticalFrame(frMain, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_LEFT);
  MCBuildIntUp(frMainInt);

  // Output panel
  FXVerticalFrame *frMainOut = new FXVerticalFrame(frMain, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_SIDE_RIGHT);
  MCBuildOutUp(frMainOut);

  // timer
  timerInterval = 10;    // ms
  application->addTimeout(this, ID_UPDATEMATRIX, timerInterval);

  display = FALSE;
}


//
// ------------------ Private member functions ------------------ //
//
int MConnectorWindow::MCBuildIntUp(FXComposite *comp)
{
  FXGroupBox *gb_RC = new FXGroupBox(comp, "Connect parameters", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);
  FXMatrix *mxRC = new FXMatrix(gb_RC, 2, MATRIX_BY_COLUMNS, FRAME_RIDGE);

  dtRorC = new FXDataTarget();
  rbtnReceive = new FXRadioButton(mxRC, "Receive", this, FXDataTarget::ID_OPTION);
  rbtnClient = new FXRadioButton(mxRC, "Client", this, FXDataTarget::ID_OPTION+1);

  FXGroupBox *gb_1 = new FXGroupBox(comp, "Connect parameters", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_TOP);
  mxIntUp = new FXMatrix(gb_1, 2, MATRIX_BY_COLUMNS, FRAME_RIDGE);

  new FXLabel(mxIntUp, "Hostname: ");
  txHost = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  new FXLabel(mxIntUp, "Port: ");
  txPort = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  new FXLabel(mxIntUp, "X: ");
  txX = new FXTextField(mxIntUp, 10, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN);

  new FXButton(mxIntUp, "&Submit", NULL, this, ID_SUBMITVALUE, BUTTON_NORMAL);
  new FXButton(mxIntUp, "&Clear", NULL, NULL, 0, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X);
 
  return 1;
}


//
// 
int MConnectorWindow::MCBuildOutUp(FXComposite *comp)
{  
  FXGroupBox *gbData = new FXGroupBox(comp, "gbData", FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_CENTER_Y);
  FXHorizontalFrame *frData = new FXHorizontalFrame(gbData, FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  m_Build4Matrix(frData, 10);
  
  return 1;
}


// ------------------ Message handler functions ------------------ //
//

int testTime = 0;
long MConnectorWindow::onSubmitValue(FXObject *sender, FXSelector, void*)
{
  // get string value from "port"
  intPort = FXIntVal(txPort->getText());
  std::cerr << "Port:" << intPort << std::endl;

  display = TRUE;

  // ********** Set OpenIGTLink sockets ********** //
  serverSocket = igtl::ServerSocket::New();
  serverSocket->CreateServer(intPort);

  headerMsg = igtl::MessageHeader::New();
   
  socket = serverSocket->WaitForConnection(1000);
  // ********************************************* //
 
  return 1;
}


int times = 0;

long MConnectorWindow::onUpdateMatrix(FXObject*, FXSelector, void*)
{
  std::cerr << "into break " << (times++) << ", typeof : " << display << std::endl;
  
  if(display == TRUE)
  {  
    if (socket.IsNotNull())  // if client connected
    {

std::cerr << "client not null" << std::endl;

      headerMsg->InitPack();
      int r = socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
      
      if (r == 0)
      {
	socket->CloseSocket(); 
      }

      headerMsg->Unpack();

      if(strcmp(headerMsg->GetDeviceType(), "TRANSFORM") == 0)
      {
        transMsg = igtl::TransformMessage::New();

        // Put the header information to the transform message
        transMsg->SetMessageHeader(headerMsg);
        transMsg->AllocatePack();
       
        // Receive the message body
        socket->Receive(transMsg->GetPackBodyPointer(), transMsg->GetPackBodySize());

        // Unpack the message body
        int c = transMsg->Unpack(1);
        if (c & igtl::MessageHeader::UNPACK_BODY)   // if Cyclic redundancy check is ok, read transform data.
        {

std::cerr << "into CRC" << std::endl;

          transMsg->GetMatrix(mat);
           
          mat0->setText(FXStringVal(mat[0][0]));
          mat1->setText(FXStringVal(mat[0][1]));
          mat2->setText(FXStringVal(mat[0][2]));
          mat3->setText(FXStringVal(mat[0][3]));
  
          mat4->setText(FXStringVal(mat[1][0]));
          mat5->setText(FXStringVal(mat[1][1]));
          mat6->setText(FXStringVal(mat[1][2]));
          mat7->setText(FXStringVal(mat[1][3]));
 
          mat8->setText(FXStringVal(mat[2][0]));
          mat9->setText(FXStringVal(mat[2][1]));
          mat10->setText(FXStringVal(mat[2][2]));
          mat11->setText(FXStringVal(mat[2][3]));
  
          mat12->setText(FXStringVal(mat[3][0]));
          mat13->setText(FXStringVal(mat[3][1]));
          mat14->setText(FXStringVal(mat[3][2]));
          mat15->setText(FXStringVal(mat[3][3]));
        }    // endif CRC
      }    // endif check with transform
    }    // endif client connect
  }    // endif display

  application->addTimeout(this, MConnectorWindow::ID_UPDATEMATRIX, timerInterval);
  return 1;
}


long MConnectorWindow::onChooseReceive(FXObject*, FXSelector, void*)
{
}



long MConnectorWindow::onChooseClient(FXObject*, FXSelector, void*)
{
}


//
// ------------------ Create class ------------------ //
//
void MConnectorWindow::create(){
  FXMainWindow::create();
  show(PLACEMENT_SCREEN);
}

