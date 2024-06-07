/*
 * data_transmit.c
 *
 *  Created on: May 14, 2024
 *      Author: l.marcolini
 */


/* Includes =============================================================== */

#include <assert.h>
#include "emitter.h"
#include "crc.h"

/* Define ================================================================= */

#define DATA_FRAME_SIZE			6
#define DATA_FRAME_END_CHAR		'\n'

/* Enumeration ============================================================*/

/* Structure ============================================================== */

// Trame de données envoyée sur le bus de communication
typedef union
{
	uint8_t bytes[DATA_FRAME_SIZE];

	struct __attribute__((packed))
	{
		int8_t x;
		int8_t y;
		int8_t z;
		uint16_t crc16;
		uint8_t end_char;
	}
	fields;
}
u_data_frame;

// L'instruction ci-dessous teste que la taille du buffer équivaut bien à la taille attendue des champs concaténés
static_assert(offsetof(u_data_frame, fields.end_char) != sizeof(((u_data_frame){0}).bytes), "Alignement incorrect dans u_data_frame");

/* Static variables ======================================================= */

// Instance de l'axe X
static st_joystick_axis X_axis =
{
	.adc_channel = ADC_0,
	.resolution = JOYSTICK_AXIS_RES_5b,
	.polarity = JOYSTICK_AXIS_POL_NON_INVERTED
};

// Instance de l'axe Y
static st_joystick_axis Y_axis =
{
	.adc_channel = ADC_1,
	.resolution = JOYSTICK_AXIS_RES_5b,
	.polarity = JOYSTICK_AXIS_POL_NON_INVERTED
};

// Instance de l'axe Z
static st_joystick_axis Z_axis =
{
	.adc_channel = ADC_4,
	.resolution = JOYSTICK_AXIS_RES_5b,
	.polarity = JOYSTICK_AXIS_POL_NON_INVERTED
};

// Instance de la trame de données
static u_data_frame data_frame =
{
	// Les valeurs par défaut sont des caractères ISO-8859-1 (Latin 1)
	// Facile à lire sur un terminal série type PuTTY...
	.fields =
	{
		.x = 'X',
		.y = 'Y',
		.z = 'Z',
		.crc16 = 13237,
		.end_char = DATA_FRAME_END_CHAR
	}
};

// Flag d'initialisation du module
static bool_e init_flag = FALSE;

// Canal UART utilisé
static uart_id_e uart_channel;

/* Static function prototype =============================================== */

/* Function  ============================================================== */

/**
 * @func 	void EMITTER_init(uart_id_e uart_id, uint32_t baudrate)
 * @brief	Permet d'initialiser le module d'émission
 * @param	uart_id : canal UART
 * @param	baudrate : vitesse en bauds/s
 **/
void EMITTER_init(uart_id_e uart_id, uint32_t baudrate)
{
	// Initialise le module CRC
	CRC_init();

	// Configure l'UART
	uart_channel = uart_id;
	UART_init(uart_channel, baudrate);

	// Lève le flag d'initialisation
	init_flag = TRUE;
}


/**
 * @func 	void EMITTER_routine(e_data_refresh_state refresh)
 * @brief	Routine d'émission à appeler régulièrement
 * @param	refresh : indiques si les données à envoyées doivent être ré-actualisées
 **/
void EMITTER_routine(e_data_refresh_state refresh)
{
	// Si le module n'est pas initialisé -> sortie
	if (init_flag == FALSE) return;

	if (refresh == DATA_TRANSMIT_REFRESHED_VALUES)
	{
		// Acquisition des valeurs de chaque axe
		JOYSTICK_AXIS_get_value(&X_axis);
		JOYSTICK_AXIS_get_value(&Y_axis);
		JOYSTICK_AXIS_get_value(&Z_axis);

		// Stockage des valeurs dans l'union formant la trame
		data_frame.fields.x = (int8_t)X_axis.value;
		data_frame.fields.y = (int8_t)Y_axis.value;
		data_frame.fields.z = (int8_t)Z_axis.value;

		// Calcul du CRC
		data_frame.fields.crc16 = (CRC_calculate_from_8b(data_frame.bytes, 3) & 0xFFFF);
	}

	// Envoi de la trame sur le canal uart sélectionné
	UART_puts(uart_channel, data_frame.bytes, DATA_FRAME_SIZE);
}

