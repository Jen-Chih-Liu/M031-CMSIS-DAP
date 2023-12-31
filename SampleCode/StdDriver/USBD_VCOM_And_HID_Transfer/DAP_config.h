#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__


#define CPU_CLOCK               48000000        ///< Specifies the CPU Clock in Hz


#define IO_PORT_WRITE_CYCLES    2               ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0


#define DAP_SWD                 1               ///< SWD Mode:  1 = available, 0 = not available

#define DAP_JTAG                0               ///< JTAG Mode: 0 = not available

#define DAP_JTAG_DEV_CNT        8               ///< Maximum number of JTAG devices on scan chain

#define DAP_DEFAULT_PORT        1               ///< Default JTAG/SWJ Port Mode: 1 = SWD, 2 = JTAG.

#define DAP_DEFAULT_SWJ_CLOCK   4000000         ///< Default SWD/JTAG clock frequency in Hz.


/// Maximum Package Size for Command and Response data.
#define DAP_PACKET_SIZE         64              ///< USB: 64 = Full-Speed, 1024 = High-Speed.

/// Maximum Package Buffers for Command and Response data.
#define DAP_PACKET_COUNT        1              ///< Buffers: 64 = Full-Speed, 4 = High-Speed.


/// Indicate that UART Serial Wire Output (SWO) trace is available.
#define SWO_UART                0               ///< SWO UART:  1 = available, 0 = not available

#define SWO_UART_MAX_BAUDRATE   115200U       ///< SWO UART Maximum Baudrate in Hz

/// Indicate that Manchester Serial Wire Output (SWO) trace is available.
#define SWO_MANCHESTER          0               ///< SWO Manchester:  1 = available, 0 = not available

#define SWO_BUFFER_SIZE         4096U           ///< SWO Trace Buffer Size in bytes (must be 2^n)

#define SWO_STREAM              0               ///< SWO Streaming Trace: 1 = available, 0 = not available.

/// Clock frequency of the Test Domain Timer. Timer value is returned with \ref TIMESTAMP_GET.
#define TIMESTAMP_CLOCK         1000000U      ///< Timestamp clock in Hz (0 = timestamps not supported).

/// Debug Unit is connected to fixed Target Device.
#define TARGET_DEVICE_FIXED     0               ///< Target Device: 1 = known, 0 = unknown;

#if TARGET_DEVICE_FIXED
#define TARGET_DEVICE_VENDOR    ""              ///< String indicating the Silicon Vendor
#define TARGET_DEVICE_NAME      ""              ///< String indicating the Target Device
#endif


//**************************************************************************************************
/**
JTAG I/O Pin                 | SWD I/O Pin          | CMSIS-DAP Hardware pin mode
---------------------------- | -------------------- | ---------------------------------------------
TCK: Test Clock              | SWCLK: Clock         | Output Push/Pull
TMS: Test Mode Select        | SWDIO: Data I/O      | Output Push/Pull; Input (for receiving data)
TDI: Test Data Input         |                      | Output Push/Pull
TDO: Test Data Output        |                      | Input
nTRST: Test Reset (optional) |                      | Output Open Drain with pull-up resistor
nRESET: Device Reset         | nRESET: Device Reset | Output Open Drain with pull-up resistor

DAP Hardware I/O Pin Access Functions
*/
#include "NuMicro.h"


// Configure DAP I/O pins ------------------------------

#define SWCLK_PORT			PA
#define SWCLK_PIN			1
#define SWDIO_PORT			PA
#define SWDIO_PIN			2

#define SWD_SWCLK   		PA1
#define SWD_SWDIO   		PA2

#define SWD_RST_PORT		PA
#define SWD_RST_PIN			0

#define SWD_RST				PA0


/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
 - TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
 - TDO to input mode.
*/
static void PORT_JTAG_SETUP(void)
{
#if (DAP_JTAG != 0)
#endif
}

/** Setup SWD I/O pins: SWCLK, SWDIO, and nRESET.
 - SWCLK, SWDIO, nRESET to output mode and set to default high level.
*/
static void PORT_SWD_SETUP(void)
{
    GPIO_SetMode(SWCLK_PORT, (1 << SWCLK_PIN), GPIO_MODE_OUTPUT); SWD_SWCLK = 1;
	GPIO_SetMode(SWDIO_PORT, (1 << SWDIO_PIN), GPIO_MODE_OUTPUT); SWD_SWDIO = 1;
	
	GPIO_SetMode(SWD_RST_PORT, (1 << SWD_RST_PIN), GPIO_MODE_OUTPUT); SWD_RST = 1;
	
}

/** Disable JTAG/SWD I/O Pins.
 - TCK/SWCLK, TMS/SWDIO, TDI, TDO, nTRST, nRESET to High-Z mode.
*/
static void PORT_OFF(void)
{
	GPIO_SetMode(SWCLK_PORT, (1 << SWCLK_PIN), GPIO_MODE_INPUT);
	GPIO_SetMode(SWDIO_PORT, (1 << SWDIO_PIN), GPIO_MODE_INPUT);
	
	GPIO_SetMode(SWD_RST_PORT, (1 << SWD_RST_PIN), GPIO_MODE_INPUT);
}


// SWCLK/TCK I/O pin -------------------------------------

// Current status of the SWCLK/TCK DAP hardware I/O pin
static __inline uint32_t PIN_SWCLK_TCK_IN(void)
{
     //return (SWD_GPIO->PMD & (3 << (PIN_SWCLK << 1))) ? 1 : 0;
	return  SWD_SWCLK;
}

static __inline void PIN_SWCLK_TCK_SET(void)
{
	SWD_SWCLK = 1;
}

static __inline void PIN_SWCLK_TCK_CLR(void)
{
        SWD_SWCLK = 0;
}


// SWDIO/TMS Pin I/O --------------------------------------

// Current status of the SWDIO/TMS DAP hardware I/O pin
static __inline uint32_t PIN_SWDIO_TMS_IN(void)
{
    return SWD_SWDIO;
}

static __inline void PIN_SWDIO_TMS_SET(void)
{
     SWD_SWDIO = 1;
}

static __inline void PIN_SWDIO_TMS_CLR(void)
{
    SWD_SWDIO = 0;
}


static __inline uint32_t PIN_SWDIO_IN(void)
{
    return SWD_SWDIO;
}

static __inline void PIN_SWDIO_OUT(uint32_t bit)
{
     SWD_SWDIO = bit;
}

static __inline void PIN_SWDIO_OUT_ENABLE(void)
{
	GPIO_SetMode(SWDIO_PORT, (1 << SWDIO_PIN), GPIO_MODE_OUTPUT);
}

static __inline void PIN_SWDIO_OUT_DISABLE(void)
{
    GPIO_SetMode(SWDIO_PORT, (1 << SWDIO_PIN), GPIO_MODE_INPUT);
}


// TDI Pin I/O ---------------------------------------------

static __inline uint32_t PIN_TDI_IN(void)
{
#if (DAP_JTAG != 0)
#endif
	return 0;
}

static __inline void PIN_TDI_OUT(uint32_t bit)
{
#if (DAP_JTAG != 0)
#endif
}


// TDO Pin I/O ---------------------------------------------

static __inline uint32_t PIN_TDO_IN(void)
{
#if (DAP_JTAG != 0)
#endif
	return 0;
}


// nTRST Pin I/O -------------------------------------------

static __inline uint32_t PIN_nTRST_IN(void)
{
    return 0;
}

static __inline void PIN_nTRST_OUT(uint32_t bit)
{
}

// nRESET Pin I/O------------------------------------------
static __inline uint32_t PIN_nRESET_IN(void)
{
    return SWD_RST;
}

extern uint8_t swd_write_word(uint32_t addr, uint32_t val);
static __inline void PIN_nRESET_OUT(uint32_t bit)
{
	SWD_RST = bit;
	
	if(bit == 0)
	{
		swd_write_word((uint32_t)&SCB->AIRCR, ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk));
	}
}


//**************************************************************************************************
/** Connect LED: is active when the DAP hardware is connected to a debugger
    Running LED: is active when program execution in target started
*/

static __inline void LED_CONNECTED_OUT(uint32_t bit)
{
}

static __inline void LED_RUNNING_OUT(uint32_t bit)
{
}


__STATIC_INLINE uint32_t TIMESTAMP_GET (void) {
	//return (DWT->CYCCNT) / (CPU_CLOCK / TIMESTAMP_CLOCK);
	return 0;
}

static void DAP_SETUP(void)
{
	PORT_OFF();
}


extern uint8_t swd_write_word(uint32_t addr, uint32_t val);
static uint32_t RESET_TARGET(void)
{
	swd_write_word((uint32_t)&SCB->AIRCR, ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk));
	
    return 1;	// change to '1' when a device reset sequence is implemented
}





#include <string.h>

/** Get Vendor ID string.
\param str Pointer to buffer to store the string.
\return String length.
*/
__STATIC_INLINE uint8_t DAP_GetVendorString (char *str) {
	memcpy((unsigned char*)str, "XIVN1987", sizeof("XIVN1987"));
	return sizeof("XIVN1987");
}

/** Get Product ID string.
\param str Pointer to buffer to store the string.
\return String length.
*/
__STATIC_INLINE uint8_t DAP_GetProductString (char *str) {
	memcpy((unsigned char*)str, "XV-Link CMSIS-DAP", sizeof("XV-Link CMSIS-DAP"));
	return sizeof("XV-Link CMSIS-DAP");
}

/** Get Serial Number string.
\param str Pointer to buffer to store the string.
\return String length.
*/
__STATIC_INLINE uint8_t DAP_GetSerNumString (char *str) {
    memcpy((unsigned char*)str, "002201110000", sizeof("002201110000"));
	return sizeof("002201110000");
}

/** Get firmware version string.
\param str Pointer to buffer to store the string.
\return String length.
*/
__STATIC_INLINE uint8_t DAP_ProductFirmwareVerString (char *str) {
    memcpy((unsigned char*)str, "V1.0", sizeof("V1.0"));
	return sizeof("V1.0");
}


#endif // __DAP_CONFIG_H__
