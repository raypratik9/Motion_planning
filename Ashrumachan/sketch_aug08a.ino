#include <Servo.h>
Servo myservo;
int pos=0;   
void setup() {
  // put your setup code here, to run once:
myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
/*if(pos<=180)
{
 myservo.write(pos);
 pos++; 
 delay(20);
}
if(pos>180)
{
for(int i=180;i>0;i--)
{
myservo.write(i);
}
}*/
myservo.write(150);
}
