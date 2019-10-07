#define a 2
#define b 4
#define a1 3
#define b1 5

int d_1, d_2, d_3, d_4;
int s1, s2, s3, s4;
int count = 0, sf = 1, w = 0;
int x_val, y_val, x_motion, y_motion;
volatile int c = 0;
volatile int c1 = 0;
int x, y, arr[8][2] = {{0, 0}, {10, 0}, {10, 8}, {12, 8}, {12, 12}, {10, 12}, {10, 20}, {20, 20}};
void motion(int x_val, int y_val);
void setup() {
  pinMode(a, INPUT);
  digitalWrite(a, HIGH);
  pinMode(b, INPUT);
  digitalWrite(b, HIGH);

  pinMode(a1, INPUT);
  digitalWrite(a1, HIGH);
  pinMode(b1, INPUT);
  digitalWrite(b1, HIGH);

  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(2), func, RISING);
  attachInterrupt(digitalPinToInterrupt(3), func1, RISING);

  Serial.begin(115200);
}

void loop()
{
  Serial.print(c);
  Serial.print("   ");
  Serial.print(c1);
  Serial.println("   ");
  x = c / 100;
  y = c1 / 100;

  if (count % 2 == 0)
  {
    if (x == 12)
    {
      do  {
        motion (-200, 0);
      }
      while (x != arr[count][0]);

    }
    else {
      do  {
        motion (200, 0);
      }
      while (x != arr[count][0]);
    }
    count++;
    }
  else
  {
    do  {
      motion (0, 200);
    }
    while (y != arr[count][1]);
    count++;
  }
}


void func() {

  int  s = digitalRead(a);
  int  d = digitalRead(b);
  if (d != s) {
    c++ ;
  }

  else {
    c-- ;
  }

}


void func1() {

  int  s1 = digitalRead(a1);
  int  d1 = digitalRead(b1);
  if (d1 != s1) {
    c1++ ;
  }

  else {
    c1-- ;
  }

}
void motion(int x_val, int y_val)
{
  x_motion = x_val;
  y_motion = y_val;

  sf = 1;
  s1 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s2 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s3 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  s4 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  d_1 = (s1 > 0 ? 1 : 0);
  d_2 = (s2 > 0 ? 1 : 0);
  d_3 = (s3 > 0 ? 1 : 0);
  d_4 = (s4 > 0 ? 1 : 0);
  digitalWrite(6, d_1);
  digitalWrite(7, d_2);
  digitalWrite(8, d_3);
  digitalWrite(9, d_4);
  analogWrite(23, s1);
  analogWrite(25, s2);
  analogWrite(27, s3);
  analogWrite(29, s4);
}
