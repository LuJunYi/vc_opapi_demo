/*
 * $Id: opapi_template.c,v 5.2 2014/05/16 20:40:55 jchen Exp $
 *
 * Copyright (c) 2002 by CGTech.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optimport.h"

 /*----------------------------------------------------------------------------
  * Initialization function
  * called each time OptiPath is turned on.
  * Input: usrData - user defined data
  *----------------------------------------------------------------------------*/
static int opapi_usr_init(void* usrData)
{

	/* do initialization here */

	return 1;
}

/*----------------------------------------------------------------------------
 * Tool change initialization function
 * call each time a new tool is loaded
 * Input: usrData - user defined data
 *---------------------------------------------------------------------------*/
static int opapi_usr_tool_change(void* userData)
{
	char* tool_id;
	int			is_apt;
	sOPAPI_APT_CUTTER	apt_cutter;
	double			override_rpm;
	double 			distance;

	/* get curent loaded tool */
	opapi_get_current_tool(&tool_id, &is_apt, &apt_cutter);

	/*  call user setup routine for this tool here */

	if (tool_id)
	{
		/* if does not need to optimize tool11 */
		if (strcmp(tool_id, "11") == 0)
		{
			return 0;
		}

		/* if needs to set overide rpm known from setup rountine for tool2*/
		override_rpm = 1000.0;

		if (strcmp(tool_id, "2") == 0)
		{
			opapi_set_override_rpm(override_rpm);
		}
	}

	/* set optimization resolution based on tool size */
	distance = 1.0;
	opapi_set_resolution(distance);

	return 1;
}
/*----------------------------------------------------------------------------
 * Optimization function
 * called multiple times for each motion, depending on resolution distance
 * Input : usrData      - user defined data
 * Output: feedRate     - optimized feed rate
 *         spindleSpeed - optimized rpm
 *---------------------------------------------------------------------------*/
static void opapi_usr_optimize(void* userData, double* feedRate, double* spindleSpeed)
{
	int					rec_num, contact, num_loops, * loop_size;
	char* record;
	double				tool_start[6], tool_end[6], tool_pos[6], machine_start[12], machine_end[12], machine_pos[12];
	double				circle[6];
	eOPAPI_MOTION_TYPE	motion_type;
	double				feedrate, rpm, width, depth, volume, area, dist, time;
	sOPAPI_MAP			map;
	int					i, size, j;
	char* bit_values;
	sOPAPI_PROFILE* profile;

	/*---------------------------------------------------------------------------*/

	/* get motion related info */

	/* toolpath record*/
	opapi_get_toolpath_record(&rec_num, &record);
	/* start and end tool position */
	opapi_get_cut_tool_position(tool_start, tool_end);
	/* current tool position */
	opapi_get_current_tool_position(tool_pos);
	/* start and end machine position at current step */
	opapi_get_cut_machine_position(machine_start, machine_end);
	/* current machine position at motion interval */
	opapi_get_current_machine_position(machine_pos);
	/* motion type */
	opapi_get_motion_type(&motion_type, circle);
	/* feedrate */
	feedrate = opapi_get_program_feedrate();
	/* spindle speed */
	rpm = opapi_get_spindle_speed();
	/* distance at interval end */
	dist = opapi_get_current_distance();
	/* time at interval end */
	time = opapi_get_current_time();

	/*---------------------------------------------------------------------------*/

	/* get milling tool-material contact info */

	/* radial width */
	width = opapi_get_radial_width();
	char s[50];
	sprintf(s, "width is %f", width);
	opapi_write_out_comment_line(s);
	
	/* axial depth */
	depth = opapi_get_axial_depth();
	/* volume removed */
	volume = opapi_get_volume_removed();
	/* contact area */
	opapi_get_contact_area(&contact, &area);

	//char s[50];
	//sprintf(s, "contact area = %f", area);
	//opapi_send_message(s, 1);

	/* grid map */
	opapi_get_grid_map(&map);
	/* get decompressed bit data */
	bit_values = NULL;
	if (map.gridMask)
	{
		opapi_get_decompressed_map_data(&map, &size, &bit_values);
		/* print out grid map */
		for (i = 0; i < size; i++)
		{
			if (fmod(i, map.numGridsX) == 0)
			{
				//printf("\n");
			}
			//printf("%d,", abs(bit_values[i]));
		}
	}

	/*---------------------------------------------------------------------------*/

	/* get turning tool-material contact info */
	loop_size = NULL;
	profile = NULL;
	rec_num = opapi_get_turning_contact_profile(&num_loops, &loop_size, &profile);
	if (rec_num)
	{
		/* print out profile elment */
		size = 0;
		for (i = 0; i < num_loops; i++)
		{
			for (j = 0; j < loop_size[i]; j++)
			{
				//printf("ptx = %f, pty =%f, radius = %f\n", profile[size].pt[0], profile[size].pt[1], profile[size].rad);
				size++;
			}
		}
	}
	/*---------------------------------------------------------------------------*/


	/* call user optimization function here */

	/*---------------------------------------------------------------------------*/

	/* free milling contact resources */
	opapi_free((char*)map.gridMask);
	opapi_free(bit_values);

	/* free trurning contact resources */
	opapi_free((char*)loop_size);
	opapi_free((char*)profile);

	/*---------------------------------------------------------------------------*/

	/* write out comments to Optimized NC program */
	opapi_write_out_comment_line("(my comments here)\n");
}
/*----------------------------------------------------------------------------
 * Termination function
 * called each time OptiPath is turned off
 * Input : usrData - user defined data
 *----------------------------------------------------------------------------*/
static void opapi_usr_terminate(void* usrData)
{
	/* free resources */


	/* send a message to VERICUT logger*/
	opapi_send_message("Optimization is off", 1);
}

/*------------------------------------------------------------------------------
 * OptiPath API setup initialization function.
 * Called before optimization, can be used to initialize register user
 * initialization, tool change setup, optimization, termination functions.
 *-----------------------------------------------------------------------------*/
void opapi_setup()
{
	opapi_set_user_data(NULL);
	opapi_set_initialize_function(opapi_usr_init);
	opapi_set_tool_change_setup_function(opapi_usr_tool_change);
	opapi_set_optimize_function(opapi_usr_optimize);
	opapi_set_terminate_function(opapi_usr_terminate);
}
