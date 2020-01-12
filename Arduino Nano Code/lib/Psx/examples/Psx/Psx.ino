/*  PSX Controller Decoder Library (Psx.pde)
	Written by: Kevin Ahrendt June 22nd, 2008
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10

#define LEDPin 13

Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response

void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
  pinMode(LEDPin, OUTPUT);                                // Establishes LEDPin as an output so the LED can be seen
  Serial.begin(9600);
}

void loop()
{
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
                                                          // the button data
  Serial.println(data);                                   // Display the returned numeric value
  if (data & psxR2)                                       // If the data anded with a button's hex value is true,
                                                          // it signifies the button is pressed. Hex values for each
                                                          // button can be found in Psx.h
  {
    digitalWrite(LEDPin, HIGH);                           // If button is pressed, turn on the LED
  }
  else
  {
    digitalWrite(LEDPin, LOW);                            // If the button isn't pressed, turn off the LED
  }
  delay(20);
}
