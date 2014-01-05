#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <malloc.h>

#include "bacterias.h"
#include "animaciones.c"
#include "movimientos.c"
#include "bacterias.c"
#include "menu.c"
#include "ai.c"
#include "xml.c"
#include "game.c"

volatile long speed_counter = 0;//variable para controlar el tiempo global
//incrementa el contador de tiempo
void increment_speed_counter(){
	if(speed_counter < 2000000000)
		speed_counter++;
	else
		speed_counter = 0;
}END_OF_FUNCTION(increment_speed_counter);
//funcion principal
int main(int argc, char *argv[]){

	int seguro = seguridad();//para verificar que todos los archivos esten accesibles
	
	set_uformat(U_ASCII);//permite usar teclado latino
	
	srand ( time(NULL) );//randomizar random
	
	allegro_init();//inicializar allegro
	install_keyboard();//añadir teclado
	install_timer();//añadir funcion de timer
	install_mouse();//añadir mouse
	
	//las funciones de timer corren en background
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));
	
	//inicializar sonido
	
	reserve_voices(5,5);
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
	
	set_volume(255,255);
	
	//inicializar video
	set_color_depth(desktop_color_depth());
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
	
	if(!seguro){//si algun archivo necesario no se encuentra se informa y termina el programa
		allegro_message("ERROR, no se encuentran todos los archivos, el programa debe cerrarse");
		exit(1);
	}
	//sonidos de botones
	SAMPLE *btn_clicked = load_sample("sonidos/btn_clicked.wav");
	SAMPLE *boton = load_sample("sonidos/boton.wav");
	SAMPLE *sonido_seleccion = load_sample("sonidos/seleccionado.wav");
	
	//se prepara el tipo de fuente propio
	DATAFILE *font_source;
	FONT *mv_boli;
	font_source = load_datafile("font/mv_boli.dat");
	mv_boli = (FONT *)font_source[0].dat;
	
	//se reemplaza el cursor del mouse por nuestro cursor
	BITMAP* cursor = load_bitmap("imagenes/cursor.bmp",NULL);
	set_mouse_sprite(cursor);
	
	char tablero_inicial[12][12];//tablero de estado inicial de cualquier juego
	int game_type;//tipo de juego 
	int current_menu = PORTADA;//iniciamos el menu del programa en la portada
	
	//vaciamos los strings de nombres y carpetas para xml
	char folder1[200] = "";
	char folder2[200] = "";
	char player0[26]  = "";
	char player1[26]  = "";
	
	/*el sieguiente while se encarga de que el programa siga mientras algun elemento del jeugo este activo*/
	while(current_menu){
		//[ver glosario DEFINICIONES DE MENU]
		switch(current_menu){
			case PORTADA:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = portada();
			}
			case MAIN_MENU:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = main_menu(&game_type,boton);
				if (current_menu == EXIT)
					current_menu = FALSE;
				break;
			}
			case PVPC:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = name_menu(PVPC,player0,player1,mv_boli,tablero_inicial,boton,sonido_seleccion);
				break;
			}
			case PVP:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = name_menu(PVP,player0,player1,mv_boli,tablero_inicial,boton,sonido_seleccion);
				break;
			}
			case PCVPC:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = xml_menu(folder1,folder2);
				break;
			}
			case PCVPC_NAME:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = pcvpc_name_menu(player0,player1,mv_boli,boton,tablero_inicial);
				break;
			}
			case BOARD_EDITOR:{
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = board_editor_menu(game_type,tablero_inicial,boton,sonido_seleccion);
				break;
			}
			case GAME:{
				if(game_type == PCVPC){
					if(folder1[strlen(folder1)]=='\\'){
						strcat(folder1,"\\");
					}
					strcat(folder1,player1);
					strcat(folder1,".xml");
					if(folder1[strlen(folder1)]=='\\'){
						strcat(folder1,"\\");
					}
					strcat(folder2,player0);
					strcat(folder2,".xml");
				}
				play_sample(btn_clicked,255,128,1000,0);
				current_menu = game(cursor,player0,player1,game_type,tablero_inicial,boton,sonido_seleccion,folder1,folder2);
				break;
			}
		}
	}
	
	
	
	return 0;

}END_OF_MAIN();
