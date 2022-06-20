#ifndef _USERDEFINEDPRIMITIVEDLLINCLUDE_H_
#define _USERDEFINEDPRIMITIVEDLLINCLUDE_H_

#include "geomkernel/UserDefinedPrimitiveStructures.h"

#ifdef WIN32
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT
#endif

/* mandatory functions common for both signatures */
extern "C" DLLEXPORT
struct UDPPrimitiveTypeInfo* GetPrimitiveTypeInfo();

extern "C" DLLEXPORT
char* GetLengthParameterUnits();

/* mandatory functions only for signature1 */
extern "C" DLLEXPORT
int GetPrimitiveParametersDefinition(struct UDPPrimitiveParameterDefinition** paramDefinition);

extern "C" DLLEXPORT
int AreParameterValuesValid(char** errorMessageStr, double* paramValues);

extern "C" DLLEXPORT
int CreatePrimitive(struct UDPFunctionLib* functionLib, void* callbackData, double* paramValues);

/* mandatory functions only for signature2 */
extern "C" DLLEXPORT
int GetPrimitiveParametersDefinition2(struct UDPPrimitiveParameterDefinition2** paramDefinition2);

extern "C" DLLEXPORT
int AreParameterValuesValid2(char** errorMessageStr, struct UDPParam* paramValues);

extern "C" DLLEXPORT
int CreatePrimitive2(struct UDPFunctionLib* functionLib, void* callbackData, struct UDPParam* paramValues);

/* Optional functions common for both signature */
extern "C" DLLEXPORT
int GetPrimitiveParameters(char** paramValues);

extern "C" DLLEXPORT
int GetRegisteredFaceNames(char*** faceNames);

extern "C" DLLEXPORT
int GetRegisteredEdgeNames(char*** edgeNames);

extern "C" DLLEXPORT
int GetRegisteredVertexNames(char*** vertexNames);

/* Optional functions only for signature1 */
extern "C" DLLEXPORT
int ProjectParametersOnToValidPlane(double* paramValues, double* projectedParamValues);

/*
 * newParamValues: output - space is already allocated by HFSS. UDP Programmer needs to fill the data
 * oldVersion: input - version string in the old dll
 * oldNumberOfParams: input - number of parameters in the old dll
 * oldParamDefinition: input - parameter definition in the old dll
 * return value 0 means failure, anything else is success
*/
extern "C" DLLEXPORT
int MapParametersDefinitionVersions(double** newParamValues, char* oldVersion, int oldNumberOfParams, struct UDPPrimitiveParameterDefinition* oldParamDefinition);

/* Optional functions only for signature2 */
extern "C" DLLEXPORT
int ProjectParametersOnToValidPlane2(struct UDPParam* paramValues, struct UDPParam* projectedParamValues);

extern "C" DLLEXPORT
int GetOldPrimitiveParametersDefinition2(char* oldVersion, struct UDPPrimitiveParameterDefinition2** oldParamDefinition2);

extern "C" DLLEXPORT
int MapParametersDefinitionVersions2(struct UDPParam* newParamValues, char* oldVersion, int oldNumberOfParams, struct UDPParam* oldParamValues);

#endif /* _USERDEFINEDPRIMITIVEDLLINCLUDE_H_ */


