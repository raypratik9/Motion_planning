/*#include <PS4USB.h>

  // Satisfy the IDE, which needs to see the include statment in the ino too.
  #ifdef dobogusinclude
  #include <spi4teensy3.h>
  #endif
  #include <SPI.h>

  USB Usb;
  PS4USB PS4(&Usb);
*/
#define ax_en 14
#define bx_en 24
#define ay_en 11
#define by_en 21

volatile int counter_x = 0;             //counts the x axis encoder ticks
volatile int counter_y = 0;             //counts the y axix encoder ticks
int prev_x=0,prev_y=0;                    //stores the immediate previous value of x and y

//int *ptr_x, *ptr_y;
int final_x = 100, final_y = 100;       //final co-ordinates
int initial_x = 0, initial_y = 0;       //initial co-ordinate which also stores the current position(varies)
float x, y, w;
float scale;                            //slope of the line of follow 
void change_x();                        //isr for encoder of x axis
void change_y();                        //isr for encoder of y axis
void motion();                          //holonomic
//ptr_x = (int*)calloc(200, sizeof(int));
//ptr_y = (int*)calloc(200, sizeof(int));


byte m1 = 23;
byte m2 = 25;
byte m3 = 27;
byte m4 = 29;
bool dir1, dir2, dir3, dir4;
float s1, s2, s3, s4;
int d1 = 2;
int d2 = 3;
int d3 = 4;
int d4 = 5;


void setup() {
  // put your setup code here, to run once:

  pinMode(ax_en, INPUT);
  pinMode(bx_en, INPUT);
  pinMode(ay_en, INPUT);
  pinMode(by_en, INPUT);

  digitalWrite(ax_en, HIGH);
  digitalWrite(bx_en, HIGH);
  digitalWrite(ay_en, HIGH);
  digitalWrite(by_en, HIGH);



  attachInterrupt(digitalPinToInterrupt(14), change_x, RISING);
  attachInterrupt(digitalPinToInterrupt(11), change_y, RISING);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);

  Serial.begin(115200);


  /*#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
    #endif{
    if (Usb.Init() == -1) {
      Serial.print(F("\r\nOSC did not start"));
      while (1); // Halt
    }
    Serial.print(F("\r\nPS4 USB Library Started"));*/
}


void loop() {
  // put your main code here, to run repeatedly:


  /*Usb.Task();

    if (PS4.connected()) {
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
        x= map(PS4.getAnalogHat(LeftHatX),0,255,-255,255) ;
        y= map(PS4.getAnalogHat(LeftHatY),0,255,-255,255);
        w= map(PS4.getAnalogHat(RightHatX),0,255,-255,255);
    }*/
  if ((initial_x <= final_x) && (initial_y <= final_y)) {
    if(initial_x==0 && final_x==0){
      x=0;
      y=final_y;
    }
    elseif(initial_y==0 && final_y==0){
      x=final_x;
      y=0;
    }
    else{
    scale = ((final_y - initial_y) / (final_x - initial_x));
    x = initial_x;
    y = initial_x * scale+(final_y - (scale*final_x));
    //x=final_x-initial_x; to store the live position of x
    //y=final_y-initial_y; to store the live position of y
    }
  
      s1 = (0.1768 *  x + 0.1768 *  y + 0.25 * 0);
      s2 = (0.1768 *  x + 0.1768 *  y + 0.25 * 0);
      s3 = (-0.1768 * x - 0.1768 *  y + 0.25 * 0);
      s4 = (-0.1768 * x - 0.1768 * y + 0.25 * 0);
   
    motion();
    
    if (x > prev_x || y > prev_y) {
    Serial.print(x + (String)"," +y);
   }

  }
 
}


void change_x() {
  int a_xS;
  int b_xS;

  a_xS = digitalRead(ax_en);
  b_xS = digitalRead(bx_en);

  if (b_xS != a_xS)
    counter_x++;
  else
    counter_x--;

  if (counter_x == 100) {
    prev_x=x;
    initial_x += 1;
    counter_x = 0;

  }
}

void change_y() {
  int a_yS;
  int b_yS;
  a_yS = digitalRead(ay_en);
  b_yS = digitalRead(by_en);

  if (b_yS != a_yS)
    counter_y++;
  else
    counter_y--;
  if (counter_y == 100) {
    prev_y=y;
    initial_y += 1;
    counter_y = 0;
  }
}

void motion() {
  s1 > 0 ? dir1 = HIGH : dir1 = LOW;
  s2 > 0 ? dir2 = HIGH : dir2 = LOW;
  s3 > 0 ? dir3 = HIGH : dir3 = LOW;
  s4 > 0 ? dir4 = HIGH : dir4 = LOW;

  digitalWrite(d1, dir1);
  digitalWrite(d2, dir2);
  digitalWrite(d3, dir3);
  digitalWrite(d4, dir4);


  analogWrite(m1, abs(s1));
  analogWrite(m2, abs(s2));
  analogWrite(m3, abs(s3));
  analogWrite(m4, abs(s4));
}
