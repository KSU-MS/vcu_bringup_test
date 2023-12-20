#include <Arduino.h>
#include <pindefs.h>
#include <ADC_SPI.h>

float channel1reading, channel2reading, channel3reading, channel4reading;
float readings[]={channel1reading,channel2reading,channel3reading,channel4reading};
ADC_SPI spi_adc;

void setup() {
  delay(100);
  Serial.begin(115200);
  Serial.println("Starting");
  delay(100);
  spi_adc.init(DEFAULT_SPI_CS,DEFAULT_SPI_SPEED);
  // spi_adc.init(10,1000000);
  for (uint64_t i = 0; i <(sizeof(ANALOG_INPUTS)/sizeof(ANALOG_INPUTS[0])); i++){
    pinMode(ANALOG_INPUTS[i],INPUT);
    Serial.printf("set pin %d to input");
    Serial.print(analogRead(ANALOG_INPUTS[i]));
    Serial.print("\n");
  }
  for (uint64_t i = 0; i <(sizeof(DIGITAL_OUTPUTS)/sizeof(DIGITAL_OUTPUTS[0])); i++){
    pinMode(DIGITAL_OUTPUTS[i],OUTPUT);
    Serial.printf("set pin %d to output\n");
    digitalWrite(DIGITAL_OUTPUTS[i],HIGH);
  }
}

void loop() {
  // for (uint64_t i = 0; i <(sizeof(ANALOG_INPUTS)/sizeof(ANALOG_INPUTS[0])); i++){
  //   pinMode(ANALOG_INPUTS[i],INPUT);
  //   Serial.printf("reading pin %d: ",ANALOG_INPUTS[i]);
  //   Serial.print(analogRead(ANALOG_INPUTS[i]));
  //   Serial.print("\n");
  //   delay(100);
  // }
  // for (uint64_t i = 0; i <(sizeof(DIGITAL_OUTPUTS)/sizeof(DIGITAL_OUTPUTS[0])); i++){
  //   pinMode(DIGITAL_OUTPUTS[i],OUTPUT);
  //   Serial.printf("toggle pin %d\n",DIGITAL_OUTPUTS[i]);
  //   digitalToggle(DIGITAL_OUTPUTS[i]);
  //   delay(100);
  // }
  for (int i = 0; i< 4; i++){
    readings[i]=static_cast<float>(spi_adc.read_adc(i));
    // Serial.printf("Spi adc channel %d, reading: %f\n",i,(static_cast<float>(spi_adc.read_adc(i)))/ADC_CONVERSION_FACTOR);
    // Serial.printf("%f",i,(static_cast<float>(spi_adc.read_adc(i)))/ADC_CONVERSION_FACTOR);

  }
  Serial.printf("%f\t%f\t%f\t%f\n",readings[0],readings[1],readings[2],readings[3]);
  delay(500);
}

