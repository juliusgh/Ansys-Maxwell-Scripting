##############################################################
#                           Imports
##############################################################
import sys 

##############################################################
#                           Constants
##############################################################
primitiveInfo = UDPPrimitiveTypeInfo(
	name = "Rectangular Spiral",
	purpose = "Create a Rectangular Spiral in XY plane",
	company = "Ansys",
	date = "12-5-2012",
    version = "2.0")

defaultPrimitiveParams = [
	 "0.0", 
     "0.0",
     "5.0",
     "2",
     "2.0",
     "1.0" 
]
primitiveParamDefs = [ UDPPrimitiveParameterDefinition2(
                        "Xpos", 
                        "X Position of start point", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double,defaultPrimitiveParams[0])), #1 parameter
	                   
                       UDPPrimitiveParameterDefinition2(
                        "Ypos", 
                        "Y Position of start point", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[1])), #2 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "Dist", 
                        "Distance between turns", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double,defaultPrimitiveParams[2])), #3 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "Turns", 
                        "Number of turns", 
                        UnitType.NoUnit, 
                        ParamPropType.Number, 
                        ParamPropFlag.MustBeInt, 
                        UDPParam(ParamDataType.Int, defaultPrimitiveParams[3])), #4 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "Width", 
                        "Width of the spiral", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[4])), #5 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "Thickness", 
                        "Thickness/height of the spiral", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[5]))] #6 parameter


numParams = 6
lengthUnits = "mm"

registeredFaceNames = [ "InnerEndFace", "OuterEndFace"]
registeredEdgeNames = [ "Inner-B", "Inner-L", "Inner-T", "Inner-R",
                        "Outer-B", "Outer-L", "Outer-T", "Outer-R"]
registeredVertexNames =  ["Inner-B-L", "Inner-L-T", "Inner-T-R", "Inner-R-B",
                          "Outer-B-L", "Outer-L-T", "Outer-T-R", "Outer-R-B"]


##############################################################
#                       Class Implementation
##############################################################
class UDPExtension(IUDPExtension):

  def __init__(self):
    m_StartPt = UDPPosition(0,0,0)
    m_EndPt = UDPPosition(0,0,0)

#----------------------------------------------
# Interface implementations
#-----------------------------------------------

  def CreatePrimitive2(self, funcLib, paramValues):
    path = self._CreatePath(funcLib, paramValues) 
    if (path < 0):
        funcLib.AddMessage(MessageSeverity.ErrorMessage, "Could not create path")
    profile = self._CreateProfile(funcLib, paramValues)
    if (profile < 0):
        funcLib.AddMessage(MessageSeverity.ErrorMessage, "Could not create profile")

    theUDPSweepOptions = UDPSweepOptions(SweepDraftType.RoundDraft, 0.0, 0.0)
    bRet = funcLib.SweepAlongPath(profile, path, theUDPSweepOptions)
    if (bRet == False):
        funcLib.AddMessage(MessageSeverity.ErrorMessage, "Could not sweep profile along path")   
    self._NameEntities(funcLib, paramValues)
    return bRet


  def GetPrimitiveTypeInfo(self):
    return primitiveInfo

  def GetLengthParameterUnits(self):
    return lengthUnits

  def GetPrimitiveParametersDefinition2(self):
    return primitiveParamDefs
    
  def GetRegisteredFaceNames(self):
    return registeredFaceNames

  def GetRegisteredEdgeNames(self):
    return registeredEdgeNames

  def GetRegisteredVertexNames(self):
    return registeredVertexNames
  
  def AreParameterValuesValid2(self, error, udpParams):
    numTurns = udpParams[3].Data
    if (numTurns < 1):
      error.Add("Number of turns cannot be less than 1.")
      return False
    dist   = udpParams[2].Data
    width  = udpParams[4].Data
    height = udpParams[5].Data
    
    if (dist <= 0):
        error.Add("Distance should be more than 0.")
        return False

    if (width <= 0):
        error.Add("Width should be more than 0.")
        return False

    if (height <= 0):
        error.Add("Height should be more than 0.")
        return False

    if (dist <= width):
        error.Add("Distance between turns should be more than the width.")
        return False
    return True
#----------------------------------------------
# Private functions creating geometry of spiral
#-----------------------------------------------
  def _CreatePath(self, funcLib, paramValues):
    xStart = paramValues[0].Data
    yStart = paramValues[1].Data
    zStart = 0.0

    dist =     paramValues[2].Data
    numTurns = paramValues[3].Data

    numPoints = 2 + 4*numTurns
    numSegments = numPoints - 1

    thePointArrayX = []
    thePointArrayY = []
    thePointArray = []
    for indexPt in xrange(0, numPoints):
        thePointArrayX.append(xStart)
        thePointArrayY.append(yStart)

    thePointArrayY[1] = yStart
    thePointArrayX[numPoints-1] = xStart

    for indexPt in xrange(0, numTurns):
        xIndex = indexPt*4 + 1
        yIndex = xIndex + 1
        coord = dist*(indexPt + 1)

        thePointArrayX[xIndex] = xStart - coord
        thePointArrayX[xIndex + 1] = xStart - coord
        thePointArrayX[xIndex + 2] = xStart + coord
        thePointArrayX[xIndex + 3] = xStart + coord

        thePointArrayY[yIndex] = yStart + coord
        thePointArrayY[yIndex + 1] = yStart + coord
        thePointArrayY[yIndex + 2] = yStart - coord
        thePointArrayY[yIndex + 3] = yStart - coord

    for indexPt in xrange(0, numPoints):
        thePointArray.append(UDPPosition(thePointArrayX[indexPt], thePointArrayY[indexPt], zStart))

    self._m_StartPt = thePointArray[0]
    self._m_EndPt = thePointArray[numPoints - 1]

    theSegArray = []
    for indexSeg in xrange(0, numSegments):
        theSegDefinition = UDPPolylineSegmentDefinition(PolylineSegmentType.LineSegment,
                                                        indexSeg,
                                                        0, 0.0, UDPPosition(0,0,0), CoordinateSystemPlane.XYPlane)
        theSegArray.append(theSegDefinition)

    thePolylineDefinition = UDPPolylineDefinition(thePointArray, theSegArray, 0, 0)
    return funcLib.CreatePolyline(thePolylineDefinition)

  def _CreateProfile(self, funcLib, paramValues):
    xStart = paramValues[0].Data
    yStart = paramValues[1].Data
    
    width =  paramValues[4].Data
    height = paramValues[5].Data

    numPoints = 5
    numSegments = numPoints - 1
    
    thePointArray = []
    thePointArray.append(UDPPosition(xStart, yStart - (width/2.0), -height/2.0))
    thePointArray.append(UDPPosition(xStart, yStart + (width/2.0), -height/2.0))
    thePointArray.append(UDPPosition(xStart, yStart + (width/2.0), height/2.0))
    thePointArray.append(UDPPosition(xStart, yStart - (width/2.0), height/2.0))
    thePointArray.append(UDPPosition(xStart, yStart - (width/2.0), -height/2.0))

    theSegArray = []
    for indexSeg in xrange(0, numSegments):
        theSegDefinition = UDPPolylineSegmentDefinition(PolylineSegmentType.LineSegment,
                                                        indexSeg,
                                                        0, 0.0, UDPPosition(0,0,0), CoordinateSystemPlane.XYPlane)
        theSegArray.append(theSegDefinition)

    thePolylineDefinition = UDPPolylineDefinition(thePointArray, theSegArray, 1, 1)
    return funcLib.CreatePolyline(thePolylineDefinition)

  def _NameEntities(self, funcLib, paramValues):
    # Name faces
    funcLib.NameAFace(self._m_StartPt, registeredFaceNames[0])
    funcLib.NameAFace(self._m_EndPt, registeredFaceNames[1])

    width =  paramValues[4].Data
    height = paramValues[5].Data

    # Inner face edges
    # Inner face edge - Bottom
    posOnEdge = []
    posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y, self._m_StartPt.Z - height/2.0))
    # Inner face edge - Left
    posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - width/2.0, self._m_StartPt.Z))
    # Inner face edge - Top
    posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y, self._m_StartPt.Z + height/2.0))
    # Inner face edge - Right
    posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + width/2.0, self._m_StartPt.Z))
    # Outer face edges
    # Outer face edge - Bottom
    posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y, self._m_EndPt.Z - height/2.0))
    # Outer face edge - Left
    posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - width/2.0, self._m_EndPt.Z))
    # Outer face edge - Top
    posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y, self._m_EndPt.Z + height/2.0))
    # Outer face edge - Right
    posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y+ width/2.0, self._m_EndPt.Z))
   
    # Inner face vertexs
    # Inner face vertex - (common to Bottom & Left edge)
    posOnVertex = []
    posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - width/2.0, self._m_StartPt.Z - height/2.0))
    # Inner face vertex - (common to Left & Top edge)
    posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - width/2.0, self._m_StartPt.Z + height/2.0))
    # Inner face vertex - (common to Top & Right edge)
    posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + width/2.0, self._m_StartPt.Z + height/2.0))
    # Inner face vertex - (common to Right & Bottom edge)
    posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + width/2.0, self._m_StartPt.Z - height/2.0))

    # Outer face vertexs
    # Outer face vertex - (common to Bottom & Left edge)
    posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - width/2.0, self._m_EndPt.Z - height/2.0))
    # Outer face vertex - (common to Left & Top edge)
    posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - width/2.0, self._m_EndPt.Z + height/2.0))
    # Outer face vertex - (common to Top & Right edge)
    posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y + width/2.0, self._m_EndPt.Z + height/2.0))
    # Outer face vertex - (common to Right & Bottom edge)
    posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y + width/2.0, self._m_EndPt.Z - height/2.0))
    
    for i in xrange(0, 8):
        funcLib.NameAEdge(posOnEdge[i], registeredEdgeNames[i])
        funcLib.NameAVertex(posOnVertex[i], registeredVertexNames[i])
