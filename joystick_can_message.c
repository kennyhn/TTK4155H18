#include "Node_1/adc.h"
#include "Node_1/can.h"


//forslag til hvordan vi kan løse siste oppgave i del 6
void createmessage(){
  //send joystick direction
  //Send joystick values
  //send joystick click
  volatile (uint8_t*) adc = (uint8_t*)0x1400;
  joystick_direction jd = check_joystick_direction(adc);
  joystick_perc_angle jpa = get_perc_angle(adc);
  //må legge til kode for å sjekke om knappen på joysticken er trukket ned
  can_message msg;
  msg.id = 10;
  msg.length = 3 //4 når vi får med knappen også
  msg.data[0]=(uint8_t)jpa.X_value;
  msg.data[1]=(uint8_t)jpa.Y_value;
  msg.data[2]=jd;
  can_message_send(msg);
}



void recieve_message(joystick_perc_angle* jpa, joystick_direction* jd){
  //Denne koden settes kanskje i en while løkke på en eller annen måte?
  can_message rmsg;
  rmsg=can_data_recieve();
  jpa->X_value=(int8_t)rmsg.data[0];
  jpa->Y_value=(int8_t)rmsg.data[1];
  *jd=rmsg.data[2];
}
