/*
 * data_transmit.h
 *
 *  Author: l.marcolini
 */

#ifndef EMITTER_H_
#define EMITTER_H_

/* Includes =============================================================== */

#include "config.h"
#include "stm32f1_uart.h"
#include "macro_types.h"
#include "Joystick/joystick_axis.h"

/* Defines ================================================================ */

/* Enumerations ============================================================*/

typedef enum
{
	DATA_TRANSMIT_PREVIOUS_VALUES = 0,
	DATA_TRANSMIT_REFRESHED_VALUES = 1
}
e_data_refresh_state;

/* Structures ============================================================= */

/* External function prototypes =========================================== */

void EMITTER_init(uart_id_e uart_id, uint32_t baudrate);

void EMITTER_routine(e_data_refresh_state refresh);

#endif /* EMITTER_H_ */
