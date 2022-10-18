int cod = 80;
int munec = 80;
int man = 80;

int direccion = 90;
int das = 1;
int est = 80;

void setup() {
  Serial.begin(9600);
  
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);


  sMotor(4,180);
  sMotor(5,180);
  sMotor(6,180);
}

void loop() {
  //
  
  //String Datos = Serial.readStringUntil('\n'); 
  String Datos = "2-3;390;490;5180;2+6;3180;4180;50;1-60;2-3;390;490;5180;2+6;3180;4180;50;1+70;";
  //String Datos = "1+50;";
  if(Datos != 0 && Datos != "")
  Serial.println(Datos);
  
  int numL = 0;
  for(int i=0;i<Datos.length();i++){
    if(Datos.substring(i,i+1)== ";"){
      numL++;
    }
  }
  for(int i=0;i<numL+1;i++){
    String Dato = split(Datos,";",i,numL);
    int motor = 0;
    int t = 0;
    switch(Dato.substring(0,1).toInt()){
      case 1:
        motor = 3;
      break;
      case 2:
        motor = 9;
      break;
      case 3:
        motor = 4;
      break;
      case 4:
        motor = 5;
      break;
      case 5:
        motor = 6;
      break;
    }
    
    if(Dato.substring(0,1).toInt() == 1 || Dato.substring(0,1).toInt() == 2){
      if(Dato.substring(1,2)=="+")
        direccion = 70;
      else if(Dato.substring(1,2)=="-")
        direccion = 30;
      
      int veces = Dato.substring(2).toInt();
      t = veces*10;
      analogWrite(motor,direccion);
      delay(t);   
      analogWrite(motor,0);
    } else {
      int grados = Dato.substring(1).toInt();
      t = grados;
      sMotor(motor,grados);
    }
    delay(t);
  }
}

void sMotor(int motor,int grado){
  int ms = 1000;
  int grados = map(grado,0,180,145,840);
  for(int Hz = 0;Hz < 100;Hz++){
     digitalWrite(motor,HIGH);
     delayMicroseconds(grados);
     digitalWrite(motor,LOW);
     delayMicroseconds(ms-grados);
  }
}

String split(String cadena,String separador, int pos,int numL){
  String commands[numL] = {};
  int Parray = 0;
  for(int i=0;i<cadena.length();i++){
    if(cadena.substring(i,i+1)!= separador){
      commands[Parray] = commands[Parray]+cadena.substring(i,i+1);
    } else {
      Parray++;
    }
  }
  return commands[pos];
}
