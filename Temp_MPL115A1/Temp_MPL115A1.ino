//3.3 V
//pin 9 to SHDN
//pin 10 to CS
//pin 11 to Din (MOSI)
//pin 12 to Dout (MISO)
//pin 13 to SCLK
// 
#include <SPI.h>
#include <Wire.h>
#define NWS_BARO 30.04 

// Pin definitions
#define MPL115A1_ENABLE_PIN 9
#define MPL115A1_SELECT_PIN 10

// Masks for MPL115A1 SPI i/o
#define MPL115A1_READ_MASK  0x80
#define MPL115A1_WRITE_MASK 0x7F 

// MPL115A1 register address map
#define PRESH   0x00    // 80
#define PRESL   0x02    // 82
#define TEMPH   0x04    // 84
#define TEMPL   0x06    // 86

#define A0MSB   0x08    // 88
#define A0LSB   0x0A    // 8A
#define B1MSB   0x0C    // 8C
#define B1LSB   0x0E    // 8E
#define B2MSB   0x10    // 90
#define B2LSB   0x12    // 92
#define C12MSB  0x14    // 94
#define C12LSB  0x16    // 96
#define C11MSB  0x18    // 98
#define C11LSB  0x1A    // 9A
#define C22MSB  0x1C    // 9C
#define C22LSB  0x1E    // 9E

// Macro di conversione
#define FT_TO_M(x) ((long)((x)*(0.3048)))
#define KPA_TO_INHG(x) ((x)*(0.295333727))
#define KPA_TO_ATM(x) ((x)*(0.00986923267))
#define KPA_TO_MMHG(x) ((x)*(7.50061683))
#define KPA_TO_PSIA(x) ((x)*(0.145037738))
#define KPA_TO_KGCM2(x) ((x)*(0.0102))
#define INHG_TO_PSIA(x) ((x)*(0.49109778))
#define DEGC_TO_DEGF(x) ((x)*(9.0/5.0)+32)




//void writeRegister(unsigned char r, unsigned char v);
//void writeInteger(unsigned char r, unsigned int v);
//unsigned char readRegister(unsigned char r);
//void readRegisters(unsigned char r, unsigned int numberOfBytes, unsigned char buffer[]);
//unsigned int readInteger(unsigned char r);
//unsigned long readLong(unsigned char r);

//byte READ = 0b11111100;     // SCP1000's read command
//byte WRITE = 0b00000010;   // SCP1000's write command
 
void setup(void) {
   Serial.begin(9600);
  
   SPI.begin();
      
   // Enable SPI Pins
   pinMode(MPL115A1_SELECT_PIN, OUTPUT);
   pinMode(MPL115A1_ENABLE_PIN, OUTPUT);
   
   digitalWrite(MPL115A1_ENABLE_PIN, LOW);
   digitalWrite(MPL115A1_SELECT_PIN, HIGH);

// spam welcome banner
    Serial.print("\n************************************************************************************\n");
    Serial.print("Temperature Readings from MPL115A1          *\n");
    Serial.print("************************************************************************************\n");
}
void loop() { 
float tempF = 0;
float tempC = 0;
float uiTadc = 0;
     
    digitalWrite(MPL115A1_ENABLE_PIN, HIGH);
    delay(20);  // give the chip a few ms to wake up
     
  
    tempF = calculateTemperatureC(); 

  
  digitalWrite(MPL115A1_ENABLE_PIN, LOW);

  Serial.print(tempF);
  Serial.println(" degrees F ");  
   delay(500); 
} 


float calculateTemperatureC() { 
    unsigned int uiTadc;
    unsigned char uiTH, uiTL;
 unsigned int temperature_counts = 0;
     
     float tempC = 0;
	 float tempF = 0;
    writeRegister(0x22, 0x00);  // Start temperature conversion
    delay(2);                   // Max wait time is 0.7ms, typ 0.6ms
    
    // Read pressure
    uiTH = readRegister(TEMPH);
    uiTL = readRegister(TEMPL);
    
    uiTadc = (unsigned int) uiTH << 8;
    uiTadc += (unsigned int) uiTL & 0x00FF;
    
    // Temperature is a 10bit value
    uiTadc = uiTadc >> 6;
    
    tempC = 25 + (uiTadc - 472) / -5.35;
    // -5.35 counts per °C, 472 counts is 25°C
	tempF = (tempC * 9 / 5 + 32) + 6;
    return tempF;
}

unsigned int readRegister(byte thisRegister) {
    
    byte result = 0;
    
    // select the MPL115A1
    digitalWrite(MPL115A1_SELECT_PIN, LOW);
    
    // send the request
    SPI.transfer(thisRegister | MPL115A1_READ_MASK);
    result = SPI.transfer(0x00);
    
    // deselect the MPL115A1
    digitalWrite(MPL115A1_SELECT_PIN, HIGH);
    
    return result; 
}

void writeRegister(byte thisRegister, byte thisValue) {
    
    // select the MPL115A1
    digitalWrite(MPL115A1_SELECT_PIN, LOW);
    
    // send the request
    SPI.transfer(thisRegister & MPL115A1_WRITE_MASK);
    SPI.transfer(thisValue);
    
    // deselect the MPL115A1
    digitalWrite(MPL115A1_SELECT_PIN, HIGH);
}

