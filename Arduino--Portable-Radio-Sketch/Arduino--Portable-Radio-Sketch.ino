#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial softSerial(10,11);
DFRobotDFPlayerMini reproductor;

#include <TM1637Display.h>

#define CLK 3
#define DIO 4

TM1637Display display(CLK, DIO);

const int ProxSensor = 2;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
  
  reproductor.begin(softSerial);
  reproductor.volume(10); //Hasta 30
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Wire.begin(); // Pa el cableado
   lcd.begin(16,2);
    lcd.backlight(); //Enciende la retroiluminación del LCD
  
    lcd.clear();
    lcd.setCursor(0,0); //A donde apunto, posicion en el LCD
    lcd.print("MP3 Viperidae");
    delay(500);
  //Pin 2 is connected to the output of proximity sensor
  pinMode(ProxSensor, INPUT);
  display.setBrightness(1);
  display.clear();
    reproductor.start();
   reproductor.enableLoopAll();
  lcd.clear();
}

//Pausa Debe mostrar este const:
const uint8_t pausa[] = {SEG_C | SEG_B, SEG_F | SEG_E};

//Play Debe mostrar este const:
const uint8_t play[] = {
SEG_A | SEG_B | SEG_F | SEG_G | SEG_E , //P
SEG_D | SEG_F | SEG_E, //L
SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, //A
SEG_B | SEG_C | SEG_F | SEG_G | SEG_D }; //Y

const uint8_t next[] = {
SEG_C | SEG_G | SEG_E , //n
SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, //e
SEG_E | SEG_F | SEG_G , //X
SEG_D | SEG_E | SEG_F | SEG_G }; //t

const uint8_t back[] = {
SEG_D | SEG_E | SEG_F | SEG_G | SEG_C , //b
SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, //A
SEG_E | SEG_D | SEG_G , //c
SEG_B | SEG_D | SEG_E | SEG_F | SEG_G }; //K

const uint8_t lop[] = {
SEG_D | SEG_E | SEG_F , //L
SEG_D | SEG_E | SEG_G | SEG_C , //O
SEG_D | SEG_E | SEG_G | SEG_C , //O
SEG_B | SEG_A | SEG_E | SEG_F | SEG_G }; //p

const uint8_t volu[] = {
SEG_B | SEG_D | SEG_F | SEG_C | SEG_E , //V
SEG_D | SEG_E | SEG_G | SEG_C , //o
SEG_F | SEG_E, //l
SEG_E | SEG_C | SEG_D }; //U

const uint8_t vold[] = {
SEG_B | SEG_D | SEG_F | SEG_C | SEG_E , //V
SEG_D | SEG_E | SEG_G | SEG_C , //o
SEG_F | SEG_E, //l
SEG_B | SEG_C | SEG_E | SEG_D | SEG_G }; //d

const uint8_t boom[] = {
SEG_D | SEG_E | SEG_F | SEG_G | SEG_C , //b
SEG_D | SEG_E | SEG_G | SEG_C , //o
SEG_D | SEG_E | SEG_G | SEG_C , //o
SEG_G | SEG_C | SEG_E }; //d

int sitio = 55; //Valor basura
unsigned long tiempoInicioCancion = 0;  // Guardar el tiempo de inicio de la canción
bool subibaja = false;
String playlist[] ={"My True Self","Specialist","Dance!","Mass Destruction","Light the FireUp","Whims of Fate",
"Maze of Life","Want to Be Close","Chachacha","PXNDX","Snow Queen","All I Want"};

void loop() {
 // if (digitalRead(ProxSensor) == HIGH)  //Check the sensor output
  //{
    display.setSegments(play,4,0);
    if(sitio != (reproductor.readCurrentFileNumber()-1)){
      lcd.clear();
      ELECEDE();
        reiniciarTiempo();  // Reiniciar el tiempo para la nueva canción
      sitio = (reproductor.readCurrentFileNumber()-1);
    }
    clearLine(1);
    ANIM(1);
    //digitalWrite(13, HIGH);
   // reproductor.start();  //start the mp3 from the pause
    //REPRODUCIR MUSICA
    delay(350);
  //} else 
  if (digitalRead(ProxSensor) == LOW)  //OTRAS CONDICIONES
  {
    display.setSegments(lop,4,0);
    delay(1000);
        if (digitalRead(ProxSensor) == HIGH)  
      {
        reproductor.next();
        reproductor.previous();
        //REINICIAR CANCION
        reproductor.enableLoopAll();
        //clearLine(1);
        ANIM(2);
        reiniciarTiempo(); 

      } else if (digitalRead(ProxSensor) == LOW)
      {
        display.setSegments(next,4,0);
        delay(1000);
            if (digitalRead(ProxSensor) == HIGH)  
          {
            reproductor.next();
            //SIGUIENTE CANCION
            reproductor.enableLoopAll();
            //clearLine(1);
            ANIM(3);
        
          } else if (digitalRead(ProxSensor) == LOW)
          {
            display.setSegments(back,4,0);
            delay(1000);
             if (digitalRead(ProxSensor) == HIGH)  
          {
            reproductor.previous();
            //ANTERIOR CANCION
            reproductor.enableLoopAll();
            //clearLine(1);
            ANIM(4);
        
              } else if (digitalRead(ProxSensor) == LOW)
              {
                display.clear();
                display.setSegments(pausa,2,1);
                delay(200);
                do{
                  reproductor.pause();  
                  //PAUSAR CANCION
                  //clearLine(1);
                  ANIM(5);

                }while(digitalRead(ProxSensor) == LOW);
                reproductor.start();
              }
    
          }
    
      }
  }

  if((digitalRead(7)) == LOW){
    //Entra al loop
    digitalWrite(13, HIGH);
    delay(600);
    if((digitalRead(7)) == HIGH){

      //MOSTRAR VOL UP O VOL DOWN
      if(subibaja == false){
        display.setSegments(volu,4,0);
        //clearLine(1);
            ANIM(6);
        delay(1000);
        reproductor.volume(30); //Poner luego en 30
        subibaja = true;
      }
      else{
        display.setSegments(vold,4,0);
        //clearLine(1);
            ANIM(7);
        delay(1000);
        reproductor.volume(20); //Poner luego en 17
        subibaja = false;
      }

    }
    else{
      display.setSegments(boom,4,0);
      //clearLine(1);
      reproductor.advertise(1);
            ANIM(8);
        delay(1000);
      //Reproducir advertisement
      //reproductor.advertise(numerodecancion);
    }
    digitalWrite(13, LOW);
  }
  delay(100);
}

void ELECEDE(){
    lcd.setCursor(0,0); //A donde apunto, posicion en el LCD
    String aux = playlist[reproductor.readCurrentFileNumber()-1];
    lcd.print(aux);
}
void ANIM(int tipo){
  switch(tipo){
    //clearLine(1);
    case 1: //play
    lcd.setCursor(0,1); // A donde apunto, posición en el LCD

      // Usamos 'tiempoInicioCancion' para calcular el tiempo transcurrido desde el inicio de la canción
      unsigned long tiempoTranscurrido = millis() - tiempoInicioCancion; // Tiempo transcurrido desde el inicio de la canción
      
      // Convertir el tiempo en minutos y segundos
      unsigned long minutos = (tiempoTranscurrido / 60000);  // Dividir entre 60000 para obtener minutos
      unsigned long segundos = (tiempoTranscurrido % 60000) / 1000; // Obtener los segundos

      // Formatear el tiempo en el formato mm:ss
      String tiempoFormateado = String(minutos) + ":" + (segundos < 10 ? "0" : "") + String(segundos);

      // Mostrar el tiempo en el LCD
    lcd.print(tiempoFormateado); // Imprimir en el LCD
    break;
    case 2: // loop
    lcd.setCursor(7,1);
    lcd.print("|");
    delay(150);
    lcd.setCursor(7,1);
    lcd.print("/");
    delay(150);
    lcd.setCursor(7,1);
    lcd.print("-");
    delay(150);
    lcd.setCursor(7,1);
    lcd.print("\\");
    delay(150);
    lcd.setCursor(7,1);
    lcd.print("|");
    delay(150);
    break;
    case 3: //next
    lcd.setCursor(7,1);
    for(int i = 0; i<=5;i++){
    lcd.print(">");
    delay(150);}
    break;
    case 4: //back
    lcd.setCursor(13,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(12,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(11,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(10,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(9,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(8,1);
    lcd.print("<");
    delay(150);
    lcd.setCursor(7,1);
    lcd.print("<");
    delay(150);
    break;
    case 5: //pausa
    lcd.setCursor(7,1);
    for(int i = 0; i<=5;i++){
    lcd.print(".");
    delay(150);}
    break;
    case 6: //Volumen up
    lcd.setCursor(7,1);
    lcd.print("Mas alto!");
    break;
    case 7: //Volumen down
    lcd.setCursor(7,1);
    lcd.print("Shhh...");
    break;
    case 8: //Ad
    lcd.setCursor(7,1);
    for(int i = 0; i<=5;i++){
    lcd.print("A");
    delay(150);}
    break;
  }
}

void clearLine(int line) {
  // Set the cursor to the beginning of the line
  lcd.setCursor(0, line);
  
  // Write spaces to overwrite the entire line
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");  // Print a space on each column of the selected line
  }
  
  // Optionally, move the cursor back to the beginning of the line
  lcd.setCursor(0, line);
}

void reiniciarTiempo() {
  tiempoInicioCancion = millis();  // Reiniciar el tiempo de inicio a la hora actual
}