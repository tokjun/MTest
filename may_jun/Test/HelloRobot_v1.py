from __main__ import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *

#
# HelloRobot
#

class HelloRobot(ScriptedLoadableModule):
  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    parent.title = "Hello Robot"
    parent.categories = ["Hello Python"]
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
    self.strHostname = None
    self.intPort = None

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

  def setup(self):
    ScriptedLoadableModuleWidget.setup(self) 
    # Instantiate and connect widgets ...
    self.connectNode = None
    self.strHostname = None
    self.intPort = None

    self.logic = HelloRobotLogic(None)


    # Collapsible button
    mainCollapsibleButton = ctk.ctkCollapsibleButton()
    mainCollapsibleButton.text = "Robot!"
    self.layout.addWidget(mainCollapsibleButton)

    # Layout within the sample collapsible button
##    sampleFormLayout = qt.QFormLayout(sampleCollapsibleButton)
    HostPortLayout = qt.QVBoxLayout(mainCollapsibleButton)

    ########################
    # Add tutorial code here
    labelHostname = qt.QLabel("Hostname: ")
    lineEditHostname = qt.QLineEdit()
    labelPort = qt.QLabel("Port: ")
    lineEditPort = qt.QLineEdit()

    buttonConnect = qt.QPushButton("Connect")
    buttonConnect.toolTip = "Print 'Hello world' in standard output."
    buttonRegistration = qt.QPushButton("ZFrameTransform")
    buttonTarget = qt.QPushButton("find Target")
    buttonSendTarget = qt.QPushButton("send Target")
    buttonCurrent = qt.QPushButton("Current")
    buttonDisconnect = qt.QPushButton("Disconnect")

    HostPortLayout.addWidget(labelHostname)
    HostPortLayout.addWidget(lineEditHostname)
    HostPortLayout.addWidget(labelPort)
    HostPortLayout.addWidget(lineEditPort)


    HostPortLayout.addWidget(buttonConnect)
    HostPortLayout.addWidget(buttonRegistration)
    HostPortLayout.addWidget(buttonTarget)
    HostPortLayout.addWidget(buttonCurrent)
    HostPortLayout.addWidget(buttonDisconnect)

    buttonConnect.connect('clicked(bool)', self.onButtonConnectClicked)
    buttonRegistration.connect('clicked(bool)', self.onButtonRegistrationClicked)
    buttonTarget.connect('clicked(bool)', self.onButtonTargetClicked)
    buttonSendTarget.connect('clicked(bool)', self.onButtonSendTargetClicked)
    buttonCurrent.connect('clicked(bool)', self.onButtonCurrentClicked)
    buttonDisconnect.connect('clicked(bool)', self.onButtonDisconnectClicked)
    ########################
    
    # Add vertical spacer
    self.layout.addStretch(1)

    # Set local var as instance attribute
    self.buttonConnect = buttonConnect


  def onButtonConnectClicked(self):
    self.logic.setupConnection()
    print "establish connection"


  def onButtonRegistrationClicked(self):
    self.logic.ZFrameRegistrationTransform()

    ########################
    # Add tutorial code here
    '''qt.QMessageBox.information(
      slicer.util.mainWindow(),
      'Slicer Python', 'Hello World!')'''
    ########################

  def onButtonTargetClicked(self):
    self.logic.TargetTransform()


  def onButtonSendTargetClicked(self):
    self.logic.SendTargetTransform()


  def onButtonCurrentClicked(self):
    self.logic.CurrentTransform():


  def onButtonDisconnectClicked(self):
    '''unregister'''
    self.connectNode.Stop()



class HelloRobotLogic:
  def __init__(self, parent):
    pass

  def setupConnection(self):
    self.connectNode = slicer.vtkMRMLIGTLConnectorNode()
    self.connectNode.SetName('testConnect')
    slicer.mrmlScene.AddNode(self.connectNode)
    self.connectNode.SetTypeClient('localhost', 10000)
    self.connectNode.Start()  # connect


  def ZFrameRegistrationTransform(self):
    self.dataNodeZFrame = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeZFrame.SetName('ZFrameTransform')
    slicer.mrmlScene.AddNode(self.dataNodeZFrame)

    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeZFrame)
    self.connectNode.PushNode(self.dataNodeZFrame)

    print self.connectNode.PushNode(self.dataNodeZFrame)

    '''query the status of server, if registration -> stop node and delete the node'''


  def TargetTransform(self):
    ## change -> up func
    self.dataNodeZFrame.Stop()
    self.connectNode.UnregisterOutgoingMRMLNode(self.dataNodeZFrame)
    ##

    self.dataNodeTarget = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeTarget.SetName('TARGET')
    slicer.mrmlScene.AddNode(self.dataNodeTarget)

    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeTarget)

    '''check node status'''


  def SendTargetTransform(self):
    '''check whether dataNodeTarget exist'''
    self.connectNode.PushNode(self.dataNodeTarget)


  def CurrentTransform(self):
    self.dataNodeCurrent = slicer.vtkMRMLLinearTransformNode
    self.dataNodeCurrent.SetName('CURRENT')
    slicer.mrmlScene.AddNode(self.dataNodeCurrent)
    self.connectNode.RegisterIncomingMRMLNode(self.dataNodeCurrent)


    '''queryNode = slicer.vtkMRMLIGTQueryNode()
       '''
    # self.connectNode.PushQuery
    '''check node status'''
