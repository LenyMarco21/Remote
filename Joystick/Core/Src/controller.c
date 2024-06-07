/**
 * \file    	controller.c
 * \brief   	Manette
 * \details
 */

/* Includes =============================================================== */

#include <controller.h>
#include "adc.h"

/* Define ================================================================= */

/* Enumeration ============================================================*/

/* Structure ============================================================== */

typedef struct
{
	uint32_t adc_channel;							// Voie d'ADC utilisée pour sampler la valeur de l'axe
	e_controller_axis_resolution resolution;		// Nombre de bits sur lesquels la valeur finale est codée
	e_controller_axis_polarity polarity;			// Inverse la polarité de l'axe
}
st_axis;

/* Static variables ======================================================= */
/*
static st_axis x =
{
	.adc_channel = CHANNEL_0,
	.resolution = AXIS_RESOLUTION_5_BITS,
	.polarity = AXIS_NON_INVERTED
};

static st_axis y =
{
	.adc_channel = CHANNEL_1,
	.resolution = AXIS_RESOLUTION_5_BITS,
	.polarity = AXIS_NON_INVERTED,
};

static st_axis z =
{
	.adc_channel = CHANNEL_2,
	.resolution = AXIS_RESOLUTION_5_BITS,
	.polarity = AXIS_NON_INVERTED,
};
*/
/* Static function prototype =============================================== */

int16_t GetAxisValue(st_axis* axis);

/* Function  ============================================================== */

/**
 * @brief Obtient la position sur l'axe passé en entrée
 * @param pointeur sur une structure st_joystick_axis décrivant un axe
 * @return status sur l'execution de la fonction
 */
int16_t GetAxisValue(st_axis* axis)
{
	/* Contrôle des valeurs d'entrée */

	if (axis->adc_channel > ADC_CHANNEL_15)
	{
		return 0;
	}

	if (axis->resolution < AXIS_RESOLUTION_2_BITS)
	{
		axis->resolution = AXIS_RESOLUTION_2_BITS;
	}
	else if (axis->resolution > AXIS_RESOLUTION_12_BITS)
	{
		axis->resolution = AXIS_RESOLUTION_12_BITS;
	}

	/* Sampling */

	uint16_t adc_value = ADC1_GetSample(axis->adc_channel);

	/* Conversion en valeur signée (moitié supérieure positive / moitié inférieure négative) */

	int16_t normalized_value = adc_value - (0x1 << (ADC_RESOLUTION_BITS - 1));

	/* Downscaling */

	//normalized_value >>= ADC_RESOLUTION_BITS - resolution;

	// Permet d'obtenir le même nombre de valeurs en négatif et en positif (0+ et 0-)
	if (normalized_value < 0)
	{
		normalized_value += 1;
	}

	/* Inversion de la polarité */

	if (axis->polarity == AXIS_INVERTED)
	{
		normalized_value = -normalized_value;
	}

	return normalized_value;
}

int16_t CONTROLLER_GetAxisValue(e_controller_axis axis)
{
	switch (axis)
	{
		case X_AXIS:
			return GetAxisValue(&x);

		case Y_AXIS:
			return GetAxisValue(&y);

		case Z_AXIS:
			return GetAxisValue(&z);

		default:
			return 0;
	}
}

e_controller_status CONTROLLER_SetAxisResolution(e_controller_axis axis, e_controller_axis_resolution resolution)
{
	switch (axis)
	{
		case X_AXIS:
			x.resolution = resolution;
			break;

		case Y_AXIS:
			y.resolution = resolution;
			break;

		case Z_AXIS:
			z.resolution = resolution;
			break;

		default:
			return CONTROLLER_CONFIG_ERROR;
	}

	return CONTROLLER_CONFIG_SUCCESS;
}

e_controller_status CONTROLLER_SetAxisPolarity(e_controller_axis axis, e_controller_axis_polarity polarity)
{
	switch (axis)
	{
		case X_AXIS:
			x.polarity = polarity;
			break;

		case Y_AXIS:
			y.polarity = polarity;
			break;

		case Z_AXIS:
			z.polarity = polarity;
			break;

		default:
			return CONTROLLER_CONFIG_ERROR;
	}

	return CONTROLLER_CONFIG_SUCCESS;
}
