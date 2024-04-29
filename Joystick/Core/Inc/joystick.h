/**
 * \file    	joystick.h
 * \brief   	Gestion des joysticks
 * \details
 */


#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

/* Includes =============================================================== */

#include "adc.h"

/* Define ================================================================= */

/* Enumeration ============================================================*/

typedef enum
{
	AXIS_NEGATIVE = 0,
	AXIS_POSITIVE = 1
}
e_axis_direction;

typedef enum
{
	AXIS_NON_INVERTED = 0,
	AXIS_INVERTED = 1
}
e_axis_polarity;

typedef enum
{
	AXIS_SAMPLING_SUCCESS = 0,
	AXIS_SAMPLING_ADC_CHANNEL_ERROR = 1,
	AXIS_SAMPLING_RESOLUTION_ERROR = 2
}
e_axis_sampling_error;

/* Structure ============================================================== */

typedef struct
{
	uint32_t adc_channel;		// Voie d'ADC utilisée pour samplé la valeur de l'axe
	uint8_t resolution;			// Nombre de valeurs totale de l'axe
	uint16_t delta;				// Écart absolu entre le milieu de l'axe et la valeur mesurée
	e_axis_direction sign;		// Direction du delta
	e_axis_polarity polarity;	// Inverse le signe

	// Paramètres optionnels pour ajuster l'ergonomie
	// uint16_t deadzone
	// uint16_t sensibility
}
st_joystick_axis;

typedef struct
{
	st_joystick_axis x;
	st_joystick_axis y;
}
st_joystick;

/* External function prototype =============================================== */

e_axis_sampling_error JOYSTICK_GetAxisValue(st_joystick_axis* axis);

#endif /* INC_JOYSTICK_H_ */
