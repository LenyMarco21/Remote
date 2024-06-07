/**
 * \file    	controller.h
 * \brief   	Manette
 * \details
 */


#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

/* Includes =============================================================== */

#include <stdint.h>

/* Defines ================================================================ */

/* Enumerations ============================================================*/

/**
 * Défini le nombre de valeurs différentes sur un axe
 */
typedef enum
{
	AXIS_RESOLUTION_2_BITS  = 2,
	AXIS_RESOLUTION_3_BITS  = 3,
	AXIS_RESOLUTION_4_BITS  = 4,
	AXIS_RESOLUTION_5_BITS  = 5,
	AXIS_RESOLUTION_6_BITS  = 6,
	AXIS_RESOLUTION_7_BITS  = 7,
	AXIS_RESOLUTION_8_BITS  = 8,
	AXIS_RESOLUTION_9_BITS  = 9,
	AXIS_RESOLUTION_10_BITS = 10,
	AXIS_RESOLUTION_11_BITS = 11,
	AXIS_RESOLUTION_12_BITS = 12
}
e_controller_axis_resolution;

/**
 * Défini l'inversion de l'axe
 */
typedef enum
{
	AXIS_NON_INVERTED = 0,
	AXIS_INVERTED = 1
}
e_controller_axis_polarity;

typedef enum
{
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2
}
e_controller_axis;

typedef enum
{
	CONTROLLER_CONFIG_SUCCESS = 0,
	CONTROLLER_CONFIG_ERROR	= 1
}
e_controller_status;

/* Structures ============================================================= */

/* External function prototypes =========================================== */

int16_t CONTROLLER_GetAxisValue(e_controller_axis axis);

e_controller_status CONTROLLER_SetAxisResolution(e_controller_axis axis, e_controller_axis_resolution resolution);

e_controller_status CONTROLLER_SetAxisPolarity(e_controller_axis axis, e_controller_axis_polarity polarity);

#endif /* INC_CONTROLLER_H_ */
