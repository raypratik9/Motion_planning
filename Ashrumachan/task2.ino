#define enc_11 2
#define enc_12 4
#define enc_21 3
#define enc_22 5

volatile int enc1_val = 0;
volatile int enc2_val = 0;
int x_counter, x_motion, y_counter, y_motion, X_motion, Y_motion, x_val, y_val, arr[2][2] = {{0, 0}, {10, 10}};
int d_1, d_2, d_3, d_4;
int s1, s2, s3, s4;
int count = 0, sf = 1, w = 0;
void setup() {
  pinMode(enc_11, INPUT);
  digitalWrite(enc_11, HIGH);
  pinMode(enc_12, INPUT);
  digitalWrite(enc_12, HIGH);

  pinMode(enc_21, INPUT);
  digitalWrite(enc_21, HIGH);
  pinMode(enc_22, INPUT);
  digitalWrite(enc_22, HIGH);

  attachInterrupt(digitalPinToInterrupt(2), func, RISING);
  attachInterrupt(digitalPinToInterrupt(3), func1, RISING);

  Serial.begin(115200);
}

void loop()
{
  Serial.print(enc1_val);
  Serial.print("   ");
  Serial.print(enc2_val);
  Serial.print("   ");
  x_counter = enc1_val / 100;
  y_counter = enc2_val / 100;

  x_val = arr[1][0] - arr[0][0];
  y_val = arr[1][1] - arr[0][1];
  x_motion = map(x_motion, -x_val, x_val, 0, 255);
  y_motion = map(y_motion, -y_val, y_val, 0, 255);
  motion(x_motion, y_motion);

}


void func() {
  if (digitalRead(enc_12) != digitalRead(enc_11)) {
    enc1_val++ ;
  }

  else {
    enc1_val-- ;
  }

}


void func1() {
  if (digitalRead(enc_22) != digitalRead(enc_21)) {
    enc2_val++ ;
  }

  else {
    enc2_val-- ;
  }

}
void motion(int x_motion, int y_motion)
{
  X_motion = x_motion ;
  Y_motion = y_motion ;

  sf = 1;
  s1 = sf * (0.1768 * X_motion + 0.1768 * Y_motion + 0.25 * w);
  s2 = sf * (0.1768 * X_motion + 0.1768 * Y_motion + 0.25 * w);
  s3 = sf * (-0.1768 * X_motion - 0.1768 *  Y_motion + 0.25 * w);
  s4 = sf * (-0.1768 * X_motion - 0.1768 * Y_motion + 0.25 * w);
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
