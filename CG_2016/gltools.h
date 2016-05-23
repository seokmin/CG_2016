// GLTools.h
// OpenGL SuperBible
// Copyright 1998 - 2003 Richard S. Wright Jr..
// Code by Richard S. Wright Jr.
// All Macros prefixed with GLT_, all functions prefixed with glt... This
// should avoid most namespace problems
// Some of these functions allocate memory. Use CRT functions to free
// Report bugs to rwright@starstonesoftware.com

#ifndef __GLTOOLS__LIBRARY
#define __GLTOOLS__LIBRARY

// Windows
#ifdef WIN32
#include <windows.h>
#include <winnt.h>
#include <gl\gl.h>
#include <gl\glu.h>
#endif

// Mac OS X
#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <sys/time.h>
#endif

// Universal includes
#include <math.h>



///////////////////////////////////////////////////////
// Useful constants
#define GLT_PI	3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229

///////////////////////////////////////////////////////////////////////////////
// Useful shortcuts and macros
// Radians are king... but we need a way to swap back and forth
#define gltDegToRad(x)	((x)*GLT_PI_DIV_180)
#define gltRadToDeg(x)	((x)*GLT_INV_PI_DIV_180)


///////////////////////////////////////////////////////
// Some data types
typedef GLfloat GLTVector2[2];      // Two component floating point vector
typedef GLfloat GLTVector3[3];      // Three component floating point vector
typedef GLfloat GLTVector4[4];      // Four component floating point vector
typedef GLfloat GLTMatrix[16];      // A column major 4x4 matrix of type GLfloat

typedef struct{                     // The Frame of reference container
    GLTVector3 vLocation;
    GLTVector3 vUp;
    GLTVector3 vForward;
    } GLTFrame;

typedef struct 			    // High resolution timer
    {
    #ifdef WIN32
    LARGE_INTEGER m_LastCount;
    #else
    struct timeval last;
    #endif
    } GLTStopwatch;
    
    
///////////////////////////////////////////////////////
// Macros for big/little endian happiness
#define BYTE_SWAP(x)    x = ((x) >> 8) + ((x) << 8)


///////////////////////////////////////////////////////////////////////////////
//         THE LIBRARY....
///////////////////////////////////////////////////////////////////////////////

// vector functions in VectorMath.c 
void gltAddVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);
void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale);
GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector);
GLfloat gltGetVectorLength(const GLTVector3 vVector);
void gltNormalizeVector(GLTVector3 vNormal);
void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal);
void gltCopyVector(const GLTVector3 vSource, GLTVector3 vDest);
GLfloat gltVectorDotProduct(const GLTVector3 u, const GLTVector3 v);
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult);
void gltTransformPoint(const GLTVector3 vSrcPoint, const GLTMatrix mMatrix, GLTVector3 vPointOut);
void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vPointOut);
void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane);
GLfloat gltDistanceToPlane(GLTVector3 vPoint, GLTVector4 vPlane);


//////////////////////////////////////////
// Other matrix functions in matrixmath.c
void gltLoadIdentityMatrix(GLTMatrix m);
void gltMultiplyMatrix(const GLTMatrix m1, const GLTMatrix m2, GLTMatrix mProduct );
void gltRotationMatrix(float angle, float x, float y, float z, GLTMatrix mMatrix);
void gltTranslationMatrix(GLfloat x, GLfloat y, GLfloat z, GLTMatrix mTranslate);
void gltScalingMatrix(GLfloat x, GLfloat y, GLfloat z, GLTMatrix mScale);
void gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos, GLTMatrix destMat);
void gltTransposeMatrix(GLTMatrix mTranspose);
void gltInvertMatrix(const GLTMatrix m, GLTMatrix mInverse);

/////////////////////////////////////////
// Frames and frame stuff. All in FrameMath.c 
void gltInitFrame(GLTFrame *pFrame);
void gltGetMatrixFromFrame(GLTFrame *pFrame, GLTMatrix mMatrix);
void gltApplyActorTransform(GLTFrame *pFrame);
void gltApplyCameraTransform(GLTFrame *pCamera);
void gltMoveFrameForward(GLTFrame *pFrame, GLfloat fStep);
void gltMoveFrameUp(GLTFrame *pFrame, GLfloat fStep);
void gltMoveFrameRight(GLTFrame *pFrame, GLfloat fStep);
void gltTranslateFrameWorld(GLTFrame *pFrame, GLfloat x, GLfloat y, GLfloat z);
void gltTranslateFrameLocal(GLTFrame *pFrame, GLfloat x, GLfloat y, GLfloat z);
void gltRotateFrameLocalY(GLTFrame *pFrame, GLfloat fAngle);

//////////////////////////////////////////////////
// Timer class. Found in stopwatch.c
void gltStopwatchReset(GLTStopwatch *pWatch);
float gltStopwatchRead(GLTStopwatch *pWatch);


/////////////////////////////////////////////////////////////////////////////////////
// Functions, need to be linked to your program. Source file for function is given
// LoadTGA.c
GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

// WriteTGA.c
GLint gltWriteTGA(const char *szFileName);

// Torus.c
void gltDrawTorus(GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor);

// Sphere.c
void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks);

// UnitAxes.c
void gltDrawUnitAxes(void);

// IsExtSupported.c
int gltIsExtSupported(const char *szExtension);

// GetExtensionPointer.c
void *gltGetExtensionPointer(const char *szFunctionName);

///////////////////////////////////////////////////////////////////////////////
// Win32 Only
#ifdef WIN32
int gltIsWGLExtSupported(HDC hDC, const char *szExtension);
#endif


#endif



// Adds two vectors together
void gltAddVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult) {
    vResult[0] = vFirst[0] + vSecond[0];
    vResult[1] = vFirst[1] + vSecond[1];
    vResult[2] = vFirst[2] + vSecond[2];
    }

// Subtract one vector from another
void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult) 
    {
    vResult[0] = vFirst[0] - vSecond[0];
    vResult[1] = vFirst[1] - vSecond[1];
    vResult[2] = vFirst[2] - vSecond[2];
    }

// Scales a vector by a scalar
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
    { 
    vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale; 
    }

// Gets the length of a vector squared
GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector)
    { 
    return (vVector[0]*vVector[0]) + (vVector[1]*vVector[1]) + (vVector[2]*vVector[2]); 
    }
    
// Gets the length of a vector
GLfloat gltGetVectorLength(const GLTVector3 vVector)
    { 
    return (GLfloat)sqrt(gltGetVectorLengthSqrd(vVector)); 
    }
    
// Scales a vector by it's length - creates a unit vector
void gltNormalizeVector(GLTVector3 vNormal)
    { 
    GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
    gltScaleVector(vNormal, fLength); 
    }
    
// Copies a vector
void gltCopyVector(const GLTVector3 vSource, GLTVector3 vDest)
    { 
    memcpy(vDest, vSource, sizeof(GLTVector3)); 
    }

// Get the dot product between two vectors
GLfloat gltVectorDotProduct(const GLTVector3 vU, const GLTVector3 vV)
    {
    return vU[0]*vV[0] + vU[1]*vV[1] + vU[2]*vV[2]; 
    }

// Calculate the cross product of two vectors
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult)
	{
	vResult[0] = vU[1]*vV[2] - vV[1]*vU[2];
	vResult[1] = -vU[0]*vV[2] + vV[0]*vU[2];
	vResult[2] = vU[0]*vV[1] - vV[0]*vU[1];
	}



// Given three points on a plane in counter clockwise order, calculate the unit normal
void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal)
    {
    GLTVector3 vV1, vV2;
    
    gltSubtractVectors(vP2, vP1, vV1);
    gltSubtractVectors(vP3, vP1, vV2);
    
    gltVectorCrossProduct(vV1, vV2, vNormal);
    gltNormalizeVector(vNormal);
    }



// Transform a point by a 4x4 matrix
void gltTransformPoint(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
    {
    vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] *  vSrcVector[2] + mMatrix[12];
    vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] *  vSrcVector[2] + mMatrix[13];
    vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2] + mMatrix[14];    
    }

// Rotates a vector using a 4x4 matrix. Translation column is ignored
void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
    {
    vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] *  vSrcVector[2];
    vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] *  vSrcVector[2];
    vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2];    	
    }


// Gets the three coefficients of a plane equation given three points on the plane.
void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane)
    {
    // Get normal vector from three points. The normal vector is the first three coefficients
    // to the plane equation...
    gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane);
    
    // Final coefficient found by back substitution
    vPlane[3] = -(vPlane[0] * vPoint3[0] + vPlane[1] * vPoint3[1] + vPlane[2] * vPoint3[2]);
    }
    
// Determine the distance of a point from a plane, given the point and the
// equation of the plane.
GLfloat gltDistanceToPlane(GLTVector3 vPoint, GLTVector4 vPlane)
    {
    return vPoint[0]*vPlane[0] + vPoint[1]*vPlane[1] + vPoint[2]*vPlane[2] + vPlane[3];
    }
    