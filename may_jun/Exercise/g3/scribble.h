#include <fx.h>


// Define new class
class MYScribbleWindow : public FXMainWindow {
  // Macro for class hierarchy declariations
  FXDECLARE(MYScribbleWindow)

  protected:
    MYScribbleWindow(){};
  
  private:
    FXHorizontalFrame *contents;
    FXVerticalFrame   *canvasFrame;
    FXVerticalFrame   *buttonFrame;
    FXCanvas          *canvas;
    int                mdflag;
    int                dirty;
    FXColor            drawColor;

 
  public:
    // Message handlers
    long onPaint(FXObject *, FXSelector, void *);
    long onMouseDown(FXObject *, FXSelector, void *);
    long onMouseUp(FXObject *, FXSelector, void *);
    long onMouseMove(FXObject *, FXSelector, void *);
    long onCmdClear(FXObject *, FXSelector, void *);
    long onUpdClear(FXObject *, FXSelector, void *);
  

    // Message for our class
    enum {
      ID_CANVAS = FXMainWindow::ID_LAST,
      ID_CLEAR,
      ID_LAST,
    };


    // MYScribbleWindow's constructor
    MYScribbleWindow(FXApp* a);


    // Initialize
    virtual void create();
    virtual ~MYScribbleWindow(){};
};

