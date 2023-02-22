// C++ code
//add more colors for "color wheel" (6 colors - 3 primary colors plus their combinations)
//give feedback of right or wrong response (sounds? lights flashing? vibration?)

/////PIN SETUP////
int xJoy = A0;
int yJoy = A1;

int GreenPin = 2; // X LOW
int YellowPin = 3;// Y HIGH
int RedPin = 4;  // X HIGH
int BluePin = 5;  // Y LOW
int OrangePin = 6;
int PurplePin = 7;



int numlevels = 10; //sets game array sizes. Controlling game lenght and therefore difficulty


void setup()
{
  //allow for serial monitor communication
  Serial.begin(9600);


  //set LED pins to output
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(PurplePin, OUTPUT);
  pinMode(OrangePin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  //turn off all LEDs (this is probably not actually needed)
  digitalWrite(RedPin, LOW);
  digitalWrite(GreenPin, LOW);
  digitalWrite(YellowPin, LOW);
  digitalWrite(BluePin, LOW);
  digitalWrite(PurplePin, LOW);
  digitalWrite(OrangePin, LOW);
}

void loop()
{
  //initiate game arrays
  int gamearr[numlevels]; //will be populated with random game array
  int userarr[numlevels]; //will be populated with user responses

  //game begin (NOTE: you should include some sort of "game start" here)
  for (int i = 0; i < numlevels ; i++){

    //Pause between user seeing their last entry and new sequence begin. On first play, this will act as a delay.
    delay(2000);

    gamearr[i] = random(2,8); //ranodm LED pin chosen and added to sequence (I dont like how ranodom works.. try something else?)

    //sequence to match shown to user
    for(int y = 0; y <= i; y++)
    {
      digitalWrite(gamearr[y],HIGH);
      delay(1500);
      digitalWrite(gamearr[y],LOW);
      delay(150);
    }

    //user entry recoreded here
    for(int userentries = -1; userentries < i; userentries){
      
      //joystick input read from user
      int xValue = analogRead(A0);
      int yValue = analogRead(A1);


      //process joystick input..
        //1. determine what light was selected
        //2. turn on that light for user to see what they selected
        //3. delay for half second so that one selection isnt taken multiple times
        //4. enter user selection into user entered array
        //5. delay so that user can process thier entry
        //6. turn off the light

        //(NOTE: Else statments are probably unnecessary)

      ////X CONTROLS////
      //Red//
      if(xValue >= 800 && yValue <= 600 && yValue >= 400){
      digitalWrite(RedPin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = RedPin;
      delay(1000);
      digitalWrite(RedPin, LOW);
      }
      else{
      digitalWrite(RedPin,LOW);
      }

      //Green//
      if(xValue <= 200 && yValue <= 600 && yValue >= 400){
      digitalWrite(GreenPin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = GreenPin;
      delay(1000);
      digitalWrite(GreenPin, LOW);
      }
      else{
      digitalWrite(GreenPin,LOW);
      }

      ////Y CONTROLS////
      //Yellow//
      if(yValue >= 650 && xValue <= 350){
      digitalWrite(YellowPin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = YellowPin;
      delay(1000);
      digitalWrite(YellowPin, LOW);
      }
      else{
      digitalWrite(YellowPin,LOW);
      }
    
      //Orange//
      if(yValue >= 650 && xValue >= 650){
      digitalWrite(OrangePin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = OrangePin;
      delay(1000);
      digitalWrite(OrangePin, LOW);
      }
      else{
      digitalWrite(OrangePin,LOW);
      }  
    

      //Blue//
      if(yValue <= 350 && xValue <= 350){
      digitalWrite(BluePin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = BluePin;
      delay(1000);
      digitalWrite(BluePin, LOW);
      }
      else{
      digitalWrite(BluePin,LOW);
      }
      
      //Purple//
      if(yValue <= 350 && xValue >= 650){
      digitalWrite(PurplePin, HIGH);
      userentries++;
      delay(500);
      userarr[userentries] = PurplePin;
      delay(1000);
      digitalWrite(PurplePin, LOW);
      }
      else{
      digitalWrite(PurplePin,LOW);
      }
    }

    //output to serial the game array (this was used to test if the compare block is working properly later)
    Serial.println("Array Wanted:");
    for(int count = 0; count <= i; count++){
      Serial.print(gamearr[count]);
      Serial.print(" ");
    }

    Serial.println("");

    Serial.println("Array Recieved:");
    for(int count = 0; count <= i; count++){
      Serial.print(userarr[count]);
      Serial.print(" ");
    }

    Serial.println("");

    //compare the randomly generated array to the user inputted array
    int quit = 0;
    for(int count = 0; count <= i; count++){
      if(gamearr[count] != userarr[count]){
        quit = 1;
        break;
      }
    }


    //if the two arrays do not match, break the game for loop
    if(quit ==1){
      Serial.println("Inputs do not match. Quiting...");

      //flash lights
      for(int flash = 0; flash <= 4; flash++){

        digitalWrite(RedPin, HIGH);
        digitalWrite(GreenPin, HIGH);
        digitalWrite(YellowPin, HIGH);
        digitalWrite(BluePin, HIGH);
        digitalWrite(PurplePin, HIGH);
        digitalWrite(OrangePin, HIGH);

        delay (250);

        digitalWrite(RedPin, LOW);
        digitalWrite(GreenPin, LOW);
        digitalWrite(YellowPin, LOW);
        digitalWrite(BluePin, LOW);
        digitalWrite(PurplePin, LOW);
        digitalWrite(OrangePin, LOW);

        delay(250);

      }

      
      break;
    }

  
  }
  delay(1000000); //delay next playthrough for 1000s. This is temporary, for development
}