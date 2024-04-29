/**
 * \file    	joystick.c
 * \brief   	Gestion des joysticks
 * \details
 */

/* Includes =============================================================== */

#include "adc.h"
#include "joystick.h"

/* Define ================================================================= */

/* Enumeration ============================================================*/

/* Structure ============================================================== */

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

/* Function  ============================================================== */

e_axis_sampling_error JOYSTICK_GetAxisValue(st_joystick_axis* axis)
{
	// Si la voie d'ADC utilis�e est non d�finie : erreur
	if (axis->adc_channel > ADC_CHANNEL_17)
		return AXIS_SAMPLING_ADC_CHANNEL_ERROR;

	// Si la r�solution est trop grande : erreur
	if (axis->resolution > ADC_RESOLUTION_BITS)
		return AXIS_SAMPLING_RESOLUTION_ERROR;

	// Sampling des valeurs via le channel sp�cifi� de l'ADC1
	uint16_t adc_value = ADC1_GetSample(axis->adc_channel);

	// Transformation des valeurs brutes en valeurs non sign�es de r�solution axis->resolution
	uint16_t axis_normalized_value = adc_value >> (ADC_RESOLUTION_BITS - axis->resolution);

	// D�termination de la valeur absolue maximale dans une direction
	uint16_t axis_max_abs_val = (0x1 << (axis->resolution - 1)) - 1;

	// D�termination du signe
	axis->sign = (axis_normalized_value > axis_max_abs_val);

	// Calcul de la position relative par rapport � la valeur milieu
	if (axis->sign)
	{
		axis->delta = axis_normalized_value - axis_max_abs_val - 1;
	}
	else
	{
		axis->delta = axis_max_abs_val - axis_normalized_value;
	}

	// Inversion de la polarit� si d�fini
	if (axis->polarity == AXIS_INVERTED)
	{
		axis->sign = ~(axis->sign);
	}

	// Sampling r�alis� sans erreur
	return AXIS_SAMPLING_SUCCESS;
}
