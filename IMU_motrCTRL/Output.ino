/*

MinIMU-9-Arduino-AHRS
Pololu MinIMU-9 + Arduino AHRS (Attitude and Heading Reference System)

Copyright (c) 2011 Pololu Corporation.
http://www.pololu.com/

MinIMU-9-Arduino-AHRS is based on sf9domahrs by Doug Weibel and Jose Julio:
http://code.google.com/p/sf9domahrs/

sf9domahrs is based on ArduIMU v1.5 by Jordi Munoz and William Premerlani, Jose
Julio and Doug Weibel:
http://code.google.com/p/ardu-imu/

MinIMU-9-Arduino-AHRS is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

MinIMU-9-Arduino-AHRS is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License along
with MinIMU-9-Arduino-AHRS. If not, see <http://www.gnu.org/licenses/>.

*/

void printdata(void)
{    
 //     Serial.print("!");
/*
      #if PRINT_EULER == 1
      Serial.print("ANG:");
      Serial.print(ToDeg(roll));
      Serial.print(",");
      Serial.print(ToDeg(pitch));
      Serial.print(",");
      Serial.print(ToDeg(yaw));
      #endif      
      #if PRINT_ANALOGS==1
      Serial.print(",AN:");
      Serial.print(AN[0]);  //(int)read_adc(0)
      Serial.print(",");
      Serial.print(AN[1]);
      Serial.print(",");
      Serial.print(AN[2]);  
      Serial.print(",");
      Serial.print(AN[3]);
      Serial.print (",");
      Serial.print(AN[4]);
      Serial.print (",");
      Serial.print(AN[5]);
      Serial.print(",");
      Serial.print(c_magnetom_x);
      Serial.print (",");
      Serial.print(c_magnetom_y);
      Serial.print (",");
      Serial.print(c_magnetom_z);
      #endif
      /*#if PRINT_DCM == 1
      Serial.print (",DCM:");
      Serial.print(convert_to_dec(DCM_Matrix[0][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[0][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[0][2]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[1][2]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][0]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][1]));
      Serial.print (",");
      Serial.print(convert_to_dec(DCM_Matrix[2][2]));
      #endif*/
      //Serial.println();    
int roll_deg = ToDeg(roll);
int pitch_deg = ToDeg(pitch);
int speedCtrl = 0;
int start_deg_pos = 3;
int start_deg_neg = -3;


    if((roll_deg > start_deg_pos) && (roll_deg > abs(pitch_deg))
			&& dir_counter != 10)
    {
		//speedCtrl = map(roll_deg, 0, 180, 0, 255);
		Serial.println("F");
		//Serial.print("S");
		//Serial.print("5");
		//Serial.println(roll_deg);
		moving = true;
		dir_counter++;
    }
	
    else if((roll_deg < start_deg_neg) && (abs(roll_deg) > abs(pitch_deg))
			&& dir_counter != 10 && moving==false)
    {
        Serial.println("B");
        //speedCtrl = map(abs(roll_deg), 0, 180, 0, 255);
        //Serial.print("S");
		//Serial.print("5");
        //Serial.println(abs(roll_deg));       
		moving = true;
		dir_counter++;
    }
        
    else if( (pitch_deg < start_deg_neg) && (abs(pitch_deg) > abs(roll_deg))
			&& dir_counter != 10)
    {
        Serial.println("L");
        //speedCtrl = map(abs(roll_deg), 0, 180, 0, 255);
        //Serial.print("S");
		//Serial.print("5");
        //Serial.println(abs(pitch_deg));
		moving = true;
		dir_counter++;
    }
    else if((pitch_deg > start_deg_pos) && (pitch_deg > abs(roll_deg))
			&& dir_counter != 10)
    {
        Serial.println("R");
        //speedCtrl = map(roll_deg, 0, 180, 0, 255);
        //Serial.print("S");
		//Serial.print("5");
        //Serial.println(abs(pitch_deg));
		moving = true;
		dir_counter++;
    }
 
	else if( (((pitch_deg > start_deg_neg) && (pitch_deg < start_deg_pos)) &&
		  ((roll_deg > start_deg_neg) && (roll_deg < start_deg_pos)))
			&& dir_counter != 0 )
	{
		dir_counter = 0;
		Serial.println("N");
		Serial.print("S");
		Serial.print("5");
		Serial.println("000");
		moving = false;
	}
	
	if (moving == true)
	{
		if((abs(pitch_deg) > abs(roll_deg)) && pitch_deg_old!=pitch_deg)
		{
			Serial.print("S");
			Serial.print("5");
			pitch_deg = abs(pitch_deg) * 1.6;
			pitch_deg = constrain(pitch_deg, 0, 255);
			Serial.println(pitch_deg*1.6);
			pitch_deg_old = pitch_deg;
		}
		
		else if ((abs(roll_deg) > abs(pitch_deg)) && roll_deg_old!=roll_deg)
		{
			Serial.print("S");
			Serial.print("5");
			roll_deg = abs(roll_deg) * 1.6;
			roll_deg = constrain(roll_deg, 0, 255);
			Serial.println(roll_deg);
			roll_deg_old = roll_deg;
		}
	}
}

long convert_to_dec(float x)
{
  return x*10000000;
}

