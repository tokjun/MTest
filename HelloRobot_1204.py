from __main__ import vtk, qt, ctk, slicer

#
# HelloRobot
#

class HelloRobot:
  def __init__(self, parent):
    parent.title = "Hello Robot"
    parent.categories = ["IGT"]
    parent.dependencies = []
    parent.contributors = [""] # replace with "Firstname Lastname (Org)"
    parent.helpText = """
    Example of scripted loadable extension for the HelloPython tutorial.
    """
    parent.acknowledgementText = """
    This file""" # replace with organization, grant and thanks.
    self.parent = parent

#
# qHelloRobotWidget
#

class HelloRobotWidget:
  def __init__(self, parent = None):
    #self.cnode = None
    self.tnode = None
    self.strHostname = None
    #self.intPort = None
    

    if not parent:
      self.parent = slicer.qMRMLWidget()
      self.parent.setLayout(qt.QVBoxLayout())
      self.parent.setMRMLScene(slicer.mrmlScene)
    else:
      self.parent = parent
    self.layout = self.parent.layout()
    if not parent:
      self.setup()
      self.parent.show()
    
    self.logic = HelloRobotLogic()

  def setup(self):
    # Instantiate and connect widgets ...

    # Collapsible button
    mainCollapsibleButton = ctk.ctkCollapsibleButton()
    mainCollapsibleButton.text = "Robot!"
    self.layout.addWidget(mainCollapsibleButton)

    # Layout within the sample collapsible button
    HostPortLayout = qt.QVBoxLayout(mainCollapsibleButton)

    ########################
    labelHostname = qt.QLabel("Hostname: ")
    self.lineEditHostname = qt.QLineEdit()
    labelPort = qt.QLabel("Port: ")
    self.lineEditPort = qt.QLineEdit()

    buttonConnect = qt.QPushButton("Connect")
    buttonConnect.toolTip = "Print 'Hello world' in standard output."
    buttonRegistration = qt.QPushButton("ZFrameTransform")
    buttonTarget = qt.QPushButton("find Target")
    buttonSendTarget = qt.QPushButton("send Target")
    buttonCurrent = qt.QPushButton("Current")
    buttonDisconnect = qt.QPushButton("Disconnect")

    HostPortLayout.addWidget(labelHostname)
    HostPortLayout.addWidget(self.lineEditHostname)
    HostPortLayout.addWidget(labelPort)
    HostPortLayout.addWidget(self.lineEditPort)

    HostPortLayout.addWidget(buttonConnect)
    HostPortLayout.addWidget(buttonRegistration)
    HostPortLayout.addWidget(buttonTarget)
    HostPortLayout.addWidget(buttonSendTarget)
    HostPortLayout.addWidget(buttonCurrent)
    HostPortLayout.addWidget(buttonDisconnect)

    buttonConnect.connect('clicked(bool)', self.onButtonConnectClicked)
    buttonRegistration.connect('clicked(bool)', self.onButtonRegistrationClicked)
    buttonTarget.connect('clicked(bool)', self.onButtonTargetClicked)
    buttonSendTarget.connect('clicked(bool)', self.onButtonSendTargetClicked)
    buttonCurrent.connect('clicked(bool)', self.onButtonCurrentClicked)
    buttonDisconnect.connect('clicked(bool)', self.onButtonDisconnectClicked)

    #########################

    # Add vertical spacer
    self.layout.addStretch(1)

    # Set local var as instance attribute
    #self.buttonConnect = buttonConnect

  def onButtonConnectClicked(self):
    self.strHostname = str(self.lineEditHostname.text)
    self.intPort = int(self.lineEditPort.text)
    self.logic.buttonConnect(self.strHostname, self.intPort)
    self.logic.activeEvent()  # active the monitor
    
  def onButtonRegistrationClicked(self):
    self.logic.buttonRegistration()

  def onButtonTargetClicked(self):
    self.logic.buttonTarget()

  def onButtonSendTargetClicked(self):
    self.logic.buttonSendTarget()

  def onButtonCurrentClicked(self):
    self.logic.buttonCurrent()

  def onButtonDisconnectClicked(self):
    self.logic.buttonDisconnect()  

#
# HelloRobotLogic
#

class HelloRobotLogic:
  def __init__(self):
    pass


  def buttonConnect(self, strHostname, intPort):
    self.connectNode = slicer.vtkMRMLIGTLConnectorNode()
    self.connectNode.SetName('testConnectNode')
    slicer.mrmlScene.AddNode(self.connectNode)

    self.connectNode.SetTypeClient(strHostname, intPort)
    self.connectNode.Start()  # connect


  def buttonRegistration(self):
    self.dataNodeZFrame = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeZFrame.SetName('ZFrameTransform')
    slicer.mrmlScene.AddNode(self.dataNodeZFrame)
    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeZFrame)

    self.connectNode.PushNode(self.dataNodeZFrame)  # send the ZFrameTransform data to controller


  def buttonTarget(self):
    self.dataNodeTarget = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeTarget.SetName('TARGET')
    slicer.mrmlScene.AddNode(self.dataNodeTarget)
   #self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeTarget)
    '''check node status'''

  def buttonSendTarget(self):
    '''check whether dataNodeTarget exist'''
    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeTarget)
    self.connectNode.PushNode(self.dataNodeTarget)

  def buttonCurrent(self):
    self.dataNodeCurrent = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeCurrent.SetName('CURRENT22222')
    slicer.mrmlScene.AddNode(self.dataNodeCurrent)
    #self.connectNode.RegisterIncomingMRMLNode(self.dataNodeCurrent)

  def buttonDisconnect(self):
    self.connectNode.Stop()
    '''unregister'''

#-------------------------------------------------------------------
  def activeEvent(self):
    print "into activeEvent"
    # ceate tmpNode and add it into connectNode
    self.tempLinearNode = slicer.vtkMRMLLinearTransformNode()
    self.tempLinearNode.SetName('temp')
    #slicer.mrmlScene.AddNode(self.tempLinearNode)
    #self.connectNode.RegisterIncomingMRMLNode(self.tempLinearNode)
   
    #self.tagTemp = self.tempLinearNode.AddObserver('ModifiedEvent', self.putInfo)
    self.tagTemp = self.connectNode.AddObserver('ModifiedEvent', self.putInfo)
    #self.tagTemp = self.connectNode.AddObserver(slicer.vtkMRMLIGTLConnectorNode.ReceiveEvent, self.putInfo)
    #self.tagTemp = self.tempLinearNode.AddObserver(vtk.vtkCommand.ModifiedEvent, self.putInfo)
    #self.tagTemp = self.tempLinearNode.AddObserver(self.connectNode.ReceiveEvent, self.putInfo)
    #self.tagTemp = self.connectNode.AddObserver(self.connectNode.ReceiveEvent, self.putInfo)
    
    #test
    self.times1 = 0

  def putInfo(self, caller, event):  # caller: vtkMRMLIGTLConnectorNode
    self.times1 = self.times1+1
    print "********************"
    print ("into caller", self.times1)

#    if caller.IsA("vtkMRMLIGTLConnectorNode"):
#      print "caller is connect"
#    elif caller.IsA("vtkMRMLLinearTransformNode"):
#      print "caller is linear"
#    else:
#      print "else"


    if caller.IsA('vtkMRMLIGTLConnectorNode'):
      print "temp"
      print event

      #print "caller is connectNode!"
      nInNode =  caller.GetNumberOfIncomingMRMLNodes()
      #print nInNode
      for i in range(nInNode):  # start from 0
        node = caller.GetIncomingMRMLNode(i)

        
        if node.GetName() == "feedZFrame":
          self.fFeedZFrame = True
        elif node.GetName() == "feedTarget":
          self.fFeedTarget = True

        

        if node.IsA("vtkMRMLLinearTransformNode"):
          if node.GetName() == "feedZFrame":
            #self.fFeedZFrame = False
            qt.QMessageBox.information(
              slicer.util.mainWindow(),
              "Slicer Python", "Registration OK!"
            )
            self.connectNode.UnregisterIncomingMRMLNode(node)
            
          elif node.GetName() == "feedTarget":
            #self.fFeedTarget = False
            #print "Target OK!!!!!"
            qt.QMessageBox.information(
              slicer.util.mainWindow(),
              "Slicer Python", "Send Target OK!"
            )
            self.connectNode.UnregisterIncomingMRMLNode(node)
          
          else:
            print "else!!!!!"
            



'''
        if node.IsA("vtkMRMLLinearTransformNode"):
          if node.GetName() == "CURRENT":
            print "current"
          elif node.GetName() == "feedZFrame":
            qt.QMessageBox.information(
              slicer.util.mainWindow(),
              'Slicer Python', 'Registration OK!'
            )
            print "Registration OK!!!!!"
          elif node.GetName() == "feedTarget":
            print "Target OK!!!!!"
          else:
            print "else"
'''
          
        #print i  # start from 0
        #print node.GetID()  # MRML ID
        #print node.GetNodeTagName()  # MRML Type
        #print node.GetClassName() 
        #print node.GetName()
        #print node.IsA('vtkMRMLLinearTransformNode')  # True
        #print "!!!!!!!!!!!!!!!!!!!"


