/*dibuja la bacteria en la casilla correspondiente despues de la accion multiplicar*/
void animacion_multiplicar(int f, int c, int tipo, BITMAP* hex, int tab_pos_x, int tab_pos_y){
	/*
	esta funcion carga del disco la imagen de la bacteria que se debe mostrar y la imprime al bitmap que se ha de imprimir en la pantalla
	
	parametros
		f = fila del hexagono
		c = columna del hexagono
		tipo = tipo de bacteria a imprimir
		hex = puntero a un bitmap que se utiliza para cargar las imagenes
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
	
	*/
	int hex_pos_x, hex_pos_y;//posicion horizontal y vertical del hexagono a imprimir
	
	hex_pos_y = (c%2)*((hex->h)/2) + tab_pos_y + f*(hex->h); //posicion vertical del hexagono que se va a dibujar
	hex_pos_x = c*hex_w2 + tab_pos_x;//posicion horizontal del hexagono que se va a dibujar
	
	/*en cada caso se carga la imagen correspondiente, se oculta el mouse[ver glosario] y 
	se dibuja en el buffer el hexagono correspondiente, se vuelve a mostrar el mouse
	*/
	switch(tipo){
		case TEJIDO_SANO:
			hex = load_bitmap("imagenes/hexagono_original.bmp",NULL);
			show_mouse(NULL);
			draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
			show_mouse(tab_bmp);
			break;
		case BACTERIA_AZUL: 
			hex = load_bitmap("imagenes/bacteria_azul.bmp",NULL);
			show_mouse(NULL);
			draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
			show_mouse(tab_bmp);
			break;
		case BACTERIA_VERDE:
			hex = load_bitmap("imagenes/bacteria_verde.bmp",NULL);		
			show_mouse(NULL);
			draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
			show_mouse(tab_bmp);
			break;
	}	
}
/*imprime al buffer las imagenes respectivas en los lugares de contaminacion a partir de la posicion dada*/
void animacion_contaminar(int f, int c, char tablero[tab_h][tab_w], BITMAP* hex, int tab_pos_x, int tab_pos_y){
	/*
	esta funcion carga del disco la imagen de la bacteria que se debe mostrar y la imprime al bitmap que se ha 
	de imprimir en la pantalla
	
	recorre el vecindario de la posicion dada, actualizando los hexagonos segun los valores del tablero actual
	
	parametros
		f = fila del hexagono
		c = columna del hexagono
		tablero = tablero actual de juego
		hex = puntero a un bitmap que se utiliza para cargar las imagenes
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
	
	*/
	int hex_pos_x, hex_pos_y;//posicion horizontal y vertical del hexagono a imprimir
	int i,j;//variables para recorrer el vecindario
	for(i=f-1+c%2 ; i<=f+c%2 ; i++){//recorremos el vecindario [ver glosario para metodo]
		for(j=c-1 ; j<=c+1 ; j++){
			
			if( (0<=i && i<tab_h) && (0<=j && j<tab_w) ){//verificamos que la posicion este en el tablero
				if(i==f && j==c){
					hex_pos_y = (j%2)*((hex->h)/2) + tab_pos_y + (i+1-2*(c%2))*(hex->h); //posicion vertical del hexagono que se va a dibujar
					hex_pos_x = j*hex_w2 + tab_pos_x;//posicion horizontal del hexagono que se va a dibujar
					if((i+1-2*(c%2))>=0 && (i+1-2*(c%2))<tab_h  && j<tab_w && j>=0){
						switch(tablero[i+1-2*(c%2)][j]){
							/*en cada caso se carga la imagen correspondiente, se oculta el mouse[ver glosario] y 
							se dibuja en el buffer el hexagono correspondiente, se vuelve a mostrar el mouse
							*/
							case TEJIDO_SANO:
								hex = load_bitmap("imagenes/hexagono_original.bmp",NULL);
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
								show_mouse(tab_bmp);
								break;
							case BACTERIA_AZUL: 
								hex = load_bitmap("imagenes/bacteria_azul.bmp",NULL);
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
								show_mouse(tab_bmp);
								break;
							case BACTERIA_VERDE:
								hex = load_bitmap("imagenes/bacteria_verde.bmp",NULL);		
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
								show_mouse(tab_bmp);
								break;
							default:
								break;
						}
					}
				}else{
					hex_pos_y = (j%2)*((hex->h)/2) + tab_pos_y + i*(hex->h); //posicion vertical del hexagono que se va a dibujar
					hex_pos_x = j*hex_w2 + tab_pos_x; //posicion horizontal del hexagono que se va a dibujar
					if(i>=0 && i<tab_h  && j<tab_w && j>=0){
						switch( tablero[i][j]){
							/*en cada caso se carga la imagen correspondiente, se oculta el mouse[ver glosario] y 
							se dibuja en el buffer el hexagono correspondiente, se vuelve a mostrar el mouse
							*/
							case TEJIDO_SANO:
								hex = load_bitmap("imagenes/hexagono_original.bmp",NULL);
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
								show_mouse(tab_bmp);
								break;
							case BACTERIA_AZUL: 
								hex = load_bitmap("imagenes/bacteria_azul.bmp",NULL);
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y); 
								show_mouse(tab_bmp);
								break;
							case BACTERIA_VERDE:
								hex = load_bitmap("imagenes/bacteria_verde.bmp",NULL);		
								show_mouse(NULL);
								draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
								show_mouse(tab_bmp);
								break;
						}
					}
				}
			}
		}
	}
}
