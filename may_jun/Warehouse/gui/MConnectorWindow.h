#ifndef _MConnector_h
#define _MConnector_h

#include <fx.h>

// class MConnectorWindow
class MConnectorWindow : public FXMainWindow {
  FXDECLARE(MConnectorWindow);

 //
 // ------------------ Constructor & Destructor ------------------ //
 //
 protected:
  MConnectorWindow(){};
  
 public:
  MConnectorWindow(FXApp* app);
  virtual ~MConnectorWindow(){};
;


  // ------------------ GUI widget variables ------------------ //
  // Layout
 private:
  FXVerticalFrame   *frMain;
  FXHorizontalFrame *frInforPanel;
  FXHorizontalFrame *frIOPanel;

  FXVerticalFrame   *frMainInt;
  FXVerticalFrame   *frMainOut;

  FXTabBook         *mainTab;
  

  // Widget variables
 protected:
  FXMenuBar         *menubar;    // Menu bar
  FXToolBar         *toolbar;    // Tool bar
  FXStatusBar       *statusbar;

  FXTabBook         *leftMainTab;


  // ------------------ Public functions------------------ //
 public:  
  virtual void create();
  

  // ------------------ Private functions ------------------ //
 private:
  int               MCBuildInfor(FXComposite*);
  int               MCBuildIntUp(FXComposite*);
  int               MCBuildIntDown(FXComposite*);
  int               MCBuildOutUp(FXComposite*);
  int               MCBuildOutDown(FXComposite*);
 
  
  // ------------------ Message ------------------ //
  // Message for the class
 public:
  enum{
   ID_CANVAS = FXMainWindow::ID_LAST,
   ID_ANIMATION,
  };

  // Message handlers
 public:
  long onCmdClear(FXObject *, FXSelector, void *);
  // long onAnimation(FXObject *, FXSelector, void *);

};

#endif
