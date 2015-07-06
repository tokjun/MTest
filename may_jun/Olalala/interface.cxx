#include <fx.h>
#include "MConnectorWindow.h"

// =====================================================================
// Main
int main(int argc, char* argv[])
{
  MConnectorWindow* interWindow;

  // Make app
  FXApp application("SRConnector", "Just for TEST!");

  // Open display
  application.init(argc, argv);

  // MConnectorWindow
  interWindow = new MConnectorWindow(&application);

  // Create app
  application.create();

  // Run 
  return application.run();
}
