/*
 * joystick.c
 *
 *  Created on: May 8, 2024
 *  Author: l.marcolini ESEO E3A
 */


/* Includes =============================================================== */

#include "joystick.h"

/* Define ================================================================= */

/* Enumeration ============================================================*/

/* Structure ============================================================== */

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

/* Function  ============================================================== */

e_joystick_status JOYSTICK_refresh(st_joystick * joystick)
{
	e_joystick_status status = JOYSTICK_STATUS_OK;

	if (JOYSTICK_AXIS_get_value(&joystick->x) != JOYSTICK_AXIS_STATUS_OK)
	{
		status = JOYSTICK_CONFIG_ERROR;
	}

	if (JOYSTICK_AXIS_get_value(&joystick->y) != JOYSTICK_AXIS_STATUS_OK)
	{
		status = JOYSTICK_CONFIG_ERROR;
	}

	return status;
}
