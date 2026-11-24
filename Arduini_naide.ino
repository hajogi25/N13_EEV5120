/*
 * Nimetus: Reaktsioonimäng
 * Kirjeldus: Vajuta õiget lülitit vastavalt süttinud LED-ile
 * Autor: Hans Joosep Jõgisalu
 * Versioon: v1.0
 */

// Sisendid ja väljundid
#define E1 8
#define E2 9
#define E3 10

#define S1 2
#define S2 3
#define S3 4

// Globaalsed muutujad
byte punktid = 0;
byte lamp = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(E3, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);

  randomSeed(analogRead(A0));
}

void kustutaLEDid()
{
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(E3, LOW);
}

void valiLamp()
{
  lamp = random(1, 4);

  kustutaLEDid();

  switch(lamp)
  {
    case 1:
      digitalWrite(E1, HIGH);
      break;

    case 2:
      digitalWrite(E2, HIGH);
      break;

    case 3:
      digitalWrite(E3, HIGH);
      break;
  }
}

bool kontrolliVajutust()
{
  unsigned long algus = millis();

  while(millis() - algus < 2000)
  {
    if(lamp == 1 && digitalRead(S1))
      return true;

    if(lamp == 2 && digitalRead(S2))
      return true;

    if(lamp == 3 && digitalRead(S3))
      return true;
  }

  return false;
}

void loop()
{
  if(punktid >= 5)
  {
    kustutaLEDid();

    Serial.println("Mangu lopp!");
    Serial.print("Loppskoor: ");
    Serial.println(punktid);

    while(1);
  }

  valiLamp();

  if(kontrolliVajutust())
  {
    punktid++;

    Serial.print("Punktid: ");
    Serial.println(punktid);
  }

  delay(500);
}
