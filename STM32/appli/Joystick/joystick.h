/*
 * joystick.h
 *
 *  Created on: May 8, 2024
 *  Author: l.marcolini ESEO E3A
 */

#ifndef BSP_JOYSTICK_JOYSTICK_H_
#define BSP_JOYSTICK_JOYSTICK_H_

/* Includes =============================================================== */

#include "macro_types.h"
#include "config.h"

#include "joystick_button.h"
#include "joystick_axis.h"

/* Defines ================================================================ */

/* Enumerations ============================================================*/

typedef enum
{
	JOYSTICK_STATUS_OK = 0,
	JOYSTICK_CONFIG_ERROR = 1
}
e_joystick_status;

/* Structures ============================================================= */

/**
 * Structure modélisant un joystick à 2 axes
 */
typedef struct
{
	st_joystick_axis x;
	st_joystick_axis y;
}
st_joystick;

/* External function prototypes =========================================== */

e_joystick_status JOYSTICK_refresh(st_joystick * joystick);

#endif /* BSP_JOYSTICK_JOYSTICK_H_ */
