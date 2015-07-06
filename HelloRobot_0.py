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
    self.cnode = None
    self.strHostname = 'localhost'
    self.intPort = 10000
    self.tnode = None

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
    self.buttonConnect = buttonConnect

  def onButtonConnectClicked(self):
    self.connectNode = slicer.vtkMRMLIGTLConnectorNode()
    self.connectNode.SetName('testConnect')
    slicer.mrmlScene.AddNode(self.connectNode)

    self.strHostname = str(self.lineEditHostname.text)
    self.intPort = int(self.lineEditPort.text)
    self.connectNode.SetTypeClient(self.strHostname, self.intPort)
    self.connectNode.Start()  # connect

    self.logic.activeEvent()
    
  def onButtonRegistrationClicked(self):
    self.dataNodeZFrame = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeZFrame.SetName('ZFrameTransform')
    slicer.mrmlScene.AddNode(self.dataNodeZFrame)
    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeZFrame)

    self.connectNode.PushNode(self.dataNodeZFrame)

  def onButtonTargetClicked(self):
    self.dataNodeTarget = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeTarget.SetName('TARGET')
    slicer.mrmlScene.AddNode(self.dataNodeTarget)
    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeTarget)

    '''check node status'''

  def onButtonSendTargetClicked(self):
    '''check whether dataNodeTarget exist'''
    self.connectNode.PushNode(self.dataNodeTarget)

  def onButtonCurrentClicked(self):
    self.dataNodeCurrent = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeCurrent.SetName('CURRENT')
    slicer.mrmlScene.AddNode(self.dataNodeCurrent)
    self.connectNode.RegisterIncomingMRMLNode(self.dataNodeCurrent)

  def onButtonDisconnectClicked(self):
    '''unregister'''
    self.connectNode.Stop()


#
# HelloRobotLogic
#

class HelloRobotLogic:
  def __init__(self):
    pass

  def activeEvent(self):
    print "into activeEvent"
    # ceate tmpNode and add it into connectNode
    self.tmpLinearNode = slicer.vtkMRMLLinearTransformNode()
    self.tmpLinearNode.SetName('tmp')
    slicer.mrmlScene.AddNode(self.tmpLinearNode)
#    self.widget.connectNode.RegisterIncomingMRMLNode(self.tmpLinearNode)
    # creat an observer, trigger ?= extMsg in
    self.tag = self.tmpLinearNode.AddObserver('ModifiedEvent', self.putInfo)
    #self.tag = self.connectNode.AddObserver(slicer.vtkMRMLIGTLConnectorNode.ReceiveEvent, self.putInfo)
    print self.tag

  def putInfo(self, caller, event):
    print "into putInfo"
    #if (caller.IsA('vtkMRMLLinearTransformNode') and event == 'ModifiedEvent'):
    if (caller.IsA('TRANSFORM') and event == slicer.vtkMRMLIGTLConnectorNode.ReceiveEvent):
    # check msgName
      if (caller.GetName == 'feedBackMsg'):
        print "feedBackMsg!!!"
      
    #  # check rcvMsgID
    #  checkID = self.caller.GetNodeReferenceID()
    #  if (checkID == "ZFrame"):
    #    print "rcv ZFrame!"
    #  else if (checkID == "Target"):
    #    print "rcv Target!"
    #   else:
    #     pass

    else:  # endif check msgName
        print "Nooo!"




