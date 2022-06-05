##############################################################
#                           Imports
##############################################################
import sys 

##############################################################
#                           Constants
##############################################################
primitiveInfo = UDPPrimitiveTypeInfo(
    name = "Rectangular Coil",
    purpose = "Create a Rectangular Coil in XY plane",
    company = "Kistler",
    date = "4-6-2022",
    version = "1.0")

defaultPrimitiveParams = [
    "0.0", 
    "0.0",
    "5.0",
    "2",
    "12.0",
    "6.0",
    "2.0",
    "1.0" 
]

primitiveParamDefs = [ UDPPrimitiveParameterDefinition2(
                        "Xpos", 
                        "X Position of coil center point", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double,defaultPrimitiveParams[0])), #1 parameter
	                   
                       UDPPrimitiveParameterDefinition2(
                        "Ypos", 
                        "Y Position of coil center point", 
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
                        "CoilWidth", 
                        "Width of the coil (length along X axis)", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[4])), #5 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "CoilHeight", 
                        "Height of the coil (length along Y axis)", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[5])), #6 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "WireWidth", 
                        "Width of the wire (length along Y axis)", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[6])), #7 parameter
                                 
                       UDPPrimitiveParameterDefinition2(
                        "WireHeight", 
                        "Height of the wire (length along Z axis)", 
                        UnitType.LengthUnit, 
                        ParamPropType.Value, 
                        ParamPropFlag.MustBeReal, 
                        UDPParam(ParamDataType.Double, defaultPrimitiveParams[7]))] #8 parameter


numParams = len(primitiveParamDefs)
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

#-----------------------------------------------
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
        coil_width  = udpParams[4].Data
        coil_height = udpParams[5].Data
        wire_width  = udpParams[6].Data
        wire_height = udpParams[7].Data
        
        if (dist <= 0):
            error.Add("Distance should be more than 0.")
            return False

        if (coil_width <= 0):
            error.Add("Coil width should be more than 0.")
            return False

        if (coil_height <= 0):
            error.Add("Coil height should be more than 0.")
            return False

        if (wire_width <= 0):
            error.Add("Wire width should be more than 0.")
            return False

        if (wire_height <= 0):
            error.Add("Wire height should be more than 0.")
            return False

        if (dist <= wire_width):
            error.Add("Distance between turns should be more than the width.")
            return False
        return True

#------------------------------------------------
# Private functions creating geometry of the coil
#------------------------------------------------
    def _CreatePath(self, funcLib, paramValues):
        centre_x = paramValues[0].Data
        centre_y = paramValues[1].Data

        dist = paramValues[2].Data
        num_turns = paramValues[3].Data
        coil_width = paramValues[4].Data
        coil_height = paramValues[5].Data

        num_points = 2 + 4 * num_turns
        num_segments = num_points - 1

        start_x = centre_x + 0.5 * coil_width
        start_y = centre_y
        start_z = 0

        points_x = []
        points_y = []
        points_z = []
        points = []
        for i in xrange(0, num_points):
            points_x.append(start_x)
            points_y.append(start_y)
            points_z.append(start_y)

        points_y[1] = centre_y + 0.5 * coil_height
        points_x[2] = centre_x - 0.5 * coil_width
        points_y[2] = points_y[1]
        points_x[3] = points_x[2]
        points_y[3] = centre_y - 0.5 * coil_height
        points_x[4] = points_x[1] + dist
        points_y[4] = points_y[3]

        for turn in xrange(0, num_turns):
            old_i = 4 * (turn - 1) + 1
            new_i = 4 * turn + 1

            points_x[new_i] = points_x[old_i] + dist
            points_y[new_i] = points_y[old_i] + dist
            points_x[new_i + 1] = points_x[old_i + 1] - dist
            points_y[new_i + 1] = points_y[old_i + 1] + dist
            points_x[new_i + 2] = points_x[old_i + 2] - dist
            points_y[new_i + 2] = points_y[old_i + 2] - dist
            points_x[new_i + 3] = points_x[old_i + 3] - dist
            points_y[new_i + 3] = points_y[old_i + 3] + dist

        for i in xrange(0, num_points):
            points.append(UDPPosition(points_x[i], points_y[i], points_z[i]))

        self._m_StartPt = points[0]
        self._m_EndPt = points[num_points - 1]

        segments = []
        for i in xrange(0, num_segments):
            segment = UDPPolylineSegmentDefinition(PolylineSegmentType.LineSegment, i, 0, 0.0, UDPPosition(0,0,0), CoordinateSystemPlane.XYPlane)
            segments.append(segment)

        polyline = UDPPolylineDefinition(points, segments, 0, 0)
        return funcLib.CreatePolyline(polyline)

    def _CreateProfile(self, funcLib, paramValues):
        start_x = paramValues[0].Data
        start_y = paramValues[1].Data
        
        wire_width =  paramValues[6].Data
        wire_height = paramValues[7].Data

        num_points = 5
        num_segments = num_points - 1
        
        points = []
        points.append(UDPPosition(start_x, start_y - (wire_width/2.0), -wire_height/2.0))
        points.append(UDPPosition(start_x, start_y + (wire_width/2.0), -wire_height/2.0))
        points.append(UDPPosition(start_x, start_y + (wire_width/2.0), wire_height/2.0))
        points.append(UDPPosition(start_x, start_y - (wire_width/2.0), wire_height/2.0))
        points.append(UDPPosition(start_x, start_y - (wire_width/2.0), -wire_height/2.0))

        segments = []
        for i in xrange(0, num_segments):
            segment = UDPPolylineSegmentDefinition(PolylineSegmentType.LineSegment, i, 0, 0.0, UDPPosition(0,0,0), CoordinateSystemPlane.XYPlane)
            segments.append(segment)

        polyline = UDPPolylineDefinition(points, segments, 1, 1)
        return funcLib.CreatePolyline(polyline)

    def _NameEntities(self, funcLib, paramValues):
        # Name faces
        funcLib.NameAFace(self._m_StartPt, registeredFaceNames[0])
        funcLib.NameAFace(self._m_EndPt, registeredFaceNames[1])

        wire_width =  paramValues[6].Data
        wire_height = paramValues[7].Data

        # Inner face edges
        # Inner face edge - Bottom
        posOnEdge = []
        posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y, self._m_StartPt.Z - wire_height/2.0))
        # Inner face edge - Left
        posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - wire_width/2.0, self._m_StartPt.Z))
        # Inner face edge - Top
        posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y, self._m_StartPt.Z + wire_height/2.0))
        # Inner face edge - Right
        posOnEdge.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + wire_width/2.0, self._m_StartPt.Z))
        # Outer face edges
        # Outer face edge - Bottom
        posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y, self._m_EndPt.Z - wire_height/2.0))
        # Outer face edge - Left
        posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - wire_width/2.0, self._m_EndPt.Z))
        # Outer face edge - Top
        posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y, self._m_EndPt.Z + wire_height/2.0))
        # Outer face edge - Right
        posOnEdge.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y+ wire_width/2.0, self._m_EndPt.Z))
    
        # Inner face vertexs
        # Inner face vertex - (common to Bottom & Left edge)
        posOnVertex = []
        posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - wire_width/2.0, self._m_StartPt.Z - wire_height/2.0))
        # Inner face vertex - (common to Left & Top edge)
        posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y - wire_width/2.0, self._m_StartPt.Z + wire_height/2.0))
        # Inner face vertex - (common to Top & Right edge)
        posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + wire_width/2.0, self._m_StartPt.Z + wire_height/2.0))
        # Inner face vertex - (common to Right & Bottom edge)
        posOnVertex.append(UDPPosition(self._m_StartPt.X, self._m_StartPt.Y + wire_width/2.0, self._m_StartPt.Z - wire_height/2.0))

        # Outer face vertexs
        # Outer face vertex - (common to Bottom & Left edge)
        posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - wire_width/2.0, self._m_EndPt.Z - wire_height/2.0))
        # Outer face vertex - (common to Left & Top edge)
        posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y - wire_width/2.0, self._m_EndPt.Z + wire_height/2.0))
        # Outer face vertex - (common to Top & Right edge)
        posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y + wire_width/2.0, self._m_EndPt.Z + wire_height/2.0))
        # Outer face vertex - (common to Right & Bottom edge)
        posOnVertex.append(UDPPosition(self._m_EndPt.X, self._m_EndPt.Y + wire_width/2.0, self._m_EndPt.Z - wire_height/2.0))
        
        for i in xrange(0, 8):
            funcLib.NameAEdge(posOnEdge[i], registeredEdgeNames[i])
            funcLib.NameAVertex(posOnVertex[i], registeredVertexNames[i])
