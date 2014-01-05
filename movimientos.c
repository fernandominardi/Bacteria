
extern volatile long speed_counter;
/*se encarga de contaminar una posicion en el tablero principal y el buffer*/
void contaminar(char tablero[tab_h][tab_w],int f,int c, BITMAP* hexagono, int tab_pos_x, int tab_pos_y){
	/*
	parámetros
		tablero = tablero principal del jeugo
		f = fila
		c = columna
		hexagono = imagen del hexagono
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero	
	*/
	SAMPLE *sonido;//sonido a cargarse 
	long time_counter;//variable de tiempo para controlar los delay de animacion y sonido
	int i,j;//variables apra recorrer tablero
	
	time_counter = speed_counter;
	//se randomiza el sonido de la bacteria al multiplicarse
	switch(rand()%4){
		case 0:
			sonido = load_sample("sonidos/bacteria1.wav");
			break;
		case 1:
			sonido= load_sample("sonidos/bacteria2.wav");
			break;
		case 2:
			sonido = load_sample("sonidos/bacteria3.wav");
			break;
		case 3:
			sonido = load_sample("sonidos/bacteria4.wav");
			break;
	}
	//se ejecuta el sonido del movimiento realizado
	play_sample(sonido,255,128,1000,0);
	//delay para empezar la animacion
	while( !(speed_counter - time_counter > 20) || (speed_counter < time_counter ) ){
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	
	for(i=f-1+c%2 ; i<=f+c%2 ; i++){//recorremos los vecinos [ver glosario]
		for(j=c-1 ; j<=c+1 ; j++){
			
			if(i==f && j==c){
				
				if(i+1-2*(c%2)>=0 && i+1-2*(c%2)<tab_h  && j<tab_w && j>=0 && tablero[i+1-2*(c%2)][j]==(TURNO^1) ){//es bacteria enemiga
					tablero[i+1-2*(c%2)][j]=TURNO;//se contamina la posicion vecina
					//animacion de la contaminacion de esta posicion
					animacion_contaminar(f,c,tablero,hexagono, tab_pos_x, tab_pos_y);
					//capturamos el tiempo global
					time_counter = speed_counter;
					//randomizamos el sonido de la contaminacion
					switch(rand()%5){
						case 0:
							sonido = load_sample("sonidos/contaminacion1.wav");
							break;
						case 1:
							sonido= load_sample("sonidos/contaminacion2.wav");
							break;
						case 2:
							sonido = load_sample("sonidos/contaminacion3.wav");
							break;
						case 3:
							sonido = load_sample("sonidos/contaminacion4.wav");
							break;
						case 4:
							sonido = load_sample("sonidos/contaminacion5.wav");
							break;
					}
					//reproducimos sonido de la contaminacion
					play_sample(sonido,255,128,1000,0);
					//delay para la siguiente contaminacion 
					while( !(speed_counter - time_counter > 10) || (speed_counter < time_counter ) ){
						blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
					}
				}
				
				
			}else{
				
				if(i>=0 && i<tab_h  && j<tab_w && j>=0 &&  tablero[i][j]==(TURNO^1) ){//es bacteria enemiga
					tablero[i][j]=TURNO;//se contamina la posicion vecina
					//animacion de la contaminacion de esta posicion
					animacion_contaminar(f,c,tablero,hexagono, tab_pos_x, tab_pos_y);
					//capturamos el tiempo global
					time_counter = speed_counter;
					//randomizamos el sonido de la contaminacion
					switch(rand()%5){
						case 0:
							sonido = load_sample("sonidos/contaminacion1.wav");
							break;
						case 1:
							sonido= load_sample("sonidos/contaminacion2.wav");
							break;
						case 2:
							sonido = load_sample("sonidos/contaminacion3.wav");
							break;
						case 3:
							sonido = load_sample("sonidos/contaminacion4.wav");
							break;
						case 4:
							sonido = load_sample("sonidos/contaminacion5.wav");
							break;
					}
					//reproducimos sonido de la contaminacion
					play_sample(sonido,255,128,1000,0);
					//delay para la siguiente contaminacion
					while( !(speed_counter - time_counter > 10) || (speed_counter < time_counter ) ){
						blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
					}
				}
				
			}
			
		}   
	}
	
	time_counter = speed_counter;
	//delay para animacion y sonido
	while( !(speed_counter - time_counter > 10) || (speed_counter < time_counter ) ){
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
	}
	//liberamos memoria
	destroy_sample(sonido);
	
}
/*se encarga de multiplicar una posicion en el tablero principal y el buffer*/
int multiplicar(char tablero[tab_h][tab_w],int f, int c, BITMAP* hexagono, int tab_pos_x, int tab_pos_y){
	/*
	se recorre el vecindario, si es una bacteria aliada, procedemos a la multiplicacion
	
	parámetros
		tablero = tablero principal del jeugo
		f = fila
		c = columna
		hexagono = imagen del hexagono
		int tab_pos_x = posicion horizontal del tablero
		int tab_pos_y = posicion vertical del tablero	
	*/
	int i,j;//variables para recorrer el vecindario
	for(i=f-1+c%2 ; i<=f+c%2 ; i++)//recorremos el vecindario [ver glosario]
		for(j=c-1 ; j<=c+1 ; j++)
			if(i==f && j==c){
				
				if(i+1-2*(c%2)>=0 && i+1-2*(c%2)<tab_h  && j<tab_w && j>=0 && tablero[i+1-2*(c%2)][j] == TURNO){//es bacteria aliada
					//multiplicamos
					tablero[f][c] = TURNO;
					//se reprodude la animacion de multiplicar
					animacion_multiplicar(f,c,tablero[f][c],hexagono, tab_pos_x, tab_pos_y);
					//se contamina alrededor de la coordenada multiplicada
					contaminar(tablero,f,c,hexagono, tab_pos_x, tab_pos_y);
					//se cambia el turno
					cambiar_turno();
					return TRUE;
				}
			}else{
				
				if(i>=0 && i<tab_h  && j<tab_w && j>=0 &&   tablero[i][j] == TURNO){//es bacteria aliada
					//multiplicamos
					tablero[f][c] = TURNO;
					//se reprodude la animacion de multiplicar
					animacion_multiplicar(f,c,tablero[f][c],hexagono, tab_pos_x, tab_pos_y);
					//se contamina alrededor de la coordenada multiplicada
					contaminar(tablero,f,c,hexagono, tab_pos_x, tab_pos_y);
					//se cambia el turno
					cambiar_turno();
					return TRUE;
				}
			}
	return FALSE;
}
/*se encarga de propagar de la posicion origen a la destino en el tablero principal y el buffer*/
int propagar(char tablero[tab_h][tab_w],int f,int c,int tab_pos_x,int tab_pos_y,BITMAP* hexagono,BITMAP* cursor){
	
	/*
	se recorre el vecindario, si es una bacteria aliada, procedemos a la multiplicacion
	
	parámetros
		tablero = tablero principal del jeugo
		f = fila
		c = columna
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
		hexagono = imagen del hexagono
			
	*/
	
	int ban,x,y;
	//dependiendo del turno se cargan las imagenes correspondientes en el hexagono y el mouse
	if(TURNO==BACTERIA_AZUL){
		hexagono = load_bitmap("imagenes/marca_de_agua_azul.bmp",NULL);
		cursor = load_bitmap("imagenes/cursor_con_bacteria_azul.bmp",NULL);
	}else{
		hexagono = load_bitmap("imagenes/marca_de_agua_verde.bmp",NULL);
		cursor = load_bitmap("imagenes/cursor_con_bacteria_verde.bmp",NULL);
	}
	//calculamos la posicion del hexagono
	int hex_pos_y = (c%2)*((hexagono->h)/2) + tab_pos_y + f*(hexagono->h);
	int hex_pos_x = c*hex_w2 + tab_pos_x;

	show_mouse(NULL);
	//dibujamos la marca de agua en laposicion origen
	draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
	//cambiamos el aspecto del cursor
	set_mouse_sprite(cursor);
	set_mouse_sprite_focus((cursor->w)/2,(cursor->h)/2);
	show_mouse(tab_bmp);
	
	ban = TRUE;
	
	while(ban){//meintrasel boton se mantenga apretado
		//actualizamos la apantalla
		blit(tab_bmp, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
		if(!(mouse_b & 1)){
			//si se solto el mouse capturamos la posicion del mouse
			ban = FALSE;
			x = mouse_x;
			y = mouse_y;
		}
	}

	
	int fd,cd;//fila y columna destino
	
	//calculamos la posicion destino con la posicion capturada del mouse
	fd = get_pos_f(x,y,tab_pos_x,tab_pos_y);
	cd = get_pos_c(x,y,tab_pos_x,tab_pos_y);
	show_mouse(NULL);
	//reseteamos la imagen del cursor
	cursor = load_bitmap("imagenes/cursor.bmp",NULL);
	set_mouse_sprite(cursor);
	set_mouse_sprite_focus(0,0);
	//verificamos que las posiciones origen y destino cumplan es_vecino_al_vecino, y que la posicion destino sea una celda libre
	if(es_casilla_valida( tab_pos_x, tab_pos_y, x, y) && tablero[fd][cd]==TEJIDO_SANO && es_vecino_al_vecino( f, c, fd, cd) ){
		//se hace el intercambio correspondiente en la matriz
		tablero[f][c]=TEJIDO_SANO;
		tablero[fd][cd] = TURNO;
		
		//se reproduce el intercambio en el buffer
		
		//imprimimos el tejido sano
		hexagono = load_bitmap("imagenes/hexagono_original.bmp",NULL);
		draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
		
		if(TURNO==BACTERIA_AZUL)
			hexagono=load_bitmap("imagenes/bacteria_azul.bmp",NULL);
		else
			hexagono=load_bitmap("imagenes/bacteria_verde.bmp",NULL);
		//se calcula la posicion del hexagono con bacteria
		hex_pos_y = (cd%2)*((hexagono->h)/2) + tab_pos_y + fd*(hexagono->h);
		hex_pos_x = cd*hex_w2 + tab_pos_x;
		//imprimimo el hexagono con bacteria
		draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
		show_mouse(tab_bmp);
		//se contamina la posicion destino
		contaminar(tablero, fd, cd, hexagono, tab_pos_x, tab_pos_y);
		//se cambia el turno
		cambiar_turno();
		return TRUE;
	}else{//si no es una propagacion valida
		//se imprime en la posicion destino de nuevo las bacterias originales
		if(TURNO==BACTERIA_AZUL)
			hexagono=load_bitmap("imagenes/bacteria_azul.bmp",NULL);
		else
			hexagono=load_bitmap("imagenes/bacteria_verde.bmp",NULL);
		draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
		show_mouse(tab_bmp);
		return FALSE;
	}
}
/*se encarga de propagar de la posicion origen a la destino en el tablero principal y el buffer en una jugada realizada por la PC*/
int propagar_PC(char tablero[tab_h][tab_w],int f,int c,int fd,int cd,int tab_pos_x,int tab_pos_y,BITMAP* hexagono){
	/*
	
	parámetros
		tablero = tablero principal del jeugo
		f = fila origen
		c = columna origen
		fd = fila destino
		cd = columna destino
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
		hexagono = imagen del hexagono
			
	*/
	
	//calculamos las posiciones de impresion del hexagono
	int hex_pos_y = (c%2)*((hexagono->h)/2) + tab_pos_y + f*(hexagono->h);
	int hex_pos_x = c*hex_w2 + tab_pos_x;
	show_mouse(NULL);
	
	if( tablero[fd][cd]==TEJIDO_SANO && es_vecino_al_vecino( f, c, fd, cd)  ){//si la propagacion es valida
		//se hace el intercambio correspondiente en la matriz
		tablero[f][c]=TEJIDO_SANO;
		tablero[fd][cd] = TURNO;
		
		//se reproduce el intercambio en el buffer
		
		//imprimimos el tejido sano
		hexagono = load_bitmap("imagenes/hexagono_original.bmp",NULL);
		draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
		
		if(TURNO==BACTERIA_AZUL)
			hexagono=load_bitmap("imagenes/bacteria_azul.bmp",NULL);
		else
			hexagono=load_bitmap("imagenes/bacteria_verde.bmp",NULL);
		//se calcula la posicion del hexagono con bacteria
		hex_pos_y = (cd%2)*((hexagono->h)/2) + tab_pos_y + fd*(hexagono->h);
		hex_pos_x = cd*hex_w2 + tab_pos_x;
		//imprimimo el hexagono con bacteria
		draw_sprite(tab_bmp, hexagono, hex_pos_x, hex_pos_y);
		//se contamina la posicion destino
		contaminar(tablero, fd, cd, hexagono, tab_pos_x, tab_pos_y);
		//se cambia el turno
		cambiar_turno();
		
		show_mouse(tab_bmp);
		return TRUE;
	}else{//propagacion no es valida
		printf("entro mal");
		show_mouse(tab_bmp);
		return FALSE;
	}
}
