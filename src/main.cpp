#include <Arduino.h>
#include <pindefs.h>
#include <ADC_SPI.h>
#include <FlexCAN_T4.h>
#include <ksu_dbc.h>
FlexCAN_T4<CAN1, RX_SIZE_1024, TX_SIZE_1024> can1;
FlexCAN_T4<CAN2, RX_SIZE_1024, TX_SIZE_1024> can2;
FlexCAN_T4<CAN3, RX_SIZE_1024, TX_SIZE_1024> can3;
uint8_t fanduty=0x00;
float channel1reading, channel2reading, channel3reading, channel4reading;
float readings[]={channel1reading,channel2reading,channel3reading,channel4reading};
ADC_SPI spi_adc;
uint16_t glv_i_sense;

can_obj_ksu_dbc_h_t ksu_can_obj_t;

void InitCAN()
{
  // In CAN2.0 mode, setRegion doesn't exist, you have 64 mailboxes on Teensy 4.0, and 16 on Teensy 3.x.
  can1.begin();
  can1.setBaudRate(500000);
  can1.setMaxMB(NUM_TX_MAILBOXES+NUM_RX_MAILBOXES);
  for (int i = 0; i < NUM_RX_MAILBOXES; i++)
  {
      can1.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
  {
      can1.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }
  can1.mailboxStatus();
  //inverter can must send & receive, 6rx MB and 2tx MB
  can2.begin();
  can2.setBaudRate(500000);
  can2.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);
  // FCTP_OPT canbuslist[]={can1,can2,can3}
  for (int i = 0; i < NUM_RX_MAILBOXES; i++)
  {
      can2.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
  {
      can2.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }
    can2.mailboxStatus();
  //accumulator can must send & receive, 6rx MB and 2tx MB

  can3.begin();
  can3.setBaudRate(500000);
  can3.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);
  for (int i = 0; i < (NUM_RX_MAILBOXES); i++)
  { // leave one free for ext ID
      can3.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }
  for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
  {
      can3.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }
  can3.mailboxStatus();
}
void setup() {
  delay(100);
  Serial.begin(115200);
  Serial.println("Starting");
  InitCAN();
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
    analogWriteFrequency(DIGITAL_OUTPUTS[i],1000);

  }
}

void loop() {
  for (uint64_t i = 0; i <(sizeof(ANALOG_INPUTS)/sizeof(ANALOG_INPUTS[0])); i++){
    Serial.printf("reading pin  %d: ",ANALOG_INPUTS[i]);
    Serial.print(" "+sensor_names[i] + " ");
    Serial.print(analogRead(ANALOG_INPUTS[i]));
    if(ANALOG_INPUTS[i]==GLV_ISENSE){
      glv_i_sense=analogRead(GLV_ISENSE);
    }
    Serial.print("\n");
  }
  for (uint64_t i = 0; i <(sizeof(DIGITAL_OUTPUTS)/sizeof(DIGITAL_OUTPUTS[0])); i++){
    Serial.printf("toggle pin %d\n",DIGITAL_OUTPUTS[i]);
    analogWrite(DIGITAL_OUTPUTS[i],fanduty);
  }
  for (int i = 0; i< 4; i++){
    readings[i]=static_cast<float>(spi_adc.read_adc(i));
    Serial.printf("Spi adc channel %d, reading: %f\n",i,(static_cast<float>(spi_adc.read_adc(i)))/ADC_CONVERSION_FACTOR);
  }
  CAN_message_t msg;
  msg.id = 0x01;
  for ( uint8_t i = 0; i < 8; i++ ){
    msg.buf[i] = i + 1;
  }
  msg.buf[0]=((glv_i_sense&0xFF00)>>0x8);


  msg.buf[1]=glv_i_sense&0x00FF;
  msg.len=8;
  can1.write(msg);
  can2.write(msg);
  can3.write(msg);
  fanduty+=0x10;
  delay(500);
}

// int unpack_flexcan_msg(CAN_message_t message,can_obj_ksu_dbc_h_t *out){
//   uint64_t data = message.buf[0];
//   return unpack_message(out,message.id,data,message.len,message.timestamp);
// }
