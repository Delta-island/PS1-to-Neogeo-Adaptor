/*  

============================================
PS1 to Neogeo Controller V1.0
Written by Delta-island.com, October 2019
============================================

    This program allow to Use Joypad and Joystick Asciiware playstation 1 on NeoGoo AES/MVS

    This program use PSX Controller Decoder Library, you can download at this adress :
    https://playground.arduino.cc/Main/PSXLibrary/
    Big thanks to Kevin Ahrendt for the "PSX Controller Decoder Library"

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

// Button Hex Representations:
#define psxLeft    0x0001 
#define psxDown   0x0002
#define psxRight  0x0004
#define psxUp   0x0008
#define psxStrt   0x0010
#define psxSlct   0x0080

#define psxSqu    0x0100
#define psxX    0x0200
#define psxO    0x0400
#define psxTri    0x0800
#define psxR1   0x1000
#define psxL1   0x2000
#define psxR2   0x4000
#define psxL2   0x8000


*/

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 12
#define cmndPin 10
#define attPin 5
#define clockPin 4

#define UP 7
#define DOWN 6
#define LEFT A5
#define RIGHT A4
#define Strt_Button 2
#define Slct_Button 3
#define A_Button A3
#define B_Button A2
#define C_Button A1
#define D_Button A0

byte mode = 0; //   Joypad Mode = 0  Joystick Mode = 1

Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response

void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 11);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
  pinMode(UP, INPUT);                                // Establishes LEDPin as an output so the LED can be seen
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(Strt_Button, INPUT);
  pinMode(Slct_Button, INPUT);
  pinMode(A_Button, INPUT);
  pinMode(B_Button, INPUT);
  pinMode(C_Button, INPUT);
  pinMode(D_Button, INPUT);
  
  // Serial.begin(115200);
}

void loop()
{
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
                                                          // the button data

  if (data == 12416) // 12416 = Data L1 + R1 + SELECT
    {
    if (mode == 0)
      { 
        mode = 1;
        // Serial.println("Joystick Mode");
        delay (300);
      }
     else
     { 
        mode = 0;
        // Serial.println("Joypad Mode");
        delay (300);
      }
    }              
                                                          
  //Serial.println(data);       // Display the returned numeric value
//---------------------Bouton A---------------------------- 
if (data & psxX && (mode == 0))                                      
 {
    // Serial.println("A - Joypad");
    pinMode(A_Button, OUTPUT);
    digitalWrite(A_Button, LOW);
  }
else if  (data & psxL2 && (mode == 1))                                       
 {
    // Serial.println("A - Joystick");
    pinMode(A_Button, OUTPUT);
    digitalWrite(A_Button, LOW);
  }
else
  { 
    pinMode (A_Button, INPUT);   // Mise en mode haute impedance de la PIN
  }

//---------------------Bouton B---------------------------- 
if (data & psxO && (mode == 0))                                      
 {
    // Serial.println("B - Joypad");
    pinMode(B_Button, OUTPUT);
    digitalWrite(B_Button, LOW);
  }
else if  (data & psxX && (mode == 1))                                       
 {
    // Serial.println("B - Joystick");
    pinMode(B_Button, OUTPUT);
    digitalWrite(B_Button, LOW);
  }
else
  { 
    pinMode (B_Button, INPUT);   // Mise en mode haute impedance de la PIN
  }
  
//---------------------Bouton C---------------------------- 
if (data & psxSqu && (mode == 0))                                      
 {
    // Serial.println("C - Joypad");
    pinMode(C_Button, OUTPUT);
    digitalWrite(C_Button, LOW);
  }
else if  (data & psxO && (mode == 1))                                       
 {
    // Serial.println("C - Joystick");
    pinMode(C_Button, OUTPUT);
    digitalWrite(C_Button, LOW);
  }
else
  { 
    pinMode (C_Button, INPUT);   // Mise en mode haute impedance de la PIN
  }

//---------------------Bouton D---------------------------- 
if (data & psxTri && (mode == 0))                                      
 {
    // Serial.println("D- Joypad");
    pinMode(D_Button, OUTPUT);
    digitalWrite(D_Button, LOW);
  }
else if  (data & psxR2 && (mode == 1))                                       
 {
    // Serial.println("D - Joystick");
    pinMode(D_Button, OUTPUT);
    digitalWrite(D_Button, LOW);
  }
else
  { 
    pinMode (D_Button, INPUT);   // Mise en mode haute impedance de la PIN
  }




/* Zonne commune Joypad & Joystick */
//---------------------Bouton Start---------------------------- 
if (data & psxStrt)                                      
 {
    // Serial.println("Strt_Button");
    pinMode(Strt_Button, OUTPUT);
    digitalWrite(Strt_Button, LOW);
  }
else
  { 
    pinMode (Strt_Button, INPUT);   // Mise en mode haute impedance de la PIN
  } 

//---------------------Bouton Select---------------------------- 
  if (data & psxSlct)                                       
 {
    // Serial.println("Slct_Button");
    pinMode(Slct_Button, OUTPUT);
    digitalWrite(Slct_Button, LOW);
  }
else
  { 
    pinMode (Slct_Button, INPUT);   // Mise en mode haute impedance de la PIN
  } 

//---------------------Bouton UP---------------------------- 
if (data & psxUp)                                       
 {
    // Serial.println("UP");
    pinMode(UP, OUTPUT);
    digitalWrite(UP, LOW);
  }
else
  { 
    pinMode (UP, INPUT);   // Mise en mode haute impedance de la PIN
  } 
  
//---------------------Bouton DOWN---------------------------- 
if (data & psxDown)                                       
 {
    // Serial.println("DOWN");
    pinMode(DOWN, OUTPUT);
    digitalWrite(DOWN, LOW);
  }
else
  { 
    pinMode (DOWN, INPUT);   // Mise en mode haute impedance de la PIN
  } 

//---------------------Bouton LEFT---------------------------- 
if (data & psxLeft)                                       
 {
    // Serial.println("LEFT");
    pinMode(LEFT, OUTPUT);
    digitalWrite(LEFT, LOW);
  }
else
  { 
    pinMode (LEFT, INPUT);   // Mise en mode haute impedance de la PIN
  } 

//---------------------Bouton RIGHT---------------------------- 
if (data & psxRight)                                       
 {
    // Serial.println("RIGHT");
    pinMode(RIGHT, OUTPUT);
    digitalWrite(RIGHT, LOW);
  }
else
  { 
    pinMode (RIGHT, INPUT);   // Mise en mode haute impedance de la PIN
  } 
}
