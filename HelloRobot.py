import os
import unittest
import csv
import numpy
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
    self.tnode = None
    self.strHostname = None
    self.times0 = 0

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

    # Collapsible button - Settings
    setCollapsibleButton = ctk.ctkCollapsibleButton()
    setCollapsibleButton.text = "Settings"
    self.layout.addWidget(setCollapsibleButton)

    gridLayout = qt.QGridLayout(setCollapsibleButton)
    gridLayout.setSpacing(10)

    labelHostname = qt.QLabel("Hostname: ")
    self.lineEditHostname = qt.QLineEdit()
    labelPort = qt.QLabel("Port: ")
    self.lineEditPort = qt.QLineEdit()
    labelStatus = qt.QLabel("Status: ")
    self.lineEditStatus = qt.QLineEdit()
    self.lineEditStatus.setText("pending...")

    gridLayout.addWidget(labelHostname, 1, 0)
    gridLayout.addWidget(self.lineEditHostname, 1, 1)
    gridLayout.addWidget(labelPort, 2, 0)
    gridLayout.addWidget(self.lineEditPort, 2, 1)
    gridLayout.addWidget(labelStatus, 3, 0)
    gridLayout.addWidget(self.lineEditStatus, 3, 1)

    # Collapsible button - Controller
    controlCollapsibleButton = ctk.ctkCollapsibleButton()
    controlCollapsibleButton.text = "SNRMRRobot Controller"
    self.layout.addWidget(controlCollapsibleButton)

    # Layout within the sample collapsible button
    mainLayout = qt.QVBoxLayout(controlCollapsibleButton)

    controllerFormFrame = qt.QFrame()
    controllerFormLayout = qt.QFormLayout(controllerFormFrame)
    mainLayout.addWidget(controllerFormFrame)
   
    buttonConnect = qt.QPushButton("Connect")
    buttonConnect.toolTip = "Print 'Hello world' in standard output."
    buttonRegistration = qt.QPushButton("ZFrameTransform Registration")
    buttonTarget = qt.QPushButton("find Target")
    buttonSendTarget = qt.QPushButton("send Target")
    buttonCurrent = qt.QPushButton("Current")
    buttonDisconnect = qt.QPushButton("Disconnect")

    controllerFormLayout.addWidget(buttonConnect)
    controllerFormLayout.addWidget(buttonRegistration)
    controllerFormLayout.addWidget(buttonTarget)
    controllerFormLayout.addWidget(buttonSendTarget)
    controllerFormLayout.addWidget(buttonCurrent)
    controllerFormLayout.addWidget(buttonDisconnect)

    #
    # input markup fiducial node
    #
    self.targetFiducialsSelector = slicer.qMRMLNodeComboBox()
    self.targetFiducialsSelector.nodeTypes = (("vtkMRMLMarkupsFiducialNode"), "")
    self.targetFiducialsSelector.addEnabled = True
    self.targetFiducialsSelector.removeEnabled = True
    self.targetFiducialsSelector.selectNodeUponCreation = True
    self.targetFiducialsSelector.noneEnabled = False
    self.targetFiducialsSelector.showHidden = False
    self.targetFiducialsSelector.showChildNodeTypes = False
    self.targetFiducialsSelector.setMRMLScene(slicer.mrmlScene)
    controllerFormLayout.addRow("Target: ", self.targetFiducialsSelector)

    self.targetFiducialsNode = None
    self.targetFiducialsSelector.connect("currentNodeChanged(vtkMRMLNode*)", self.onFiducialsSelected)


    #
    # target list table
    #
    self.table = qt.QTableWidget(1, 4)
    self.table.setSelectionBehavior(qt.QAbstractItemView.SelectRows)
    self.table.setSelectionMode(qt.QAbstractItemView.SingleSelection)
    
    self.headers = ["Name", "Hole", "Depth(mm)", "Position(RAS)"]
    self.table.setHorizontalHeaderLabels(self.headers)
    self.table.horizontalHeader().setStretchLastSection(True)
    
    mainLayout.addWidget(self.table)

    self.onFiducialsSelected()

    
    # connect of the buttons
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

  def onFiducialsSelected(self):
    # Remove observer if previous node exists
    if self.targetFiducialsNode and self.tag:
      self.targetFiducialsNode.RemoveObserver(self.tag)
    
    # Update selected node, add observer, and update control points
    if self.targetFiducialsSelector.currentNode():
      self.targetFiducialsNode = self.targetFiducialsSelector.currentNode()
      self.tag = self.targetFiducialsNode.AddObserver("ModifiedEvent", self.onFiducialsUpdated)
    
    self.updateTable()


  def onFiducialsUpdated(self, caller, event):
    if caller.IsA("vtkMRMLMarkupsFiducialNode") and event == "ModifiedEvent":
      self.updateTable()
      

  def updateTable(self):
    self.times0 = self.times0 + 1
    print "updateTable: ", self.times0
    
    if not self.targetFiducialsNode:
      self.table.clear()
      self.table.setHorizontalHeaderLabels(self.headers)
    
    else:
      self.tableData = []
      nOfControlPoints = self.targetFiducialsNode.GetNumberOfFiducials()

      if self.table.rowCount != nOfControlPoints:
        self.table.setRowCount(nOfControlPoints)

      for i in range(nOfControlPoints):
        label = self.targetFiducialsNode.GetNthFiducialLabel(i)
        print label
      
        pos = [0.0, 0.0, 0.0]
        self.targetFiducialsNode.GetNthFiducialPosition(i, pos)
        (indexX, indexY, depth, inRange) = self.logic.computeNearestPath(pos)

        posStr = "(%.3f, %.3f, %.3f)" %(pos[0], pos[1], pos[2])
        cellLabel = qt.QTableWidgetItem(label)
        cellIndex = qt.QTableWidgetItem("(%s, %s)" %(indexX, indexY))
      
        cellDepth = None
        if inRange:
          cellDepth = qt.QTableWidgetItem("(%.3f)" %depth)
        else:
          cellDepth = qt.QTableWidgetItem("(%.3f)" %depth)
          cellPosition = qt.QTableWidgetItem(posStr)
      
        row = [cellLabel, cellIndex, cellDepth, cellPosition]

        self.table.setItem(i, 0, row[0])
        self.table.setItem(i, 1, row[1])
        self.table.setItem(i, 2, row[2])
        self.table.setItem(i, 3, row[3])
        
        self.tableData.append(row)

    # end the range
    
    # show the table
    self.table.show()
    
#
# HelloRobotLogic
#

class HelloRobotLogic:
  def __init__(self):
    self.pathVectors = []
    self.pathOrigins = []


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
    '''check node status'''

  def buttonSendTarget(self):
    '''check whether dataNodeTarget exist'''
#-------------------- july9, ez
    # no choice, send the 1st one fnode
    self.currentTargetFiducialsNode = self.targetFiducialsSelector.currentNode().GetNthMarkupLabel(0)  # return 'fnode-1' 
    print self.currentTargetFiducialsNode

    self.connectNode.RegisterOutgoingMRMLNode(self.currentTargetFiducialsNode)
    self.connectNode.PushNode(self.currentTargetFiducialsNode)

    self.connectNode.RegisterOutgoingMRMLNode(self.dataNodeTarget)
    self.connectNode.PushNode(self.dataNodeTarget)  # send the Target data to controller

#-------------------- end july9, ez
  def buttonCurrent(self):
    self.dataNodeCurrent = slicer.vtkMRMLLinearTransformNode()
    self.dataNodeCurrent.SetName('CURRENT22222')
    slicer.mrmlScene.AddNode(self.dataNodeCurrent)

  def buttonDisconnect(self):
    self.connectNode.Stop()
    '''unregister'''

#-------------------------------------------------------------------
  def activeEvent(self):
    print "into activeEvent"
    self.tempLinearNode = slicer.vtkMRMLLinearTransformNode()
    self.tempLinearNode.SetName('temp')
   
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

    if caller.IsA('vtkMRMLIGTLConnectorNode'):
      print "temp"
      print event

      #print "caller is connectNode!"
      nInNode =  caller.GetNumberOfIncomingMRMLNodes()
      #print nInNode
      for i in range(nInNode):  # start from 0
        node = caller.GetIncomingMRMLNode(i) 

        if node.IsA("vtkMRMLLinearTransformNode"):
          if node.GetName() == "feedStatus":
            pass
          if node.GetName() == "feedZFrame":
            qt.QMessageBox.information(
              slicer.util.mainWindow(),
              "Slicer Python", "Registration Accepted!")
            self.connectNode.UnregisterIncomingMRMLNode(node)
            
          elif node.GetName() == "feedTarget":
            qt.QMessageBox.information(
              slicer.util.mainWindow(),
              "Slicer Python", "Target Accepted!")
            self.connectNode.UnregisterIncomingMRMLNode(node)
          else:
            print "no feed!!!!!"
            
          
        #print i  # start from 0
        #print node.GetID()  # MRML ID
        #print node.GetNodeTagName()  # MRML Type
        #print node.GetClassName() 
        #print node.GetName()
        #print node.IsA('vtkMRMLLinearTransformNode')  # True
        #print "!!!!!!!!!!!!!!!!!!!"

  def computeNearestPath(self, pos):
    p = numpy.array(pos)

    minMag2 = numpy.Inf
    minDepth = 0.0
    minIndex = -1

    i = 0
    for orig in self.pathOrigins:
      vec = self.pathVectors[i]
      op = p - orig
      aproj = numpy.inner(op, vec)
      perp = op-aproj*vec
      mag2 = numpy.vdot(perp, perp)  # magnitude^2
      if mag2 < minMag2:
        minMag2 = mag2
        minIndex = i
        minDepth = aproj
      i = i + 1

    indexX = "--"
    indexY = "--"
    inRange = False
    
    if minIndex >= 0:
        indexX = self.templateIndex[minIndex][0]
        indexY = self.templateIndex[minIndex][1]
        if minDepth > 0 and minDepth < self.templateMaxDepth[minIndex]:
          inRange = True

    return (indexX, indexY, minDepth, inRange)

