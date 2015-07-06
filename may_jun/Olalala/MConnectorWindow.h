#ifndef _MConnector_h
#define _MConnector_h

#include <iostream>
#include <cstring>

#include <fx.h>
#include "MReceiveServer.h"


// class MConnectorWindow
class MConnectorWindow:public FXMainWindow {
  FXDECLARE(MConnectorWindow);

 // ------------------ Constructor & Destructor ------------------ //
 protected:
  MConnectorWindow(){};
  
 public:
  MConnectorWindow(FXApp* app);
  virtual ~MConnectorWindow(){
    // app->removeTimeout(this, ID_UPDATEMATRIX)
  };


  // ------------------ GUI widget variables ------------------ //
  // Layout
 private:
  FXHorizontalFrame *frMain;
  FXVerticalFrame   *frMainInt;
  FXVerticalFrame   *frMainOut;
  FXMatrix          *mxIntUp;

  FXTabBook         *mainTab;

  FXTextField       *txHost;
  FXTextField       *txPort;
  FXTextField       *txX;

  FXRadioButton     *rbtnReceive;
  FXRadioButton     *rbtnClient;
  
  FXString           strHost;
  FXString           strPort;

  int                intPort;
  FXDataTarget      *dtRorC;

  FXTextField       *mat0;
  FXTextField       *mat1;
  FXTextField       *mat2;
  FXTextField       *mat3;

  FXTextField       *mat4;
  FXTextField       *mat5;
  FXTextField       *mat6;
  FXTextField       *mat7;

  FXTextField       *mat8;
  FXTextField       *mat9;
  FXTextField       *mat10;
  FXTextField       *mat11;

  FXTextField       *mat12;
  FXTextField       *mat13;
  FXTextField       *mat14;
  FXTextField       *mat15;


 float              flmat0;
 float              flmat1;
 float              flmat2;
 float              flmat3;

 float              flmat4;
 float              flmat5;
 float              flmat6;
 float              flmat7;

 float              flmat8;
 float              flmat9;
 float              flmat10;
 float              flmat11;

 float              flmat12;
 float              flmat13;
 float              flmat14;
 float              flmat15;

  FXApp             *application;
  int                timerInterval;
  FXTimer           *updateTimer;

  bool               display;


  MReceiveServer    *MRS;
  double             mxUpd[];

  float                matData[15];


  // ********** igtl
 igtl::ServerSocket::Pointer        serverSocket;
 igtl::Socket::Pointer              socket;
 igtl::MessageHeader::Pointer       headerMsg;
 igtl::TransformMessage::Pointer    transMsg;
 igtl::Matrix4x4                    mat;
  // **********



  // Widget variables
 protected:
  FXMenuBar         *menubar;    // Menu bar
  FXToolBar         *toolbar;    // Tool bar
  FXStatusBar       *statusbar;

  // ------------------ Public functions------------------ //
 public:  
  virtual void create();
  
  // ------------------ Private functions ------------------ //
 private:
  int               MCBuildIntUp(FXComposite*);
  int               MCBuildOutUp(FXComposite*);
  int               m_Build4Matrix(FXComposite*, int textLen);

  
  // ------------------ Message ------------------ //
  // Message for the class
 public:
  enum{
   ID_CANVAS = FXMainWindow::ID_LAST,

   ID_SUBMITVALUE, 
   ID_UPDATEMATRIX,
   ID_OPTION,

   ID_DTPORTNO,

   ID_CLEAR,
   ID_LAST
  };

  // Message handlers
 public:
  long onSubmitValue(FXObject *, FXSelector, void *);
  long onUpdateMatrix(FXObject *, FXSelector, void *);
  long onChooseReceive(FXObject *, FXSelector, void *);
  long onChooseClient(FXObject *, FXSelector, void *);
};

#endif
