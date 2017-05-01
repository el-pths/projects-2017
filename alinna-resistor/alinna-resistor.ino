byte value[4]={14, 16, 10, 9};

byte numbers[4]={4, 5, 6, 7};

// Cool idea with using "15" as special value
// perhaps "0" could be more meaningful :)
// but that is not important
byte digits[10][7]={
  {2, 3, 4, 6, 7, 8, 15},
  {4, 6, 15, 15, 15, 15, 15},
  {2, 4, 5, 7, 8, 15, 15},
  {2, 4, 5, 6, 7, 15, 15},
  {3, 4, 5, 6, 15, 15, 15},
  {2, 3, 5, 6,7 ,15,15},
  {2, 3, 5, 6, 7, 8, 15},
  {2, 4, 6, 15, 15, 15, 15},
  {2, 3, 4, 5, 6, 7, 8},
  {2, 3, 4, 5, 6, 7, 15}
};

int c, R=0;
double r, U, X=0; // U and c could be declared locally in "loop"
byte Char=0; // this may be declared locally in "show"

void setup() {
  // couldn't remember well what we need here, but I believe it is:
  // set 9, 10, 14, 16 as outputs, LOW
  // set 2, 3, 4, 5, 6, 7, 8 as outputs, HIGH
  
  Serial.begin(9600);
  
  // what this loop is for? :)
  for(byte j=0; j<10; j++){
    for(int x=0; x<4; x++){ 
      pinMode(value[x], INPUT);
      // it seems we made these pins "input" and never make them "output"
      // are they connected to bases of transistors?
      // curiously, that it still works somehow :)
    }
    for(int i=0; i<7; i++){
      if(digits[j][i]!=15){
        pinMode(digits[j][i], OUTPUT);
      }
    }
  }
  
  // that's good
  pinMode(A2, INPUT);
  pinMode(A3, OUTPUT);
}

void loop() {
  digitalWrite(A3, HIGH);
  Serial.println(c); // perhaps it's better to move "c=analogRead..." above this line
  
  // some curious transformations... I think c is 1023 maximum
  // which corresponds to 5000 milliVolts (i.e. 5 Volts)
  // so it should be enough to multiply c by (5000/1023) i.e. 4.887
  U=c*0.0049;
  R=U/0.04;

  digitalRead(A3); // probably, this is not needed at all
  c= analogRead(A2); // may be move it before "println" above
  delay(1);
  show(R); // great! good idea to move indication to separate function
}

void show(int r){
  /*
   this is mainly good, though probably we can simplify it a bit:
   by splitting in two functions
   
   one function will care of converting "r" to 4 digits
   and placing them into "numbers[]" array
   
   the other function can display digits out of this array
   probably, repeating it several times (say, 100 or 1000)
  */
  X=r;
  int Div=1000;
  for(byte q=0; q<4; q++){
    Char=X/Div;
    X=X-Char*Div;
    Div=Div/10;
    digitalWrite(value[q], HIGH); // remember, these pins are configured as inputs... how it works? I don't know :)
    for(byte i=0; i<7; i++){
      if(digits[Char][i]!=15){
        digitalWrite(digits[Char][i], LOW);
      }
    }
    delay(1);
    digitalWrite(value[q], LOW);
    for(byte i=0; i<7; i++){
      if(digits[Char][i]!=15){    
        digitalWrite(digits[Char][i], HIGH);
      }
    }
  }
}
