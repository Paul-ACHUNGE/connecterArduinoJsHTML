const int ledspin[4][4]={
  {22,23,24,25},
  {26,27,28,29},
  {30,31,32,33},
  {34,35,36,37},
};
void setup() {
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      pinMode(ledspin[i][j],OUTPUT);
      digitalWrite(ledspin[i][j],LOW);
    }
  }
  randomSeed(analogRead(0));
  // put your setup code here, to run once:

}

void loop() {
  for(int i=0;i<4;i++)mode1();
    for(int i=0;i<4;i++)mode2();
    for(int i=0;i<5;i++)mode3();
    for(int i=0;i<30;i++)mode4();
  }
  void clear(){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        digitalWrite(ledspin[i][j],LOW);
      }
      }
    }
    void mode1(){
      for(int i=0;i<4;i++){
        clear();
        for(int j=0;j<4;j++)digitalWrite(ledspin[i][j],HIGH);
        delay(300);
      }
     }
     void mode2(){
      for(int j=0;j<4;j++){
        clear();
        for(int i=0;i<4;i++)digitalWrite(ledspin[i][j],HIGH);
        delay(300);
      }
      }
      void mode3(){
        for(int k=0;k<=6;k++){
          clear();
          for(int i=0;i<4;i++){
           for(int j=0;j<4;j++){
            if(i+j==k)digitalWrite(ledspin[i][j],HIGH); 
           }
          }
          delay(200);
         }
        }
        void mode4(){
          clear();
          digitalWrite(ledspin[random(0,4)][random(0,4)],HIGH);
          delay(150);
  // put your main code here, to run repeatedly:

}
