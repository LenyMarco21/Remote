/**
 * \file    	rf_com.c
 * \brief   	transmission RF
 * \details
 */

/* Includes =============================================================== */

#include <rf_com.h>
#include <usart.h>
#include <controller.h>

/* Define ================================================================= */

/* Enumeration ============================================================*/

typedef enum
{
	PARITY_ODD = 0,
	PARITY_EVEN = 1
}
e_parity;

/* Structure ============================================================== */

typedef union
{
    uint8_t bytes[4];

    struct
    {
    	int16_t x		:5;
		int16_t y		:5;
		int16_t z		:5;
		uint16_t parity	:1;
		uint16_t crc16	:16;
    }
    bitfields __attribute__((__packed__));
}
u_data_2_bytes;

typedef union
{
    uint8_t bytes[4];

    struct
    {
    	int8_t x		:8;
		int8_t y		:8;
		int8_t z		:8;
		uint16_t crc16	:16;
    }
    bitfields __attribute__((__packed__));
}
u_data_3_bytes;

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

/* Function  ============================================================== */

void RF_SendAxisData(uint8_t resolution)
{
	CONTROLLER_SetAxisResolution(X_AXIS, resolution);
	CONTROLLER_SetAxisResolution(Y_AXIS, resolution);
	CONTROLLER_SetAxisResolution(Z_AXIS, resolution);

	if (resolution <= AXIS_RESOLUTION_5_BITS)
	{
		u_data_2_bytes data = {0};

		data.x = CONTROLLER_GetAxisValue(X_AXIS);
		data.y = CONTROLLER_GetAxisValue(Y_AXIS);
		data.z = CONTROLLER_GetAxisValue(Z_AXIS);

		uint32_t concat_values = data.bytes[0] + (data.bytes[1] << 8);
		data.parity = GetOddParity(concat_values);
		data.crc16 = CRC_calculate(data.bytes, 2);

		// uart send

	}
	else if (resolution <= AXIS_RESOLUTION_8_BITS)
	{
		u_data_3_bytes data = {0};

		data.x = CONTROLLER_GetAxisValue(X_AXIS);
		data.y = CONTROLLER_GetAxisValue(Y_AXIS);
		data.z = CONTROLLER_GetAxisValue(Z_AXIS);

		uint32_t concat_values = data.bytes[0] + (data.bytes[1] << 8) + (data.bytes[2] << 16);
		data.parity = GetOddParity(concat_values);
		data.crc16 = CRC_calculate(data.bytes, 3);

		// uart send
	}
}

// Impair
uint8_t GetOddParity(uint32_t value)
{
	uint8_t count = 0;

	for (uint8_t i = 0; i < 32; i++)
	{
		count += (value & 0x1);
		value >>= 1;
	}

	return count & 0x1;
}
