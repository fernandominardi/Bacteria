/*comprueba el acceso exitoso a cada archivo que se usa durante el proceso del programa*/
int seguridad(){
	/*
		se intenta abrir la lista completa de los archivos que forman parte de los recursos necesarios del programa
		en caso de que falte alguno de ellos, se devuelve false
		
	*/
	if(!fopen("font/mv_boli.dat","r")){return FALSE;}
	if(!fopen("font/mv_boli_12.dat","r")){return FALSE;}
	if(!fopen("imagenes/azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/azul_wins.bmp","r")){return FALSE;}
	if(!fopen("imagenes/background.bmp","r")){return FALSE;}
	if(!fopen("imagenes/bacteria_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/bacteria_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/borde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/btn_skip.bmp","r")){return FALSE;}
	if(!fopen("imagenes/btn_skip_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/cuadro_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/cuadro_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/cursor.bmp","r")){return FALSE;}
	if(!fopen("imagenes/cursor_con_bacteria_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/cursor_con_bacteria_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/draw.bmp","r")){return FALSE;}
	if(!fopen("imagenes/editor_inst.bmp","r")){return FALSE;}
	if(!fopen("imagenes/game_inst.bmp","r")){return FALSE;}
	if(!fopen("imagenes/hexagono_original.bmp","r")){return FALSE;}
	if(!fopen("imagenes/hex_shape.bmp","r")){return FALSE;}
	if(!fopen("imagenes/marca_de_agua_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/marca_de_agua_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu-instrucciones.bmp","r")){return FALSE;}
	if(!fopen("imagenes/portada.bmp","r")){return FALSE;}
	if(!fopen("imagenes/posible_multiplicacion.bmp","r")){return FALSE;}
	if(!fopen("imagenes/posible_propagacion.bmp","r")){return FALSE;}
	if(!fopen("imagenes/verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/verde_wins.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_azul_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_begin.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_begin_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_begin_off.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_borrar.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_borrar_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_hex_shape.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_inst.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_punteado.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_sano.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_sano_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/editor_verde_brillando.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_cheat_off.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_cheat_on.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_exit.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_mainmenu.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_off.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_on.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_reset.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/ingame_shape.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_exit.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_menu.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_pcvpc.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_pvp.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_pvpc.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/main_shape.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_board_editor.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_input_pl_0.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_input_pl_1.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_menu.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_player0.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_player1.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_shape.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/name_standard_board.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pcvpc_begin_game.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pcvpc_name_ambos.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pcvpc_name_azul.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pcvpc_name_menu.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pcvpc_name_verde.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/pvp_input_pl_1.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_continue.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_input1.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_input2.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_menu.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_select1.bmp","r")){return FALSE;}
	if(!fopen("imagenes/menu/xml_select2.bmp","r")){return FALSE;}
	if(!fopen("sonidos/bacteria1.wav","r")){return FALSE;}
	if(!fopen("sonidos/bacteria2.wav","r")){return FALSE;}
	if(!fopen("sonidos/bacteria3.wav","r")){return FALSE;}
	if(!fopen("sonidos/bacteria4.wav","r")){return FALSE;}
	if(!fopen("sonidos/boton.wav","r")){return FALSE;}
	if(!fopen("sonidos/btn_clicked.wav","r")){return FALSE;}
	if(!fopen("sonidos/contaminacion1.wav","r")){return FALSE;}
	if(!fopen("sonidos/contaminacion2.wav","r")){return FALSE;}
	if(!fopen("sonidos/contaminacion3.wav","r")){return FALSE;}
	if(!fopen("sonidos/contaminacion4.wav","r")){return FALSE;}
	if(!fopen("sonidos/contaminacion5.wav","r")){return FALSE;}
	if(!fopen("sonidos/draw.wav","r")){return FALSE;}
	if(!fopen("sonidos/seleccionado.wav","r")){return FALSE;}
	if(!fopen("sonidos/winner.wav","r")){return FALSE;}
	
	return TRUE;
}
/*cuenta las casillas existentes en el tablero*/
int contar_casillas(char tablero[tab_h][tab_w]){
	/*
	parámetro
		tablero = tablero actual del juego
	*/
	int i,j,cont=0;//variables para recorrer el tablero, contador
	for(i=0;i<tab_h;i++){//se recorre el tablero
		for(j=0;j<tab_w;j++){
			if( tablero[i][j]!=SIN_TEJIDO )//si la casilla no esta deshabilitada [ver glosario] se cuenta
				cont++;
		}
	}
	return cont;
}
/*crea el tablero standad de juego*/
void standard_board_creator(char tablero_inicial[12][12]){
	/*
	el tablero standard es un tablero de 8*8 con las bacterias en las esquinas superior izquierda e inferior derecha
	
	parámetro 
		tablero_inicial = tablero al cual se va a cargar la disposicion standard
	*/
	int i,j;//variables para recorrer el tablero
	tab_h = tab_w = 8;//se asigna las magnitudes del tablero standar
	for(i=0;i<tab_h;i++){//recorremos el tablero
		for(j=0;j<tab_w;j++){
			if( i==0 && j==0)
				tablero_inicial[i][j] = BACTERIA_AZUL;//asignamos bacteria azul inicial
			else
				if( i==tab_h-1 && j==tab_w-1)
					tablero_inicial[i][j] = BACTERIA_VERDE;//asignamos bacteria verde inicial
				else
					tablero_inicial[i][j] = TEJIDO_SANO;
		}
	}
}
/*genera el tablero en el buffer, y lo muestra en pantalla*/
int generar_tablero(char tablero[tab_h][tab_w],BITMAP* hex, int tab_pos_x, int tab_pos_y, int tab_bmp_w, int tab_bmp_h){
	
	//cargamos el fondo en el buffer
	tab_bmp = load_bitmap("imagenes/background.bmp",NULL);
	//cargamos las instrucciones que se muestran en la esquina superior derecha
	BITMAP* menu_inst = load_bitmap("imagenes/menu-instrucciones.bmp",NULL);
	
	int i,j;//variables para recorrer el tablero
	int hex_pos_x, hex_pos_y;//posiciones horizontal y vertical de los hexagonos a imprimir
	
	//creamos un bitmap auxiliar para rescatar las posiciones del tablero
	aux_tab_bmp = create_bitmap(tab_bmp_w,tab_bmp_h);
	//limpiamos el bitmap auxiliar
	clear_to_color(aux_tab_bmp,COLOR_NULO);
	//cargamos la forma del hexagono
	BITMAP* hex_shape = load_bitmap("imagenes/hex_shape.bmp",NULL);
	//cargamos los bordes de las casillas
	BITMAP* border = load_bitmap("imagenes/borde.bmp",NULL);

	//recorremos el tablero para imprimir los bordes
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			if(tablero[i][j]!=SIN_TEJIDO){
				hex_pos_y = (j%2)*((hex->h)/2) + tab_pos_y + i*(hex->h); 
				hex_pos_x = j*hex_w2 + tab_pos_x;
				draw_sprite(tab_bmp, border, hex_pos_x-4, hex_pos_y-7);
			}
		}
	}
	//encima de los bordes se imprimen los hexagonos correspondientes de la matriz
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			if(tablero[i][j]!=SIN_TEJIDO){
				hex_pos_y = (j%2)*((hex->h)/2) + tab_pos_y + i*(hex->h); //posicion vertical del hexagono que se va a dibujar
				hex_pos_x = j*hex_w2 + tab_pos_x; //posicion horizontal del hexagono que se va a dibujar 
				/*en cada caso se carga el hexagono correspondiente al de la posicion en la matriz
				y se imprime en su posicion corresppondiente en el buffer*/
				switch(tablero[i][j]){
					case TEJIDO_SANO:
						hex = load_bitmap("imagenes/hexagono_original.bmp",NULL);
						draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
						break;
					case BACTERIA_AZUL:
						hex = load_bitmap("imagenes/bacteria_azul.bmp",NULL);
						draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
						break;
					case BACTERIA_VERDE:
						hex = load_bitmap("imagenes/bacteria_verde.bmp",NULL);
						draw_sprite(tab_bmp, hex, hex_pos_x, hex_pos_y);
						break;
				}
				//se asigna un color de identifiacion de casilla [ver glosario] a cada casilla impresa
				floodfill(hex_shape,(hex->w)/2,(hex->h)/2, j + i*tab_w);
				//se prepara la grilla de colores del tablero
				draw_sprite(aux_tab_bmp, hex_shape,(hex_pos_x - tab_pos_x),(hex_pos_y - tab_pos_y));
			}
		}
	}
	//imprimimos el mensaje de isntrucciones
	draw_sprite(tab_bmp, menu_inst, 647, 0);
	
	return TRUE;

}
/*cuenta las bacterias de cada tipo en el tablero dado*/
void contar_bacterias(char tablero[tab_w][tab_h], int *cant_azul, int *cant_verde){
	/*
	parámetros
		tablero = tablero cuyas bacterias se han de contar
		cant_azul = puntero a un int a modificar, con la cantidad de bacterias azules
		cant_verde = puntero a un int a modificar, con la cantidad de bacterias verdes
	*/
	int i,j;//variables para recorrer el tablero
	//se ceran los contadores
	*cant_azul = 0;
	*cant_verde = 0;
	for(i=0 ; i<tab_h ; i++){//se recorre el tablero
		for(j=0 ; j<tab_w ; j++){
			//se cuenta cada ceaso respectivamente
			if(tablero[i][j]==BACTERIA_AZUL){
				(*cant_azul)++;
			}
			if(tablero[i][j]==BACTERIA_VERDE){
				(*cant_verde)++;
			}
		}
	}
	
}

void cambiar_turno(){
	TURNO^=1;
}
/*funcion que verifica si una posicion es vecina o no a otra*/
int es_vecino(int fo,int co,int fd,int cd){
    /*
		esta funcion recorre el vecindario de la posicion fo,co (posicion origen) x la compara con la posicion fd,cd (posicion destino)
		si la posicion destino se encuentra en una posicion del vecindario de la posicion origen retorna TRUE, en caso contrario retorna FALSE
	
	parámetros
		fo = fila origen
		co = columna origen
		fd = fila dstino
		cd = columna destino
	*/

	int i,j;
	for(i=fo-1+co%2 ; i<=fo+co%2 ; i++)//se recorren las filas, en caso de que fo sea par, desde la fila anterior a la fila origen, en caso de fo impar, desde la fila origen, se recorren dos filas
		for(j=co-1 ; j<=co+1 ; j++)//en cualquier caso se recorren tres columnas, la origen x sus costados
				
				if(i==fo && j==co){//si la posicion actual coincide con la posicion origen
					if( (0<=i+1-2*(co%2) && i+1-2*(co%2)<tab_h) && (0<=j && j<tab_w) && i+1-2*(co%2)==fd && j==cd )//se revisan los casos PAR e IMPAR de vecinos
						return TRUE;
				}else{
				
					if( (0<=i && i<tab_h) && (0<=j && j<tab_w) && i==fd && j==cd )//si la posicion destino es alguna posicion vecina que no sea el caso anterior se retorna TRUE
						return TRUE;
				}
			
	return FALSE;//si no se retorno TRUE, es porque simplemente la posicion destino no es una posicion vecina a la origen
}

/*funcion que verifica si una posicion es vecina o no a otra, recibe la posicion origen x la posicion destino*/
int es_vecino_al_vecino(int fo,int co,int fd,int cd){
	/*
		esta funcion recorre la matriz de la misma manera que la funcion es_vecino
	
	parámetros
		fo = fila origen
		co = columna origen
		fd = fila dstino
		cd = columna destino
	*/

	int i,j;
	for(i=fo-1+co%2 ; i<=fo+co%2 ; i++)
		for(j=co-1 ; j<=co+1 ; j++)
			
			if(i==fo && j==co){
				if( (0<=i+1-2*(co%2) && i+1-2*(co%2)<tab_h) && (0<=j && j<tab_w) && es_vecino(i+1-2*(co%2),j,fd,cd)) //se revisan los casos PAR e IMPAR de vecinos
					return TRUE;
			}else{
				if((0<=i && i<tab_h) && (0<=j && j<tab_w) && es_vecino(i,j,fd,cd))//se llama a es_vecino en una posicion vecina a la posicion origen para ver si es vecino al vecino
					return TRUE;
			}
			
	return FALSE;//si no se retorno TRUE, es porque simplemente la posicion destino no es una posicion vecina a la origen
}
/*verfica que el mouse fue clickeado en una casilla*/
int es_casilla_valida( int tab_pos_x, int tab_pos_y, int x, int y){
	/*
	verrifica el color de la posicion del mouse cuando fue clickeado en la grilla de colores
	si el color corresponde a un valor distinto de COLOR_NULO o - (valor que devuelve el api si estamos fuera del bitmap grilla)
	se devuelve TRUE
	
	parametros
		tab_pos_x = posicion horizontal del tablero
		tab_pos_y = posicion vertical del tablero
		x = posicion horizontal del mouse
		y = posicion vertical del mouse
	
	*/
	if(getpixel(aux_tab_bmp,x - tab_pos_x,y - tab_pos_y)==COLOR_NULO || getpixel(aux_tab_bmp,x - tab_pos_x,y - tab_pos_y) == -1 )
        return FALSE;

	return TRUE;
}
/*devuelve el valor de la fila segun la posicion clickeada*/
int get_pos_f(int x,int y,int tab_pos_x, int tab_pos_y){
	/*usa la formula inversa de creacion de color de la grilla para el tablero, para devolver la fila*/
	return getpixel(aux_tab_bmp,x - tab_pos_x,y - tab_pos_y)/tab_w;
}
/*devuelve el valor de la columna segun la posicion clickeada*/
int get_pos_c(int x,int y,int tab_pos_x, int tab_pos_y){
	/*usa la formula inversa de creacion de color de la grilla para el tablero, para devolver la columna*/
	return getpixel(aux_tab_bmp,x - tab_pos_x,y - tab_pos_y)%tab_w;
}

