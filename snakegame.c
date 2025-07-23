#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define HEIGHT 20
#define WIDTH 60
#define MAX_SNAKE_LENGTH 100

int score = 0;
int snake_length = 1;
int speed = 100;
int tail_x[MAX_SNAKE_LENGTH], tail_y[MAX_SNAKE_LENGTH];

enum Direction{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  STOP
};

enum Direction dir;
int fruit_x, fruit_y;
int snake_head_x, snake_head_y;

void set_terminal_settings();
void reset_terminal_settings();
void clear_screen();
void print_screen();
void setup();
void gameplay();
void input();
void hide_cursor();
void show_cursor();
int check_collision();

static HANDLE hStdin, hStdout;
static DWORD originalInputMode, originalOutputMode;

int main(){
  srand(time(NULL));
  set_terminal_settings();
  setup();
  while(1){
   print_screen();
   input();
   gameplay();
   
   if(check_collision()){
     clear_screen();
     printf("\n\n\t\tGAME OVER!\n");
     printf("\t\tFinal Score: %d\n", score);
     printf("\t\tThankyou for playing!Developed by cheescake.");
     printf("\t\tPress any key to exit..\n");
     _getch();
     break;
   }
   
   Sleep(speed);
  }
return 0;
}

void input(){
    if(_kbhit()){ 
        char ch = _getch();
        switch (ch) {
            case'w': dir = UP; break;
            case'a': dir = LEFT; break;
            case's': dir = DOWN; break;
            case'd': dir = RIGHT; break;
            case'x': exit(0); break;
            default: break;
        }
    }
}

void setup(){
  snake_head_x = WIDTH/2;
  snake_head_y = HEIGHT/2;
  fruit_x = rand() % WIDTH ;
  fruit_y = rand() % HEIGHT;
  dir = STOP;
  
  // tail
  for(int i = 0; i < MAX_SNAKE_LENGTH; i++){
    tail_x[i] = -1;
    tail_y[i] = -1;
  }
}

void gameplay(){
  int prev_head_x = snake_head_x;
  int prev_head_y = snake_head_y;
  
  switch(dir){
    case UP:
    snake_head_y--;
    break;
    case DOWN:
    snake_head_y++;
    break;
    case LEFT:
    snake_head_x--;
    break;
    case RIGHT:
    snake_head_x++;
    break;
    case STOP:
    break;
  }

  if(snake_head_x < 0){
    snake_head_x = WIDTH - 1;
  }else if(snake_head_x >= WIDTH){
    snake_head_x = 0;
  }

  if(snake_head_y < 0){
    snake_head_y = HEIGHT - 1;
  }else if(snake_head_y >= HEIGHT){
    snake_head_y = 0;
  }

  int temp_x = prev_head_x;
  int temp_y = prev_head_y;
  
  for(int i = 0; i < snake_length - 1; i++){
    int temp2_x = tail_x[i];
    int temp2_y = tail_y[i];
    
    tail_x[i] = temp_x;
    tail_y[i] = temp_y;
    
    temp_x = temp2_x;
    temp_y = temp2_y;
  }

  if(snake_head_x == fruit_x && snake_head_y == fruit_y){
    score += 10;
    snake_length++;
    
    // Increase speed
    if(speed > 30){
      speed -= 5;
    }
    
    fruit_x = rand() % WIDTH ;
    fruit_y = rand() % HEIGHT;
  }
}

int check_collision(){
  for(int i = 0; i < snake_length - 1; i++){
    if(snake_head_x == tail_x[i] && snake_head_y == tail_y[i]){
      return 1;
    }
  }
  return 0;
}

void print_screen(){
  clear_screen();
  printf("\t\tWelcome to snake game!");
  printf("\n");
  for(int i =0;i< WIDTH+2;i++){
    printf("#");
  }

  for(int i =0;i<HEIGHT;i++){
    printf("\n#");
    for(int j = 0;j<WIDTH;j++){
      int is_tail = 0;
      
      for(int k = 0; k < snake_length - 1; k++){
        if(tail_x[k] == j && tail_y[k] == i){
          printf("o");
          is_tail = 1;
          break;
        }
      }
      
      if(!is_tail){
        if(i == snake_head_y && j == snake_head_x){
          printf("O");
        }
        else if(i == fruit_y && j == fruit_x){
          printf("F");
        }
        else{
          printf(" ");
        }
      }
    }
    printf("#");
  }

  printf("\n");
  for(int i =0;i< WIDTH+2;i++){
    printf("#");
  }
  printf("\nScore: %d",score);
}

void set_terminal_settings(){
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  
    GetConsoleMode(hStdin, &originalInputMode);
    GetConsoleMode(hStdout, &originalOutputMode);
    atexit(reset_terminal_settings);
    DWORD inputMode = originalInputMode;
    inputMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, inputMode);
    hide_cursor();
}

void reset_terminal_settings(){
   SetConsoleMode(hStdin, originalInputMode);
    SetConsoleMode(hStdout, originalOutputMode);
    show_cursor();
}

 void clear_screen(){
    #ifdef _WIN32
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    GetConsoleScreenBufferInfo(hStdout, &csbi);
    FillConsoleOutputCharacter(hStdout, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdout, coord);
    #else
    system("clear");
    #endif
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdout, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdout, &cursorInfo);
}

void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hStdout, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hStdout, &cursorInfo);
}