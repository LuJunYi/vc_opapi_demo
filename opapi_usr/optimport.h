/*
	@(#)optimport.h	17.1	12/19/06
*/
#ifndef REVIEWER_IGNORE

/* DO NOT MODIFY THIS FILE */
/* For C++ add to beginning of each function declaration: extern "C" */

#ifndef OPTIMPORT_H
#define OPTIMPORT_H

#include "optiapi.h"

#define DllExport _declspec(dllexport)
/*----------------------------------------------------------------------------
 * Function: opapi_setup
 * Setup function. Must be present with exactly the same declaration style and name. 
 * Called when OptiPath API library is first loaded. It is to register user's 
 * optimization function.
 *---------------------------------------------------------------------------*/
DllExport void   opapi_setup(void);

#define DllImport _declspec(dllimport)
/*------------------------------------------------------------------------------
 * Function: opapi_send_message
 * API error messages to VERICUT logger/log file.
 * Input:  message - message to be sent to VERICUT
 *         display - display mode - 0 : to log file
 *                                 1 : to GUI logger
 *                                 2 : to both log file and logger
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_send_message(char *message, int display);

/*------------------------------------------------------------------------------
 * Function: opapi_set_override_rpm
 * Set override rpm value.
 * This function should only be called within OPAPI_ToolSetupFunction!
 *
 * Input:  rpm - override spindle speed(rpm)
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_override_rpm(double rpm);

/*------------------------------------------------------------------------------
 * Function: opapi_set_resolution
 * Set OptiPath resolution distance.
 * This function should only be called within OPAPI_InitializeFunction!
 *
 * Input:  dist - resolution distance
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_resolution(double dist);

/*------------------------------------------------------------------------------
 * Function: opapi_set_user_data
 * Register user data
 * This function should only be called within opapi_setup()!
 *
 * Input:  usr_data : pointer to usr data being passed to other user functions.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_user_data(void * usr_data);

/*------------------------------------------------------------------------------
 * Function: opapi_set_initialize_function
 * Register users initialize function
 * This function should only be called within opapi_setup()!
 * 
 * Input:  function_p : init function pointer.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_initialize_function(OPAPI_InitializeFunction function_p);

/*------------------------------------------------------------------------------
 * Function: opapi_set_tool_change_setup_function
 * Register users tool change setup function
 * This function should only be called within opapi_setup()!
 * 
 * Input: function_p : tool setup function pointer.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_tool_change_setup_function(OPAPI_ToolSetupFunction function_p);

/*------------------------------------------------------------------------------
 * Function: opapi_set_optimize_function
 * Register user optimization function
 * This function should only be called within opapi_setup()!
 *
 * Input function_p : optimization function pointer.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_optimize_function(OPAPI_OptimizeFunction function_p);

/*------------------------------------------------------------------------------
 * Function: opapi_set_terminate_function
 * Register user termination function
 * This function should only be called within opapi_setup()!
 *
 * Input: function_p : optimization function pointer.
 * Return: None.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_set_terminate_function(OPAPI_TerminateFunction function_p);

/*------------------------------------------------------------------------------
 * Function: opapi_get_current_tool
 * Gets the current tool data 
 * Output: tool_id : current tool id, NULL if no tls file. 
 *		   isApt   : 1 if apt cutter, 0 if not.
 *		   aptData : Apt parameters if tool is an apt cutter.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_current_tool(char **tool_id, int *isApt, sOPAPI_APT_CUTTER *aptData);

/*------------------------------------------------------------------------------
 * Function: opapi_get_toolpath_record
 * Gets current toolpath record
 * Output: rec_num: toolpath file line number
 *         record : toolpath record txt, needs to be freeed by calling routine. 
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_toolpath_record(int *rec_num, char **record);

/*------------------------------------------------------------------------------
 * Function: opapi_get_current_tool_position
 * Gets current tool position.
 * Output:  toolpos: tool position at current interval of current cut in (x,y,z,i,j,k) in cut stock coordinate system
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_current_tool_position(double toolpos[6]);

/*------------------------------------------------------------------------------
 * Function: opapi_get_current_tool_position_in_active_csys
 * Gets current tool position.
 * Output:  toolpos: tool position at current interval of current cut in (x,y,z,i,j,k) in VERICUT's active coordinate system
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_current_tool_position_in_active_csys(double toolpos[6]);
/*------------------------------------------------------------------------------
 * Function: opapi_get_current_tool_position_in_machine_csys
 * Gets current tool position.
 * Output:  toolpos: tool position at current interval of current cut in (x,y,z,i,j,k) in machine origin coordinate system
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_current_tool_position_in_machine_csys(double toolpos[6]);

/*------------------------------------------------------------------------------
 * Get locations of machine axes(X, Y, Z) resulting from processing the current G-Code NC program record at current interval of motion
 * (O) pos:(machine axes value x,y,z)
 *-----------------------------------------------------------------------------*/
DllExport void opapi_get_current_machine_axes_location(double pos[3]);

/*------------------------------------------------------------------------------
 * Get locations of machine axes(X, Y, Z) in local coordinate system at current interval of motion
 * (O) pos:(machine axes value x,y,z in local coordinate system)
 *-----------------------------------------------------------------------------*/
DllExport void opapi_get_current_local_axes_location(double pos[3]);

/*------------------------------------------------------------------------------
 * Function: opapi_get_cut_tool_position
 * Gets start and end tool positions at current cut.
 * Output:  start:  tool position at the start of the cut in (x,y,z,i,j,k)
 *          end:    tool position at the end   of the cut in (x,y,z,i,j,k)
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_cut_tool_position(double start[6], double end[6]);

/*------------------------------------------------------------------------------
 * Function: opapi_cut_machine_position
 * Gets start and end machine positions at current cut.
 * Output: start: machine position at the start of the cut in (x,y,z,u,v,w,a,b,c,a2,b2,c2)
 *         end:   machine position at the end   of the cut in (x,y,z,u,v,w,a,b,c,a2,b2,c2)
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_cut_machine_position(double start[12], double end[12]);

/*------------------------------------------------------------------------------
 * Function: opapi_current_machine_position
 * Gets current machine positions at motion interval.
 * Output: pos: machine position in (x,y,z,u,v,w,a,b,c,a2,b2,c2)
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_current_machine_position(double pos[12]);
/*------------------------------------------------------------------------------
 * Function: opapi_get_motion_type
 * Gets motion type
 * Output: type: motion type
 *         circle: circle center in (x,y,z, i,j,k) in case of circular motion.
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_motion_type(eOPAPI_MOTION_TYPE *motion_type, double circle[6]);

/*------------------------------------------------------------------------------
 * Function: opapi_get_contact_area
 * Get tool-material contact info
 * Output: contact: 1 if tool is in contact with the material; 
 *              0 if not.
 *         area:    contact area
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_contact_area(int *contact, double *area);

/*------------------------------------------------------------------------------
 * Function: opapi_get_grid_map
 * Gets grid map
 * Output: map: pointer to grid map.
 *               returned map->gridMask must be freed by using opapi_free!
 *-----------------------------------------------------------------------------*/
DllImport void   opapi_get_grid_map(sOPAPI_MAP *map);

/*------------------------------------------------------------------------------
 * Function: opapi_get_decompressed_map_data
 * Gets grid map knots data
 * Input:  map: pointer to grid map.
 * Output: size: size of knots
 *		   values: an arrary of 1/0 indicating whether tool is in contact with material
 *         at each knots. values must be freed by using opapi_free!
 *----------------------------------------------------------------------------*/
DllImport void   opapi_get_decompressed_map_data(sOPAPI_MAP *map, int *size, char **values);

/*------------------------------------------------------------------------------
 * Function: opapi_free
 * Free memory allocated by API program.
 * Input:  data : pointer to memory to be freed
 *----------------------------------------------------------------------------*/
DllImport void   opapi_free(char *data);

/*------------------------------------------------------------------------------
 * Function: opapi_get_chip_thickness
 * Returns chip thickness.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_chip_thickness(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_radial_width
 * Returns radial width.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_radial_width(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_axial_depth
 * Returns axial depth.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_axial_depth(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_contact_depth
 * Returns depth between highest contact point to lowest contact point.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_contact_depth(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_volume_removed
 * Returns volume removed.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_volume_removed(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_program_feedrate
 * Returns current program feedrate.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_program_feedrate(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_program spindle_speed
 * Returns spindle speed in rpm defined in NC program.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_program_spindle_speed(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_spindle_speed
 * Returns current spindle speed in rpm.
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_spindle_speed(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_conventional_cut_flag
 * Returns conventional cut flag
 *-----------------------------------------------------------------------------*/
DllImport int opapi_get_conventional_cut_flag(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_side_cut_flag
 * Returns side cut flag
 *-----------------------------------------------------------------------------*/
DllImport int opapi_get_side_cut_flag(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_thin_cut_flag
 * Returns thin cut flag
 *-----------------------------------------------------------------------------*/
DllImport int opapi_get_thin_cut_flag(void);

/*-----------------------------------------------------------------------------*
 * Function: opapi_write_out_comment_line
 * Write out a comment line to optimized G-code toolpath file
 * comment string must include starting comment character and end of line 
 * character return
 * (I) data : pointer to comment string
 *----------------------------------------------------------------------------*/
DllImport void opapi_write_out_comment_line(char *);

/*------------------------------------------------------------------------------
 * Function opapi_get_variable_value
 * Get a G-code variable value, only valid for mcd file
 * Input: variable name
 *----------------------------------------------------------------------------*/
DllImport char *opapi_get_variable_value(char *);

/*------------------------------------------------------------------------------
 * Function: opapi_get_total_time
 * Returns total time
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_total_time(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_total_distance
 * Returns total distance
 *----------------------------------------------------------------------------*/
DllImport double opapi_get_total_distance(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_total_volume_removed
 * Returns total volume removed
 *----------------------------------------------------------------------------*/
DllImport double opapi_get_total_volume_removed(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_turning_contact_profile
 * Returns total number of elements in contact profile
 * (O) num_loops: number of closed loops in contact profile.
 * (O) size: an array of element size for each loop, needs to be freed by calling routine.
 * (O) profile: an arrary of profile elements of contact profile, needs to be freed by calling routine.
 *----------------------------------------------------------------------------*/
DllImport int opapi_get_turning_contact_profile(int *num_loops, int **size, sOPAPI_PROFILE **profile);

/*------------------------------------------------------------------------------
 * Function: opapi_get_current_time
 * Returns time at the end of current motion interval
 *-----------------------------------------------------------------------------*/
DllImport double opapi_get_current_time(void);

/*------------------------------------------------------------------------------
 * Function: opapi_get_current_distance
 * Returns distance at the end of current motion interval
 *----------------------------------------------------------------------------*/
DllImport double opapi_get_current_distance(void);

#endif /* OPTIMPORT_H */
#endif /* REVIEWER_IGNORE */