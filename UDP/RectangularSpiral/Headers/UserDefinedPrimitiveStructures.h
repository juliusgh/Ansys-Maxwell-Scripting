#ifndef _USERDEFINEDPRIMITIVESTRUCTURES_H_
#define _USERDEFINEDPRIMITIVESTRUCTURES_H_

enum UDPUnitType {kUDPNoUnit, kUDPLengthUnit, kUDPAngleUnit};	/* Angle units are always in degrees */

struct UDPPrimitiveTypeInfo
{
    char*  name;        /* Name of the functionality provided by this user defined part) */
    char*  purpose;     /* Explains little more on the functionality */
    char*  company;     /* Company/Author */
    char*  date;        /* Created/distributed on date */
    char*  version;     /* Version no */
};

struct UDPPrimitiveParameterDefinition
{
    char*  name;            /* Name of the parameter */
    char*  description;     /* some description of the parameter */
    UDPUnitType unitType;   /* No unit/length/angle */
    double defaultValue; 
};

enum UDPParamDataType
{
  kUDPParamDataType_Int,
  kUDPParamDataType_Double,
  kUDPParamDataType_String,
  kUDPParamDataType_Bool,
  kUDPParamDataType_Position, /* UDPParamData.v should point to a UDPPosition object */

  kUDPParamDataType_Unknown = 0XFFFFFFFF
};

union UDPParamData
{
  int     i;
  double  d;
  char*   s;
  bool    b;
  void*   v; /* for future use */
};

struct UDPParam
{
  UDPParamDataType dataType;
  UDPParamData data;
};

enum UDPParamPropType
{
  /* property is text, user can type in any text */
  /* data type must be kUDPParamDataType_String */
  kUDPParamPropType_Text, 

  /* property is menu option, where user can select one of available menus */
  /* data type must be kUDPParamDataType_String. */
  /* Menu options will be comma seperated string with */
  /* additional default option at the start. */
  /* E.g., string "YZ,XY,YZ,ZX" says, YZ is default */
  /* with order of options being XY,YZ,ZX */
  kUDPParamPropType_Menu, 

  /* property is number, variables/expressions will NOT be accepted */
  /* data type must be kUDPParamDataType_Int */
  /* or kUDPParamDataType_Double */
  kUDPParamPropType_Number,   

  /* property can accept any number, variables and expressions */
  /* data type must be kUDPParamDataType_Double */
  /* or kUDPParamDataType_Int */
  kUDPParamPropType_Value,    

  /* property allows user to select file name */
  /* default vaule can be file path or simple file filter e.g. *.txt */
  /* data type must be kUDPParamDataType_String */
  kUDPParamPropType_FileName,

  /* property corresponds to a checkbox */
  /* data type must be kUDPParamDataType_Bool */
  kUDPParamPropType_Checkbox,

  /* property allows user to specify 3d position */
  /* data type must be kUDPParamDataType_Position */
  kUDPParamPropType_Position,

  kUDPParamPropType_Unknown = 0XFFFFFFFF
};

enum UDPParamPropFlag
{
  kUDPParamPropFlag_NoFlag = 0,

  /* prop will be always read only */
  kUDPParamPropFlag_ReadOnly = 1,

  /* ensures that property tab always show int */
  /* goes only with kUDPParamPropType_Number */
  kUDPParamPropFlag_MustBeInt = 2, 

  /* goes with kUDPParamPropType_Value or _Number */
  kUDPParamPropFlag_MustBeReal = 4, 

  /* prop will be hidden */
  kUDPParamPropFlag_Hidden = 8,

  kUDPParamPropFlag_Unknown = 0XFFFFFFFF
};

struct UDPPrimitiveParameterDefinition2
{
  /* Name of the parameter */
  char*  name;            

  /* some description of the parameter */
  char*  description;     

  UDPUnitType unitType; /* kUDPLengthUnit, kUDPAngleUnit not allowed for _String and _Int */  
  UDPParamPropType propType;
  UDPParamPropFlag propFlag;

  /* Data type of default decides data type used for communication */ 
  /* E.g, if kUDPParamDataType_Int type is used for values */
  /* data type of passing params to CreatePrimitive2 will be _Int */
  UDPParam defaultValue;  
};

enum UDPCoordinateSystemAxis {kUDPXAxis=0, kUDPYAxis, kUDPZAxis};

enum UDPCoordinateSystemPlane {kUDPXYPlane=0, kUDPYZPlane, kUDPZXPlane};

enum UDPSweepDraftType {kUDPExtendedDraft=0, kUDPRoundDraft, kUDPNaturalDraft, kUDPMixedDraft};

enum UDPSplitWhichSideToKeep{kUDPSplitKeepBoth=0, kUDPSplitKeepPositiveOnly, kUDPSplitKeepNegativeOnly};

enum UDPPolylineSegmentType
{
    kUDPLineSegment,        /* No extra information required, 2 points */
    kUDPArcSegment,         /* No extra information required, 3 point arc */
    kUDPSplineSegment,      /*  number of points information required */
    kUDPAngularArcSegment   /* Center position, angle and arc plane information required */
};

enum UDPMessageSeverity
{
  /* Has warning (IDI_EXCLAMATION) icon. */
  kUDPWarningMessage,    
  /* Has error (IDI_HAND) icon. */
  kUDPErrorMessage,      
  /* Has info (IDI_ASTERISK) icon. */
  kUDPInfoMessage,       
  /* Has incomplete (IDI_QUESTION) icon. */
  kUDPIncompleteMessage, 
  /* Message shows up in an AfxMessageBox. */
  kUDPFatalMessage       
};

/* For fillet/chamfer currently only these enums are supported
   kUDPBLNDConstantRadius
   kUDPBLNDRound
   kUDPBLNDConstantRange

   Rest are reserved for future enhancement.
*/

enum UDPBLNDFilletRadiusLaw {kUDPBLNDConstantRadius=0, kUDPBLNDVariableRadius};
enum UDPBLNDFilletType {kUDPBLNDRound=0, kUDPBLNDMitered};
enum UDPBLNDChamferRangeLaw {kUDPBLNDConstantRange=0, kUDPBLNDVariableRange};


struct UDPPosition
{
    double x;
    double y;
    double z;
};

struct UDPVector
{
    double x;
    double y;
    double z;
};

struct UDP3x3Matrix
{
    double mat[3][3];
};

struct UDPSweepOptions
{
    UDPSweepDraftType draftType;
    double draftAngle;
    double twistAngle;
};

struct UDPPolylineSegmentDefinition
{
    UDPPolylineSegmentType segmentType;
    int segmentStartIndex;

    /* Below information is required to be set only if you are using Spline */
    int numberOfPoints; 

    /* Below information is required to be set only if you are using Angular Arc */
    double angle; 					/* in degrees */
    UDPPosition centerPoint;
    UDPCoordinateSystemPlane arcPlane;
};

struct UDPPolylineDefinition
{
    int noOfPoints;
    struct UDPPosition* arrayOfPosition;
    int noOfSegments;
    struct UDPPolylineSegmentDefinition* arrayOfSegmentDefinition;
    int isClosed;
    int isCovered;			/* Only if it is closed, then it can be covered */
};

struct UDPEquationBasedCurveDefinition
{
    const char* functionXt;
    const char* functionYt;
    const char* functionZt;

    double tStart;
    double tEnd;

    int numOfPointsOnCurve;     /* For true curve this is 0 */
                                /* For segmented curve more than 0 */
};

struct UDPEquationBasedSurfaceDefinition
{
    const char* functionXuv;
    const char* functionYuv;
    const char* functionZuv;

    double uStart;
    double uEnd;

    double vStart;
    double vEnd;

    int reserved1;     /* Reserved for future */
    int reserved2;     /* Reserved for future */
};

struct UDPHelixDefinition
{
    int profileID;             /* profile ID to be swept */

    struct UDPPosition ptOnAxis;        /* a point on axis */
    struct UDPPosition axisDir;         /* direction of axis */

    double noOfTurns;           /* number of turns */
    bool isRightHanded;         /* right/left handed? */

    double radiusChangePerTurn; /* radius change per turn */
    double pitch;               /* distance along axis per turn */
};

struct UDPSpiralDefinition
{
    int profileID;             /* profile ID to be swept */

    struct UDPPosition ptOnAxis;        /* a point on axis */
    struct UDPPosition axisDir;         /* direction of axis */

    double noOfTurns;           /* number of turns */
    bool isRightHanded;         /* right/left handed? */

    double radiusChangePerTurn; /* radius change per turn */
};

/* Note that UDPBLNDElements can hold either edges or vertices, 
 * but not both at the same time.
 * Further, edges should be applied to solids, and vertices should be applied to sheets.
*/
struct UDPBLNDElements
{
    int partID;                /* part to be blended i.e. filleted/chamfered */

    int noOfEdges;
    int* listOfEdges;          /* edges to be blended */

    int noOfVertices;
    int* listOfVertices;          /* vertices to be blended */
};

struct UDPBLNDFilletOptions
{
    bool supressFillet;             /* Reserved for future */
    UDPBLNDFilletRadiusLaw filletRadiusLaw; /* Currently only kUDPBLNDConstantRadius supported */
    double filletStartRadius;       /* This is fillet radius */
    double filletEndRadius;         /* Reserved for future */
    bool followSmoothEdgeSequence;  /* Reserved for future */
    // Vertex properties
    UDPBLNDFilletType filletType;   /* Currently only kUDPBLNDRound supported */    
    double setbackDistance;
    double bulgeFactor;             /* Reserved for future */
};

struct UDPBLNDChamferOptions
{
    bool supressChamfer;            /* Reserved for future */
    UDPBLNDChamferRangeLaw chamferRangeLaw; /* Currently only kUDPBLNDConstantRange supported */
    double chamferLeftRange;        /* This is chamfer value */
    double chamferRightRange;       /* Reserved for future */
};


/* RESERVED LIBRARY FUNCTIONS FOR FUTURE */
/* BEGIN - DO NOT INVOKE THESE RESERVED FUNCTIONS IN YOUR UDP DLL CREATION CODE */
typedef int (*UDPReservedForFutureFP)
(void*					/* callbackData */
);
/* END - DO NOT INVOKE THESE RESERVED FUNCTIONS IN YOUR UDP DLL CREATION CODE */



/* LIBRARY FUNCTION POINTER TYPEDEFS */
/* Utility Functions */
/* Add a message to the message window, with desired severity level */
typedef void (*UDPAddMessageFP)
(UDPMessageSeverity,	/* Message severity */
const char*,			/* message string */
void*					/* callbackData */
);

/* Name a face.
 *
 * Named faces retain their id, i.e. the boundary etc on a named face will be
 * retained, even though topology changes. All face names must be registered
 * thru the optional dll function RegisterFaceNames. 
 *
 * The face is identified by a point that lies on it. Point must lie inside
 * the face, point on boundary of face (edge/vertex) is not valid. If a point
 * lies on more than one face, then the first call to UDPNameAFaceFP wins,
 * i.e. once a face is named, it is not named again. If the UDP dll creates
 * more then one body then the face will be seeked on the resultant union.
 *
 * Face id for named faces can be queried thru the script command 
 * GetFaceIDFromNameForFirstOperation("PartName", "FaceName")
 */
typedef int (*UDPNameAFaceFP)
(const struct UDPPosition*,		/* coordinates of a point lying on face */
const char*,		         	/* name of the face */
void*						    /* callbackData */
);


/* Name a edge.
 *
 * Named edges retain their id, i.e. the integration line etc on a named
 * edge/edge positions will be retained, even though topology changes. All
 * edges names must be registered thru the optional dll function RegisterEdgeNames. 
 *
 * The edge is identified by a point that lies on it. Point must lie inside
 * the edge, point on vertex of edge is not valid. If a point
 * lies on more than one edge, then the first call to UDPNameAEdgeFP wins,
 * i.e. once a edge is named, it is not named again. If the UDP dll creates
 * more then one body then the edge will be seeked on the resultant union.
 *
 * Edge id for named edges can be queried thru the script command 
 * GetEdgeIDFromNameForFirstOperation("PartName", "EdgeName")
 */
typedef int (*UDPNameAEdgeFP)
(const struct UDPPosition*,		/* coordinates of a point lying on edge */
const char*,		         	/* name of the edge */
void*						    /* callbackData */
);

/* Name a vertex.
 *
 * Named vertices retain their id, i.e. the integration line etc on a named vertex
 * will be retained, even though topology changes. All vertex names must be registered
 * thru the optional dll function RegisterVertexNames. 
 *
 * The vertex is identified by the point. Point must lie exactly on
 * the vertex. If a vertex is named more then once, then the first call to
 * UDPNameAVertexFP wins, i.e. once a vertex is named, it is not named again.
 *
 * Vertex position for named vertices can be queried thru the script command
 * GetVertexIDFromNameForFirstOperation("PartName", "VertexName").
 *
 */
typedef int (*UDPNameAVertexFP)
(const struct UDPPosition*,		/* coordinates of a point lying on vertex*/
const char*,		         	/* name of the vertex */
void*						    /* callbackData */
);


/* Get Face ID From Position
 *
 * The face is identified by a point that lies on it. Point must lie inside
 * the face, point on boundary of face (edge/vertex) is not valid. If a point
 * lies on more than one face, then the first face found will be returned.
 *
 */
typedef int (*UDPGetFaceIDFromPositionFP)
(const struct UDPPosition*,		/* coordinates of a point lying on Face*/
void*						    /* callbackData */
);


/* Get Edge ID From Position
 *
 * The edge is identified by a point that lies on it. Point must lie inside
 * the edge, point on boundary of edge (i.e. on vertex) is not valid. If a point
 * lies on more than one edge, then the first edge found will be returned.
 *
 */
typedef int (*UDPGetEdgeIDFromPositionFP)
(const struct UDPPosition*,		/* coordinates of a point lying on Edge*/
void*						    /* callbackData */
);


/* PRIMITIVES */
/* The return type for all primitives (except for spiral and helix) is the ID of
 * the body created -1 is an invalid ID, which means the operation failed.
 *
 * Spiral and helix are like sweep operations and operate on a profile. 
 * The return value indicates if the operation succeeded,
 * return value 0 means operation failed, any other value
 * means operation succeeded.
 */
/* 1D/2D ENTITIES */
typedef int (*UDPCreatePolylineFP)
(const struct UDPPolylineDefinition* ,	/* polylineDefinition */
void*						/* callbackData */
);

typedef int (*UDPCreateRectangleFP)
(UDPCoordinateSystemPlane,		/* plane */
const struct UDPPosition*,		/* start point coordinates */
double[2],					/* width, height */
int,						/* is covered? */
void*						/* callbackData */
);

typedef int (*UDPCreateArcFP)
(UDPCoordinateSystemPlane,  /* csPlane */
const struct UDPPosition*,  /* center */
const struct UDPPosition*,  /* start point */
double,                     /* angle */
void*                       /* callbackData */
);

typedef int (*UDPCreateCircleFP)
(UDPCoordinateSystemPlane,  /* csPlane */
const struct UDPPosition*,  /* center */
double,                     /* radius */
int,                        /* isCovered */
void*                       /* callbackData */
);

typedef int (*UDPCreateEllipseFP)
(UDPCoordinateSystemPlane,  /* csPlane */
const struct UDPPosition*,  /* center */
double,                     /* majorRadius */
double,                     /* ratio */
int,                        /* isCovered */
void*                       /* callbackData */
);

typedef int (*UDPCreateRegularPolygonFP)
(UDPCoordinateSystemPlane,  /* csPlane */
const struct UDPPosition*,  /* center */
const struct UDPPosition*,  /* startPosition */
int,                        /* noOfSides */
int,                        /* isCovered */
void*                       /* callbackData */
);

typedef int (*UDPCreateEquationBasedCurveFP)
(const struct UDPEquationBasedCurveDefinition*, 	/* curveDefinition */
void*					                        	/* callbackData */
);

typedef int (*UDPCreateEquationBasedSurfaceFP)
(const struct UDPEquationBasedSurfaceDefinition*,	/* surfaceDefinition */
void*				                        		/* callbackData */
);

typedef int (*UDPCreateSpiralFP)
(const struct UDPSpiralDefinition*,                  /* spiralDefinition */
void*				                                 /* callbackData */
);

/* 3D ENTITIES */
typedef int (*UDPCreateBoxFP)
(const struct UDPPosition*,	/* start point coordinates */
double[3],					/* size along x, y and z */
void*						/* callbackData */
);

typedef int (*UDPCreateSphereFP)
(const struct UDPPosition*,     /* position */
double,                         /* radius */
void*                           /* callbackData */
);

typedef int (*UDPCreateCylinderFP)
(UDPCoordinateSystemAxis,       /* axis */
const struct UDPPosition*,      /* center */
double,                         /* radius */
double,                         /* height */
void*                           /* callbackData */
);

typedef int (*UDPCreateConeFP)
(UDPCoordinateSystemAxis,       /* axis */
const struct UDPPosition*,      /* center */
double,                         /* bottomRadius */
double,                         /* topRadius */
double,                         /* height */
void*                           /* callbackData */
);

typedef int (*UDPCreateTorusFP)
(UDPCoordinateSystemAxis,       /* axis */
const struct UDPPosition*,      /* center */
double,                         /* majorRadius */
double,                         /* minorRadius */
void*                           /* callbackData */
);

typedef int (*UDPCreatePolyhedronFP)
(UDPCoordinateSystemAxis,       /* axis */
const struct UDPPosition*,      /* center */
const struct UDPPosition*,      /* startPosition */
int,                            /* noOfSides */
double,                         /* height */
void*                           /* callbackData */
);

typedef int (*UDPCreateHelixFP)
(const struct UDPHelixDefinition*, /* helixDefinition */
void*				               /* callbackData */
);



/* OPERATIONS */
/* BOOLEANS */
/* Booean operations (unite, subtarct and intersect) modify the
 * blank body. The resultant body id is same as the blank id.
 * Tool bodies are consumed during the operation.
 * The return value indicates if the operation succeeded,
 * return value 0 means operation failed, any other value
 * means operation succeeded.
 */
typedef int (*UDPUniteFP)
(int*,						/* objectIDs */
int,						/* numObjects */
void*						/* callbackData */
);

typedef int (*UDPSubtractFP)
(int*,						/* blankIDs */
int,						/* numBlanks */
int*,						/* toolIDs */
int,						/* numTools */
void*						/* callbackData */
);

typedef int (*UDPIntersectFP)
(int*,						/* objectIDs */
int,						/* numObjects */
void*						/* callbackData */
);

typedef int (*UDPImprintFP)
(int*,						/* blankIDs */
int,						/* numBlanks */
int*,						/* toolIDs */
int,						/* numTools */
void*						/* callbackData */
);

/* SWEEPS */
/* Sweep operations (Sweep along vector, around axis and
 * along path) modify the profile body. The resultant body
 * id is same as the profile id.
 *
 * Incase of path sweep, the path body is consumed during the
 * sweep operation.
 *
 * The return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPSweepAlongVectorFP)
(int,						/* profileID */
const struct UDPVector*,			/* sweepVector */
const struct UDPSweepOptions*,		/* sweepOptions */
void*						/* callbackData */
);

typedef int (*UDPSweepAroundAxisFP)
(int,						/* profileID */
UDPCoordinateSystemAxis,			/* sweepAxis */
double sweepAngle,                  /* sweepAngle */
const struct UDPSweepOptions*,		/* sweepOptions */
void*						/* callbackData */
);

typedef int (*UDPSweepAlongPathFP)
(int,						/* profileID */
int,						/* pathID */
const struct UDPSweepOptions*,		/* sweepOptions */
void*						/* callbackData */
);


/* TRANSFORMATIONS */
/* Transform operations (Translate i.e.move, rotate, mirror and
 * scale) modify the part body. The resultant body
 * id is same as the part id. The return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPTranslateFP)
(int,						/* partID */
const struct UDPVector*,	/* translation vector */
void*						/* callbackData */
);

typedef int (*UDPRotateFP)
(int,						/* partID */
UDPCoordinateSystemAxis,    /* axis */
double,                     /* angle */
void*						/* callbackData */
);

typedef int (*UDPMirrorFP)
(int,						/* partID */
const struct UDPPosition*,		/* mirror base */
const struct UDPVector*,	/* mirror normal vector */
void*						/* callbackData */
);

typedef int (*UDPTransformFP)
(int,						/* partID */
const struct UDP3x3Matrix*,	/* rotation matrix */
const struct UDPVector*,	/* translation vector */
void*						/* callbackData */
);

typedef int (*UDPScaleFP)
(int,						/* partID */
double,                     /* X scale */
double,                     /* Y scale */
double,                     /* Z scale */
void*						/* callbackData */
);


/* DUPLICATES */
/* Duplicate operations (Duplicate along line, around axis
 * and duplicate and mirror) create new bodies.
 *
 * Incase of duplicate and mirror, only 1 duplicate can be
 * created. The ID of the duplicate body is returned by the
 * function. ID of -1 means the operation failed.
 *
 * For the other two cases multiple duplicates can be created.
 * The IDs of all such duplicates are returned in the function
 * parameter. The function return value indicates if the operation
 * succeeded, return value 0 means operation failed, any other
 * value means operation succeeded.
 */
typedef int (*UDPDuplicateAlongLineFP)
(int,						/* partID */
const struct UDPVector*,	/* translation vector */
int,						/* num of clones (including original) */
int*,						/* returned clone ids */
void*						/* callbackData */
);

typedef int (*UDPDuplicateAroundAxisFP)
(int,						/* partID */
UDPCoordinateSystemAxis,    /* axis */
double,                     /* angle */
int,						/* num of clones (including original) */
int*,						/* returned clone ids */
void*						/* callbackData */
);

typedef int (*UDPDuplicateAndMirrorFP)
(int,						/* partID */
const struct UDPPosition*,		/* mirror base */
const struct UDPVector*,	/* mirror normal vector */
void*						/* callbackData */
);


/* CONNECT */
/* Connect operations is done on multiple bodies. It modifies
 * the first body. All other bodies are consumed.
 * The function return value indicates if the operation
 * succeeded, return value 0 means operation failed, any other
 * value means operation succeeded.
 */
typedef int (*UDPConnectFP)
(int*,						/* part ids */
int,						/* numObjects */
void*						/* callbackData */
);


/* OFFSET */
/* Offset operations is done on 3D body. It modifies
 * the given body. The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPOffsetFP)
(int,						/* partID */
double,                     /* offset distance */
void*						/* callbackData */
);


/* SECTION */
/* Section operations is done on a 3D body. It creates a new body.
 * The function returns the ID of the newly created body.
 * -1 is an invalid ID, which means the operation failed.
 */
typedef int (*UDPSectionFP)
(int,						/* partID */
UDPCoordinateSystemPlane,   /* section plane*/
void*						/* callbackData */
);


/* SPLIT */
/* Section operations modifies given body or create a new body,
 * depending on the enum which side to keep.
 *
 * For kUDPSplitKeepPositiveOnly and kUDPSplitKeepNegativeOnly it
 * modifies the existing body.
 *
 * For kUDPSplitKeepBoth it creates a new body. Only in this case
 * the 4th argument to the function (newly created partID) will be
 * having the id of the new part.
 *
 * The return value indicates if the operation succeeded,
 * return value 0 means operation failed, any other value
 * means operation succeeded.
 */
typedef int (*UDPSplitFP)
(int,						/* partID */
UDPCoordinateSystemPlane,   /* csPlane of split */
UDPSplitWhichSideToKeep,    /* side to keep */
bool,                       /* SplitCrossingObjectsOnly: if true only objects crossing split plane will be splitted */
int*,						/* newly created partID, only for kUDPSplitKeepBoth */
void*						/* callbackData */
);


/* IMPORT NATIVE BODY */
/* Import native body reads a file and imports the objects in it.
 *
 * File formats supported are: sm2, sm3, sat, step, iges, proe
 * dxf, dwg, gds, geo, stl and sld.
 *
 * The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPImportNativeBodyFP)
(char*,						/* file name with full path */
int*,						/* returned part ids */
int*,						/* num of objects returned */
void*						/* callbackData */
);

/* IMPORT NATIVE BODY2 */
/* Same as above except that this correctly returns part id array
 */
typedef int (*UDPImportNativeBody2FP)
(char*,						/* file name with full path */
int**,						/* returned part ids */
int*,						/* num of objects returned */
void*						/* callbackData */
);

/* Import ansoft geometry core.
 * The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPImportAnsoftGeometryFP)
(char*,						/* file name with full path */
int,              /* number of overriding params */
char**,           /* name of overriding params */
UDPParam*,        /* overriding params */ 
int**,						/* returned part ids */
int*,						/* num of objects returned */
void*						/* callbackData */
);

/* Import ansoft component core.
 * The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPImport3DComponentFP)
(char*,						/* file name with full path */
int,              /* number of overriding params */
char**,           /* name of overriding params */
UDPParam*,        /* overriding params */ 
int**,						/* returned part ids */
int*,						/* num of objects returned */
void*						/* callbackData */
);

/* CLONE */
/* Clone clones an existing body. The function returns the
 * ID of the newly created body. -1 is an invalid ID, which
 * means the operation failed.
 */
typedef int (*UDPCloneFP)
(int,						/* partID */
void*						/* callbackData */
);


/* DELETE */
/* Deletes a body. The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPDeletePartFP)
(int,						/* partID */
void*						/* callbackData */
);


/* CREATE OBJECT FROM FACE */
/* Creates a new sheet object from the given face.
 * It returns the ID of the new sheet body being created. -1 is an invalid ID,
 * which means the operation failed.
 */
typedef int (*UDPCreateObjectFromFaceFP)
(int,						/* faceID */
void*						/* callbackData */
);


/* FILLET */
/* Fillet operations is done on 3D body. It modifies
 * the given body. The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPFilletFP)
(const struct UDPBLNDElements* ,    /* part/edges/faces to fillet */
const struct UDPBLNDFilletOptions* ,    /* Fillet parameters/options */
void*						        /* callbackData */
);


/* Chamfer */
/* Chamfer operations is done on 3D body. It modifies
 * the given body. The function return value indicates
 * if the operation succeeded, return value 0 means operation
 * failed, any other value means operation succeeded.
 */
typedef int (*UDPChamferFP)
(const struct UDPBLNDElements* ,    /* part/edges/faces to chamfer */
const struct UDPBLNDChamferOptions* ,    /* Chamfer parameters/options */
void*						        /* callbackData */
);


/* Detach faces from object */
/* Deatches given face(s) from solid or sheet object and
 * creates a new sheet object for each detached face.
 * Number of objects created will be same as number of faces. 
 * All faces must belong to single part.
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPDetachFacesFP)
(int,						/* num faces */
 int*,         /* face ids */
 int*,         /* parts ids for new parts created */ 
void*						/* callbackData */
);

/* Detach edges from object */
/* Deatches given edge(s) from wire object and
 * creates a new wire object for each detached edge.
 * Number of objects created will be same as number of edges. 
 * All edges must belong to single part.
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPDetachEdgesFP)
(int,						/* num edges */
 int*,         /* edge ids */
 int*,         /* part ids for new parts created */ 
void*						/* callbackData */
);

/* CREATE OBJECT FROM EDGE */
/* Creates a new wire object from the given edge.
 * It returns the ID of the new wire body being created. -1 is an invalid ID,
 * which means the operation failed.
 */
typedef int (*UDPCreateObjectFromEdgeFP)
(int,						/* edgeID */
void*						  /* callbackData */
);

/* Thicken sheet */
/* Thickens the sheet ( i.e. makes it solid) with given thickness
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPSheetThickenFP)
(int,						/* part ID */
 double,          /* thickenss */
 bool,            /* thicken both sides? */
void*						  /* callbackData */
);

/* Sweep face(s) along the normal */
/* Sweeps given face(s) along the normal of the face and
 * creates a new solid object for each given face.
 * Number of objects created will be same as number of input faces. 
 * All faces must belong to single part.
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPSweepFaceAlongNormalFP)
(int,						/* num faces */
 int*,         /* face ids */
 int*,         /* parts ids for new parts created */ 
 double,        /* sweep length */
void*						/* callbackData */
);

/* Cover line */
/* Covers closed wire body. Input body is covered on success. 
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPCoverLineFP)
(int,						/* part id */
void*						  /* callbackData */
);

/* Cover surface */
/* Covers sheet body to make it solid. Input body is covered on success. 
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPCoverSurfaceFP)
(int,						/* part id */
void*						  /* callbackData */
);

/* Uncover faces */
/* Uncovers the faces from body.  
 * All faces must belong to single part.
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPUncoverFacesFP)
(int,						  /* number of faces */
 int*,           /* face ids */
void*						  /* callbackData */
);

/* Separate Bodies */
/* Separates the multi-lump body into multiple bodies with single lump.  
 * Input body retains the first lump. New parts will be created for all remaining lumps.
 * UDP dll is supposed to allocate memory for parts id arrya and
 * size of that needs to be specified as number of parts
 * Function will return actual number of parts. If number of parts is more than size of part array
 * function fails, but can user can call it again with increased array size
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPSeparateBodiesFP)
(int,						/* part id */
 int*,						/* this is in/out, size of part ids as input, number of new parts as output */
 int*,           /* part ids */
void*						  /* callbackData */
);

/* Move faces */
/* Moves the faces along normal or along given direction.  
 * Uses offset distnce when moving along normal and
 * uses vector when moving along direction.
 * All faces must belong to single part.
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPMoveFacesFP)
(int,						  /* number of faces */
 int*,           /* face ids */
 bool,            /* move along normal */
 double,          /* offset distance */
 const UDPVector*,    /* direction vector with magnitude */
void*						  /* callbackData */
);

/* Wrap sheet */
/* Wraps the sheet on given target object
 * Return value 0 means operation failed,
 * any other return value means operation succeeded.
 */
typedef int (*UDPWrapSheetFP)
(int,						/* sheet body ID */
 int,            /* target body ID */
 void*						/* callbackData */
);

typedef int (*UDPImprintProjectionFP)
(int,						/* blankID */
int*,						/* toolIDs */
int,						  /* numTools */
bool,						  /* normal projection */
const UDPVector*, /* projection direction */
double,           /* distance */ 
void*						/* callbackData */
);

// Get temp directory path 
// returns path
typedef const char* (*UDPGetTempDirPathFP)
(
 void* callbackData 
);

// Get sys lib directory path
// returns path
typedef const char* (*UDPGetSysLibDirPathFP)
(
 void* callbackData 
);

// Get user lib directory path
// returns path
typedef const char* (*UDPGetUserLibDirPathFP)
(
 void* callbackData 
);

// Get personal lib directory path
// returns path
typedef const char* (*UDPGetPersonalLibDirPathFP)
(
 void* callbackData 
);

// Get install directory path 
// returns path
typedef const char* (*UDPGetInstallDirPathFP)
(
 void* callbackData 
);

typedef const char* (*UDPGetProjectPathFP)
(
 void* callbackData 
);

struct UDPProgress
{
 int prog; // total progress
 int subProg; // sub/phase progress
 const char* mesg; // total progress message/title
 const char* subMesg; // sub progress message/title
};

// Set progress and check for abort
// returns true for success
typedef bool (*UDPSetProgressFP)
(
 UDPProgress* progress, 
 bool* abort, // should abort? 
 void* callbackData 
);

struct UDPFunctionLib
{
    /* Utility functions */
    UDPAddMessageFP addMessage;
    UDPNameAFaceFP nameAFace;
    UDPNameAEdgeFP nameAEdge;
    UDPNameAVertexFP nameAVertex;
    UDPGetFaceIDFromPositionFP getFaceIDFromPosition;
    UDPGetEdgeIDFromPositionFP getEdgeIDFromPosition;
    UDPGetTempDirPathFP getTempDirPath;
    UDPGetInstallDirPathFP getInstallDirPath;
    UDPGetSysLibDirPathFP getSysLibDirPath;
    UDPGetUserLibDirPathFP getUserLibDirPath;
    UDPGetPersonalLibDirPathFP getPersonalLibDirPath;
    UDPSetProgressFP setProgress;

    /* Primitives */
    /* 1D/2D ENTITIES */
    UDPCreatePolylineFP createPolyline;
    UDPCreateRectangleFP createRectangle;
    UDPCreateArcFP createArc;
    UDPCreateCircleFP createCircle;
    UDPCreateEllipseFP createEllipse;
    UDPCreateRegularPolygonFP createRegularPolygon;
    UDPCreateEquationBasedCurveFP createEquationBasedCurve;
    UDPCreateEquationBasedSurfaceFP createEquationBasedSurface;
    UDPCreateSpiralFP createSpiral;

    UDPGetProjectPathFP getProjectPath;

    /* BEGIN - RESERVED FOR FUTURE 1D/2D PRIMITIVES */
    /* DO NOT INVOKE THESE RESERVED FUNCTIONS IN YOUR UDP DLL CREATION CODE */
    UDPReservedForFutureFP reserved1D2DPrimitive5;
    UDPReservedForFutureFP reserved1D2DPrimitive6;
    UDPReservedForFutureFP reserved1D2DPrimitive7;
    UDPReservedForFutureFP reserved1D2DPrimitive8;
    UDPReservedForFutureFP reserved1D2DPrimitive9;
    UDPReservedForFutureFP reserved1D2DPrimitived10;
    /* END - RESERVED FOR FUTURE 1D/2D PRIMITIVES */

    /* 3D ENTITIES */
    UDPCreateBoxFP createBox;
    UDPCreateSphereFP createSphere;
    UDPCreateCylinderFP createCylinder;
    UDPCreateConeFP createCone;
    UDPCreateTorusFP createTorus;
    UDPCreatePolyhedronFP createPolyhedron;
    UDPCreateHelixFP createHelix;

    /* BEGIN - RESERVED FOR FUTURE 3D PRIMITIVES */
    /* DO NOT INVOKE THESE RESERVED FUNCTIONS IN YOUR UDP DLL CREATION CODE */
    UDPReservedForFutureFP reserved3DPrimitive2;
    UDPReservedForFutureFP reserved3DPrimitive3;
    UDPReservedForFutureFP reserved3DPrimitive4;
    UDPReservedForFutureFP reserved3DPrimitive5;
    UDPReservedForFutureFP reserved3DPrimitive6;
    UDPReservedForFutureFP reserved3DPrimitive7;
    UDPReservedForFutureFP reserved3DPrimitive8;
    UDPReservedForFutureFP reserved3DPrimitive9;
    UDPReservedForFutureFP reserved3DPrimitive10;
    /* END - RESERVED FOR FUTURE 3D PRIMITIVES */

    /* Operations */
    /* Booleans */
    UDPUniteFP unite;
    UDPSubtractFP subtract;
    UDPIntersectFP intersect;

    /* Sweeps */
    UDPSweepAlongVectorFP sweepAlongVector;
    UDPSweepAroundAxisFP sweepAroundAxis;
    UDPSweepAlongPathFP sweepAlongPath;

    /* Transformation */
    UDPTranslateFP translate;
    UDPRotateFP rotate;
    UDPMirrorFP mirror;
    UDPScaleFP scale;

    /* Duplicate */
    UDPDuplicateAlongLineFP duplicateAlongLine;
    UDPDuplicateAroundAxisFP duplicateAroundAxis;
    UDPDuplicateAndMirrorFP duplicateAndMirror;

    /* Connect */
    UDPConnectFP connect;

    /* Offset */
    UDPOffsetFP offset;

    /* Section */
    UDPSectionFP section;

    /* Split */
    UDPSplitFP split;

    /* Import native body */
    UDPImportNativeBodyFP importNativeBody;

    /* Clone */
    UDPCloneFP clone;

    /* Delete part */
    UDPDeletePartFP deletePart;

    /* Create Object From Face */
    UDPCreateObjectFromFaceFP createObjectFromFace;

    /* Fillet/Chamfer */
    UDPFilletFP fillet;
    UDPChamferFP chamfer;

    /* Detach Faces/Edges */
    UDPDetachFacesFP detachFaces;
    UDPDetachEdgesFP detachEdges;

    UDPCreateObjectFromEdgeFP createObjectFromEdge;

    UDPSheetThickenFP sheetThicken;
    
    UDPSweepFaceAlongNormalFP sweepFaceAlongNormal;
    
    /* cover/uncover */
    UDPCoverLineFP  coverLine;
    UDPCoverSurfaceFP coverSurface;
    UDPUncoverFacesFP uncoverFaces;

    UDPSeparateBodiesFP separateBodies;

    UDPMoveFacesFP moveFaces;
    UDPWrapSheetFP wrapSheet;
    UDPImprintFP imprint;
    UDPImprintProjectionFP imprintProjection;

    /* Import ansoft geometry */
    UDPImportAnsoftGeometryFP importAnsoftGeometry;

    /* Import 3D component geometry */
    UDPImport3DComponentFP import3DComponent;

    /* correctly rerurns part ids */
    UDPImportNativeBody2FP importNativeBody2;

    UDPTransformFP transform;

    /* BEGIN - RESERVED FOR FUTURE OPERATIONS */
    /* DO NOT INVOKE THESE RESERVED FUNCTIONS IN YOUR UDP DLL CREATION CODE */
    UDPReservedForFutureFP reservedOperation20;
    /* END - RESERVED FOR FUTURE OPERATIONS */
};

#endif /* _USERDEFINEDPRIMITIVESTRUCTURES_H_ */

