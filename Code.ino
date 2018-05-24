// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>


double distF = 0.0;
double distR = 0.0;
double distL = 0.0;

int trigPinR = D4;
int echoPinR = D5;
int trigPinL = D3;
int echoPinL = D2;
int trigPinF = D1;
int echoPinF = D0;

HC_SR04 rangefinderR = HC_SR04(trigPinR, echoPinR,0,1000);
HC_SR04 rangefinderL = HC_SR04(trigPinL, echoPinL,0,1000);
HC_SR04 rangefinderF = HC_SR04(trigPinF, echoPinF,0,1000);

void setup()
{
    Serial.begin(9600);
    pinMode(D7, OUTPUT);
    pinMode(D6, OUTPUT);
    digitalWrite(D6,HIGH);
    digitalWrite(D7,HIGH);
    delay(2000);
    Serial.printf("Motor's are working fine.");
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
}

void loop()
{
    String data = " ";
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    double distF = 0.0;
    double distR = 0.0;
    double distL = 0.0;
    
    distR = rangefinderR.getDistanceCM();
    distF = rangefinderF.getDistanceCM();
    distL = rangefinderL.getDistanceCM();
   
    if(distR > 0 && distR < 20 && distL > 0 && distL < 20 && distF > 0 && distF < 20){
        digitalWrite(D6,LOW);
        digitalWrite(D7,LOW);
    }
    else{
        distR = rangefinderR.getDistanceCM();
        Serial.printf("Distance: Right: %.2f cm\t Front: %.2f cm\t Left: %.2f cm\n", distR, distF, distL);
        if(distR > 0 && distR < 20){
             Particle.publish("PROJECTMOVER", data, PRIVATE);
             digitalWrite(D6,LOW);
             digitalWrite(D7,LOW);
             
             distF = rangefinderF.getDistanceCM();
             Serial.printf("Distance: Right: %.2f cm\t Front: %.2f cm\t Left: %.2f cm\n", distR, distF, distL);
             if(distF > 0 && distF < 20){
                 Particle.publish("PROJECTMOVEF", data, PRIVATE);
                 digitalWrite(D6,HIGH);
                 digitalWrite(D7,HIGH);
                 delay(500);
             }
             else{
                digitalWrite(D6,LOW);
                digitalWrite(D7,HIGH);
                delay(500);
             }
        }
        else{
            digitalWrite(D6,LOW);
            digitalWrite(D7,LOW);
        }
        
        distF = rangefinderF.getDistanceCM();
        Serial.printf("Distance: Right: %.2f cm\t Front: %.2f cm\t Left: %.2f cm\n", distR, distF, distL);
            if(distF > 0 && distF < 20){
                 Particle.publish("PROJECTMOVEF", data, PRIVATE);
                 digitalWrite(D6,HIGH);
                 digitalWrite(D7,HIGH);
                 delay(500);
            }
            else{
                digitalWrite(D6,LOW);
                digitalWrite(D7,LOW);
            }
        
        distL = rangefinderL.getDistanceCM();
        Serial.printf("Distance: Right: %.2f cm\t Front: %.2f cm\t Left: %.2f cm\n", distR, distF, distL);
        if(distL > 0 && distL < 20){
             Particle.publish("PROJECTMOVEL", data, PRIVATE);
             digitalWrite(D6,LOW);
             digitalWrite(D7,LOW);
             
             distF = rangefinderF.getDistanceCM();
             Serial.printf("Distance: Right: %.2f cm\t Front: %.2f cm\t Left: %.2f cm\n", distR, distF, distL);
             if(distF > 0 && distF < 20){
                 digitalWrite(D6,HIGH);
                 digitalWrite(D7,HIGH);
                 delay(500);
             }
             else{
                 digitalWrite(D6,HIGH);
                 digitalWrite(D7,LOW);
                 delay(500);
             }
        }
        else{
            digitalWrite(D6,LOW);
            digitalWrite(D7,LOW);
        }
    
    }
}
