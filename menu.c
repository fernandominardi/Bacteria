
extern volatile long speed_counter;
/* Muestra la pantalla inicial del juego */
int portada(){
	int current_menu = PORTADA;
	BITMAP* portada_bmp = load_bitmap("imagenes/portada.bmp",NULL);
	show_mouse(portada_bmp);
	while(key[KEY_ESC]){//En el caso de que se ingrese a la portada (desde el main_menu) por medio del botón ESC se actualiza la pantalla hasta que se libere dicho boton
		blit(portada_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	clear_keybuf();
	while(current_menu==PORTADA){//Se actualiza la pantalla hasta que se presione cualquier tecla 
		blit(portada_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		if(keypressed()){
			current_menu = MAIN_MENU;
		}
		
	}
	show_mouse(NULL);
	clear_keybuf();
	destroy_bitmap(portada_bmp);
	return current_menu;
}
/* Esta función es llamada cuando se debe que mostrar alguna instrucción */
void instrucciones(int id){
	/*
	parametro
		id = identificador de la instruccion a mostrar (posibles valores GAME y BOARD_EDITOR)
	
	Las instrucciones pueden tener mas de una pagina y cada pagina tiene su versión en ingles y en español.
	Para indicar la pagina a mostrar se utiliza la varible pag ( 1, 2, 3 = paginas en español ; 11, 12, 13 = paginas en en ingles).
	Si la variable pag tiene un valor negativo es porque indica que se acaba de cambiar de 
	pagina por lo que se multiplica por -1 para obtener el verdadero valor de la pagina.
	*/
	
	//Se carga la fuente correspondiente
	DATAFILE *font_source_12;
	FONT *mv_boli_12;
	font_source_12 = load_datafile("font/mv_boli_12.dat");
	mv_boli_12 = (FONT *)font_source_12[0].dat;
	
	BITMAP* inst_fondo = load_bitmap("imagenes/background.bmp",NULL);
	int pag = -1;//Se inicializa pag indicando la primera pagina en ingles y con valor negativo para indicar cambio reciente
	clear_keybuf();
	switch(id){
		
		
		case GAME:{
			BITMAP* game_inst = load_bitmap("imagenes/game_inst.bmp",NULL);//game_inst contiene un bmp con las explicaciones de las teclas que se utilizan en el menu de instrucciones actual 
			while(pag){//la pagina cero indica salida de las instrucciones
				if(pag<0){//numero negativo = cambio de pagina reciente
					pag *= -1;//El valor se vuelve positivo
					inst_fondo = load_bitmap("imagenes/background.bmp",NULL);
					draw_sprite(inst_fondo, game_inst, 576, 0);//se pinta el fondo ( tapando cualquier palabra previamente impresa )
					switch(pag){
						case 1:{
							show_mouse(NULL);
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 700, 90,180, makecol(239,189,39),-1,"RULES");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 700, 100+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"The object is to own the greatest possible");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 700, 100+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"amount of bacteria on the board. Each Player");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 700, 100+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"can either move or skip turn.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 580, 280-1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"MOVES");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+0*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Spread: consists on displace one of your own bacterium to");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"a healthy tissue cell (cell without bacteria) which must be");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"one or two cells away.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 300+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Multiply: consists on adding one bacterium of your own to a");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 300+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"healthy tissue cell which must be next to an existing owned cell.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 310+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"These moves can generate contamination.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Contamination: if any bacterium reaches a healthy tissue cell");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"(by spreading or multiplying) enemy bacteria around will be");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+8*text_height( mv_boli_12),180, makecol(239,189,39),-1,"infected and will swap colors so they now belong to the player");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+9*text_height( mv_boli_12),180, makecol(239,189,39),-1,"who made the move.");
							
							show_mouse(inst_fondo);
							break;
						}
						case 2:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 90,180, makecol(239,189,39),-1,"GAME ENDS WHEN");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 110+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Board is full (no healthy tissue left)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 120+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Bacteria fully infected (only one kind");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 120+3*text_height( mv_boli_12),180, makecol(239,189,39),-1," of bacteria remains)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 130+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Three consecutive skipped turns (game");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 130+5*text_height( mv_boli_12),180, makecol(239,189,39),-1," is declared draw)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 320+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"WINNER");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"The player owning the greatest amount of");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"bacteria at end of game is the winner");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"If the end of game is caused by consecutive");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"skipped turns, game is declared draw ragardless");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"of the number of bacteria");
							show_mouse(inst_fondo);
							break;
						}
						case 3:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 70,180, makecol(239,189,39),-1,"HOW TO PLAY");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* To spread you have to click one of your own");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"bacterium, without releasing you can drag the");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"bacterium to the cell you want to spread to and");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"release the mouse-click.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* To multiply you have to click the healthy tissue");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"cell you want to multiply on, this cell must be");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"next to one existing of your bacterium.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 100+8*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* To skip turn you just have to click the");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 100+9*text_height( mv_boli_12),180, makecol(239,189,39),-1,"\"Skip Turn\" button.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 320+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"CHEAT MODE");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"When cheat mode is active you will be able to easily");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"know where to spread or multiply, to do so just place");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"mouse over your bacteria.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Blue cells shows available spreading");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 350+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Yellow cells shows available multiplying/spreading");
							
							show_mouse(inst_fondo);
							break;
						}
						case 11:{
							show_mouse(NULL);
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 90,180, makecol(239,189,39),-1,"REGLAS");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 100+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"El objetivo del juego consiste en tener la mayor");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 100+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"cantidad posible de bacterias propias en el tablero.");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 100+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"Cada jugador puede hacer un movimiento por turno");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 100+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"o saltar su turno.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 580, 280-1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"MOVIMIENTOS");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+0*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Propagar: consiste en mover una bacteria propia a una celda");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"con tejido sano (celda sin bacteria) la cual debe estar a una");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 290+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"o dos celdas de distancia.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 300+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Multiplicar: consiste en agregar al tablero una bacteria");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 300+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"propia en una celda con tejido sano la cual debe ser contigua");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 300+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"a otra bacteria propia.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 310+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"Estos movimientos pueden generar una contaminacion.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Contaminacion: si una bacteria cae a una celda sana (ya sea");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+8*text_height( mv_boli_12),180, makecol(239,189,39),-1,"por propagacion o por multiplicacion) entonces las bacterias");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+9*text_height( mv_boli_12),180, makecol(239,189,39),-1,"enemigas que esten en celdas contiguas seran contaminadas,");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+10*text_height( mv_boli_12),180, makecol(239,189,39),-1,"es decir, cambiaran de color de tal forma que ahora le");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 580, 320+11*text_height( mv_boli_12),180, makecol(239,189,39),-1,"pertenezcan al jugador que realizo el movimiento.");
							
							show_mouse(inst_fondo);
							break;
						}
						case 12:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 90,180, makecol(239,189,39),-1,"SITUACIONES DE FIN DE JUEGO");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 110+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Tablero lleno (no hay tejido sano)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 120+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Una de las bacterias es totalmente contaminada");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 120+3*text_height( mv_boli_12),180, makecol(239,189,39),-1," (solo queda un tipo de bacteria)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 130+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Se realizan tres saltos de turno consecutivos");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 130+5*text_height( mv_boli_12),180, makecol(239,189,39),-1," (esto genera un empate)");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 320+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"GANADOR");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"El ganador es el jugador que tenga el mayor");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"numero de bacterias al final del juego.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"Si el juego finalizo por producirse tres saltos");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"de turno consecutivos el juego termina en empate");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"sin importar quien tenga la mayor cantidad");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"de bacterias.");
							show_mouse(inst_fondo);
							break;
						}
						case 13:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 740, 70,180, makecol(239,189,39),-1,"COMO JUGAR");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Para propagar debes hacer click sobre una bacteria");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"propia, mantener el click, arrastrar la bacteria hasta");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"la celda en la que desees hacer este movimiento y");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"luego liberar el click. Esta celda debe estar a una o");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 80+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"dos celdas de distancia de la bacteria a propagar.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Para multiplicar debes hacer click en la celda en");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"la que desees hacer este movimiento. Esta celda debe");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 90+8*text_height( mv_boli_12),180, makecol(239,189,39),-1,"ser contigua a una o más bacterias propias.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 100+9*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Para pasar el turno debes hacer click en");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 255, 770, 100+10*text_height( mv_boli_12),180, makecol(239,189,39),-1,"el botón \"skip turn\".");
							
							
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 320+1*text_height( mv_boli_12),180, makecol(239,189,39),-1,"MODO TRUCO");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"Cuando el \"cheat mode\" este activado podrás ver con");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"facilidad las celdas en las que tus bacterias pueden");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"propagarse y multiplicarse. Para ello solo debes mover");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 330+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"el ratón sobre tus bacterias.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 340+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Las celdas celestes indican una posible propagación");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 350+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"* Las celdas amarillas indican una posible");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 770, 350+8*text_height( mv_boli_12),180, makecol(239,189,39),-1," propagación o multiplicación  ");
							
							show_mouse(inst_fondo);
							break;
						}
					}
				}
				
				
				if(keypressed()){
					if(key[KEY_ESC]){//se indica la pagina nula (cero)
						pag = FALSE;
					}else if(key[KEY_L]){//se cambia de idioma
						if(pag > 10)
							pag -= 10;
						else
							pag += 10;
						pag *= -1;//se indica que hubo un cambio de pagina
					}else if(key[KEY_RIGHT] && (pag%10)!=3 ){//si no es la ultima pagina se avanza a la siguiente
						pag++;
						pag *= -1;//se indica que hubo un cambio de pagina
					}else if(key[KEY_LEFT] && (pag%10)!=1 ){//si no es la primera pagina se retrocede a la anterior
						pag--;
						pag *= -1;//se indica que hubo un cambio de pagina
					}
					
					clear_keybuf();
				}
				
				blit(inst_fondo, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			}
			while(key[KEY_ESC]){//se actualiza la pantalla mientras se mantega presionado ESC
				blit(inst_fondo, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
			}
			break;
			destroy_bitmap(game_inst);
		}
		
		
		case BOARD_EDITOR:{
			BITMAP* editor_inst = load_bitmap("imagenes/editor_inst.bmp",NULL);//editor_inst contiene un bmp con las explicaciones de las teclas que se utilizan en el menu de instrucciones actual 
			while(pag){//la pagina cero indica salida de las instrucciones
				if(pag<0){//numero negativo = cambio de pagina reciente
					pag *= -1;//El valor se vuelve positivo
					inst_fondo = load_bitmap("imagenes/background.bmp",NULL);
					draw_sprite(inst_fondo, editor_inst, 0, 545);//se pinta el fondo ( tapando cualquier palabra previamente impresa )
					switch(pag){
						case 1:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90,180, makecol(239,189,39),-1,"HOW TO USE BOARD EDITOR");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+2*text_height( mv_boli_12),190, makecol(239,189,39),-1,"To edit custom boards you have to select the cells you want");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+3*text_height( mv_boli_12),190, makecol(239,189,39),-1,"to put in the board by clicking the right corner cells, the");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+4*text_height( mv_boli_12),190, makecol(239,189,39),-1,"glowing cell is the selected one. Then you have to click on");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+5*text_height( mv_boli_12),190, makecol(239,189,39),-1,"the board to add selected cell type.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 565, 340,180, makecol(239,189,39),-1,"WARNING");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"This Board Editor do not verifies if created board is");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"playable. A board with at least one bacterium of each colors");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"and one healthy tissue is accepted");
							
							show_mouse(inst_fondo);
							break;
						}
						case 11:{
							show_mouse(NULL);
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90,180, makecol(239,189,39),-1,"COMO USAR EL EDITOR DE TABLERO");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+2*text_height( mv_boli_12),190, makecol(239,189,39),-1,"Para la edicion debes seleccionar el tipo de celda que deseas");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+3*text_height( mv_boli_12),190, makecol(239,189,39),-1,"colocar en el tablero haciendo click en la celda deseada de la");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+4*text_height( mv_boli_12),190, makecol(239,189,39),-1,"parte superior derecha. La celda elegida se iluminara");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+5*text_height( mv_boli_12),190, makecol(239,189,39),-1,"indicando que esta seleccionada. Luego deberas hacer chick en");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+6*text_height( mv_boli_12),180, makecol(239,189,39),-1,"la marca de tablero para colocar dicha celda. Puedes hacer esto");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 225, 770, 90+7*text_height( mv_boli_12),180, makecol(239,189,39),-1,"manteniendo el click y arrastrando.");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 565, 340,180, makecol(239,189,39),-1,"ADVERTENCIA");
							
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+2*text_height( mv_boli_12),180, makecol(239,189,39),-1,"El editor solo controla que el tablero creado tenga por lo");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+3*text_height( mv_boli_12),180, makecol(239,189,39),-1,"menos una bacteria azul, una verde y un tejido sano, pero");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+4*text_height( mv_boli_12),180, makecol(239,189,39),-1,"no se controla el hecho de que con el tablero creado sea");
							textprintf_justify_ex(inst_fondo, mv_boli_12, 30, 575, 340+5*text_height( mv_boli_12),180, makecol(239,189,39),-1,"posible terminar el juego.");
							show_mouse(inst_fondo);
							break;
						}
					}
				}
				
				
				if(keypressed()){
					if(key[KEY_ESC]){//se indica la pagina nula (cero)
						pag = FALSE;
					}else if(key[KEY_L]){//se cambia de idioma
						if(pag > 10)
							pag -= 10;
						else
							pag += 10;
						pag *= -1;
					}
					clear_keybuf();
				}
				
				
				
				blit(inst_fondo, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			}
			while(key[KEY_ESC]){
				blit(inst_fondo, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla mientras se mantega presionado ESC
			}
			destroy_bitmap(editor_inst);
			break;
		}
		
	}
	
	show_mouse(tab_bmp);
	destroy_bitmap(inst_fondo);
	destroy_font(mv_boli_12);
}
/* Se utiliza para hacer una verificación del tablero editado */
int verificar_edicion(char tablero[12][12]){
	/*
	Esta función hace una simple verificación que consiste en ver que en el tablero
	estén presente por lo menos una bacteria verde, una azul, y un tejido sano
	*/
	
	int i,j;
	int bact_azul = 0, bact_verde = 0, tej_sano = 0; //estas son variables se usan para contar las bacterias de cada tipo y los tejidos sanos
	for(i=0;i<tab_h;i++){//se recorre el tablero
		for(j=0;j<tab_w;j++){
			switch(tablero[i][j]){//segun sea la celda, se incrementa en 1 el contador correspondoente
				case BACTERIA_AZUL: bact_azul++; break;
				case BACTERIA_VERDE: bact_verde++; break;
				case TEJIDO_SANO: tej_sano++; break;
			}
		}
	}
	
	if( bact_azul==0 || bact_verde==0 || tej_sano==0 ){//si alguno de los contadores es cero se retorna FALSE
		return FALSE;
	}
	return TRUE;//si se llego a este punto es porque el tablero cumple las especificaciones por lo que se retorn TRUE
	
}
/* este menu se utiliza para la edicion del tablero */
int board_editor_menu(int game_type,char tablero_inicial[12][12], SAMPLE *sonido_boton,SAMPLE *sonido_seleccion){
	/*
	parametros
		game_type = esta variable se utiliza para ser retornada en caso de que se deba volver al menu anterior (vease DEFINICIONES DE MENU en el glosario)
		tablero_inicial = se recibe esta matriz para ser modificada de acuerdo a las especificaciones del usuario
		sonido_boton = este SAMPLE se reproduce cuando el mouse se posa sobre un boton
		sonido_seleccion = este SAMPLE se reproduce cuando se clickea un boton
	*/
	aux_tab_bmp = create_bitmap(800,600);//se crea el bitmap que se utilizara para los shape (vease DEFINICIONES VARIAS en el glosario)
	BITMAP *sano = load_bitmap("imagenes/menu/editor_hex_shape.bmp",NULL);//se carga la silueta de un hexagono (vease DEFINICIONES VARIAS en el glosario)
	clear_to_color(aux_tab_bmp,COLOR_NULO);
	
	int i,j,sonido_ban=FALSE;//sonido_ban es una bandera utilizada para la reproduccion de sonido
	
	/*
	Lo que viene a continuación hasta antes de las declaraciones de los bitmap consiste 
	en la creación del bitmap shape que se utiliza para saber en qué hexagono o boton se clickea
	(vease DEFINICIONES VARIAS en el glosario)
	*/
	int hex_pos_x,hex_pos_y;
	int tab_pos_x,tab_pos_y;
	int tab_bmp_w,tab_bmp_h;
	
	//al alto y largo de la matriz se le dan los valores maximos (12 para ambos)
	tab_w = tab_h = 12;
	
	//Se calcula en pixeles el alto y el ancho de la sección rectangular que forma el tablero de hexagonos
	tab_bmp_w = tab_w*hex_w2 + sano->w - hex_w2;
	tab_bmp_h = tab_h*(sano->h) + (sano->h)/2;
	
	//Se calcula la posición del pixel inicial de la sección rectangular antes mencionada
	tab_pos_x = SCREEN_W/2 - tab_bmp_w/2;
	tab_pos_y = SCREEN_H/2 - tab_bmp_h/2;
	
	
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			//por cada posicion del tablero se calcula la posicion del hexagono correspondiente en el bitmap aux_tab_bmp
			hex_pos_y = (j%2)*((sano->h)/2) + tab_pos_y + i*(sano->h);
			hex_pos_x = j*hex_w2 + tab_pos_x;
			//con las posiciones calculadas se dibujan los hexagonos (pintados segun la posicion que representa en el tablero)
			floodfill(sano,(sano->w)/2,(sano->h)/2, j + i*tab_w);
			draw_sprite(aux_tab_bmp, sano,(hex_pos_x),(hex_pos_y));
			
		}
	}
	
	//los botones se pintan con su color identificador y se dibujan el aux_tab_bmp
	floodfill(sano,(sano->w)/2,(sano->h)/2, AZUL);
	draw_sprite(aux_tab_bmp, sano, 694, 40);
	
	floodfill(sano,(sano->w)/2,(sano->h)/2, VERDE);
	draw_sprite(aux_tab_bmp, sano, 694, 103);
	
	floodfill(sano,(sano->w)/2,(sano->h)/2, SANO);
	draw_sprite(aux_tab_bmp, sano, 694, 166);
	
	floodfill(sano,(sano->w)/2,(sano->h)/2, BORRAR);
	draw_sprite(aux_tab_bmp, sano, 694, 237);
	
	//para el boton "begin game" se dibuja en aux_tab_bmp un rectangulo con su color identificador
	rectfill(aux_tab_bmp, 24, 375, 126, 463, BEGIN_GAME	);
	
	
	//estos tres bitmaps se utilizaran para crear el fondo a mostrar
	BITMAP* fondo = load_bitmap("imagenes/background.bmp",NULL);
	BITMAP* punteado = load_bitmap("imagenes/menu/editor_punteado.bmp",NULL);
	BITMAP* inst = load_bitmap("imagenes/menu/editor_inst.bmp",NULL);
	
	//se cargan los bitmap de los botones en sus diferentes estados
	BITMAP* begin = load_bitmap("imagenes/menu/editor_begin.bmp",NULL);
	BITMAP* begin_brillando = load_bitmap("imagenes/menu/editor_begin_brillando.bmp",NULL);
	BITMAP* begin_off = load_bitmap("imagenes/menu/editor_begin_off.bmp",NULL);
	
	BITMAP* azul_brillando = load_bitmap("imagenes/menu/editor_azul_brillando.bmp",NULL);
	BITMAP* azul = load_bitmap("imagenes/menu/editor_azul.bmp",NULL);
	
	BITMAP* verde_brillando = load_bitmap("imagenes/menu/editor_verde_brillando.bmp",NULL);
	BITMAP* verde = load_bitmap("imagenes/menu/editor_verde.bmp",NULL);
	
	BITMAP* sano_brillando = load_bitmap("imagenes/menu/editor_sano_brillando.bmp",NULL);
			sano = load_bitmap("imagenes/menu/editor_sano.bmp",NULL);
	
	BITMAP* borrar_brillando = load_bitmap("imagenes/menu/editor_borrar_brillando.bmp",NULL);
	BITMAP* borrar = load_bitmap("imagenes/menu/editor_borrar.bmp",NULL);
	
	
	show_mouse(NULL);
	draw_sprite(fondo, inst, 0, 550);//se colocan las explicaciones de los botones que se utilizan en este menu
	destroy_bitmap(inst);
	
	//se dibujan los exagonos que forman un tablero sobre el que el usuario puede crear el tablero real
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			//se calculan las posiciones de los exagonos y se dibujan en el fondo
			hex_pos_y = (j%2)*((44)/2) + tab_pos_y + i*(44); 
			hex_pos_x = j*hex_w2 + tab_pos_x;
			draw_sprite(fondo, punteado, hex_pos_x-4, hex_pos_y-7);
		}
	}
	destroy_bitmap(punteado);
	
	tab_bmp = create_bitmap(800,600);//este será el bitmap a mostrar en pantalla
	draw_sprite(tab_bmp, fondo, 0, 0);
	
	//se llena el tablero_inicial con el identificador de que no hay tejido
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			tablero_inicial[i][j] = SIN_TEJIDO;
		}
	}
	
	
	int boton = BORRAR;//siempre indica el boton de edicion seleccionado
	int clicked = FALSE;//se utiliza para saber si se acaba de clickear o desclickear
	int begin_habilitado = FALSE;//bandera que se utiliza para saber si el boton "begin game" esta habilitado
	int pixel_col;//En cada ciclo del while se guarda pixel_col el color del pixel que corresponde a la posicion del mouse pero en el bitmap aux_tab_bmp
	int color;//cuando se clickea, en "color" se guarda el color del pixel que corresponde a la posicion del mouse pero en el bitmap aux_tab_bmp
	int f,c;
	
	BITMAP* azul_tablero = load_bitmap("imagenes/bacteria_azul.bmp",NULL);
	BITMAP* verde_tablero = load_bitmap("imagenes/bacteria_verde.bmp",NULL);
	BITMAP* sano_tablero = load_bitmap("imagenes/hexagono_original.bmp",NULL);

	
	clear_keybuf();
	/*
	El motivo de este while(1) es que dentro de este se encuentran los return que hacer que
	la función termine, por lo que no importa que la condición de siempre sea verdadera
	*/
	while(1){
		pixel_col = getpixel(aux_tab_bmp, mouse_x, mouse_y);
		
		show_mouse(NULL);
		draw_sprite(tab_bmp, begin_off, 12, 365);
		
		if( !(clicked) && mouse_b&1 ){
			clicked = TRUE;
			color = pixel_col;//se guarda el color que contiene pixel_col ya que se acaba de desclickear
		}
		
		
		if( clicked && !(mouse_b&1) ){
			clicked = FALSE;
			if( color==pixel_col ){//si se desclickeo en el mismo boton que se clickeo entonces "color" y "pixel_col" coincidirán
				switch(color){//segun el boton que se haya elegido (clickeado y desclickeado) se realiza la accion correspondiente (si no fue un boton no pasa nada)
					case AZUL: 
							play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de "boton elegido" 
							boton = AZUL;//a boton se le asigna el identificador correspondiente
							break;
					case VERDE: 
							play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de "boton elegido" 
							boton = VERDE;//a boton se le asigna el identificador correspondiente
							break;
					case SANO: 
							play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de "boton elegido" 
							boton = SANO;//a boton se le asigna el identificador correspondiente
							break;
					case BORRAR: 
							play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de "boton elegido" 
							boton = BORRAR;//a boton se le asigna el identificador correspondiente
							break;
					case BEGIN_GAME: 
							if(begin_habilitado){//si el boton "begin game" esta habilitado se hacen los destroy de los bitmaps y se retorna el identificador correspondiente
								show_mouse(NULL);
								destroy_bitmap(sano);
								destroy_bitmap(fondo);
								destroy_bitmap(begin);
								destroy_bitmap(begin_brillando);
								destroy_bitmap(begin_off);
								destroy_bitmap(azul_brillando);
								destroy_bitmap(azul);
								destroy_bitmap(verde_brillando);
								destroy_bitmap(verde);
								destroy_bitmap(sano_brillando);
								destroy_bitmap(borrar_brillando);
								destroy_bitmap(borrar);
								return BEGIN_GAME;
							}
							break;
				}
			}
			begin_habilitado = verificar_edicion(tablero_inicial);//a begin_habilitado se le asigna TRUE si el tablero es correcto, sino se asigna FALSE
		}
		
		if( mouse_b&1 && -1<pixel_col && pixel_col<144 ){//if(mouse_clickeado y pixel_corresponde_a_un_hexagono_del_tablero)
			//en f y c se guardan la fila y la columna del tablero(matriz) correspondiente al hexagono clickeado
			f = get_pos_f(mouse_x, mouse_y, 0, 0);
			c = get_pos_c(mouse_x, mouse_y, 0, 0);
			
			switch(boton){//segun el boton que este elegido se edita el tablero de cierta manera (se actualiza en tablero tanto en matriz como en lo que se dibuja)
				case AZUL: 
						tablero_inicial[f][c] = BACTERIA_AZUL;
						hex_pos_y = (c%2)*((44)/2) + tab_pos_y + f*(44); 
						hex_pos_x = c*hex_w2 + tab_pos_x;
						draw_sprite(tab_bmp, azul_tablero, hex_pos_x, hex_pos_y);
						break;
				case VERDE: 
						tablero_inicial[f][c] = BACTERIA_VERDE;
						hex_pos_y = (c%2)*((44)/2) + tab_pos_y + f*(44); 
						hex_pos_x = c*hex_w2 + tab_pos_x;
						draw_sprite(tab_bmp, verde_tablero, hex_pos_x, hex_pos_y);
						break;
				case SANO: 
						tablero_inicial[f][c] = TEJIDO_SANO;
						hex_pos_y = (c%2)*((44)/2) + tab_pos_y + f*(44); 
						hex_pos_x = c*hex_w2 + tab_pos_x;
						draw_sprite(tab_bmp, sano_tablero, hex_pos_x, hex_pos_y);
						break;
				case BORRAR: 
						tablero_inicial[f][c] = SIN_TEJIDO;
						draw_sprite(tab_bmp, fondo, 0, 0);
						for(i=0;i<tab_h;i++){
							for(j=0;j<tab_w;j++){
								if(tablero_inicial[i][j]!=SIN_TEJIDO){
									hex_pos_y = (j%2)*((sano_tablero->h)/2) + tab_pos_y + i*(sano_tablero->h); 
									hex_pos_x = j*hex_w2 + tab_pos_x;
									
									switch(tablero_inicial[i][j]){
										case TEJIDO_SANO:
											draw_sprite(tab_bmp, sano_tablero, hex_pos_x, hex_pos_y);
											break;
										case BACTERIA_AZUL:
											draw_sprite(tab_bmp, azul_tablero, hex_pos_x, hex_pos_y);
											break;
										case BACTERIA_VERDE:
											draw_sprite(tab_bmp, verde_tablero, hex_pos_x, hex_pos_y);
											break;
									}
									
								}
							}
						}
						break;
			}
			
		}
		
		
		if(COLOR_NULO==pixel_col){//si no se esta en ningun boton se le asigna FASLE a sonido_ban
			sonido_ban=FALSE;
		}
		
		/*
		En los siguientes if se pinta cada boton brillando si esta seleccionado o si el mouse esta sobre el boton.
		Tambien se reproduce sonido_boton si el mouse pasa sobre el boton
		*/
		if(boton==AZUL || AZUL==pixel_col){
			draw_sprite(tab_bmp, azul_brillando, 678, 29);
			if(pixel_col==AZUL  && sonido_ban!=AZUL){
				play_sample(sonido_boton,255,128,1000,0);
				sonido_ban=AZUL;
			}
		}else{
			draw_sprite(tab_bmp, azul, 678, 29);
		}
		
		if(boton==VERDE || VERDE==pixel_col){
			draw_sprite(tab_bmp, verde_brillando, 678, 94);
			if(pixel_col==VERDE  && sonido_ban!=VERDE){
				play_sample(sonido_boton,255,128,1000,0);
				sonido_ban=VERDE;
			}
		}else{
			draw_sprite(tab_bmp, verde, 678, 94);
		}
		
		if(boton==SANO || SANO==pixel_col){
			draw_sprite(tab_bmp, sano_brillando, 678, 157);
			if(pixel_col==SANO  && sonido_ban!=SANO){
				play_sample(sonido_boton,255,128,1000,0);
				sonido_ban=SANO;
			}
		}else{
			draw_sprite(tab_bmp, sano, 678, 157);
		}
		
		if(boton==BORRAR || BORRAR==pixel_col){
			draw_sprite(tab_bmp, borrar_brillando, 678, 224);
			if(pixel_col==BORRAR  && sonido_ban!=BORRAR){
				play_sample(sonido_boton,255,128,1000,0);
				sonido_ban=BORRAR;
			}
		}else{
			draw_sprite(tab_bmp, borrar, 678, 224);
		}
		
		if(begin_habilitado){
			if(BEGIN_GAME==pixel_col){
				draw_sprite(tab_bmp, begin_brillando, 12, 365);
				if(sonido_ban!=BEGIN_GAME){
					play_sample(sonido_boton,255,128,1000,0);
					sonido_ban=BEGIN_GAME;
				}
			}else{
				draw_sprite(tab_bmp, begin, 12, 365);
			}
		}else{
			draw_sprite(tab_bmp, begin_off, 12, 365);
		}
		
		show_mouse(tab_bmp);
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
		
		if(keypressed()){
			if(key[KEY_I]){//al presionar la tecla "I" muestran las instrucciones 
				instrucciones(BOARD_EDITOR);
			}
			if(key[KEY_ESC]){//al presionar ESC se debe volver al menu anterio por lo que se retorna game_type
				show_mouse(NULL);
				destroy_bitmap(sano);
				destroy_bitmap(fondo);
				destroy_bitmap(begin);
				destroy_bitmap(begin_brillando);
				destroy_bitmap(begin_off);
				destroy_bitmap(azul_brillando);
				destroy_bitmap(azul);
				destroy_bitmap(verde_brillando);
				destroy_bitmap(verde);
				destroy_bitmap(sano_brillando);
				destroy_bitmap(borrar_brillando);
				destroy_bitmap(borrar);
				return game_type;
			}
		}
	}
	
	
}
/* en este menu se elige el nombre de ambos jugadores(ya sea player vs PC o player vs player) */
int name_menu(int vs,char player0[26],char player1[26],FONT* mv_boli,char tablero_inicial[12][12], SAMPLE *boton,SAMPLE *sonido_seleccion){
	/*
	ademas de elegir los nombres, se puede elegir ir al menu de edicion de tablero o ir directamente al juego estandar 
	
	parametros
		vs = indica si el juego elegido es player vs PC o player vs player
		player0,player1 = son los strings que contiene los nombres de los jugadores 
		mv_boli = fuente mv boli tamaño 22
		tablero_inicial = se recibe para mandar a las funciones standard_board_creator o board_editor_menu
		sonido_boton = este SAMPLE se reproduce cuando el mouse se posa sobre un boton
		sonido_seleccion = este SAMPLE se reproduce cuando se clickea un boton
	*/
	
	BITMAP* menu_bmp = create_bitmap(SCREEN_W,SCREEN_H);
	BITMAP* fondo = load_bitmap("imagenes/menu/name_menu.bmp",NULL);
	BITMAP* aux_menu_bmp = load_bitmap("imagenes/menu/name_shape.bmp",NULL);
	BITMAP* input_pl_1;//es le cuadro donde el segundo jugador escribe su nombre
	switch (vs){
		case PVPC: 
				strcpy(player0,"Player");
				strcpy(player1,"PC");
				input_pl_1 = load_bitmap("imagenes/menu/name_input_pl_1.bmp",NULL); 
				break;
		case PVP:
				strcpy(player0,"Player 1");
				strcpy(player1,"Player 2");
				BITMAP* titulo = load_bitmap("imagenes/menu/name_player0.bmp",NULL);//si es PVP se utiliza "titulo" para arreglar los titulos que estan el fondo
				input_pl_1 = load_bitmap("imagenes/menu/pvp_input_pl_1.bmp",NULL); 
				draw_sprite(fondo, titulo, 357, 16);
				titulo = load_bitmap("imagenes/menu/name_player1.bmp",NULL);
				draw_sprite(fondo, titulo, 181, 125);
				destroy_bitmap(titulo);
				break;
	}
	draw_sprite(menu_bmp, fondo, 0, 0);
	
	int selected_ban = FALSE;//se utiliza como bandera para la reproducion de sonido
	int color = FALSE;//se utiliza para guardar el como de pixel correspondiente
	int clicked = FALSE;//se utiliza para saber si se acaba de clickear o desclickear
	int cursor_sobre_btn = FALSE;//se utiliza para saber sobre que boton esta el mouse
	int player0_click = TRUE;//se utiliza para saber si se edita el nombre por primera vez
	int player1_click = TRUE;//se utiliza para saber si se edita el nombre por primera vez
	int edit_name = FALSE;//se utiliza para saber cual es el nombre que se esta editando, si se esta editando
	char caracter;//se usa para la captura de los caracteres tecleados
	
	//se imprimen los nombres en los cuadros de nombres
	textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
	textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
	
	show_mouse(menu_bmp);
	blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	BITMAP* input_pl_0 = load_bitmap("imagenes/menu/name_input_pl_0.bmp",NULL);  
	
	//se cargan los bitmaps de los botones brillando 
	BITMAP* standard_board = load_bitmap("imagenes/menu/name_standard_board.bmp",NULL);  
	BITMAP* board_editor = load_bitmap("imagenes/menu/name_board_editor.bmp",NULL); 
	
	
	while( !key[KEY_ESC] ){
		
		if( mouse_b&1 && PLAYER0==getpixel(aux_menu_bmp, mouse_x, mouse_y) ){
			if(player0_click){
				*player0 = '\0';//si es la primera vez que se edita se vacia el nombre
				player0_click=FALSE;
			}
			edit_name = PLAYER0;
			selected_ban = TRUE;
			
			//se actualiza el nombre
			show_mouse(NULL);
			draw_sprite(menu_bmp, input_pl_0, 79, 55);
			textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
			show_mouse(menu_bmp);
			clear_keybuf();
		}else{
			if( mouse_b&1 && PLAYER1==getpixel(aux_menu_bmp, mouse_x, mouse_y) ){
				if(player1_click){
					*player1 = '\0';//si es la primera vez que se edita se vacia el nombre
					player1_click=FALSE;
				}
				edit_name = PLAYER1;
				selected_ban = TRUE;
				
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
				show_mouse(menu_bmp);
				clear_keybuf();
			}
		}
		
		
		while( edit_name==PLAYER0){//mientras que se este editando el nombre de player0...
			if(selected_ban){
				play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de seleccion
				selected_ban = FALSE;
			}
			
			if(keypressed()){
				caracter = readkey();//se aptura el caracter tecleado
				
				if( key[KEY_BACKSPACE] ){
					if( strlen(player0) )
						player0[strlen(player0)-1] = '\0';//si fue back space y el string no esta vacio se borra el ultiimo caracter
				}else{
					if( text_length(mv_boli, player0)<245 && isprint(caracter)){
						player0[strlen(player0)+1] = '\0';//se asigna \0 (fin de string) al caracter siguiente al verdadero fin de string
						player0[strlen(player0)] = caracter;//al caracter \0 que indica el fin de archivo se le asigna el caracter leido
						//ahora el \0 asignado antes es el verdadero fin de archivo
					}
				}
				clear_keybuf();
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_0, 79, 55);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
				show_mouse(menu_bmp);
			}
			
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//segun sea el pixel capturado se hace brillar el boton correspondiente
				case PLAYER1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, input_pl_1, 7, 157);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=PLAYER1;
							play_sample(boton,255,128,1000,0);
						}
						break;
				case STND_BOARD:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, standard_board, 109, 24);
							show_mouse(menu_bmp);
							cursor_sobre_btn=STND_BOARD;
							play_sample(boton,255,128,1000,0);
						}
						break;
				case BOARD_EDITOR:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, board_editor, 383, 191);
							show_mouse(menu_bmp);
							cursor_sobre_btn=BOARD_EDITOR;
							play_sample(boton,255,128,1000,0);
						}
						break;
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);//en este caso se pinta el fondo para que ningun boton brille
							draw_sprite(menu_bmp, input_pl_0, 79, 55);//luego se hacer brillar el cuadro de edicion correspondiente
							textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
				
			}
			
			
			show_mouse(NULL);
			if( (speed_counter/30)%2 ){//cada medio segundo se dibuja o desdibuja el cursor de escritura
				rectfill(menu_bmp, 110 + text_length(mv_boli, player0), 58 + text_height(mv_boli), 121 + text_length(mv_boli, player0), 60 + text_height(mv_boli), makecol(160,254,193));
			}else{
				draw_sprite(menu_bmp, input_pl_0, 79, 55);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
			}
			show_mouse(menu_bmp);
			
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			
			if( mouse_b&1 && PLAYER0!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){//si se clickea fuera del nombre que se esta editando...
				color = cursor_sobre_btn;//se guarda el indicador del boton sbre el que esta el mouse 
				clicked = TRUE;
				edit_name = FALSE;//esto es para salir de la edicion de este nombre
				
				show_mouse(NULL);
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
				show_mouse(menu_bmp);
				
				cursor_sobre_btn=FALSE;
			}
			
		}
		
		
		while( edit_name==PLAYER1){//mientras que se este editando el nombre de player1...
			if(selected_ban){
				play_sample(sonido_seleccion,255,128,1000,0);//se reproduce el sonido de seleccion
				selected_ban = FALSE;
			}
			if(keypressed()){
				caracter = readkey();//se captura el caracter tecleado
				
				if( key[KEY_BACKSPACE] ){
					if( strlen(player1) )
						player1[strlen(player1)-1] = '\0';//si fue back space y el string no esta vacio se borra el ultiimo caracter
				}else{
					if( text_length(mv_boli, player1)<245 && isprint(caracter)){
						player1[strlen(player1)+1] = '\0';//se asigna \0 (fin de string) al caracter siguiente al verdadero fin de string
						player1[strlen(player1)] = caracter;//al caracter \0 que indica el fin de archivo se le asigna el caracter leido
						//ahora el \0 asignado antes es el verdadero fin de archivo
					}
				}
				clear_keybuf();
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
				show_mouse(menu_bmp);
				
			}
			
			
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//segun sea el pixel capturado se hace brillar el boton correspondiente
				case PLAYER0:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, input_pl_0, 79, 55);
						textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
						show_mouse(menu_bmp);
						cursor_sobre_btn=PLAYER1;
						play_sample(boton,255,128,1000,0);
					}
					break;
				case STND_BOARD:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, standard_board, 109, 24);
							
							show_mouse(menu_bmp);
							cursor_sobre_btn=STND_BOARD;
							play_sample(boton,255,128,1000,0);
						}
						break;
				case BOARD_EDITOR:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, board_editor, 383, 191);
							show_mouse(menu_bmp);
							cursor_sobre_btn=BOARD_EDITOR;
							play_sample(boton,255,128,1000,0);
						}
						break;
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);//en este caso se pinta el fondo para que ningun boton brille
							draw_sprite(menu_bmp, input_pl_1, 7, 157);//luego se hacer brillar el cuadro de edicion correspondiente
							textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
			}
			
			show_mouse(NULL);
			if( (speed_counter/30)%2 ){//cada medio segundo se dibuja o desdibuja el cursor de escritura
				rectfill(menu_bmp, 30 + text_length(mv_boli, player1), 162 + text_height(mv_boli), 41 + text_length(mv_boli, player1), 164 + text_height(mv_boli), makecol(160,254,193));
			}else{
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
			}
			show_mouse(menu_bmp);
			
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			
			if( mouse_b&1 && PLAYER1!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){//si se clickea fuera del nombre que se esta editando...
				color = cursor_sobre_btn;//se guarda el indicador del boton sbre el que esta el mouse 
				clicked = TRUE;
				edit_name = FALSE;//esto es para salir de la edicion de este nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
				show_mouse(menu_bmp);
				cursor_sobre_btn=FALSE;
			}
			
		}
		
		if(!clicked && mouse_b&1){
			clicked = TRUE;
			color = cursor_sobre_btn;//como se acaba de clickear se captura el id del boton en "color"
		}
		
		
		if(clicked && !mouse_b&1){
			clicked = FALSE;
			//como se acaba de desclickear...
			if( cursor_sobre_btn==color ){//coincide el lugar de clickeo con el de desclickeo
					if(color==BOARD_EDITOR){//si fue el boton de edicion de tablero se retorna el identificador BOARD_EDITOR
						show_mouse(NULL);
						destroy_bitmap(menu_bmp);
						destroy_bitmap(fondo);
						destroy_bitmap(aux_menu_bmp);
						destroy_bitmap(input_pl_1);
						destroy_bitmap(input_pl_0);
						destroy_bitmap(standard_board);
						destroy_bitmap(board_editor);
						return BOARD_EDITOR;
					}else{
						if(color==STND_BOARD){//si fue el boton de comenzar juego se retorna el identificador STND_BOARD
							standard_board_creator(tablero_inicial);
							show_mouse(NULL);
							destroy_bitmap(menu_bmp);
							destroy_bitmap(fondo);
							destroy_bitmap(aux_menu_bmp);
							destroy_bitmap(input_pl_1);
							destroy_bitmap(input_pl_0);
							destroy_bitmap(standard_board);
							destroy_bitmap(board_editor);
							return STND_BOARD;
						}
					}
					
			}
		}
		
		switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//se dibujan los botones que corresponden al que el mouse se posa
			case PLAYER0:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, input_pl_0, 79, 55);
						textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
						show_mouse(menu_bmp);
						cursor_sobre_btn=PLAYER0;
						play_sample(boton,255,128,1000,0);
					}
					break;
			case PLAYER1:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, input_pl_1, 7, 157);
						textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
						show_mouse(menu_bmp);
						cursor_sobre_btn=PLAYER1;
						play_sample(boton,255,128,1000,0);
					}
					break;
			case STND_BOARD:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, standard_board, 109, 24);
						show_mouse(menu_bmp);
						cursor_sobre_btn=STND_BOARD;
						play_sample(boton,255,128,1000,0);
					}
					break;
			case BOARD_EDITOR:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, board_editor, 383, 191);
						show_mouse(menu_bmp);
						cursor_sobre_btn=BOARD_EDITOR;
						play_sample(boton,255,128,1000,0);
					}
					break;
			case COLOR_NULO :
					if( cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, fondo, 0, 0);
						textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
						textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
						show_mouse(menu_bmp);
						cursor_sobre_btn=FALSE;
					}
		}
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	
	show_mouse(NULL);
	destroy_bitmap(menu_bmp);
	destroy_bitmap(fondo);
	destroy_bitmap(aux_menu_bmp);
	destroy_bitmap(input_pl_1);
	destroy_bitmap(input_pl_0);
	destroy_bitmap(standard_board);
	destroy_bitmap(board_editor);
	
	return MAIN_MENU;//si se llego a este punto es porque se presionó ESC por lo que se debe retornar MAIN_MENU
}
/* en este menu se elige el nombre de ambas PCs */
int pcvpc_name_menu(char player0[26],char player1[26],FONT* mv_boli, SAMPLE *boton,char tablero_inicial[12][12]){
	/*
	ademas de elegir los nombres, se puede elegir ir al juego estandar 
	ESTE MENU NO TIENE SONIDO
	
	parametros
		player0,player1 = son los strings que contiene los nombres de las PCs
		mv_boli = fuente mv boli tamaño 22
		tablero_inicial = se recibe para mandar a las funciones standard_board_creator o board_editor_menu
	*/
	
	TURNO = BACTERIA_AZUL;
	BITMAP *menu_bmp = create_bitmap(SCREEN_W,SCREEN_H);
	BITMAP *fondo = load_bitmap("imagenes/menu/pcvpc_name_menu.bmp",NULL);
	BITMAP *aux_menu_bmp = load_bitmap("imagenes/menu/name_shape.bmp",NULL);
	strcpy(player0,"Other PC");
	strcpy(player1,"This PC");
	
	draw_sprite(menu_bmp, fondo, 0, 0);
	
	int color = FALSE;//se utiliza para guardar el como de pixel correspondiente
	int clicked = FALSE;//se utiliza para saber si se acaba de clickear o desclickear
	int cursor_sobre_btn = FALSE;//se utiliza para saber sobre que boton esta el mouse
	int player0_click = TRUE;//se utiliza para saber si se edita el nombre por primera vez
	int player1_click = TRUE;//se utiliza para saber si se edita el nombre por primera vez
	int edit_name = FALSE;//se utiliza para saber cual es el nombre que se esta editando, si se esta editando
	char caracter;//se usa para la captura de los caracteres tecleados
	
	//se imprimen los nombres en los cuadros de nombres
	textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
	textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
	
	show_mouse(menu_bmp);
	blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	BITMAP* input_pl_0 = load_bitmap("imagenes/menu/name_input_pl_0.bmp",NULL);  
	BITMAP* input_pl_1 = load_bitmap("imagenes/menu/name_input_pl_1.bmp",NULL); 
	BITMAP* begin_game = load_bitmap("imagenes/menu/pcvpc_begin_game.bmp",NULL);  
	BITMAP* verde = load_bitmap("imagenes/menu/pcvpc_name_verde.bmp",NULL);  
	BITMAP* azul = load_bitmap("imagenes/menu/pcvpc_name_azul.bmp",NULL);  
	BITMAP* azul_verde = load_bitmap("imagenes/menu/pcvpc_name_ambos.bmp",NULL);  
	
	show_mouse(NULL);
	draw_sprite(menu_bmp, azul, 580, 423);
	show_mouse(menu_bmp);
	
	while( !key[KEY_ESC] ){
		
		if( mouse_b&1 && PLAYER0==getpixel(aux_menu_bmp, mouse_x, mouse_y) ){
			if(player0_click){
				*player0 = '\0';//si es la primera vez que se edita se vacia el nombre
				player0_click=FALSE;
			}
			edit_name = PLAYER0;
			
			//se actualiza el nombre
			show_mouse(NULL);
			draw_sprite(menu_bmp, input_pl_0, 79, 55);
			textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
			show_mouse(menu_bmp);
			clear_keybuf();
		}else{
			if( mouse_b&1 && PLAYER1==getpixel(aux_menu_bmp, mouse_x, mouse_y) ){
				if(player1_click){
					*player1 = '\0';//si es la primera vez que se edita se vacia el nombre
					player1_click=FALSE;
				}
				edit_name = PLAYER1;
				
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
				show_mouse(menu_bmp);
				clear_keybuf();
			}
		}
		
		
		while( edit_name==PLAYER0){//mientras que se este editando el nombre de player0...
			
			if(keypressed()){
				if(keypressed())
					caracter = readkey();//se aptura el caracter tecleado
				
				if( key[KEY_BACKSPACE] ){
					if( strlen(player0) )
						player0[strlen(player0)-1] = '\0';//si fue back space y el string no esta vacio se borra el ultiimo caracter
				}else{
					if( text_length(mv_boli, player0)<245 && isprint(caracter) ){
						player0[strlen(player0)+1] = '\0';//se asigna \0 (fin de string) al caracter siguiente al verdadero fin de string
						player0[strlen(player0)] = caracter;//al caracter \0 que indica el fin de archivo se le asigna el caracter leido
						//ahora el \0 asignado antes es el verdadero fin de archivo
					}
				}
				clear_keybuf();
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_0, 79, 55);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
				show_mouse(menu_bmp);
			}
			
			show_mouse(NULL);
			switch(TURNO){
				case BACTERIA_AZUL:
					draw_sprite(menu_bmp, azul, 580, 423);
					break;
				case BACTERIA_VERDE:
					draw_sprite(menu_bmp, verde, 580, 423);
					break;
			}
			show_mouse(menu_bmp);
			
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//segun sea el pixel capturado se hace brillar el boton correspondiente
				case PLAYER1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, input_pl_1, 7, 157);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=PLAYER1;
						}
						break;
				case BEGIN_GAME:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, begin_game, 96, 65);
							show_mouse(menu_bmp);
							cursor_sobre_btn=BEGIN_GAME;
						}
						break;
				case BTN_AZUL:
						if( !cursor_sobre_btn ){
							cursor_sobre_btn=BTN_AZUL;
						}
						if(TURNO==BACTERIA_VERDE ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, azul_verde, 580, 423);
							show_mouse(menu_bmp);
						}
						
						break;
				case BTN_VERDE:
						if( !cursor_sobre_btn ){
							cursor_sobre_btn=BTN_VERDE;
						}
						if( TURNO==BACTERIA_AZUL){
							show_mouse(NULL);
							draw_sprite(menu_bmp, azul_verde, 580, 423);
							show_mouse(menu_bmp);
						}
						break;
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);//en este caso se pinta el fondo para que ningun boton brille
							switch(TURNO){//se hace brillar la bacteria correspondiente
								case BACTERIA_AZUL:
									draw_sprite(menu_bmp, azul, 580, 423);
									break;
								case BACTERIA_VERDE:
									draw_sprite(menu_bmp, verde, 580, 423);
									break;
							}
							draw_sprite(menu_bmp, input_pl_0, 79, 55);//se hacer brillar el cuadro de edicion correspondiente
							textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
						break;
			}
			
			
			show_mouse(NULL);
			if( (speed_counter/30)%2 ){//cada medio segundo se dibuja o desdibuja el cursor de escritura
				rectfill(menu_bmp, 110 + text_length(mv_boli, player0), 58 + text_height(mv_boli), 121 + text_length(mv_boli, player0), 60 + text_height(mv_boli), makecol(160,254,193));
			}else{
				draw_sprite(menu_bmp, input_pl_0, 79, 55);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
			}
			show_mouse(menu_bmp);
			
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			
			if( mouse_b&1 && PLAYER0!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){//si se clickea fuera del nombre que se esta editando...
				color = cursor_sobre_btn;//se guarda el indicador del boton sbre el que esta el mouse 
				clicked = TRUE;
				edit_name = FALSE;//esto es para salir de la edicion de este nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
				show_mouse(menu_bmp);
				cursor_sobre_btn=FALSE;
			}
			
		}
		
		
		while( edit_name==PLAYER1){//mientras que se este editando el nombre de player1...
			
			if(keypressed()){
				caracter = readkey();//se captura el caracter tecleado
				
				if( key[KEY_BACKSPACE] ){
					if( strlen(player1) )
						player1[strlen(player1)-1] = '\0';//si fue back space y el string no esta vacio se borra el ultiimo caracter
				}else{
					if( text_length(mv_boli, player1)<245 && isprint(caracter) ){
						player1[strlen(player1)+1] = '\0';//se asigna \0 (fin de string) al caracter siguiente al verdadero fin de string
						player1[strlen(player1)] = caracter;//al caracter \0 que indica el fin de archivo se le asigna el caracter leido
						//ahora el \0 asignado antes es el verdadero fin de archivo
					}
				}
				clear_keybuf();
				//se actualiza el nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
				show_mouse(menu_bmp);
				
			}
			
			show_mouse(NULL);
			switch(TURNO){
				case BACTERIA_AZUL:
					draw_sprite(menu_bmp, azul, 580, 423);
					break;
				case BACTERIA_VERDE:
					draw_sprite(menu_bmp, verde, 580, 423);
					break;
			}
			show_mouse(menu_bmp);
			
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//segun sea el pixel capturado se hace brillar el boton correspondiente
			case PLAYER0:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, input_pl_0, 79, 55);
							textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
							show_mouse(menu_bmp);
							cursor_sobre_btn=PLAYER1;
						}
						break;
				case BEGIN_GAME:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, begin_game, 96, 65);
							show_mouse(menu_bmp);
							cursor_sobre_btn=BEGIN_GAME;
						}
						break;
				case BTN_AZUL:
						if( !cursor_sobre_btn ){
							cursor_sobre_btn=BTN_AZUL;
						}
						if(TURNO==BACTERIA_VERDE ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, azul_verde, 580, 423);
							show_mouse(menu_bmp);
						}
						
						break;
				case BTN_VERDE:
						if( !cursor_sobre_btn ){
							cursor_sobre_btn=BTN_VERDE;
						}
						if( TURNO==BACTERIA_AZUL){
							show_mouse(NULL);
							draw_sprite(menu_bmp, azul_verde, 580, 423);
							show_mouse(menu_bmp);
						}
						break;

						
						
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);
							switch(TURNO){
								case BACTERIA_AZUL:
									draw_sprite(menu_bmp, azul, 580, 423);
									break;
								case BACTERIA_VERDE:
									draw_sprite(menu_bmp, verde, 580, 423);
									break;
							}
							draw_sprite(menu_bmp, input_pl_1, 7, 157);
							textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
							textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
			}
			
			
			show_mouse(NULL);
			if( (speed_counter/30)%2 ){//cada medio segundo se dibuja o desdibuja el cursor de escritura
				rectfill(menu_bmp, 30 + text_length(mv_boli, player1), 162 + text_height(mv_boli), 41 + text_length(mv_boli, player1), 164 + text_height(mv_boli), makecol(160,254,193));
			}else{
				draw_sprite(menu_bmp, input_pl_1, 7, 157);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
			}
			show_mouse(menu_bmp);
			
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);//se actualiza la pantalla
			
			if( mouse_b&1 && PLAYER1!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){//si se clickea fuera del nombre que se esta editando...
				color = cursor_sobre_btn;//se guarda el indicador del boton sbre el que esta el mouse
				clicked = TRUE;
				edit_name = FALSE;//esto es para salir de la edicion de este nombre
				show_mouse(NULL);
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
				textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
				show_mouse(menu_bmp);
				cursor_sobre_btn=FALSE;
			}
			
		}
		
		if(!clicked && mouse_b&1){
			clicked = TRUE;
			color = cursor_sobre_btn;//como se acaba de clickear se captura el id del boton en "color"
		}
		
		
		if(clicked && !mouse_b&1){
			clicked = FALSE;
			//como se acaba de desclickear...
			switch(color){//segun sea el id del boton se dibuja el boton correspondiente
				case BTN_AZUL:
					TURNO = BACTERIA_AZUL;
					show_mouse(NULL);
					draw_sprite(menu_bmp, azul, 580, 423);
					show_mouse(menu_bmp);
					break;
				case BTN_VERDE:
					TURNO = BACTERIA_VERDE;
					show_mouse(NULL);
					draw_sprite(menu_bmp, verde, 580, 423);
					show_mouse(menu_bmp);
					break;
				case BEGIN_GAME:
					standard_board_creator(tablero_inicial);
					show_mouse(NULL);
					destroy_bitmap(menu_bmp);
					destroy_bitmap(aux_menu_bmp);
					destroy_bitmap(fondo);
					destroy_bitmap(input_pl_0);
					destroy_bitmap(input_pl_1);
					destroy_bitmap(begin_game);
					return BEGIN_GAME;
					break;
			}
			
			
		}
		
		show_mouse(NULL);
		switch(TURNO){//se pinta el boton de la bacteria correspondiente
			case BACTERIA_AZUL:
				draw_sprite(menu_bmp, azul, 580, 423);
				break;
			case BACTERIA_VERDE:
				draw_sprite(menu_bmp, verde, 580, 423);
				break;
		}
		show_mouse(menu_bmp);
		
		switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){//se dibujan los botones que corresponden al que el mouse se posa
			case PLAYER0:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, input_pl_0, 79, 55);
						textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(160,254,193),-1,"%s",player0);
						show_mouse(menu_bmp);
						cursor_sobre_btn=PLAYER0;
					}
					break;
			case PLAYER1:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, input_pl_1, 7, 157);
						textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(160,254,193),-1,"%s",player1);
						show_mouse(menu_bmp);
						cursor_sobre_btn=PLAYER1;
					}
					break;
			case BEGIN_GAME:
					if( !cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, begin_game, 96, 65);
						show_mouse(menu_bmp);
						cursor_sobre_btn=BEGIN_GAME;
					}
					break;
			case BTN_AZUL:
					if( !cursor_sobre_btn ){
						cursor_sobre_btn=BTN_AZUL;
					}
					if(TURNO==BACTERIA_VERDE ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, azul_verde, 580, 423);
						show_mouse(menu_bmp);
					}
					
					break;
			case BTN_VERDE:
					if( !cursor_sobre_btn ){
						cursor_sobre_btn=BTN_VERDE;
					}
					if( TURNO==BACTERIA_AZUL){
						show_mouse(NULL);
						draw_sprite(menu_bmp, azul_verde, 580, 423);
						show_mouse(menu_bmp);
					}
					break;
			case COLOR_NULO :
					if( cursor_sobre_btn ){
						show_mouse(NULL);
						draw_sprite(menu_bmp, fondo, 0, 0);
						textprintf_ex(menu_bmp, mv_boli, 110, 65, makecol(16,254,158),-1,"%s",player0);
						textprintf_ex(menu_bmp, mv_boli, 30, 169, makecol(16,254,158),-1,"%s",player1);
						show_mouse(menu_bmp);
						cursor_sobre_btn=FALSE;
					}
		}
		
		
		
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	while(key[KEY_ESC]){
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	show_mouse(NULL);
	destroy_bitmap(menu_bmp);
	destroy_bitmap(aux_menu_bmp);
	destroy_bitmap(fondo);
	destroy_bitmap(input_pl_0);
	destroy_bitmap(input_pl_1);
	destroy_bitmap(begin_game);
	return PCVPC;//si se llego a este punto es porque se presionó ESC por lo que se debe retornar PCVPC
}
/*administra el menu principal*/
int main_menu(int* game_type, SAMPLE *boton){
	/*
	parametros
		game_type = tipo de juego
		boton = sonido del boton
	*/
	
	
	
	
	int cursor_sobre_btn = FALSE;//indica si el cursor esta sobre un boton
	int selection = FALSE;//varible para retornar la seleccion
	int clicked = FALSE;//indica si el mouse esta clickeado
	int sonido_ban = FALSE;//indica si hay que reproducir o no sonido
	int color;//para comparar el estado del mouse
	
	BITMAP *menu_bmp = create_bitmap(SCREEN_W,SCREEN_H);//buffer principal
	BITMAP *aux_menu_bmp = load_bitmap("imagenes/menu/main_menu.bmp",NULL);//buffer secundario
	
	//cargamos el fondo en el buffer principal
	menu_bmp = load_bitmap("imagenes/menu/main_menu.bmp",NULL);
	BITMAP* menu_shape_bmp = load_bitmap("imagenes/menu/main_shape.bmp",NULL);//bitmap de grilla de colores [ver glosario]
	
	//bitmaps de botones
	BITMAP* btn_pvp   = load_bitmap("imagenes/menu/main_pvp.bmp",NULL);
	BITMAP* btn_pvpc  = load_bitmap("imagenes/menu/main_pvpc.bmp",NULL);
	BITMAP* btn_pcvpc = load_bitmap("imagenes/menu/main_pcvpc.bmp",NULL);
	BITMAP* btn_exit  = load_bitmap("imagenes/menu/main_exit.bmp",NULL);
	
	show_mouse(menu_bmp);
	//captuamos la tecla esc para no pasar muy rapidamente a la portada
	while(key[KEY_ESC]){
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	clear_keybuf();
	//mientras no se hayta seleccionado una opcion
	while(!selection){
		show_mouse(NULL);
		draw_sprite(menu_bmp, aux_menu_bmp,0,0);
		/*
		los switch como el siguiente se refieren a la grilla de colores, sirven para identificar sobre que boton
		esta el mouse en todo momento
		
		en el caso de este switch.. simplemente se cambia el estado del boton y se imprime el boton brillando
		mientras el boton esta posado sobre el mismo, y se reproduce el sonido al entrar al boton
		*/
		switch(getpixel(menu_shape_bmp, mouse_x, mouse_y)){
			case PVPC:
				show_mouse(NULL);
				draw_sprite(menu_bmp, btn_pvpc, 0,0);
				show_mouse(menu_bmp);
				cursor_sobre_btn=PVPC;
				if(sonido_ban!=PVPC){
					play_sample(boton,255,128,1000,0);
					sonido_ban = PVPC;
				}
				break;
			case PCVPC:
				show_mouse(NULL);
				draw_sprite(menu_bmp, btn_pcvpc, 182,97);
				show_mouse(menu_bmp);
				cursor_sobre_btn=PCVPC;
				if(sonido_ban!=PCVPC){
					play_sample(boton,255,128,1000,0);
					sonido_ban = PCVPC;
				}
				break;
			case PVP:
				show_mouse(NULL);
				draw_sprite(menu_bmp, btn_pvp, 295,25);
				show_mouse(menu_bmp);
				cursor_sobre_btn=PVP;
				if(sonido_ban!=PVP){
					play_sample(boton,255,128,1000,0);
					sonido_ban = PVP;
				}
				break;
			case EXIT:
				show_mouse(NULL);
				draw_sprite(menu_bmp, btn_exit, 255,396);
				show_mouse(menu_bmp);
				cursor_sobre_btn=EXIT;
				if(sonido_ban!=EXIT){
					play_sample(boton,255,128,1000,0);
					sonido_ban = EXIT;
				}
				break;
			default :
				if( cursor_sobre_btn ){
					cursor_sobre_btn=FALSE;
					sonido_ban = TRUE;
				}
		}
		//si el mouse fue clickeado
		if(mouse_b & 1 && !clicked){
			//capturamos el color del boton sobre el cual estamos
			color = getpixel(menu_shape_bmp,mouse_x,mouse_y);
			clicked = TRUE;//el mouse esta clickeado
		}
		if(clicked){
			if(!(mouse_b & 1)){//se hizo release del click
				clicked = FALSE;//el mouse no esta clickeado
				//si el color en el momento del release coincide con el color del momento de click se selecciona la opcion del botn clickeado
				if (color == getpixel(menu_shape_bmp,mouse_x,mouse_y)){
					switch(color){
						case PVPC:
							printf("\nPVPC");
							selection = *game_type = PVPC;
							break;
						case PCVPC:
							printf("\nPCVPC");
							selection = *game_type = PCVPC;
							break;
						case PVP:
							printf("\nPVP");
							selection = *game_type = PVP;
							break;
						case EXIT:
							printf("\nEXIT");
							selection = EXIT;
							winner = EXIT;
							break;
					}
				}
			}
		}
		//si se aprieta la tecla escape se vuelve a la portada
		if(key[KEY_ESC]){
			selection = PORTADA;
		}
		show_mouse(menu_bmp);
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	//se libera la memoria
	show_mouse(NULL);
	destroy_bitmap(menu_bmp);
	destroy_bitmap(menu_shape_bmp);
	destroy_bitmap(aux_menu_bmp);
	destroy_bitmap(btn_pvp);
	destroy_bitmap(btn_pvpc);
	destroy_bitmap(btn_pcvpc);
	destroy_bitmap(btn_exit);
	//se retorna la opcion seleccionada
	return selection;
}
/*administra el menu del juego*/
int ingame_menu(char tablero[tab_h][tab_w],char tablero_inicial[12][12], BITMAP* hex, BITMAP* sano, int tab_pos_x, int tab_pos_y, int tab_bmp_w,int tab_bmp_h, int primer_turno, SAMPLE *boton,SAMPLE *sonido_seleccion){
	/*
	
	parámetros
		tablero = tablero principal del juego
		tablero_inicial = tablero con estado inicial del juego
		hex = imagen del hexagono
		sano = imagen del hexagono sano
		tab_pos_x = posicion horizontal del tablero 
		tab_pos_y = posicion vertical del tablero
		tab_bmp_w = ancho del tablero
		tab_bmp_h = alto del tablero
		primer_turno = primer turno del juego
		boton = sonido del boton
		sonido_seleccion = sonido de seleccion del boton

	*/
	int cursor_sobre_btn = FALSE;//indica si el cursor esta sobre un boton
	int clicked = FALSE;//indica si el mouse esta clickeado
	int color;//para comparar el estado del mouse
	
	BITMAP *btn_cheat;//boton cheat
	BITMAP *aux_menu_bmp;//buffer auxiliar
	BITMAP *menu_bmp;//bufer principal
	if(cheat){//si el cheat mode esta activado se cargan las imagenes "ON"
		aux_menu_bmp = load_bitmap("imagenes/menu/ingame_on.bmp",NULL);
		menu_bmp     = load_bitmap("imagenes/menu/ingame_on.bmp",NULL);
		btn_cheat    = load_bitmap("imagenes/menu/ingame_cheat_on.bmp",NULL);
	}else{//si esta desaactivado se cargan las imagenes "OFF"
		aux_menu_bmp = load_bitmap("imagenes/menu/ingame_off.bmp",NULL);
		menu_bmp     = load_bitmap("imagenes/menu/ingame_off.bmp",NULL);
		btn_cheat    = load_bitmap("imagenes/menu/ingame_cheat_off.bmp",NULL);
	}
	BITMAP* menu_shape_bmp = load_bitmap("imagenes/menu/ingame_shape.bmp",NULL);//bitmap de grilla de colores [ver glosario]
	
	//bitmaps de botones
	BITMAP* btn_mainmenu  = load_bitmap("imagenes/menu/ingame_mainmenu.bmp",NULL);
	BITMAP* btn_reset     = load_bitmap("imagenes/menu/ingame_reset.bmp",NULL);
	BITMAP* btn_exit      = load_bitmap("imagenes/menu/ingame_exit.bmp",NULL);
	
	show_mouse(menu_bmp);
	
	while(!key[KEY_ESC]){//esc para volver al juego
		show_mouse(NULL);
		/*en este switch se verifica que sobre que boton esta el mouse y se reproduce el sonido
		correspondiente al posar el mouse sobre el mismo*/
		switch(getpixel(menu_shape_bmp,mouse_x,mouse_y)){
			case MAIN_MENU:{
				if(cursor_sobre_btn != MAIN_MENU){
					draw_sprite(menu_bmp, aux_menu_bmp,0,0);
					play_sample(boton,255,128,1000,0);
					show_mouse(NULL);
					draw_sprite(menu_bmp, btn_mainmenu, 135,0);
					show_mouse(menu_bmp);
					cursor_sobre_btn = MAIN_MENU;
				}
				break;
			}
			case RESET:{
				if(cursor_sobre_btn != RESET){
					draw_sprite(menu_bmp, aux_menu_bmp,0,0);
					play_sample(boton,255,128,1000,0);
					show_mouse(NULL);
					draw_sprite(menu_bmp, btn_reset, 0,0);
					show_mouse(menu_bmp);
					cursor_sobre_btn = RESET;
				}
				break;
			}
			case EXIT:{
				if(cursor_sobre_btn != EXIT){
					draw_sprite(menu_bmp, aux_menu_bmp,0,0);
					play_sample(boton,255,128,1000,0);
					show_mouse(NULL);
					draw_sprite(menu_bmp, btn_exit, 412,196);
					show_mouse(menu_bmp);
					cursor_sobre_btn = EXIT;
				}
				break;
			}
			case CHEAT:{/*
				el caso cheat es especial ya que puede tener dos estados, ON y OFF, por lo tanto se pregunta nuevamente por
				el estado de la variable cheat antes de dibujar el boton
				*/
				if(cursor_sobre_btn != CHEAT){
					play_sample(boton,255,128,1000,0);
					cursor_sobre_btn = CHEAT;
				}
				draw_sprite(menu_bmp, aux_menu_bmp,0,0);
				show_mouse(NULL);
				if(cheat){
					draw_sprite(menu_bmp, btn_cheat, 0,244);
				}else{
					draw_sprite(menu_bmp, btn_cheat, 0,248);
				}
				show_mouse(menu_bmp);
				
				break;
			}
			default :{
				if(cursor_sobre_btn){
					draw_sprite(menu_bmp, aux_menu_bmp,0,0);
					cursor_sobre_btn = FALSE;
				}
			}
		}
		//si el mouse fue clickeado
		if(mouse_b & 1 && !clicked){
			clicked = TRUE;//el mouse esta clickeado
			//capturamos el color del boton sobre el cual estamos
			color = getpixel(menu_shape_bmp,mouse_x,mouse_y);
		}
		if(clicked){
			if(!(mouse_b & 1)){//se hizo release del click
				clicked = FALSE;//el mouse no esta clickeado
				//si el color en el momento del release coincide con el color del momento de click se selecciona la opcion del botn clickeado
				/*en los casos exit y main menu el juego termina, por lo que se modifica la variable winner,
				se libera la memoria, y retorna*/
				
				if (color == getpixel(menu_shape_bmp,mouse_x,mouse_y)){
					switch(color){
						case MAIN_MENU:
							winner = MAIN_MENU;
							show_mouse(NULL);
							destroy_bitmap(menu_bmp);
							destroy_bitmap(aux_menu_bmp);
							destroy_bitmap(btn_cheat);
							destroy_bitmap(menu_shape_bmp);
							destroy_bitmap(btn_mainmenu);
							destroy_bitmap(btn_reset);
							destroy_bitmap(btn_exit);
							return MAIN_MENU;
							break;
						case RESET:
							play_sample(sonido_seleccion,255,128,1000,0);
							//reseteamos el tablero
							reset(tablero, tablero_inicial, primer_turno);
							generar_tablero(tablero,hex,tab_pos_x,tab_pos_y,tab_bmp_w,tab_bmp_h);
							break;
						case EXIT:
							printf("\nExit");
							winner = EXIT;
							show_mouse(NULL);
							destroy_bitmap(menu_bmp);
							destroy_bitmap(aux_menu_bmp);
							destroy_bitmap(btn_cheat);
							destroy_bitmap(menu_shape_bmp);
							destroy_bitmap(btn_mainmenu);
							destroy_bitmap(btn_reset);
							destroy_bitmap(btn_exit);
							return EXIT;
							break;
						case CHEAT:
						
							play_sample(sonido_seleccion,255,128,1000,0);
							if(cheat){
								//borramos el rastro de cheat mode
								clear_cheat( tablero,  sano,  tab_pos_x, tab_pos_y);
								//intercambiamos las imagenes y el estado de cheat
								cheat = FALSE;
								aux_menu_bmp = load_bitmap("imagenes/menu/ingame_off.bmp",NULL);
								btn_cheat    = load_bitmap("imagenes/menu/ingame_cheat_off.bmp",NULL);
							}else{
								//intercambiamos las imagenes y el estado de cheat
								cheat = TRUE;
								aux_menu_bmp = load_bitmap("imagenes/menu/ingame_on.bmp",NULL);
								btn_cheat    = load_bitmap("imagenes/menu/ingame_cheat_on.bmp",NULL);
							}
						break;
					}
				}
			}
		}
		show_mouse(menu_bmp);
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		
	}
	show_mouse(menu_bmp);
	//capturamos el ESC para salir al soltar la tecla
	while(!key[KEY_ESC]){
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	while(key[KEY_ESC]){
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	//liberamos memoria (si llegamos aca es porque hubo un error)
	show_mouse(NULL);
	destroy_bitmap(menu_bmp);
	destroy_bitmap(aux_menu_bmp);
	destroy_bitmap(btn_cheat);
	destroy_bitmap(menu_shape_bmp);
	destroy_bitmap(btn_mainmenu);
	destroy_bitmap(btn_reset);
	destroy_bitmap(btn_exit);
	return 1;
}
/*captura el path de la carpeta donde se encuentra el ejecutable*/
void current_folder(char folder[200]){
	/*
	parámetro
		folder = variable donde se va a guardar el path de la carpeta actual 
	*/
	char comando[500]="";//para ejecutar comandos del sistema operativo
	char cadena[200]="";//buffer
	
	//vaciamos la cadena
	strcpy(folder,"");
	//comando cd para que nos muestre el nombre del path donde esta el ejecutable
	strcpy(comando,"cd");
	strcat(comando,folder);
	//le decimos al sistema operativo que nos genere el archivo "current_folder.txt" con el contenido del comando cd
	strcat(comando," > current_folder.txt");
	//ejecutamos el comando
	system(comando);
	//abrimos el archivo que habiamos creado
	FILE* current_folder_path = fopen("current_folder.txt","r");
	int i=0;//varible para recorrer el string
	while(1){
		fscanf(current_folder_path,"%c",&cadena[i]);//leemos caracter por caracter el archivo
		if(cadena[i]=='\n'){//si encontramos salto de linea
			//cerramos el buffer
			cadena[i]='\0';
			//vaciamos la cadena
			strcpy(folder,"");
			//copiamos el buffer a la cadena
			strcpy(folder,cadena);
			//le agregamos una barra al path
			strcat(folder,"\\");
			//salimos del while infinito
			break;
		}
		//siguiente caracter
		i++;
	}
	//cerramos y eliminamos el archivo temporal
	fclose(current_folder_path);
	remove("current_folder.txt");

}
/*administra el menu de seleccion de carpetas para archivos xml*/
int xml_menu(char write_to_folder[200],char read_from_folder[200]){
	/*
	parametros
		write_to_folder = path de la carpeta donde el ejecutable creara el xml
		read_from_folder = path de la carpeta de donde se leera el xml
	*/
	//si las cadenas estan vacias llenarlas con el path de la carpeta donde se encuentra el ejecutable
	if(!strcmp(write_to_folder,""))
		current_folder(write_to_folder);
	if(!strcmp(read_from_folder,""))
		current_folder(read_from_folder);
	
	
	BITMAP *menu_bmp = create_bitmap(SCREEN_W,SCREEN_H);//buffer principal
	BITMAP *aux_menu_bmp = create_bitmap(SCREEN_W,SCREEN_H);//buffer secundario

	BITMAP *fondo = load_bitmap("imagenes/menu/xml_menu.bmp",NULL);//bitmap de fondo
	
	//creamos nuestra grilla de colores
	clear_to_color(aux_menu_bmp,COLOR_NULO);
	rectfill(aux_menu_bmp,  30,107,778,132,XML_INPUT1);
	rectfill(aux_menu_bmp, 556,164,778,204,XML_SELECT1);
	rectfill(aux_menu_bmp,  30,320,778,345,XML_INPUT2);
	rectfill(aux_menu_bmp, 556,388,778,428,XML_SELECT2);		
	rectfill(aux_menu_bmp, 473,512,783,572,XML_CONTINUE);		
	
	
	draw_sprite(menu_bmp, fondo, 0, 0);
	int color = FALSE;//para compara el estado del mouse
	int clicked = FALSE;//indica si el mouse esta o no clickeado
	int cursor_sobre_btn = FALSE;//indica si el mouse esta sobre un boton
	int input1_clic = TRUE;//se esta editando la carpeta de escritura
	int input2_clic = TRUE;//es esta editando la carpeta de lectura
	int edit_field = FALSE;//se esta editando algun textfield
	int proceed = FALSE;//para pasar al siguiente menu
	int select_folder1 = FALSE;//se entro al submenu de seleccion 1
	int select_folder2 = FALSE;//se entro al submenu de seleccion 2
	
	char caracter;//buffer de escritura

	//imprimimos el path en la pantalla... sobre los elementos
	textprintf_ex(menu_bmp, font, 35, 115,0,-1,"%s",write_to_folder);
	textprintf_ex(menu_bmp, font, 35, 328,0,-1,"%s",read_from_folder);
	
	
	show_mouse(menu_bmp);
	blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	BITMAP* in_input1    = load_bitmap("imagenes/menu/xml_input1.bmp",NULL);  //textfield1
	BITMAP* in_input2    = load_bitmap("imagenes/menu/xml_input2.bmp",NULL);  //textfield2
	BITMAP* btn_select1  = load_bitmap("imagenes/menu/xml_select1.bmp",NULL);  //boton de seleccion 1
	BITMAP* btn_select2  = load_bitmap("imagenes/menu/xml_select2.bmp",NULL);  //boton de seleccion 2
	BITMAP* btn_continue = load_bitmap("imagenes/menu/xml_continue.bmp",NULL); //boton de continue
	
	while(!proceed){//mientras no se haya continuado
	
		if(key[KEY_ESC]){//esc para el menu anterior (main menu)
			show_mouse(NULL);
			destroy_bitmap(menu_bmp);
			destroy_bitmap(aux_menu_bmp);
			destroy_bitmap(fondo);
			destroy_bitmap(in_input1);
			destroy_bitmap(in_input2);
			destroy_bitmap(btn_select1);
			destroy_bitmap(btn_select2);
			destroy_bitmap(btn_continue);
			return MAIN_MENU;
		}
	
		
		if(mouse_b & 1 && XML_INPUT1 == getpixel(aux_menu_bmp,mouse_x,mouse_y)){//si el mouse esta clickeado y el mouse esta sobre el input 1
			
			if(input1_clic){//si es la primera vez que se modifica
				//borramos el string para que el input sea desde cero
				*write_to_folder = '\0';
				input1_clic = FALSE;
			}
			
			edit_field = XML_INPUT1;//se esta editando el input1
			show_mouse(NULL);
			//imprimimos el path nuevo
			draw_sprite(menu_bmp,in_input1,0,97);
			textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
			show_mouse(menu_bmp);
			clear_keybuf();
		}else{
			if(mouse_b & 1 && XML_INPUT2 == getpixel(aux_menu_bmp,mouse_x,mouse_y)){//si el mouse esta clickeado y el mouse esta sobre el input 2
				if(input2_clic){//si es la primera vez que se modifica
				//borramos el string para que el input sea desde cero
					*read_from_folder = '\0';
					input2_clic = FALSE;
				}
				edit_field = XML_INPUT2;//se esta editando el input2
				show_mouse(NULL);
				//imprimimos el path nuevo
				draw_sprite(menu_bmp,in_input2,0,307);
				textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
				show_mouse(menu_bmp);
				clear_keybuf();
			}
		}
		
		while(edit_field == XML_INPUT1){//si se esta editando el input 1
			if(keypressed()){//si se tiene presionada una tecla
				if(keypressed())//se captura la seleccion
					caracter = readkey();
				
				if( key[KEY_BACKSPACE] ){//si se aprieta "borrar"
					if( strlen(write_to_folder) )
						//retrocedemos un caracter
						write_to_folder[strlen(write_to_folder)-1] = '\0';
				}else{
					//vamos actualizando el path con lo que escribe el usuario
					if( text_length(font, write_to_folder)<748 ){
						write_to_folder[strlen(write_to_folder)+1] = '\0';
						write_to_folder[strlen(write_to_folder)] = caracter;
						
					}
				}
				//limpiamos el buffer de teclas
				clear_keybuf();
				show_mouse(NULL);
				//actualizamos el path editado
				draw_sprite(menu_bmp, in_input1, 0, 97);
				textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
				show_mouse(menu_bmp);
			}
			/*el switch hace que mientras se edite el input 1, los demas elementos sigan siendo sensibles al mouse*/
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){
				case XML_INPUT2:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, in_input2, 0, 307);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_INPUT2;
						}
						break;
				case XML_SELECT1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select1, 537, 147);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT1;
						}
						break;
				case XML_SELECT2:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select2, 518, 365);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT2;
						}
						break;
				case XML_CONTINUE:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_continue, 428,475);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_CONTINUE;
						}
						break;							
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);
							draw_sprite(menu_bmp, in_input1, 0, 97);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
				
			}
			show_mouse(menu_bmp);
			//se actualiza la pantalla
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
			if( mouse_b&1 && XML_INPUT1!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){//si se clickeo fuera del edit
				//se captura el color
				color = cursor_sobre_btn;
				clicked = TRUE;//mouse se esta clickeando
				edit_field = FALSE;//no hay input en edicion
				show_mouse(NULL);
				//actualizar paths
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
				textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
				show_mouse(menu_bmp);
				cursor_sobre_btn=FALSE;
			}
		}
		
		while(edit_field == XML_INPUT2){//si se esta editando el input 2
			if(keypressed()){//si se tiene presionada una tecla
				if(keypressed())//se captura la seleccion
					caracter = readkey();
				
				if( key[KEY_BACKSPACE] ){//si se aprieta "borrar"
					if( strlen(read_from_folder) )
						//retrocedemos un caracter
						read_from_folder[strlen(read_from_folder)-1] = '\0';
				}else{
					//vamos actualizando el path con lo que escribe el usuario
					if( text_length(font, read_from_folder)<748 /*&& isprint(caracter)*/ ){
						read_from_folder[strlen(read_from_folder)+1] = '\0';
						read_from_folder[strlen(read_from_folder)] = caracter;
						
					}
				}
				//limpiamos el buffer de teclas
				clear_keybuf();
				show_mouse(NULL);
				//actualizamos el path editado
				draw_sprite(menu_bmp, in_input2, 0, 307);
				textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
				show_mouse(menu_bmp);
			}
			/*el switch hace que mientras se edite el input 2, los demas elementos sigan siendo sensibles al mouse*/
			switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){
				case XML_INPUT1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, in_input1, 0, 97);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_INPUT2;
						}
						break;
				case XML_SELECT1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select1, 537, 147);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT1;
						}
						break;
				case XML_SELECT2:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select2, 518, 365);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT2;
						}
						break;
				case XML_CONTINUE:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_continue, 428,475);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_CONTINUE;
						}
						break;							
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);
							draw_sprite(menu_bmp, in_input2, 0, 307);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
				
			}
			show_mouse(menu_bmp);
			//se actualiza la pantalla
			blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
			if( mouse_b&1 && XML_INPUT2!=getpixel(aux_menu_bmp, mouse_x, mouse_y) ){
				//se captura el color
				color = cursor_sobre_btn;
				clicked = TRUE;//mouse se esta clickeando
				edit_field = FALSE;//no hay input en edicion
				show_mouse(NULL);
				//actualizar paths
				draw_sprite(menu_bmp, fondo, 0, 0);
				textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
				textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
				show_mouse(menu_bmp);
				cursor_sobre_btn=FALSE;
			}
		}
		
		if(!clicked && mouse_b&1){//si se hizo click
			clicked = TRUE;//mouse esta clickeado
			color = cursor_sobre_btn;//capturamos el color del boton
		}
		
		
		if(clicked && !mouse_b&1){//cuando se hace el release
			clicked = FALSE;//mouse no esta clickeado
			if( XML_CONTINUE==color ){
				//liberamos memoria y continuamos al siguiente menu
				show_mouse(NULL);
				destroy_bitmap(menu_bmp);
				destroy_bitmap(aux_menu_bmp);
				destroy_bitmap(fondo);
				destroy_bitmap(in_input1);
				destroy_bitmap(in_input2);
				destroy_bitmap(btn_select1);
				destroy_bitmap(btn_select2);
				destroy_bitmap(btn_continue);
				return PCVPC_NAME;
			}
			if( XML_SELECT1==color )
				select_folder1 = TRUE;//se va a entrar al menu de seleccion 1
			if( XML_SELECT2==color )
				select_folder2 = TRUE;//se va a entrar al menu de seleccion 2
		
		}
		/*switch general para que los elementos sean sensibles a la posicion del mouse*/
		switch(getpixel(aux_menu_bmp, mouse_x, mouse_y)){
				case XML_INPUT1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, in_input1, 0, 97);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_INPUT2;
						}
						break;
				case XML_INPUT2:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, in_input2, 0, 307);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_INPUT2;
						}
						break;
				case XML_SELECT1:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select1, 537, 147);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT1;
						}
						break;
				case XML_SELECT2:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_select2, 518, 365);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_SELECT2;
						}
						break;
				case XML_CONTINUE:
						if( !cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, btn_continue, 428,475);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=XML_CONTINUE;
						}
						break;							
				case COLOR_NULO :
						if( cursor_sobre_btn ){
							show_mouse(NULL);
							draw_sprite(menu_bmp, fondo, 0, 0);
							textprintf_ex(menu_bmp, font, 35, 115, 0,-1,"%s",write_to_folder);
							textprintf_ex(menu_bmp, font, 35, 328, 0,-1,"%s",read_from_folder);
							show_mouse(menu_bmp);
							cursor_sobre_btn=FALSE;
						}
				
			}
		//manejadores de la parte grafica de seleccion de carpetas
		if(select_folder1 || select_folder2){//si se tiene que entrar a algun menu de seleccion de carpetas
			if(select_folder1){//si es el menu de seleccion 1
				//llamamos al menu de seleccion de carpetas con la cadena de escritura
				if(file_select_ex("Write XML file to:", write_to_folder,"+d" , 600, 700,500)){
					select_folder1=FALSE;
				}else{
					select_folder1=FALSE;
				}
			}
			if(select_folder2){//si es el menu de seleccion 2
				//llamamos al menu de seleccion de carpetas con la cadena de lectura
				if(file_select_ex("Read XML file from:", read_from_folder,"+d" , 600, 700,500)){
					select_folder2=FALSE;
				}else{
					select_folder2=FALSE;
				}
			}
		}
		show_mouse(menu_bmp);
		//actualizamos la pantalla
		blit(menu_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	//liberamos memoria y retornamos 1 (si se llega aca es un error... no deberia pasar)
	show_mouse(NULL);
	destroy_bitmap(menu_bmp);
	destroy_bitmap(aux_menu_bmp);
	destroy_bitmap(fondo);
	destroy_bitmap(in_input1);
	destroy_bitmap(in_input2);
	destroy_bitmap(btn_select1);
	destroy_bitmap(btn_select2);
	destroy_bitmap(btn_continue);
	return 1;
}

