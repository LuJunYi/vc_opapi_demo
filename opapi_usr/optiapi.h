/*	@(#)optiapi.h	17.1	12/19/06	*/

#ifndef OPTIAPI_H
#define OPTIAPI_H


typedef struct s_OPAPI_MAP
{
   double toolEnd[2];	/* Tool tip at starting position projected to the projection grids, in gridAxisX, gridAxisY */
   double gridOrigin[3];/* Origin of projection grids in X, Y, Z */	
   double gridAxisX[3]; /* Projection grids' X axis in I, J, K. X axis in normal to the Z axis and tool axis in starting position */
   double gridAxisY[3]; /* Projection grids' Y axis in I, J, K */
   double gridAxisZ[3]; /* Projection grids' Z axis in I, J, K. Z axis is the unit vector of cutter translation position vector */
   double gridSize;		/* Length of each grid */
   int    numGridsX;	/* Number of grids along gridAxisX */
   int    numGridsY;	/* Number of grids along gridAxisY */
   int    maskSize;		/* Number of int/32 bits that are used to store the mask */
   int    *gridMask;	/* Pointer to grid mask */
}sOPAPI_MAP;

typedef struct s_OPAPI_APT_CUTTER
{
   double cutterDiameter;/* Cutter diameter, D */
   double cutterHeight;	 /* Cutter height, H */
   double cornerRadius;	 /* Corner radius, R */
   double eDistance;	 /* Distance from tool centerline to corner radius center, E */
   double fDistance;	 /* Distance from tool tip to corner radius center, F */
   double baseAngle;	 /* Base angle, A */
   double sideAngle;	 /* Side angle, B */ 
}sOPAPI_APT_CUTTER;

typedef enum e_OPAPI_MOTION_TYPE
{
   OPAPI_LINEAR = 0,
   OPAPI_CIRCLE = 1,
   OPAPI_NURBS  = 2,
   OPAPI_RAPID  = 3
}eOPAPI_MOTION_TYPE;

typedef struct s_OPAPI_PROFILE
{
	double    pt[2];  /* point or center of the arc */
	double    rad;    /* arc radius with sign: </> 0 means CW/CCW; = 0 means it is a point, not arc */
} sOPAPI_PROFILE;

/*----------------------------------------------------------------------------
 * Initialization function
 * called each time OptiPath is turned on.
 *----------------------------------------------------------------------------*/
typedef int
(*OPAPI_InitializeFunction)(void *userData);

/*----------------------------------------------------------------------------
 * Tool change initialization function
 * call each time a new tool is loaded
 *---------------------------------------------------------------------------*/
typedef int
(*OPAPI_ToolSetupFunction)(void *userData);

/*----------------------------------------------------------------------------
 * Optimization function
 * called multiple times for each motion, depending on resolution distance
 *---------------------------------------------------------------------------*/
typedef void
(*OPAPI_OptimizeFunction)(void *userData, double *feedRate, double *spindleSpeed);

/*----------------------------------------------------------------------------
 * Termination function
 * called each time OptiPath is turned off
 *----------------------------------------------------------------------------*/
typedef void
(*OPAPI_TerminateFunction)(void *userData);

#endif /* OPTIAPI_H */
