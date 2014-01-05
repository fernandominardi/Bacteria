
#define hex_w2              40 //ancho del hexagono sin un triangulo lateral
#define COLOR_NULO          65280

#define PORTADA             1

#define AZUL   	            255   //azul
#define VERDE               16777215   //blanco
#define SANO   	            16776960   //amarillo
#define BORRAR              16744192   //naranja

#define PVPC 	            6579300    //gris 
#define PCVPC               16777215   //blanco  *
#define PVP                 255        //azul    *
#define EXIT   	            16776960   //amarillo

#define MAIN_MENU           16744192   //naranja  *
#define RESET               16777215   //blanco
#define CHEAT               255        //azul

#define STND_BOARD          16711680   //rojo
#define BOARD_EDITOR        65535      //celeste *

#define BTN_AZUL        	6579300    //gris 
#define BTN_VERDE        	16744192   //naranja
#define BEGIN_GAME          16711680   //rojo

#define PLAYER0             255        //azul
#define PLAYER1             16776960   //amarillo

#define XML_INPUT1          16711680   //rojo
#define XML_INPUT2          16777215   //blanco
#define XML_SELECT1         255        //azul
#define XML_SELECT2         16776960   //amarillo
#define XML_CONTINUE        65535      //celeste


#define XML_FOLDER_OK       16711680   //rojo
#define XML_FOLDER_CANCEL   16777215   //blanco

#define PCVPC_NAME          16776960   //amarillo *
#define GAME                16711680   //rojo     *

#define EMPATE              3
#define NO_HAY_GANADOR		4

#define SKIP                5

#define MULTIPLICAR 	    1
#define PROPAGAR 	        2
#define PASAR               3

#define crear_int_jugada(a,b,c,d,e) (a)*100000000 + (b)*1000000 + (c)*10000 + (d)*100 + (e)

#define get_jugada(a)       (a)/100000000
#define get_fila_inicial(a) ((a)%100000000)/1000000
#define get_col_inicial(a)  ((a)%1000000)/10000
#define get_fila_final(a)   ((a)%10000)/100
#define get_col_final(a)    (a)%100

typedef struct hijo{
	int jugada;
	int cant_azul;
	int cant_verde;
	struct hijo *ptr_padre;
	struct hijo **pptr_hijo;

}hijo;

enum codigo{
	BACTERIA_AZUL,
	BACTERIA_VERDE,
	SIN_TEJIDO,
	TEJIDO_SANO
};

#include "globales.c"

int ai_main(char tablero[tab_h][tab_w]);
void animacion_contaminar(int f, int c, char tablero[tab_h][tab_w], BITMAP* hex, int tab_pos_x, int tab_pos_y);
void animacion_multiplicar(int f, int c, int tipo, BITMAP* hex, int tab_pos_x, int tab_pos_y);
void aplicar_jugada(char tablero[tab_h][tab_w],int jugada,int TURNO_aux);
int board_editor_menu(int game_type,char tablero_inicial[12][12], SAMPLE *sonido_boton,SAMPLE *sonido_seleccion);
void cambiar_turno();
int cant_propagaciones(char tablero[tab_h][tab_w],int TURNO_aux);
void cargar_propagaciones(char tablero[tab_h][tab_w],int prop_posibles[], int TURNO_aux);
void cheat_handler(char tablero[tab_w][tab_h],int tab_pos_x,int tab_pos_y, BITMAP* sano, BITMAP* mult, BITMAP* prop);
void clear_cheat(char tablero[tab_w][tab_h],BITMAP* sano, int tab_pos_x, int tab_pos_y);
void contaminar(char tablero[tab_h][tab_w],int f,int c, BITMAP* hexagono, int tab_pos_x, int tab_pos_y);
void contaminar_ai(char tablero[tab_h][tab_w],int f,int c,int TURNO_aux);
void contar_bacterias(char tablero[tab_w][tab_h], int *cant_azul, int *cant_verde);
int contar_casillas(char tablero[tab_h][tab_w]);
void crear_hijos(hijo *nodo,char tablero[tab_h][tab_w], int TURNO_aux);
int crear_jugada_prop(char tablero[tab_h][tab_w],int f1, int c1, int f2, int c2);
void crear_nieto(hijo *nodo,char tablero_aux_hijos[tab_h][tab_w], int TURNO_aux);
void current_folder(char folder[200]);
int elegir_jugada(hijo *nodo);
int es_casilla_valida( int tab_pos_x, int tab_pos_y, int x, int y);
int es_jugada_valida(int jugada,char tablero[tab_h][tab_w]);
int es_vecino(int fo,int co,int fd,int cd);
int es_vecino_al_vecino(int fo,int co,int fd,int cd);
int game(BITMAP* cursor,char player0[26],char player1[26], int game_type, char tablero_inicial[12][12],SAMPLE *boton,SAMPLE *sonido_seleccion,char write_to_file[],char read_from_file[]);
void ganador();
int generar_tablero(char tablero[tab_h][tab_w],BITMAP* hex, int tab_pos_x, int tab_pos_y, int tab_bmp_w, int tab_bmp_h);
int get_jugada_xml(char nombre_archivo[]);
int get_pos_c(int x,int y,int tab_pos_x, int tab_pos_y);
int get_pos_f(int x,int y,int tab_pos_x, int tab_pos_y);
void imprimir_datos(int cant_azul, int cant_verde, char player0[26], char player1[26], FONT* mv_boli_12);
void increment_speed_counter();
int ingame_menu(char tablero[tab_h][tab_w],char tablero_inicial[12][12], BITMAP* hex, BITMAP* sano, int tab_pos_x, int tab_pos_y, int tab_bmp_w,int tab_bmp_h, int primer_turno, SAMPLE *boton,SAMPLE *sonido_seleccion);
void instrucciones(int id);
void jugada_xml(char nombre_archivo[],int jugada,int f1, int c1, int f2, int c2);
void liberar_arbol(hijo *nodo);
int main_menu(int* game_type, SAMPLE *boton);
int multiplicar(char tablero[tab_h][tab_w],int f, int c, BITMAP* hexagono, int tab_pos_x, int tab_pos_y);
int multiplicar_ai(char tablero[tab_h][tab_w],int f, int c,int TURNO_aux);
int name_menu(int vs,char player0[26],char player1[26],FONT* mv_boli,char tablero_inicial[12][12], SAMPLE *boton,SAMPLE *sonido_seleccion);
int pcvpc_name_menu(char player0[26],char player1[26],FONT* mv_boli, SAMPLE *boton,char tablero_inicial[12][12]);
int portada();
void preparar_mult(char tablero[tab_h][tab_w],int mult_posibles[tab_h][tab_w],int TURNO_aux);
void preparar_prop(char tablero[tab_h][tab_w],int posib_jugadas[18],int f, int c);
int propagar(char tablero[tab_h][tab_w],int f,int c,int tab_pos_x,int tab_pos_y,BITMAP* hexagono,BITMAP* cursor);
int propagar_ai(char tablero[tab_h][tab_w],int f1, int c1,int f2,int c2,int TURNO_aux);
int propagar_PC(char tablero[tab_h][tab_w],int f,int c,int fd,int cd,int tab_pos_x,int tab_pos_y,BITMAP* hexagono);
void reset(char tablero[tab_h][tab_w], char tablero_inicial[12][12] , int primer_turno);
void reset_tablero(char tablero[tab_h][tab_w],char tablero_aux[tab_h][tab_w]);
int seguridad();
void standard_board_creator(char tablero_inicial[12][12]);
int verificar_edicion(char tablero[12][12]);
int xml_menu(char write_to_folder[200],char read_from_folder[200]);


































