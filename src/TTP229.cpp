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

#include "TTP229.h"

TTP229::TTP229(uint8_t sclPin, uint8_t sdoPin)
{
	_sclPin = sclPin;
	_sdoPin = sdoPin;
	
	pinMode(_sclPin , OUTPUT);
	pinMode(_sdoPin , INPUT);
	
	digitalWrite(_sclPin, HIGH);
}

uint8_t TTP229::ReadKey8()
{
	WaitForTouch();
	Key8();
	return _key8;
}
uint8_t TTP229::GetKey8()
{
	if (IsTouch()) Key8();
	return _key8;
}
uint8_t TTP229::ReadKeys8()
{
	WaitForTouch();
	Keys8();
	return _keys8;
}
uint8_t TTP229::GetKeys8()
{
	if (IsTouch()) Keys8();
	return _keys8;
}
uint8_t TTP229::ReadKey16()
{
	WaitForTouch();
	Key16();
	return _key16;
}
uint8_t TTP229::GetKey16()
{
	if (IsTouch()) Key16();
	return _key16;
}
uint16_t TTP229::ReadKeys16()
{
	WaitForTouch();
	Keys16();
	return _keys16;
}
uint16_t TTP229::GetKeys16()
{
	if (IsTouch()) Keys16();
	return _keys16;
}

void TTP229::Key8()
{
	_key8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (GetBit()) _key8 = i + 1;
	delay(2); // Tout
}
void TTP229::Keys8()
{
	_keys8 = 0;
	for (uint8_t i = 0; i < 8; i++)
		if (GetBit()) _keys8 |= 1 << i;
	delay(2); // Tout
}
void TTP229::Key16()
{
	_key16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (GetBit()) _key16 = i + 1;
	delay(2); // Tout
}
void TTP229::Keys16()
{
	_keys16 = 0;
	for (uint8_t i = 0; i < 16; i++)
		if (GetBit()) _keys16 |= 1 << i;
	delay(2); // Tout
}

bool TTP229::GetBit()
{
	digitalWrite(_sclPin, LOW);
	delayMicroseconds(2); // 500KHz
	bool retVal = !digitalRead(_sdoPin);
	digitalWrite(_sclPin, HIGH);
	delayMicroseconds(2); // 500KHz
	return retVal;
}

bool TTP229::IsTouch()
{
	uint16_t timeout = 5000; // 50ms timeout
	while (digitalRead(_sdoPin)) // DV LOW
	{
		if (--timeout == 0) return false;
		delayMicroseconds(10);
	}
	while (!digitalRead(_sdoPin)) // DV HIGH
	{
		if (--timeout == 0) return false;
		delayMicroseconds(10);
	}
	delayMicroseconds(10); // Tw
	return true;
}
void TTP229::WaitForTouch()
{
	while (digitalRead(_sdoPin)); // DV LOW
	while (!digitalRead(_sdoPin)); // DV HIGH
	delayMicroseconds(10); // Tw
}