#define ax_en 2
#define bx_en 4
#define ay_en 3
#define by_en 5

volatile int counter_x = 0;
volatile int counter_y = 0;
int a_xS;
int b_xS;
int a_yS;
int b_yS;
int x=0,y=0;
int prev_x=0,prev_y=0; //stores the immediate previous x and y 
int count=0;   //counts the no of elements in the array

int arr_x[200];
int arr_y[200];


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

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), change_x, RISING);
  attachInterrupt(digitalPinToInterrupt(3), change_y, RISING);



}

void loop() {
  // put your main code here, to run repeatedly:


 /* x = int(counter_x / 100);
  y = int(counter_y / 100);*/
if(x!=prev_x||y!=prev_y){
  arr_x[count-1]=x;
  arr_y[count-1]=y;
  for (int i = 0; i < count; i++) {
    
    Serial.print(arr_x[i] + "," +arr_y[i]);
    Serial.print("\n");
    }
  }
}

void change_x() {
  a_xS = digitalRead(ax_en);
  b_xS = digitalRead(bx_en);

  if (b_xS != a_xS)
    counter_x++;
  else
    counter_x--;
  if(counter_x==100)
  { count++;
    prev_x=x;
    x=x+1;
    counter_x=0;}
  
}

void change_y() {
  a_yS = digitalRead(ay_en);
  b_yS = digitalRead(by_en);

  if (b_yS != a_yS)
    counter_y++;
  else
    counter_y--;
  if(counter_y==100)
  {count++;
   prev_y=y;
   y=y+1;
   counter_y=0;}
}
