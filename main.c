#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { EMPTY, TORRE, ALFIL, REY, REINA, CABALLO, PEON } tipo_t;
typedef enum { NEGRO, BLANCO } color_t;

char *graphic_representation[] = {" ","♜","♝","♚","♛","♞","♟"};

typedef struct pieza {
  tipo_t tipo;
  color_t color;
} pieza_t;

typedef struct celda {
  pieza_t *pieza;
  color_t color;
} celda_t;


celda_t tablero[8][8];

color_t turno = BLANCO;

tipo_t init_positions[8][8] = {
  {TORRE,CABALLO,ALFIL,REINA,REY,ALFIL,CABALLO,TORRE},
  {PEON,PEON,PEON,PEON,PEON,PEON,PEON,PEON},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {PEON,PEON,PEON,PEON,PEON,PEON,PEON,PEON},
  {TORRE,CABALLO,ALFIL,REINA,REY,ALFIL,CABALLO,TORRE}
};

color_t init_colors[8][8] = {
  {BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO},
  {BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO,BLANCO},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
  {NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO},
  {NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO,NEGRO}
};


void inicializar_tablero(){
  int row, column, color;
  for( row = 0; row < 8; row++ ){
    color = row % 2;
    for( column = 0; column < 8; column++ ){
      color = !color;

      pieza_t *pieza = (pieza_t*) malloc(sizeof(pieza_t));
      pieza->color = init_colors[row][column];
      pieza->tipo = init_positions[row][column];

      tablero[row][column].color = color;
      tablero[row][column].pieza = pieza;
    }
  }
}

void imprimir_pieza( pieza_t *pieza ){
  if(!pieza){
    printf(" ");
  }else{
    printf("%s ", graphic_representation[pieza->tipo]);
  }
}

void textcolor(color_t fg, color_t bg)
{ 
  printf("\e[0;%d;%dm", ((fg)?7:0)  + 30 , ((bg)?4:6) + 40);
}

void textclear(){
  printf("\e[0m");
}

void imprimir_tablero()
{
  int row, column;
  celda_t *celda = NULL;
  pieza_t *pieza = NULL;

  textclear();
  for( row = 0; row < 8; row++ ){
    printf("%d ", 8-row);
    for( column = 0; column < 8; column++ ){
      celda = &tablero[row][column];
      pieza = celda->pieza;
      textcolor(pieza->color,celda->color);
      imprimir_pieza(pieza);
    }
    textclear();
    printf("\n");
  }
  printf("  ");
  for( column = 'a'; column <= 'h'; column++ ){
    printf("%c ", (char) column);
  }
  printf("\n");
}

void clean_buffer(){
  while(getchar()!='\n');
}

void read_command( char *command )
{
  printf(">");
  fgets(command, 512, stdin);

  int l = strlen(command);
  if( command[l-1] == '\n' ){
    command[l-1] = '\0';
  }else{
    clean_buffer();
  }
}

int process_movement( char *mov ){
  int l = strlen(mov);
  if( l != 4 )
    return 0;
  
}

void process_command( char *command )
{
  if( strcmp(command,"help") == 0 ){
    puts("Ayuda");
  }else{
    process_movement(command);
    imprimir_tablero();
  }
}

int main( int argc, char *argv[] )
{ 
  inicializar_tablero();
  
  char command[512];
  read_command(command);
  while( strcmp(command,"exit") != 0 ){
    process_command(command);
    read_command(command);
  }

  exit(EXIT_SUCCESS);
}