#include <LiquidCrystal.h>
#define TARGET_FPS 17
#define LAST_WRLD 1
#define BUTTON(x) digitalRead(x) == HIGH
LiquidCrystal lcd(12,6,11,5,4,3,2);
struct Player{
  int x;
  int y;
  int lastx;
  int lasty;
  
};
byte playerchar[8] = {
  B00000,
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};
byte emptychar[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte housechar[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B01110,
  B01110,
  B01110
};
byte wallchar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte starchar[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B00100,
  B00000,
  B00000
};
byte mountchar[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00100,
  B01100,
  B01110,
  B11110
};
byte crosschar[8] = {
  B00000,
  B00100,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};
char world1[8][2][16] = {
 {{5,1,1,3,1,1,1,5,1,1,1,1,1,1,1,3},
  {5,1,1,1,1,2,1,1,1,5,5,5,5,1,4,3}},

 {{5,1,2,1,1,1,1,1,1,1,5,1,1,1,1,3},
  {5,1,1,1,5,2,5,2,5,1,1,1,5,3,4,3}},

 {{5,1,5,1,1,1,5,1,1,1,5,1,1,1,1,3},
  {5,1,1,1,5,1,1,1,5,1,1,1,5,1,4,3}},

 {{5,1,1,1,1,1,1,1,1,1,1,5,1,1,1,3},
  {5,3,3,1,3,3,1,1,3,3,1,1,1,3,4,3}},

 {{5,1,2,1,1,1,1,1,1,1,1,1,1,1,1,3},
  {5,1,1,1,5,1,1,1,1,1,1,3,3,1,6,3}},

 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}},
  
 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}},
  
 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}} 
};
char world[8][2][16] = {
 {{5,1,1,3,1,1,1,5,1,1,1,1,1,1,1,3},
  {5,1,1,1,1,2,1,1,1,5,5,5,5,1,4,3}},

 {{5,1,2,1,1,1,1,1,1,1,5,1,1,1,1,3},
  {5,1,1,1,5,2,5,2,5,1,1,1,5,3,4,3}},

 {{5,1,5,1,1,1,5,1,1,1,5,1,1,1,1,3},
  {5,1,1,1,5,1,1,1,5,1,1,1,5,1,4,3}},

 {{5,1,1,1,1,1,1,1,1,1,1,5,1,1,1,3},
  {5,3,3,1,3,3,1,1,3,3,1,1,1,3,4,3}},

 {{5,1,2,1,1,1,1,1,1,1,1,1,1,1,1,3},
  {5,1,1,1,5,1,1,1,1,1,1,3,3,1,6,3}},

 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}},
  
 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}},
  
 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1}} 
};
int  lvl = 0;
int  wcnt = 1;
bool win = false;
bool go = false;
Player p;
void loadworld(char*** _world){
  for(int x = 0;x < 8;x++){
    for(int y = 0;y < 2;y++){
       for(int z = 0;z < 16;z++){
        world[x][y][z] = _world[x][y][z];
       }
    }
  }
  lvl = 0;
  
}
void wincutscene(){
  for(int x = 0;x < 16;x++){
      for(int y = 0;y < 2;y++){
        lcd.setCursor(x,y);
        lcd.write(char(1));
    }
  }
  lcd.setCursor(0,7);
  lcd.write(char(0));
  win = true;
  delay(2000);
  
}
void setup() {
  //initialize graphics
  lcd.createChar(0, playerchar);
  lcd.createChar(1, emptychar);
  lcd.createChar(2, housechar);
  lcd.createChar(3, wallchar);
  lcd.createChar(4, starchar);
  lcd.createChar(5, mountchar);
  lcd.createChar(6, crosschar);
  //lcd.createChar(7, mountchar);
  
  lcd.begin(16, 2);

  //initialize input
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  bool start = false;
  while (!start){
  lcd.home();
    lcd.print("  KOK:the game");
    lcd.setCursor(0,1);
    lcd.print("press anything!");
    if(BUTTON(9)){
      start = true;
    }
    if(BUTTON(7)){
      start = true;
    }
    if(BUTTON(10)){
      start = true;
    }
  
    if(BUTTON(8)){
      start = true;
    }
  }
  //load the first world
  //loadworld((char***)world1);

  p.x = 1;
  p.y = 0;
}



void display(){
if(win){
lcd.home();
lcd.print("you win!");
lcd.setCursor(0,1);
lcd.print("press anything!");
return;
}
if(go){
lcd.home();
lcd.print("GAME OVER!");
lcd.setCursor(0,1);
lcd.print("press anything!");
return;
}
for(int x = 0;x < 16;x++){
  for(int y = 0;y < 2;y++){
    lcd.setCursor(x,y);
    if (x == p.x &&y == p.y ){
      lcd.write(char(0));
      continue;
    }
    lcd.write(world[lvl][y][x]);
  }
}
}
void logic(){
if(!(win || go)){
  p.lastx = p.x;
  p.lasty = p.y;
  //movement
  if(BUTTON(9)){
    p.x++; 
    goto evalcoll;
  }
  if(BUTTON(7)){
    p.x--; 
    goto evalcoll;
  }
  if(BUTTON(10)){
    p.y++;
    goto evalcoll;
  }

  if(BUTTON(8)){
    p.y--; 
    goto evalcoll;
  }
  evalcoll:
  //position limits
  if(p.x > 15)
    p.x = 15;
  if(p.y > 1)
    p.y = 1;
  if(p.x < 0)
    p.x = 0;
  if(p.y < 0)
    p.y = 0;
  //collision
  if(world[lvl][p.y][p.x] == 4){
    if(lvl == 8){
      win = true;
      return;      
    }
    lvl++;
    p.x = 1;
    p.y = 0;
     
  }
  if(world[lvl][p.y][p.x] == 6){
    world[lvl][p.y][p.x] = 1;
    lcd.clear();
    if(wcnt == LAST_WRLD){
      wincutscene();
      return;      
    }
    
  }
  if(world[lvl][p.y][p.x] == 5){
    lcd.clear();
    go = true;
    
  }
  if(world[lvl][p.y][p.x] != 1){
    p.x = p.lastx;
    p.y = p.lasty;    
  }


}else{
    delay(500);
   if(BUTTON(9)||BUTTON(7)||BUTTON(10)||BUTTON(8)){
    win = false;
    go = false;
    lvl = 0;
    p.x = 1;
    p.y = 0;
   }
   
}
}

void loop() {
logic();
display();
delay(1000/TARGET_FPS);
}
