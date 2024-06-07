/*
 * joystick_axis.c
 *
 *  Created on: May 9, 2024
 *  Author: l.marcolini ESEO E3A
 */

/* Includes =============================================================== */

#include "joystick_axis.h"

/* Define ================================================================= */

#define ADC_RESOLUTION_BITS	12

/* Enumeration ============================================================*/

/* Structure ============================================================== */

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

static e_joystick_axis_status JOYSTICK_axis_check_config(st_joystick_axis * axis);

/* Function  ============================================================== */

/**
 * @brief Permet de v�rifier le statut de l'axe sp�cifi� en param�tre
 * @param pointeur sur une structure st_joystick_axis d�crivant un axe
 * @return statut de l'axe
 */
static e_joystick_axis_status JOYSTICK_axis_check_config(st_joystick_axis * axis)
{
	if (ADC_getValue(axis->adc_channel) == -1)
	{
		axis->status = JOYSTICK_AXIS_ADC_ERROR;
	}
	else if (axis->resolution < JOYSTICK_AXIS_RES_2b || axis->resolution > JOYSTICK_AXIS_RES_12b)
	{
		axis->status = JOYSTICK_AXIS_RES_ERROR;
	}
	else if (axis->polarity > JOYSTICK_AXIS_POL_INVERTED)
	{
		axis->status = JOYSTICK_AXIS_POL_ERROR;
	}
	else
	{
		axis->status = JOYSTICK_AXIS_STATUS_OK;
	}

	return axis->status;
}


/**
 * @brief Obtient la position sur l'axe pass� en entr�e
 * @param pointeur sur une structure st_joystick_axis d�crivant un axe
 */
e_joystick_axis_status JOYSTICK_AXIS_get_value(st_joystick_axis * axis)
{
	axis->has_changed = 0;

	if (JOYSTICK_axis_check_config(axis) == JOYSTICK_AXIS_STATUS_OK)
	{
		/* Sampling */

		uint16_t adc_value = ADC_getValue(axis->adc_channel);

		/* Conversion en valeur sign�e (moiti� sup�rieure positive / moiti� inf�rieure n�gative) */

		int16_t normalized_value = adc_value - (0x1 << (ADC_RESOLUTION_BITS - 1));

		/* Downscaling */

		normalized_value >>= ADC_RESOLUTION_BITS - axis->resolution;

		// Permet d'obtenir le m�me nombre de valeurs en n�gatif et en positif (+0 et -0)
		if (normalized_value < 0)
		{
			normalized_value += 1;
		}

		/* Inversion de la polarit� */

		if (axis->polarity == JOYSTICK_AXIS_POL_INVERTED)
		{
			normalized_value = -normalized_value;
		}

		/* Attribue la valeur finale */

		if (normalized_value != axis->value)
		{
			axis->value = normalized_value;
			axis->has_changed = 1;
		}
	}

	return axis->status;
}
