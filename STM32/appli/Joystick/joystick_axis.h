/*
 * joystick_axis.h
 *
 *  Author: l.marcolini ESEO E3A
 */

#ifndef BSP_JOYSTICK_JOYSTICK_AXIS_H_
#define BSP_JOYSTICK_JOYSTICK_AXIS_H_

/* Includes =============================================================== */

#include "macro_types.h"
#include "config.h"
#include "stm32f1_adc.h"

/* Defines ================================================================ */

/* Enumerations ============================================================*/

/**
 * Enumère les différentes résolutions programmables
 */
typedef enum
{
	JOYSTICK_AXIS_RES_2b  = 2,
	JOYSTICK_AXIS_RES_3b  = 3,
	JOYSTICK_AXIS_RES_4b  = 4,
	JOYSTICK_AXIS_RES_5b  = 5,
	JOYSTICK_AXIS_RES_6b  = 6,
	JOYSTICK_AXIS_RES_7b  = 7,
	JOYSTICK_AXIS_RES_8b  = 8,
	JOYSTICK_AXIS_RES_9b  = 9,
	JOYSTICK_AXIS_RES_10b = 10,
	JOYSTICK_AXIS_RES_11b = 11,
	JOYSTICK_AXIS_RES_12b = 12
}
e_joystick_axis_resolution;


/**
 * Enumère les polarités d'axe possible
 */
typedef enum
{
	JOYSTICK_AXIS_POL_NON_INVERTED = 0,
	JOYSTICK_AXIS_POL_INVERTED = 1
}
e_joystick_axis_polarity;


/**
 * Enumère les status de l'axe
 */
typedef enum
{
	JOYSTICK_AXIS_STATUS_OK = 0,
	JOYSTICK_AXIS_ADC_ERROR = 1,
	JOYSTICK_AXIS_RES_ERROR = 2,
	JOYSTICK_AXIS_POL_ERROR = 3
}
e_joystick_axis_status;

/* Structures ============================================================= */

/**
 * Structure modélisant un axe de joystick
 */
typedef struct
{
	/***************************
	 * Variables en read-only *
	 ***************************/
	int16_t value;								// Valeur de l'axe
	uint8_t has_changed;						// Flag indiquant que la valeur a changé
	e_joystick_axis_status status;				// Statut de l'axe

	/***************************
	 * Variables en read-write *
	 ***************************/
	adc_id_e adc_channel;						// Voie d'ADC utilisée pour sampler la valeur de l'axe
	e_joystick_axis_resolution resolution;		// Nombre de bits sur lesquels la valeur finale est codée (bit de signe inclus)
	e_joystick_axis_polarity polarity;			// Inverse la polarité de l'axe

}
st_joystick_axis;

/* External function prototypes =========================================== */

e_joystick_axis_status JOYSTICK_AXIS_get_value(st_joystick_axis * axis);

#endif /* BSP_JOYSTICK_JOYSTICK_AXIS_H_ */
