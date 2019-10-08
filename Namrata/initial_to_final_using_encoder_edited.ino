#define outputA 2
#define outputB 4
#define outputC 3
#define outputD 5

int xi, yi, xc1, xc2, yc1, yc2, xf = 500, yf = 500;
int x1, x2, y1, y2;
volatile int counter1, counter2;
int x1LastState, y1LastState;
int x2LastState, y2LastState;
float sf, s1, s2, s3, s4, w = 0;

void setup() {
  // put your setup code here, to run once:
  counter1 = counter2 = 0;
  xi = yi = 0;
  sf = 1;
  
  pinMode (outputA, INPUT);
  digitalWrite(outputA, HIGH);
  pinMode (outputB, INPUT);
  digitalWrite(outputB, HIGH);
  pinMode (outputC, INPUT);
  digitalWrite(outputC, HIGH);
  pinMode (outputD, INPUT);
  digitalWrite(outputD, HIGH);

  Serial.begin(9600);
  x1LastState = digitalRead(outputA) + xi;
  y1LastState = digitalRead(outputB) + yi;
  x2LastState = digitalRead(outputC) + xi;
  y2LastState = digitalRead(outputD) + yi;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  xc1 = digitalRead(outputA);
  yc1 = digitalRead(outputA);
  if(xc1 != x1LastState || yc1 != y1LastState)
  {
    if(digitalRead(outputB) != xc1 || digitalRead(outputB) != yc1){
      counter1++;}
    else {
      counter1--;}
  }
  x1LastState = xc1;
  y1LastState = yc1;

  xc2 = digitalRead(outputC);
  yc2 = digitalRead(outputC);
  if(xc2 != x2LastState || yc2 != y2LastState)
  {
    if(digitalRead(outputD) != xc2 || digitalRead(outputD) != yc2){
      counter2++;}
    else {
      counter2--;}
  }
  x2LastState = xc2;
  y2LastState = yc2;
  
  x1 = xf - xc1;
  x2 = xf - xc2;
  y1 = yf - yc1;
  y2 = yf - yc2;

  if(x1 == y1 && x2 == y2)
  {
    float x = x1;
    float y = y1;
    s1 = sf * (-0.33 * x + 0.35 * y + 0.25 * w);
    s2 = sf * (-0.33 * x - 0.35 * y + 0.25 * w);
    s3 = sf * (0.35 * x - 0.35 * y + 0.25 * w);
    s4 = sf * (0.35 * x + 0.35 * y + 0.25 * w);
  }
  //for first encoder 
  Serial.print(counter1);
  if(counter1 > 0)
    Serial.print("clockwise");
  else
    Serial.print("anticlockwise");
  //for second encoder
  Serial.print(counter2);
  if(counter2 > 0)
    Serial.print("clockwise");
  else
    Serial.print("anticlockwise");
}
