#define trig 11
#define echo 4
#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5
#define rightIR 3
#define leftIR 12

int distance, right_ir, left_ir;

int max_speed = 150;
int min_speed = 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(rightIR, INPUT);
  pinMode(leftIR, INPUT);

}

void loop() {

  distance = Measure_Distance();

  right_ir = digitalRead(rightIR);
  left_ir = digitalRead(leftIR);

  if (distance>5 && distance < 30)
  {
    Move_Forward();
  }
  else
  {
    Stop();
    if (right_ir == 0 && left_ir == 1)
    {
      Turn_Right();
    }
    else if (right_ir == 1 && left_ir == 0)
    {
      Turn_Left();
    }
  }

  Serial_Monitor();
}

long Measure_Distance()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long dur = pulseIn(echo, HIGH);

  return ((0.034 * dur) / 2);
}

void Turn_Left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, min_speed);
  analogWrite(enB, max_speed);
}

void Turn_Right()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, max_speed);
  analogWrite(enB, min_speed);
}

void Move_Forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, max_speed);
  analogWrite(enB, max_speed);
}

void Stop()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void Serial_Monitor()
{
  Serial.print("Distance: "); Serial.print(distance); Serial.print("\n");
  Serial.print("Right IR: "); Serial.print(right_ir); Serial.print("\n");
  Serial.print("Left IR: "); Serial.print(left_ir); Serial.print("\n");
  Serial.print("\n"); Serial.print("\n");
}
