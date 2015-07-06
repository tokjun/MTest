#include <fx.h>
#include "scribble.h"

// Main
int main(int argc, char* argv[])
{  
  MYScribbleWindow* mWindow;

  // Make application
  FXApp application("Scribble", "FoxTest");

  // Start app
  application.init(argc, argv);

  // Scribble Window
  mWindow = new MYScribbleWindow(&application);

  // Create the appliation's window
  application.create();

  // Run the application
  return application.run();
}
