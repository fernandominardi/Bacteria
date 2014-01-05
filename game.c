
extern volatile long speed_counter;
/*verifica que la jugada recibida sea realizable en el tablero actual de juego*/
int es_jugada_valida(int jugada,char tablero[tab_h][tab_w]){
	/*
	parámetros
		jugada = codigo de jugada [ver glosario] 
		tablero = tablero actual del juego
	*/
	
	
	int jugada_aux = get_jugada(jugada);//guardamos el movimiento realizado
	
	if(jugada_aux==PASAR){//si la jugada es pasar... es valida
		return TRUE;
	}
	
	int f_fin = get_fila_final(jugada);
	int c_fin = get_col_final(jugada);
	
	if(jugada_aux==MULTIPLICAR){//si la jugada es multiplicar
	
		/*si algun vecino es bacteria aliada al turno actual del juego, es una movida valida*/
		
		if( !(0<=f_fin && f_fin<tab_h && 0<=c_fin && c_fin<tab_w) ){//si la posicion destino esta fuera del tablero, el movimiento no es valido
			return FALSE;
		}
		int i,j;
		for(i=f_fin-1+c_fin%2 ; i<=f_fin+c_fin%2 ; i++){//se recorren los vecinos [ver glosario para metodo detallado]
			for(j=c_fin-1 ; j<=c_fin+1 ; j++){
				
				if(i==f_fin && j==c_fin){
					if( (0<=i+1-2*(c_fin%2) && i+1-2*(c_fin%2)<tab_h) && (0<=j && j<tab_w) && tablero[i+1-2*(c_fin%2)][j]==TURNO )//es bacteria aliada
						return TRUE;
				}else{
					if( (0<=i && i<tab_h) && (0<=j && j<tab_w) && tablero[i][j]==TURNO )//es bacteria aliada
						return TRUE;
				}
				
			}
		}
		return FALSE;
		
	}
	
	
	int f_ini = get_fila_inicial(jugada);
	int c_ini = get_col_inicial(jugada);
	
	if(jugada_aux==PROPAGAR){//si la jugada es propagar
		if( !(0<=f_fin && f_fin<tab_h && 0<=c_fin && c_fin<tab_w) ){//si la posicion destino esta fuera del tablero, el movimiento no es valido
			return FALSE;
		}
		
		if( !(0<=f_ini && f_ini<tab_h && 0<=c_ini && c_ini<tab_w) ){//si la posicion origen esta fuera del tablero, el movimiento no es valido
			return FALSE;
		}
		
		if(tablero[f_ini][c_ini]==TURNO && tablero[f_fin][c_fin]==TEJIDO_SANO && es_vecino_al_vecino(f_ini,c_ini,f_fin,c_fin)){//si la posicion origen tiene una bacteria aliada, la posicion destino una celda sana, y cumplen con es_vecino_al_vecino, es un movimiento valido
			return TRUE;
		}
		
	}
	
	return FALSE;
	
}
/*administra el proceso del juego*/
int game(BITMAP* cursor,char player0[26],char player1[26], int game_type, char tablero_inicial[12][12],SAMPLE *boton,SAMPLE *sonido_seleccion,char write_to_file[],char read_from_file[]){
	/*
	administra y controla el avance del juego, controlando las reglas y la intermitencia de los turnos
	
	parametros
		cursor = bitmap que contiene la imagen del mouse
		player0 = nombre del jugador azul
		player1 = nombre del jugador verde
		game_type = identificador del tipo de juego
		tablero_inicial = tablero cargado con el estado inicial
		boton = sonido que se reproduce al pasar el mouse sobre un boton
		sonido_seleccion = sonido que se reproduce al hacer click en un boton
		char write_to_file = ruta del xml que genera este programa
		read_from_file = ruta del xml que genera el programa externo
	*/
	DATAFILE *font_source_12;//archivo de datos para cargar fuentes
	FONT *mv_boli_12;// puntero a la fuente nueva
	
	//cargamos la fuente
	font_source_12 = load_datafile("font/mv_boli_12.dat");
	//apuntamos a la fuente cargada
	mv_boli_12 = (FONT *)font_source_12[0].dat;
	
	FILE *read;// puntero para comprobar archivo externo
	
	char tablero[tab_h][tab_w];//tablero principal del juego
	int i,j;//variables para recorrer los tableros
	
	//seteamos el tablero al estado inicial
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			tablero[i][j] = tablero_inicial[i][j];
		}
	}
	
	cheat=FALSE;// indica el estado del modo cheat TRUE = activado, FALSE = desactivado
	winner = NO_HAY_GANADOR;//indica estado de fin de jeugo
	long time_counter;//variable para control de tiempo para animaciones y sonido
	int cant_casillas = contar_casillas(tablero);//cantidad de casillas del tablero (para controlar estado de fin de juego)
	int sonido_ban = TRUE;//bandera utilizada para la reproduccion de sonidos
	int cant_azul;//cantidad de bacterias azules
	int cant_verde;//cantidad de bacterias verdes
	int primer_turno;//guarda el valor del primer turno (utilizado para resetear el juego)
	int skip_cont=0;//contador de movimientos PASAR (para controlar estado de fin de jeugo)
	int jugada;//jugada a ser aplicada por los tableros (PVPC, PCVPC)
	int color;//variable para comparar las posiciones del mouse
	
	BITMAP* hex = load_bitmap("imagenes/hexagono_original.bmp",NULL);//tejido sano (variable que se modifica)
	
	BITMAP* sano = load_bitmap("imagenes/hexagono_original.bmp",NULL);//tejido sano (variable que no se modifica)
	BITMAP* mult = load_bitmap("imagenes/posible_multiplicacion.bmp",NULL);//posible multiplicacion (cheat mode)
	BITMAP* prop = load_bitmap("imagenes/posible_propagacion.bmp",NULL);//posible propagacion(cheat mode)
	
	BITMAP* btn_skip = load_bitmap("imagenes/btn_skip.bmp",NULL);//boton de skip
	BITMAP* btn_skip_brillando = load_bitmap("imagenes/btn_skip_brillando.bmp",NULL);//boton de skip cuando el mouse esta sobre el mismo
	/*sonidos de las bacterias*/
	SAMPLE *bacteria1 = load_sample("sonidos/bacteria1.wav");
	SAMPLE *bacteria2 = load_sample("sonidos/bacteria2.wav");
	SAMPLE *bacteria3 = load_sample("sonidos/bacteria3.wav");
	SAMPLE *bacteria4 = load_sample("sonidos/bacteria4.wav");
	
	int tab_pos_x,tab_pos_y,tab_bmp_w,tab_bmp_h;//variable de posicion horizontal, posicion vertical, ancho y alto del tablero
	
	//calculamos el ancho y alto del tablero
	tab_bmp_w = tab_w*hex_w2 + hex->w - hex_w2;
	tab_bmp_h = tab_h*(hex->h) + (hex->h)/2;
	//calculamos la posicion del tablero
	tab_pos_x = SCREEN_W/2 - tab_bmp_w/2;
	tab_pos_y = SCREEN_H/2 - tab_bmp_h/2;
	
	//definimos el turno inicial
	if(game_type!=PCVPC){//si no es PC versus PC, se randomiza el turno
		primer_turno = TURNO = rand()%2;
	}else{//en caso de ser PC versus PC, el primer jugador empieza arriba a la izquierda
		primer_turno = TURNO;
		if(TURNO == BACTERIA_VERDE){
			tablero[0][0]=BACTERIA_VERDE;
			tablero[7][7]=BACTERIA_AZUL;
		}
	}
	//generamos el tablero grafico
	generar_tablero(tablero,hex,tab_pos_x,tab_pos_y,tab_bmp_w,tab_bmp_h);
	//contamos las bacterias actuales
	contar_bacterias(tablero, &cant_azul, &cant_verde);
	//imprimimos los datos en el buffer
	imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
	//dibujamos el boton skip en el buffer
	draw_sprite(tab_bmp, btn_skip, 0,530);
	//mostramos el mouse el buffer
	show_mouse(tab_bmp);
	//imprimimos el buffer en la pantalla
	blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	
	
	while(winner==NO_HAY_GANADOR){//mientras no haya ganador (estado de juego)
		while(speed_counter > 0){//mientras el timer no esta pintando la pantalla
			if(game_type==PVP || (game_type==PVPC && TURNO==BACTERIA_AZUL) ){//si el juego es player versus player o es player versus pc y es turno del jugador (turno de jugador humano)
				if(cheat){//si el modo cheat esta activado se llama a la funcion que administra dicho modo
					cheat_handler(tablero, tab_pos_x, tab_pos_y, sano, mult, prop);
				}
				if(mouse_b&1){//si el jugador hace click
					if(es_casilla_valida(tab_pos_x,tab_pos_y,mouse_x,mouse_y)){//se verifica si se hizo click en una casilla
						//si es una casilla con tejido sano se procede a verificar la multiplicacion
						if( TEJIDO_SANO==tablero[get_pos_f(mouse_x,mouse_y,tab_pos_x,tab_pos_y)][get_pos_c(mouse_x,mouse_y,tab_pos_x,tab_pos_y)] ){
							color = getpixel(aux_tab_bmp,mouse_x - tab_pos_x,mouse_y - tab_pos_y);//se captura el color del mouse al momento de hacer click
							while((mouse_b&1)){//mientras se mantiene el click apretado, se refresca la pantalla
								blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
							}
							//se solto el click
							if( color == getpixel(aux_tab_bmp,mouse_x - tab_pos_x,mouse_y - tab_pos_y) ){//si se hizo el release en la misma casilla con tejido sano
								//se limpia el rastro del modo cheat
								clear_cheat( tablero, sano, tab_pos_x, tab_pos_y);
								//se intenta multiplicar, en caso de exito se resetea el contador de turnos pasados por skip
								if(multiplicar(tablero , get_pos_f(mouse_x,mouse_y,tab_pos_x,tab_pos_y), get_pos_c(mouse_x,mouse_y,tab_pos_x,tab_pos_y),hex,tab_pos_x,tab_pos_y)){
									skip_cont=0;
								}
								//se actualiza el estado del tablero y se verifica que exista ganador
								contar_bacterias(tablero, &cant_azul, &cant_verde);
								if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
									if(cant_azul==cant_verde){
										winner=EMPATE;
									}else{
										if(cant_azul>cant_verde)
											winner=BACTERIA_AZUL;
										else
											winner=BACTERIA_VERDE;
									}
								}
								imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							}
						}else{//la casilla no esta sana
						
							//es una casilla con una bacteria aliada
							if( TURNO==tablero[get_pos_f(mouse_x,mouse_y,tab_pos_x,tab_pos_y)][get_pos_c(mouse_x,mouse_y,tab_pos_x,tab_pos_y)] ){
								//se randomiza el sonido respectivo de seleccion de bacteria
								switch(rand()%4){
									case 0:
										play_sample(bacteria1,255,128,1000,0);
										break;
									case 1:
										play_sample(bacteria2,255,128,1000,0);
										break;
									case 2:
										play_sample(bacteria3,255,128,1000,0);
										break;
									case 3:
										play_sample(bacteria4,255,128,1000,0);
										break;
								}
								//se borran los rastros del cheat mode
								clear_cheat( tablero, sano, tab_pos_x, tab_pos_y);
								//se llama a propagar, en caso de que se haya logrado terminar con exito el movimiento, se resetea el contador de turnos pasados por skip
								if( propagar(tablero, get_pos_f(mouse_x,mouse_y,tab_pos_x,tab_pos_y), get_pos_c(mouse_x,mouse_y,tab_pos_x,tab_pos_y),tab_pos_x,tab_pos_y,hex,cursor) ){
									skip_cont=0;
								}
								//se actualiza el estado del tablero y se verifica que exista ganador
								contar_bacterias(tablero, &cant_azul, &cant_verde);
								if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
									if(cant_azul==cant_verde){
										winner=EMPATE;
									}else{
										if(cant_azul>cant_verde)
											winner=BACTERIA_AZUL;
										else
											winner=BACTERIA_VERDE;
									}
								}
								imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							}
						}
					}else{//no es casilla valida
						if( (15 < mouse_x) && (mouse_x < 140) && (540 < mouse_y) && (mouse_y < 581) ){//estamos sobre el boton skip
							while((mouse_b&1)){//se clickeo el boton
							
								//se calcula la posicion para hacer que brille solo si se esta encima
								show_mouse(NULL);
								if( (15 < mouse_x) && (mouse_x < 140) && (540 < mouse_y) && (mouse_y < 581) ){
									draw_sprite(tab_bmp, btn_skip_brillando, 0,530);
								}else{
									draw_sprite(tab_bmp, btn_skip, 0,530);
								}
								show_mouse(tab_bmp);
								//se actualiza la pantalla
								blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
							}
							//se solto el click
							//si el click se solto en el boton skip
							if( (15 < mouse_x) && (mouse_x < 140) && (540 < mouse_y) && (mouse_y < 581) ){
								//se cambia de turno
								cambiar_turno();
								//se reproduce el sonido de boton clickeado
								play_sample(sonido_seleccion,255,128,1000,0);
								//se aumenta el contador de turnos pasados por skip
								skip_cont++;
								//si se pasan 3 veces seguidas, termina el juego en empate
								if( skip_cont==3 ){
									winner=EMPATE;
								}
								//delay de tiempo para actualizar los datos
								time_counter = speed_counter;
								while( !(speed_counter - time_counter > 20) || (speed_counter < time_counter ) ){
									blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
								}
								
								
								imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							}
						}
					}
				}	
				show_mouse(NULL); //[ver MOUSE en glosario]
				//se calcula la posicion para hacer que brille solo si se esta encima
				if( (15 < mouse_x) && (mouse_x < 140) && (540 < mouse_y) && (mouse_y < 581) ){
					if(sonido_ban!=SKIP){
						play_sample(boton,255,128,1000,0);
						draw_sprite(tab_bmp, btn_skip_brillando, 0,530);
						sonido_ban = SKIP;
					}
					
				}else{
					if(sonido_ban){
						draw_sprite(tab_bmp, btn_skip, 0,530);
						sonido_ban = FALSE;
					}
				}
			}else{//jugador no humano
				if(game_type==PVPC || (game_type==PCVPC && TURNO==BACTERIA_VERDE)){//juega nuestro programa
					//se carga la jugada de la AI
					jugada = ai_main(tablero);
					//delay de animacion y sonido
					time_counter = speed_counter;
					while( !(speed_counter - time_counter > 10) || (speed_counter < time_counter ) ){
						blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
					}
					//se evalua la jugada de la AI
					switch(get_jugada(jugada)){
						case MULTIPLICAR:{
							if(multiplicar(tablero,get_fila_final(jugada), get_col_final(jugada) , hex, tab_pos_x, tab_pos_y)){
								skip_cont = 0;
							}
							if(game_type==PCVPC ){//si es PC versus PC se crea el archivo xml
								if((read = fopen(write_to_file,"r"))){
									fclose(read);
									remove(write_to_file);//en caso de que el otro programa no haya borrado nuestro archivo
								}
								jugada_xml(write_to_file,MULTIPLICAR,0,0, get_fila_final(jugada),get_col_final(jugada));
							}
							//se actualiza el estado del tablero y se verifica que exista ganador
							contar_bacterias(tablero, &cant_azul, &cant_verde);
							if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
								if(cant_azul==cant_verde){
									winner=EMPATE;
								}else{
									if(cant_azul>cant_verde)
										winner=BACTERIA_AZUL;
									else
										winner=BACTERIA_VERDE;
								}
							}
							imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							break;	
						}
						case PROPAGAR:{
							if(propagar_PC(tablero,get_fila_inicial(jugada), get_col_inicial(jugada) ,get_fila_final(jugada), get_col_final(jugada) , tab_pos_x, tab_pos_y, hex)){
								skip_cont = 0;
							}
							
							if(game_type==PCVPC ){//si es PC versus PC se crea el archivo xml
								if((read = fopen(write_to_file,"r"))){
									fclose(read);
									remove(write_to_file);//en caso de que el otro programa no haya borrado nuestro archivo
								}
								jugada_xml(write_to_file,PROPAGAR,get_fila_inicial(jugada),get_col_inicial(jugada), get_fila_final(jugada),get_col_final(jugada));
							}
							//se actualiza el estado del tablero y se verifica que exista ganador
							contar_bacterias(tablero, &cant_azul, &cant_verde);
							if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
								if(cant_azul==cant_verde){
									winner=EMPATE;
								}else{
									if(cant_azul>cant_verde)
										winner=BACTERIA_AZUL;
									else
										winner=BACTERIA_VERDE;
								}
							}
							imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							break;
						}
						case (PASAR):{
						
							if(game_type==PCVPC ){//si es PC versus PC se crea el archivo xml
								if((read = fopen(write_to_file,"r"))){
									fclose(read);
									remove(write_to_file);//en caso de que el otro programa no haya borrado nuestro archivo
								}
								jugada_xml(write_to_file,PASAR,0,0,0,0);
							}
							//se incrementa el contador de turnos pasados por skip
							skip_cont++;
							if( skip_cont==3 ){
								winner=EMPATE;
							}
							
							//delay de animacion y sonido
							time_counter = speed_counter;
							while( !(speed_counter - time_counter > 20) || (speed_counter < time_counter ) ){
								blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
							}
							
							//se cambia el turno
							cambiar_turno();
							break;
						}
					}
					//se actualizan los datos en pantalla
					imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
				}else{
					//se trata de leer el archivo creado por el pograma externo, se espera hasta que se cree, o hasta que se salga manualmente delprograma
					while(!(read = fopen(read_from_file,"r"))){
						
						if(key[KEY_ESC]){//para salir manualmente
							int selection = FALSE;
							
							while(key[KEY_ESC]){
								blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
							}
							//sonido al entrar al menu
							play_sample(sonido_seleccion,255,128,1000,0);
							//entramos al menu del juego
							selection = ingame_menu(tablero, tablero_inicial, hex, sano, tab_pos_x, tab_pos_y, tab_bmp_w, tab_bmp_h, primer_turno, boton, sonido_seleccion);
							//sonido al salir del menu
							play_sample(boton,255,128,1000,0);
							//se evalua lo devuelto por el menu
							if (selection == EXIT){
								if(game_type == PCVPC){
									//resetamos las rutas
									strcpy(read_from_file,""); 
									strcpy(write_to_file,""); 
								}
								return FALSE;
							}
							
							if (selection == MAIN_MENU){
								if(game_type == PCVPC){
									//resetamos las rutas
									strcpy(read_from_file,""); 
									strcpy(write_to_file,""); 
								}
								winner = FALSE;
								return MAIN_MENU;
							}
							
							
							//actualizacion de datos en pantalla
							contar_bacterias(tablero, &cant_azul, &cant_verde);
							imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
							show_mouse(tab_bmp);
						}
						//actualizacion de la pantalla
						blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
					}
					//una vez que aseguramos que podemos leer el archivo, lo cerramos 
					fclose(read);
					//esperamos por si el otro programa siga escribiendo
					time_counter = speed_counter;
					while( !(speed_counter - time_counter > 30) || (speed_counter < time_counter ) ){
						blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
					}
					//extraemos la jugada del archivo
					jugada = get_jugada_xml(read_from_file);
					//eliminamos el archivo leido
					remove(read_from_file);
					//evaluamos la validez de la jugada enemiga
					if(es_jugada_valida(jugada,tablero)){
						//la jugada es valida
						switch(get_jugada(jugada)){
							case MULTIPLICAR:{
								multiplicar(tablero,get_fila_final(jugada), get_col_final(jugada) , hex, tab_pos_x, tab_pos_y);
								skip_cont = 0;
								//se actualiza el estado del tablero y se verifica que exista ganador
								contar_bacterias(tablero, &cant_azul, &cant_verde);
								if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
									if(cant_azul==cant_verde){
										winner=EMPATE;
									}else{
										if(cant_azul>cant_verde)
											winner=BACTERIA_AZUL;
										else
											winner=BACTERIA_VERDE;
									}
								}
								imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
								break;	
							}
							case PROPAGAR:{
								propagar_PC(tablero,get_fila_inicial(jugada), get_col_inicial(jugada) ,get_fila_final(jugada), get_col_final(jugada) , tab_pos_x, tab_pos_y, hex);
								skip_cont = 0;
								//se actualiza el estado del tablero y se verifica que exista ganador
								contar_bacterias(tablero, &cant_azul, &cant_verde);
								if( (cant_azul + cant_verde)==cant_casillas || !cant_azul || !cant_verde ){
									if(cant_azul==cant_verde){
										winner=EMPATE;
									}else{
										if(cant_azul>cant_verde)
											winner=BACTERIA_AZUL;
										else
											winner=BACTERIA_VERDE;
									}
								}
								imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
								break;
							}
							case (PASAR):{
								
								skip_cont++;
								cambiar_turno();
								break;
							}
						}
						imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
					}else{//la jugada no es valida, el programa informa y termina
						allegro_message("la jugada leída no es valida en el tablero actual, el programa debe cerrarse");
						exit(1);
					}
				}
			}
			
			if(key[KEY_I]){//ingresar a las isntrucciones del juego y reglas
				instrucciones(GAME);
			}
			//cerar variable global de tiempo
			speed_counter = 0;
		}
		
		
		
		if(key[KEY_ESC]){//para entrar a opciones del juego
			int selection = FALSE;
			while(key[KEY_ESC]){
				blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
			}
			//sonido al entrar al menu
			play_sample(sonido_seleccion,255,128,1000,0);
			//entramos al menu del juego
			selection = ingame_menu(tablero, tablero_inicial, hex, sano, tab_pos_x, tab_pos_y, tab_bmp_w, tab_bmp_h, primer_turno, boton, sonido_seleccion);
			//sonido al salir del menu
			play_sample(boton,255,128,1000,0);
			//evaluamos lo seleccionado en el menu
			if (selection == EXIT){
				if(game_type == PCVPC){
					//reseteamos las rutas a los archivos
					strcpy(read_from_file,""); 
					strcpy(write_to_file,""); 
				}
				return FALSE;
			}
			if (selection == MAIN_MENU){
				if(game_type == PCVPC){
					//reseteamos las rutas a los archivos
					strcpy(read_from_file,""); 
					strcpy(write_to_file,""); 
				}
				winner = FALSE;
				return MAIN_MENU;
			}
			//se actualizan los datos en el buffer y la pantalla
			contar_bacterias(tablero, &cant_azul, &cant_verde);
			imprimir_datos(cant_azul, cant_verde, player0, player1, mv_boli_12);
			draw_sprite(tab_bmp, btn_skip, 0,530);
			show_mouse(tab_bmp);
		}
		show_mouse(tab_bmp);
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
    }
	//estado de fin de juego
	//se muestra en pantalla las estadisticas del juego y el ganador
	ganador();
	//se libera la memoria 
	destroy_sample(bacteria1);
	destroy_sample(bacteria2);
	destroy_sample(bacteria3);
	destroy_sample(bacteria4);
	winner = FALSE;
	if(game_type == PCVPC){
		//se resetean las rutas a los archivos
		strcpy(read_from_file,""); 
		strcpy(write_to_file,""); 
	}
	return MAIN_MENU;
	
}
/*actualiza los datos del juego en el buffer*/
void imprimir_datos(int cant_azul, int cant_verde, char player0[26], char player1[26], FONT* mv_boli_12){
	/*
	imprime los datos del juego (estaditicas de cada jugador) en el buffer que luego sera mostrado en pantalla
	
	parámetros
		cant_azul = cantidad de bacterias azules
		cant_verde = cantidad de bacterias verdes
		player0 = nombre del jugador azul
		player1 = nombre del jugador verde
		mv_boli_12 = fuente MV Boli tamaño 12
		
	*/
	BITMAP *acuadro = load_bitmap("imagenes/cuadro_azul.bmp",NULL);//fondo para estadisticas azules
	BITMAP *abacteria = load_bitmap("imagenes/azul.bmp",NULL);//bacteria azul
	
	BITMAP *name = create_bitmap(170,20);//bitmap para el nombre del jugador
	
	//limpiamos el bitmap del nombre
	clear_to_color(name, makecol(255,0,255));
	//cargamos las estadisticas
	int porcentaje = (cant_azul*100)/(cant_verde+cant_azul);
	int decimales = ((cant_azul*10000)/(cant_verde+cant_azul))%100;
	if(decimales > 50)
		porcentaje++;
	
	show_mouse(NULL);
	//imprimimos el cuadro azul
	draw_sprite(tab_bmp, acuadro, 8, 310);
	draw_sprite(tab_bmp, abacteria, 36, 330);
	//imprimimos el nombre del jugador azul en forma vertical
	textprintf_ex(name, mv_boli_12, 0, 0, makecol(84,170,224),-1,"%s",player0);
	rotate_sprite(tab_bmp, name, -66, (614 + text_length(mv_boli_12, player0))/2, itofix(192));
	//imprimimos las estadisticas
	textprintf_justify_ex(tab_bmp, mv_boli_12, 88, 118, 340,180, makecol(84,170,224),-1,"X %d",cant_azul);
	
	textprintf_justify_ex(tab_bmp, mv_boli_12, 33, 141, 375,180, makecol(84,170,224),-1,"The %d%c of",porcentaje, 37);
	
	textprintf_justify_ex(tab_bmp, mv_boli_12, 33, 141, 393,180, makecol(84,170,224),-1,"the bacteria");
	textprintf_ex(tab_bmp, mv_boli_12, 33, 411, makecol(84,170,224),-1,"are blue ");
	
	//si es el turno del azul lo indicamos en el buffer
	if(TURNO==BACTERIA_AZUL){
		textprintf_ex(tab_bmp, mv_boli_12, 53, 438, makecol(84,170,224), -1, "YOUR");
		textprintf_ex(tab_bmp, mv_boli_12, 53, 453, makecol(84,170,224), -1, "TURN");
	}
	//cambiamos a la bacteria verde y repetimos el proceso
	destroy_bitmap(acuadro);
	destroy_bitmap(abacteria);
	BITMAP *vcuadro = load_bitmap("imagenes/cuadro_verde.bmp",NULL);
	BITMAP *vbacteria = load_bitmap("imagenes/verde.bmp",NULL);
	
	porcentaje = (cant_verde*100)/(cant_verde+cant_azul);
	decimales = ((cant_verde*10000)/(cant_verde+cant_azul))%100;
	if(decimales > 50)
		porcentaje++;
	
	clear_to_color(name, makecol(255,0,255));
	
	draw_sprite(tab_bmp, vcuadro, 653, 108);
	draw_sprite(tab_bmp, vbacteria, 681, 128);
	
	textprintf_ex(name, mv_boli_12, 0, 0, makecol(36,255,134),-1,"%s",player1);
	rotate_sprite(tab_bmp, name, 579, (614 + text_length(mv_boli_12, player1))/2 -202, itofix(192));
	
	textprintf_justify_ex(tab_bmp, mv_boli_12, 733, 763, 138,180, makecol(36,255,134),-1,"X %d",cant_verde);
	
	textprintf_justify_ex(tab_bmp, mv_boli_12, 678, 786, 173,180, makecol(36,255,134),-1,"The %d%c of",porcentaje, 37);
	
	textprintf_justify_ex(tab_bmp, mv_boli_12, 678, 786, 191,180, makecol(36,255,134),-1,"the bacteria");
	textprintf_ex(tab_bmp, mv_boli_12, 678, 209, makecol(36,255,134),-1,"are green ");
	
	if(TURNO==BACTERIA_VERDE){
		textprintf_ex(tab_bmp, mv_boli_12, 698, 236, makecol(36,255,134), -1, "YOUR");
		textprintf_ex(tab_bmp, mv_boli_12, 698, 251, makecol(36,255,134), -1, "TURN");
	}
	
	show_mouse(tab_bmp);
	
	destroy_bitmap(vcuadro);
	destroy_bitmap(vbacteria);
	
}
/*imprime en pantalla la imagen de la bacteria ganadora o empate, junto con las estadisticas*/
void ganador(){
	
	SAMPLE *sonido;//sonido de felicitacion al ganador o empate
	BITMAP *winner_bmp;//bitmap que carga la imagen correspondiente
	show_mouse(NULL);
	
	if(winner==EMPATE){//si es empate se carga el sonido y la imagen corespondientes
		sonido = load_sample("sonidos/draw.wav");
		winner_bmp = load_bitmap("imagenes/draw.bmp",NULL);
		draw_sprite(tab_bmp, winner_bmp, 0, 0);
	}else{// si hubo ganador se carga el sonido de felicitacion y la imagen de la bacteria ganadora
		sonido = load_sample("sonidos/winner.wav");
		if(winner==BACTERIA_AZUL){
			winner_bmp = load_bitmap("imagenes/azul_wins.bmp",NULL);
			draw_sprite(tab_bmp, winner_bmp, 0, 0);
		}else{
			winner_bmp = load_bitmap("imagenes/verde_wins.bmp",NULL);
			draw_sprite(tab_bmp, winner_bmp, 0, 0);
		}
	}
	//se reproduce el sonido
	play_sample(sonido,255,128,1000,0);
	//mientras no se apriete una tecla para continuar, se actualiza la pantalla con la imagen ganadora o de empate
	show_mouse(tab_bmp);
	clear_keybuf();
	while(!keypressed()){
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	//liberamos memoria
	destroy_bitmap(winner_bmp);
	destroy_sample(sonido);
}
 /*borra el rastro dejado por el modo cheat*/
void clear_cheat(char tablero[tab_w][tab_h],BITMAP* sano, int tab_pos_x, int tab_pos_y){
	/*
	recorremos el tablero y actualizamos todos los tejidos sanosen el buffer
	
	parámetros
		tablero = estado actual del juego
		sano = imagen de una celda sana
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
	*/
	
	int i,j,hex_x,hex_y;//variables para recorrer tablero y posiciones horizontal y vertical para la imagen del tejido sano
	show_mouse(NULL);
	for(i=0 ; i<tab_h ; i++){//recorremos el tablero
		for(j=0 ; j<tab_w ; j++){
			if(tablero[i][j]==TEJIDO_SANO){//la posicion es tejido sano
				hex_y = (j%2)*((sano->h)/2) + tab_pos_y + i*(sano->h);//posicion vertical del hexagono
				hex_x = j*hex_w2 + tab_pos_x;//posicion horizontal del hexagono
				draw_sprite(tab_bmp, sano, hex_x, hex_y);//actualizamos la celda
			}
		}
	}
	show_mouse(tab_bmp);
}
/*administra el modo cheat*/
void cheat_handler(char tablero[tab_w][tab_h],int tab_pos_x,int tab_pos_y, BITMAP* sano, BITMAP* mult, BITMAP* prop){
	
	/*
	parámetros
		tablero = estado actual del juego
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
		sano = imagen de una celda sana
		mult = imagen de una posible multiplicacion (brillo amarillo)
		prop = imagen de una posible propagacion (brillo azul)
	*/
	
	show_mouse(NULL);
	int x = mouse_x;//posicion del mouse horizontal
	int y = mouse_y;//posicion del mouse vertical
	int f,c,i,j,hex_x,hex_y;//variables para recorrer el tablero, los vecindarios y posiciones horizontal y vertical para las imagenes
	for(i=0 ; i<tab_h ; i++){//recorremos el tablero
		for(j=0 ; j<tab_w ; j++){
			if(tablero[i][j]==TEJIDO_SANO){//la celda es tejido sano
				hex_y = (j%2)*((sano->h)/2) + tab_pos_y + i*(sano->h);//posicion vertical del hexagono
				hex_x = j*hex_w2 + tab_pos_x;//posicion horizontal del hexagono
				draw_sprite(tab_bmp, sano, hex_x, hex_y);
				if(es_casilla_valida(tab_pos_x, tab_pos_y, x, y)){//si estamos en una casilla valida
					f = get_pos_f(x, y, tab_pos_x, tab_pos_y);//fila 
					c = get_pos_c(x, y, tab_pos_x, tab_pos_y);//columna
					if(tablero[f][c]==TURNO){//si es una bacteria nuestra
						if(es_vecino_al_vecino( f, c, i, j) ){//recorremos el vecindario con sus adyacentes
							if( es_vecino( f, c, i, j) ){//mostramos las posibles multiplicaciones
								hex_y = (j%2)*((mult->h)/2) + tab_pos_y + i*(mult->h);//posicion vertical del hexagono
								hex_x = j*hex_w2 + tab_pos_x;//posicion horizontal del hexagono
								draw_sprite(tab_bmp, mult, hex_x, hex_y);
							}else{//mostramos las posibles multiplicaciones
								hex_y = (j%2)*((prop->h)/2) + tab_pos_y + i*(prop->h);//posicion vertical del hexagono
								hex_x = j*hex_w2 + tab_pos_x;//posicion horizontal del hexagono
								draw_sprite(tab_bmp, prop, hex_x, hex_y);
							}
						}
					}
				}
			}
		}
	}
	show_mouse(tab_bmp);
}
/*resetea el tablero principal y el turno a su estado inicial*/
void reset(char tablero[tab_h][tab_w], char tablero_inicial[12][12] , int primer_turno){
	/*
	parámetros
		tablero = tablero principal del juego
		tablero_inicial = tablero con el estado inicial del juego actual
		pimer turno = contiene el valor del primer jugador de la partida
	*/
	int i,j;//variables para recorrer el tablero
	TURNO = primer_turno;//reseteamos el turno
	for(i=0 ; i<=tab_h ; i++){//recorremos el tablero
		for(j=0 ; j<=tab_w ; j++){
			tablero[i][j] = tablero_inicial[i][j];//reseteamos el tablero
		}
	}
}
