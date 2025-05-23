/*********************************** CIRCUIT **********************************\
| General:                                                                     |
|	* TTP229 VCC to pin VCC                                                    |
|	* TTP229 GND to pin GND                                                    |
|	* TTP229 SCL to any pin you choose...                                      |
|	* TTP229 SDO to any pin you choose...                                      |
|                                                                              |
| 16 Buttons Mode (else 8 Buttons Mode):                                       |
|	* TTP229 TP2 to GND via 1 Megohm resistor!                                 |
|	# Must use the ReadKey16, GetKeys16... else use the ReadKey8, GetKeys8...  |
|                                                                              |
| Multi Keys Mode (else Single key Mode):                                      |
|	* TTP229 TP3 to GND via 1 Megohm resistor!                                 |
|	* TTP229 TP4 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 64Hz Sampling Rate (else 8Hz Sampling Rate):                                 |
|	* TTP229 TP5 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 2ms Wake Up Rate (else 4ms Wake Up Rate):                                    |
|	* TTP229 TP6 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| 60sec Key On Timeout (else No Key On Timeout):                               |
|	* TTP229 TP7 to GND via 1 Megohm resistor!                                 |
|                                                                              |
| Important:                                                                   |
|	* Must reconnect the TTP229 power so the mode changes will take effect     |
|	* The 1 Megohm resistors already exist on some TTP229 modules              |
\******************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifndef TTP229_h
#define TTP229_h

class TTP229
{
	public:
		TTP229(uint8_t sclPin, uint8_t sdoPin);
		uint8_t
			ReadKey8(),
			GetKey8(),
			ReadKeys8(),
			GetKeys8(),
			ReadKey16(),
			GetKey16();
		uint16_t
			ReadKeys16(),
			GetKeys16();
	private:
		void
			WaitForTouch(),
			Key8(),
			Keys8(),
			Key16(),
			Keys16();
		bool
			IsTouch(),
			GetBit();
			
		uint8_t _sclPin, _sdoPin;
		uint8_t _key8, _keys8, _key16;
		uint16_t _keys16;
};

#endif