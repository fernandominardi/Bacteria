/*Funciones que tienen que ver con la inteligencia artificial

Breve descripción de la AI:

El método utilizado es el de un árbol de desiciones de profundidad 3 con la siguiente jerarquía:

abuelo = estado actual
hijos = estados despues de la jugada de la AI
nietos = respuesta del oponente

*/

/*prepara una matriz con las multiplicaciones posibles para el tablero, correspondientes a la bacteria del turno*/
void preparar_mult(char tablero[tab_h][tab_w],int mult_posibles[tab_h][tab_w],int TURNO_aux){
	
	/*
		esta funcion recorre el tablero completo, en caso de encontrar alguna casilla con tejido sano, recorre las casillas adyacentes a la misma
		y si encuentra una bacteria aliada (del mismo color que el turno), genera un codigo de jugada [ver glosario] y asigna el codigo de la jugada 
		a la matriz
		
		
	parámetros 
		tablero = tablero con el estado a analizar
		mult_posibles = matriz donde se guardan las multiplicaciones posibles
		TURNO_aux = turno a analizar
	*/
	int i,j,f,c;//variables para recorrer el tablero y las adyacencias
	for(i=0 ; i<tab_h ; i++){//recorrer tablero
		for(j=0 ; j<tab_w ; j++){
			
			if(tablero[i][j]==TEJIDO_SANO){//si la posicion es tejido sano se recorren las adyacencias en busca de una bacteria aliada
				
				for(f=i-1+j%2 ; f<=i+j%2 ; f++){//recorrer adyacencias [ver glosario para el metodo explicado]
					for(c=j-1 ; c<=j+1 ; c++){
						
						if(f==i && c==j){
							if((0<=(f+1-2*(j%2)) && (f+1-2*(j%2))<tab_h) && (0<=c && c<tab_w) && TURNO_aux==tablero[f+1-2*(j%2)][c]){ // es bacteria aliada y esta en el tablero
								mult_posibles[i][j] = crear_int_jugada(MULTIPLICAR,0,0,i,j);//guardar codigo de la jugada
								//forzar salida de la posicion actual
								f=i+j%2+1;
								c=j+2;
							}
						}else{
							if((0<=f && f<tab_h) && (0<=c && c<tab_w) && TURNO_aux==tablero[f][c] ){// es bacteria aliada y esta en el tablero
								mult_posibles[i][j] = crear_int_jugada(MULTIPLICAR,0,0,i,j);//guardar codigo de la jugada
								//forzar salida de la posicion actual
								f=i+j%2+1;
								c=j+2;
							}
						}
						
					}
				}
				
			}
			
		}
	}
}

/*verifica que en el tablero dado, la propagacion entre el apr de coordenadas dado sea posible*/
int crear_jugada_prop(char tablero[tab_h][tab_w],int f1, int c1, int f2, int c2){
	/*no se verifican las coordenadas con es_vecino_al_vecino, ya que no hay posibilidad de que esta funcion reciba coordenadas que no cumplan esa funcion
	
	parámetros 
		tablero = tablero con el estado a analizar
		f1 = fila inicial
		c1 = columna inicial
		f2 = fila final
		c2 = columna final
	*/
	if(0<=f2 && f2<tab_h && 0<=c2 && c2<tab_w && tablero[f2][c2]==TEJIDO_SANO){ // si la posicion destino esta en el tablero y es tejido sano
		
		return crear_int_jugada(PROPAGAR,f1,c1,f2,c2);//se crea el codigo de la jugada [ver glosario]
	}
	//en caso de que no se pueda propagar a la posicion destino, se retorna FALSE;
	return FALSE;
}

/*preapara un vector de propagaciones para cada la casilla dada*/
void preparar_prop(char tablero[tab_h][tab_w],int posib_jugadas[18],int f, int c){
	/*el vector de propagaciones tiene el codigo de jugada [ver glosario para mas explicacion sobre los indices del vector]
		en caso de que la propagacion sea posible, en caso contrario, NULL
		
	parámetros 
		tablero = tablero con el estado a analizar
		posib_jugadas = vector de propagaciones [ver glosario]
		f = fila
		c = columna
	*/
	if(!(c%2)){//si la columna es par se recorre las casillas adyacentes y las adyacentes a las adyacentes con las coordenadas correspondientes
	
		posib_jugadas[0]  = crear_jugada_prop(tablero,f,c,f-1,c);
		posib_jugadas[1]  = crear_jugada_prop(tablero,f,c,f-1,c+1);
		posib_jugadas[2]  = crear_jugada_prop(tablero,f,c,f,c+1);
		posib_jugadas[3]  = crear_jugada_prop(tablero,f,c,f+1,c);
		posib_jugadas[4]  = crear_jugada_prop(tablero,f,c,f,c-1);
		posib_jugadas[5]  = crear_jugada_prop(tablero,f,c,f-1,c-1);
		
		posib_jugadas[6]  = crear_jugada_prop(tablero,f,c,f-2,c);
		posib_jugadas[7]  = crear_jugada_prop(tablero,f,c,f-2,c+1);
		posib_jugadas[8]  = crear_jugada_prop(tablero,f,c,f-1,c+2);
		posib_jugadas[9]  = crear_jugada_prop(tablero,f,c,f,c+2);
		posib_jugadas[10] = crear_jugada_prop(tablero,f,c,f+1,c+2);
		posib_jugadas[11] = crear_jugada_prop(tablero,f,c,f+1,c+1);
		posib_jugadas[12] = crear_jugada_prop(tablero,f,c,f+2,c);
		posib_jugadas[13] = crear_jugada_prop(tablero,f,c,f+1,c-1);
		posib_jugadas[14] = crear_jugada_prop(tablero,f,c,f+1,c-2);
		posib_jugadas[15] = crear_jugada_prop(tablero,f,c,f,c-2);
		posib_jugadas[16] = crear_jugada_prop(tablero,f,c,f-1,c-2);
		posib_jugadas[17] = crear_jugada_prop(tablero,f,c,f-2,c-1);	
	}else{//si la columna es impar se recorre las casillas adyacentes y las adyacentes a las adyacentes  con las coordenadas correspondientes
	
		posib_jugadas[0]  = crear_jugada_prop(tablero,f,c,f-1,c);
		posib_jugadas[1]  = crear_jugada_prop(tablero,f,c,f,c+1);
		posib_jugadas[2]  = crear_jugada_prop(tablero,f,c,f+1,c+1);
		posib_jugadas[3]  = crear_jugada_prop(tablero,f,c,f+1,c);
		posib_jugadas[4]  = crear_jugada_prop(tablero,f,c,f+1,c-1);
		posib_jugadas[5]  = crear_jugada_prop(tablero,f,c,f,c-1);
		
		posib_jugadas[6]  = crear_jugada_prop(tablero,f,c,f-2,c);
		posib_jugadas[7]  = crear_jugada_prop(tablero,f,c,f-1,c+1);
		posib_jugadas[8]  = crear_jugada_prop(tablero,f,c,f-1,c+2);
		posib_jugadas[9]  = crear_jugada_prop(tablero,f,c,f,c+2);
		posib_jugadas[10] = crear_jugada_prop(tablero,f,c,f+1,c+2);
		posib_jugadas[11] = crear_jugada_prop(tablero,f,c,f+2,c+1);
		posib_jugadas[12] = crear_jugada_prop(tablero,f,c,f+2,c);
		posib_jugadas[13] = crear_jugada_prop(tablero,f,c,f+2,c-1);
		posib_jugadas[14] = crear_jugada_prop(tablero,f,c,f+1,c-2);
		posib_jugadas[15] = crear_jugada_prop(tablero,f,c,f,c-2);
		posib_jugadas[16] = crear_jugada_prop(tablero,f,c,f-1,c-2);
		posib_jugadas[17] = crear_jugada_prop(tablero,f,c,f-1,c-1);
	}
}
/*se encarga de contar cuantas proagaciones tiene la bacteria del turno*/
int cant_propagaciones(char tablero[tab_h][tab_w],int TURNO_aux){

	/*esta funcion devuelve la cantidad total de propagaciones que puede realizar el jugador del turno a analizar, para eso llena vectores auxiliares
	con los codigos de jugada, se cuentan todos los elementos no nulos de dicho vector (que por lo tanto son una propagacion posible) 
	parámetros 
		tablero = tablero con el estado a analizar
		TURNO_aux = turno a analizar	
	*/
	int prop_posibles[18];//vector de propagaciones [ver glosario]
	int i,j,k;//variables para recorrer
	int cantidad=0;//variable a retornar con la cantidad total de propagaciones posibles
	
	/*se recorre el tablero, en caso de encontrar una bacteria aliada, se utiliza la funcion preparar_prop para llenar el vector de propagaciones, 
	luego se cuentan todos los elementos no NULL de dicho vector*/
	
	for(i=0;i<tab_h;i++){//recorrer tablero
		for(j=0;j<tab_w;j++){
			if(tablero[i][j]==TURNO_aux){//es bacteria aliada
				preparar_prop(tablero,prop_posibles,i,j);//llenar vector de propagaciones
				for(k=0;k<18;k++){//recorrer vector
					if(prop_posibles[k]){//si existe propagacion posible
						cantidad++;//contar propagaciones
					}
				}
			}
		}
	}
	return cantidad;//se retorna la acntidad total de propagaciones en el tablero analizado
}
/*se encarga de cargar el vector de todas las propagaciones existentes en el tablero actual para la bacteria del turno*/
void cargar_propagaciones(char tablero[tab_h][tab_w],int prop_posibles[], int TURNO_aux){
	/*
	una vez que se conoce la cantidad total de propagaciones, se puede proceder a cargar esos codigos de jugadas a un vector general, que no contiene elementos NULL
	y que servirá luego para aplicar la jugada y generar el arbol [ver glosario]
	
	parámetros 
		tablero = tablero con el estado a analizar
		prop_posibles = vector general de propagaciones [ver glosario]
		TURNO_aux = turno a analizar
		
	*/
	int i,j,k,l=0;//variables para recoorer el tablero y los vectores
	int preparar_prop_v[18]={0};//vector de propagaciones [ver glosario]
	
	/*
	esta funcion se comporta de manera similar a cant_propagaciones, recorre el tablero por completo, y cuando encuentra una casilla
	del turno a analizar, carga el vector de propagaciones y luego lo recorre, copiando todos los codigos de jugada de propagacion
	del tablero analizado
	*/
	
	for(i=0;i<tab_h;i++){//recorrer tablero
		for(j=0;j<tab_h;j++){
			if(tablero[i][j]==TURNO_aux){//es bacteria aliada
				preparar_prop(tablero,preparar_prop_v,i,j);//llenar vector de propagaciones
				for(k=0;k<18;k++){//recorrer vector
					if(preparar_prop_v[k]){//si existe propagacion posible
						prop_posibles[l]=preparar_prop_v[k];//copiar codigo de jugada
						l++;
					}
				}
			}
		}
	}
}
/*aplica una contaminacion desde la posicion dada al tablero de analisis actual, contaminando a favor del turno dado*/
void contaminar_ai(char tablero[tab_h][tab_w],int f,int c,int TURNO_aux){
	/*
	recorre las adyacencias de la posicion dada, en caso de encontrar una bacteria enemiga al turno dado, la convierte
	
	parámetros 
		tablero = tablero con el estado a analizar
		f = fila
		c = columna
		TURNO_aux = turno a analizar
	*/
	int i,j;//variables para recorrer las adyacencias
	for(i=f-1+c%2 ; i<=f+c%2 ; i++){//recorrer adyacencias[ver glosario para método explicado]
		for(j=c-1 ; j<=c+1 ; j++){
			if(i==f && j==c){
				if(i+1-2*(c%2)>=0 && i+1-2*(c%2)<tab_h  && j<tab_w && j>=0 && tablero[i+1-2*(c%2)][j]==(TURNO_aux^1) ){//si la posicion destino es la posicion vecina sobre una posicion origen par, o bajo una posicion origen impar, y es enemiga
					tablero[i+1-2*(c%2)][j]=TURNO_aux;//se contamina la posicion vecina
				}
			}else{
				if(i>=0 && i<tab_h  && j<tab_w && j>=0 &&  tablero[i][j]==(TURNO_aux^1) ){//si la posicion vecina es una bacteria enemiga, y no es el caso anterior
					tablero[i][j]=TURNO_aux;//se contamina la posicion vecina
				}
			}
		}   
	}
	
}
/*aplica una multiplicacion a la posicion dada en el tablero de analisis actual, a favor del turno dado*/
int multiplicar_ai(char tablero[tab_h][tab_w],int f, int c,int TURNO_aux){
	/*
	recorre las adyacencias de la posicion dada, en caso de encontrar una bacteria aliada multiplica la posicion dada
	
	parámetros 
		tablero = tablero con el estado a analizar
		f = fila
		c = columna
		TURNO_aux = turno a analizar
	*/
	int i,j;//variables apra recorrer adyacencias
	if(tablero[f][c]==TEJIDO_SANO){//si la posicion dada es una casilla libre
		for(i=f-1+c%2 ; i<=f+c%2 ; i++){//recorrer adyacencias[ver glosario para método explicado]
			for(j=c-1 ; j<=c+1 ; j++){
				if(i==f && j==c){
					
					if(i+1-2*(c%2)>=0 && i+1-2*(c%2)<tab_h  && j<tab_w && j>=0 && tablero[i+1-2*(c%2)][j] == TURNO_aux){//si una de las adyacencias es una bacterai aliada
						tablero[f][c] = TURNO_aux;//multiplicacion a favor del turno a analizar
						contaminar_ai(tablero,f,c,TURNO_aux);//contaminacion alrededor de la posicion dada
						return TRUE;
					}
				}else{
					
					if(i>=0 && i<tab_h  && j<tab_w && j>=0 &&   tablero[i][j] == TURNO_aux){//si una de las adyacencias es una bacterai aliada
						tablero[f][c] = TURNO_aux;//multiplicacion a favor del turno a analizar
						contaminar_ai(tablero,f,c,TURNO_aux);//contaminacion alrededor de la posicion dada
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}
/*aplica una propagacion entre las coordenadas dadas en el tablero de analisis actual, a favor del turno dado*/
int propagar_ai(char tablero[tab_h][tab_w],int f1, int c1,int f2,int c2,int TURNO_aux){
	/*
	verifica que la propagacion sea posible en el tablero a analizar, en caso de que lo sea, realiza el intercambio propio y luego contamina
	
	parámetros 
		tablero = tablero con el estado a analizar
		f1 = fila inicial
		c1 = columna inicial
		f2 = fila final
		c2 = columna final
		TURNO_aux = turno a analizar
	*/
	if(tablero[f2][c2]==TEJIDO_SANO && es_vecino_al_vecino(f1,c1,f2,c2)){//la posicion destino esta libre y es una vecino al vecino de la posicion origen
		tablero[f2][c2]=tablero[f1][c1];//se copia el valor del origen al destino
		tablero[f1][c1]=TEJIDO_SANO;//se libera la casilla origen
		contaminar_ai(tablero,f2,c2,TURNO_aux);//se contamina alrededor de la posicion destino
		return TRUE;
	}
	return FALSE;
}
/*se encarga de aplicar la jugada dada al tablero a analizar, para su posterior analisis*/
void aplicar_jugada(char tablero[tab_h][tab_w],int jugada,int TURNO_aux){
	/*
	esta funcion descompone el codigo de jugada [ver glosario] en sus componentes utiles, y luego aplica la jugada al tablero dado
	utilizando las funciones necesarias segun el caso
	
	parámetros 
		tablero = tablero con el estado a analizar
		jugada = codigo de jugada a aplicar[ver glosario]
		TURNO_aux = turno a analizar
	*/
	int movimiento   = get_jugada(jugada);//movimiento a realizar
	int fila_inicial = get_fila_inicial(jugada);//fila inicial
	int col_inicial  = get_col_inicial(jugada);//columna inicial
	int fila_final   = get_fila_final(jugada);//fila final
	int col_final    = get_col_final(jugada);//columna final
	/*se evalua el movimiento*/
	switch(movimiento){
		case MULTIPLICAR:{
			multiplicar_ai(tablero,fila_final,col_final,TURNO_aux);
			break;
		}
		case PROPAGAR:{
			propagar_ai(tablero,fila_inicial,col_inicial,fila_final,col_final,TURNO_aux);
			break;
		}
	}
}
/*funcion que libera de la memoria el arbol creado, una vez que este se termino de analizar*/
void liberar_arbol(hijo *nodo){
	/*
	parámetro
		nodo = puntero al nodo a liberar
	*/
	int i;//variable para recorrer el vector de hijos
	for(i=0; nodo->pptr_hijo[i] ; i++){//mientras el nodo tenga algun hijo, se recorren los mismos
		if( nodo->pptr_hijo[i]->pptr_hijo[0] ){//si el hijo tiene a su vez algun hijo (nieto del nodo) se libera el nieto
			free( nodo->pptr_hijo[i]->pptr_hijo[0] );//liberar nieto
			free( nodo->pptr_hijo[i]->pptr_hijo );//lliberar vector de nietos
		}
		free(nodo->pptr_hijo[i]);//liberar hijo
	}
	free(nodo->pptr_hijo);//liberar vector de hijos
}
/*funcion que recorre el arbol para seleccionar la jugada a realizar*/
int elegir_jugada(hijo *nodo){
	/*
	la selección de la jugada se hace de la siguiente manera
	
	cada nodo cuenta con la informacion necesaria para obtener la diferencia entre la cantidad de bacterias despues de jugarse la jugada 
	(informacion que tambien esta en el nodo)
	
	se seleccionan primero los peores nietos (los que tienen diferencia mas negativa) para suponer la mejor jugada del oponente
	una vez seleccionados los nietos, se selecciona el mejor de los padres entre esos nietos de tal manera que la jugada escogida
	debería ser la respuesta más inteligente a una buena jugada del oponente
	
	parámetro
		puntero al nodo abuelo
	
	*/
	int i;//variable para recorrer los hijos
	hijo* chosen_one = NULL;// puntero al nodo seleccionado como mejor jugada
	
	int ban=TRUE;//indica si chosen_one esta vacio (primera vez que se va a cargar)
	for(i=0;nodo->pptr_hijo[i];i++){//se recorren los hijos en casod e que existan
		if(!(nodo->pptr_hijo[i]->pptr_hijo[0])){//si el hijo es una hoja (no tiene un nieto como hijo)
			if(ban){
				chosen_one = nodo->pptr_hijo[i];//se carga por primera vez el nodo
				ban =  FALSE;
			}
			if( nodo->pptr_hijo[i]->cant_verde - nodo->pptr_hijo[i]->cant_azul  >  chosen_one->cant_verde - chosen_one->cant_azul ){// si el hijo nos conviene mas, lo elegimos
				chosen_one = nodo->pptr_hijo[i];// se reemplaza la seleccion del nodo
			}
		}
	}
	
	if( !ban && chosen_one->cant_verde - chosen_one->cant_azul > 0){//si el hijo hoja es un tablero final con victoria nuestra se retorna esa jugada
		return chosen_one->jugada;
	}
	
	ban=TRUE;
	for(i=0;nodo->pptr_hijo[i];i++){//se recorren los hijos
		if(nodo->pptr_hijo[i]->pptr_hijo[0]){//se recorren los nietos
			if(ban){
				chosen_one = nodo->pptr_hijo[i];//se carga el primer nieto
				ban =  FALSE;
			}
			if( nodo->pptr_hijo[i]->pptr_hijo[0]->cant_verde - nodo->pptr_hijo[i]->pptr_hijo[0]->cant_azul  >  chosen_one->pptr_hijo[0]->cant_verde - chosen_one->pptr_hijo[0]->cant_azul ){// si el nieto nos conviene mas, lo elegimos
				chosen_one = nodo->pptr_hijo[i];// se reemplaza la seleccion del nodo
			}else{
				if( nodo->pptr_hijo[i]->pptr_hijo[0]->cant_verde - nodo->pptr_hijo[i]->pptr_hijo[0]->cant_azul  ==  chosen_one->pptr_hijo[0]->cant_verde - chosen_one->pptr_hijo[0]->cant_azul ){//si la diferencia es igual se elige el que tiene mejor padre
				    if( nodo->pptr_hijo[i]->cant_verde - nodo->pptr_hijo[i]->cant_azul  >  chosen_one->cant_verde - chosen_one->cant_azul ){//si el padre nos conviene mas, lo elegimos
						chosen_one = nodo->pptr_hijo[i];// se reemplaza la seleccion del nodo
					}else{
						if( (nodo->pptr_hijo[i]->cant_verde - nodo->pptr_hijo[i]->cant_azul  ==  chosen_one->cant_verde - chosen_one->cant_azul) && (rand()%2) ){//si los padres son iguales, elegimos cualquiera de ellos
							chosen_one = nodo->pptr_hijo[i];// se reemplaza la seleccion del nodo
						}
					}
				}
			}
		}
	}
	
	
	if(!ban){//si existe seleccion
		return chosen_one->jugada;
	}else{//si no podemos realizar jugada alguna
		return PASAR*100000000;
	}

}
/*resetea el tablero para el analisis*/
void reset_tablero(char tablero[tab_h][tab_w],char tablero_aux[tab_h][tab_w]){	
	/*
	parámetros
		tablero = tablero con estado anterior
		tablero_aux = tablero a reestablecer
	*/
	int i,j;//variables apara recorrer los tableros
	for(i=0;i<tab_h;i++){//recorrer tableros
		for(j=0;j<tab_w;j++){
			tablero_aux[i][j]=tablero[i][j];//reestablecer el tablero auxiliar
		}
	}
}
/*funcion que se encarga de crear los nietos del arbol de decisiones*/	
void crear_nieto(hijo *nodo,char tablero_aux_hijos[tab_h][tab_w], int TURNO_aux){
	/*
	parámetros
		nodo = puntero a un hijo al cual se le agrega el nieto 
		tablero_aux_hijos = tablero auxiliar con el estado del padre de los nietos
		TURNO_aux = turno a analizar
		
	*/
	TURNO_aux ^= 1;//se cambia el turno para analizar las jugadas del oponente
	int cantidad = 0;//variable que indica la cantidad de propagaciones totales
	int mult_posibles[tab_h][tab_w];//variable que indica las multiplicaciones posibles
	char tablero_aux_nietos[tab_h][tab_w];//tablero auxiliar para aplicar las jugadas y contar luego las bacterias
	int i,j,k;//variables para recorrer los tableros y vectores
	int n_hijos = 0;//indica el numero de hijos totales del nodo
	// ceramos la matriz de multiplicaciones
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			mult_posibles[i][j] = 0;
		}
	}
	//se resetea el tablero auxiliar
	reset_tablero(tablero_aux_hijos,tablero_aux_nietos);
	//se calcula la cantidad de propagaciones totales
	cantidad = cant_propagaciones(tablero_aux_hijos,TURNO_aux);
	//se prepara la matriz de multiplicaciones
	preparar_mult(tablero_aux_hijos,mult_posibles,TURNO_aux);
	//se cuenta el numero de hijos
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_h;j++){
			if(mult_posibles[i][j]){
				n_hijos++;
			}
		}
	}
	n_hijos += cantidad;
	//se declara el vector de jugadas [ver glosario]
	int jugadas[n_hijos];
	
	if(cantidad){//si existen propagaciones (si no existe propagacion tampoco existe multiplicacion)
		//se cargan las propagaciones
		cargar_propagaciones(tablero_aux_hijos,jugadas,TURNO_aux);
		k=cantidad;
		//se cargan las multiplicaciones
		for(i=0;i<tab_h;i++){
			for(j=0;j<tab_h;j++){
				if(mult_posibles[i][j]){
					jugadas[k]=mult_posibles[i][j];
					k++;
				}
			}
		}
	}
	k=0;
	
	
	int cant_azul , cant_verde;//variables auxiliares para calcular las cantidades de bacterias
	if(n_hijos){//si es necesario crear nietos (el nodo no es hoja)
		for(i=0;i<n_hijos;i++){//se recorren los nietos
			if(!i){//si es el primer nieto
				nodo->pptr_hijo = malloc(sizeof(hijo *)*2);//se crea el vector de nietos
				nodo->pptr_hijo[0] = malloc(sizeof(hijo));//se reserva memoria para el nieto
				nodo->pptr_hijo[0]->ptr_padre = nodo;// se asigna el padre al nodo (hijo)
				aplicar_jugada(tablero_aux_nietos,jugadas[0],TURNO_aux);//se aplica la jugada correspondiente al tablero auxiliar
				contar_bacterias(tablero_aux_nietos,&cant_azul, &cant_verde);//se cuentan las bacterias de cada jugador
				
				//se guarda la informacion en el nieto
				nodo->pptr_hijo[0]->cant_verde = cant_verde;
				nodo->pptr_hijo[0]->cant_azul = cant_azul;
				nodo->pptr_hijo[0]->jugada = jugadas[i];
				
				//se finaliza correctamente el vector de nietos[ver glosario]
				nodo->pptr_hijo[1] = NULL;
			}else{
				/*
					el vector de los nietos cuenta con un solo elemento, que se reemplaza, ya que nuestra
					estrategia ya define de por si que nieto elegir, al terminar de crear el arbol ya estan 
					los nietos seleccionados en cada hijo.
				*/
				
				aplicar_jugada(tablero_aux_nietos,jugadas[i],TURNO_aux);//se aplica la jugada correspondiente al tablero auxiliar
				contar_bacterias(tablero_aux_nietos,&cant_azul, &cant_verde);//se cuentan las bacterias de cada jugador
				
				if(nodo->pptr_hijo[0]->cant_verde - nodo->pptr_hijo[0]->cant_azul > cant_verde - cant_azul){//si el nieto nos conviene menos, lo elegimos [ver glosario]
					//reemplazamos la informacion del nodo nieto
					nodo->pptr_hijo[0]->cant_verde = cant_verde;
					nodo->pptr_hijo[0]->cant_azul = cant_azul;
					nodo->pptr_hijo[0]->jugada = jugadas[i];
				}else{
					if(nodo->pptr_hijo[0]->cant_verde - nodo->pptr_hijo[0]->cant_azul == cant_verde - cant_azul){//si tenemos dos nietos que nos convienen igual
						if(cant_verde > nodo->pptr_hijo[0]->cant_verde){//elegimos el que tiene mas bacterias nuestras
							//reemplazamos la informacion del nodo nieto
							nodo->pptr_hijo[0]->cant_verde = cant_verde;
							nodo->pptr_hijo[0]->cant_azul = cant_azul;
							nodo->pptr_hijo[0]->jugada = jugadas[i];
						}
					}
				}
			}
			reset_tablero(tablero_aux_hijos,tablero_aux_nietos);//se resetea el tablero al estado anterior para calcular el siguiente nieto
		}
	}else{// el nodo es hoja
		//asignamos null al vector de nietos
		nodo->pptr_hijo = malloc(sizeof(hijo *));
		nodo->pptr_hijo[0] = NULL;
	}
	
}
/*funcion que se encarga de crear los hijos del arbol de decisiones*/		
void crear_hijos(hijo *nodo,char tablero[tab_h][tab_w], int TURNO_aux){
	/*
	parámetros
		nodo = puntero a un hijo al cual se le agrega el nieto 
		tablero = tablero auxiliar con el estado de la raiz
		TURNO_aux = turno a analizar
		
	*/
	int cantidad = 0;//variable que indica la cantidad de propagaciones totales
	int mult_posibles[tab_h][tab_w];//variable que indica las multiplicaciones posibles
	char tablero_aux_hijos[tab_h][tab_w];//tablero auxiliar para aplicar las jugadas y contar luego las bacterias
	int i,j,k;//variables para recorrer los tableros y vectores
	int n_hijos = 0;//indica el numero de hijos totales del nodo
	// ceramos la matriz de multiplicaciones
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			mult_posibles[i][j] = 0;
		}
	}
	//se calcula la cantidad de propagaciones totales
	cantidad = cant_propagaciones(tablero,TURNO_aux);
	//se resetea el tablero auxiliar
	reset_tablero(tablero,tablero_aux_hijos);
	//se prepara la matriz de multiplicaciones
	preparar_mult(tablero,mult_posibles,TURNO_aux);
	//se cuenta el numero de hijos
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			if(mult_posibles[i][j]){
				n_hijos++;
			}
		}
	}
	n_hijos += cantidad;
	//se declara el vector de jugadas [ver glosario]
	int jugadas[n_hijos];
	
	if(cantidad){//si existen propagaciones (si no existe propagacion tampoco existe multiplicacion)
		//se cargan las propagaciones
		cargar_propagaciones(tablero,jugadas,TURNO_aux);
		k=cantidad;
		//se cargan las multiplicaciones
		for(j=tab_w-1;j>=0;j--){
			for(i=0;i<tab_h;i++){
				if(mult_posibles[i][j]){
					jugadas[k]=mult_posibles[i][j];
					k++;
				}
			}
		}
	}
	k=0;

	int cant_azul,cant_verde;//variables auxiliares para calcular las cantidades de bacterias
	if(n_hijos){//si la raiz no es un nodo hoja
		for(i=0;i<n_hijos;i++){//se recorre la cantidad de hijos para crearlos
			if(!i){//si es el primer hijo del arbol
				nodo->pptr_hijo = malloc(sizeof(hijo *)*2);//se reserva memoria para el vector de hijos
			}else{
				nodo->pptr_hijo = realloc(nodo->pptr_hijo,sizeof(hijo *)*(i+2));//se reubica la memoria del vector
			}
			nodo->pptr_hijo[i] = malloc(sizeof(hijo));//se reserva memoria para el nuevo hijo
			nodo->pptr_hijo[i]->ptr_padre = nodo;//se asigna el padre
			nodo->pptr_hijo[i+1] = NULL;//se finaliza correctamente el vector [ver glosario]
			nodo->pptr_hijo[i]->jugada = jugadas[i];//se asigna la jugada correspondiente al hijo
			
			aplicar_jugada(tablero_aux_hijos,nodo->pptr_hijo[i]->jugada,TURNO_aux);//se aplica la jugada al tablero raiz
			
			contar_bacterias(tablero_aux_hijos,&cant_azul, &cant_verde);//se cuentan las bacterias de cada color
			//se guarda la informacion en el hijo
			nodo->pptr_hijo[i]->cant_verde = cant_verde;
			nodo->pptr_hijo[i]->cant_azul = cant_azul;
			//se crean los nietos para el hijo actual
			crear_nieto(nodo->pptr_hijo[i],tablero_aux_hijos,TURNO_aux);
			//se restaura el tablero a su estado anterior
			reset_tablero(tablero,tablero_aux_hijos);
		}
	}else{//si la raiz es un nodo hoja
		//se asigna NULL al vector de hijos
		nodo->pptr_hijo = malloc(sizeof(hijo *));
		nodo->pptr_hijo[0] = NULL;
	}
}
/*se encarga de manejar el proceso de la inteligencia artificial*/
int ai_main(char tablero[tab_h][tab_w]){
	/*
	se encarga de ordenar el proceso de creacion del arbol, y seleccion de jugadas, una vez realizado esto, 
	libera el arbol de la memoria y devuelve la jugada seleccionada
	
	parametro
		tablero = tablero con el estado actual del juego
	*/
	hijo raiz;//se declara la raiz del arbol
	raiz.pptr_hijo = NULL;//se asigna null al vector de hijos
	int i,j;//variables para recorrer el tablero
	int jugada;//variable a retornar
	char tablero_aux[tab_h][tab_w];//tablero auxiliar para hacer los analisis
	
	//copiamos el tablero del estado actual del juego
	for(i=0;i<tab_h;i++){
		for(j=0;j<tab_w;j++){
			tablero_aux[i][j] = tablero[i][j];
		}
	}
	//asignamos la informacion a la raiz
	contar_bacterias(tablero_aux,&(raiz.cant_azul),&raiz.cant_verde);
	//copiamos el estado del turno actual del juego
	int TURNO_aux = TURNO;
	//creamos el arbol de seleccion
	crear_hijos(&raiz,tablero_aux,TURNO_aux);
	//seleccionamos la mejor jugada
	jugada = elegir_jugada(&raiz);
	//liberamos el arbol
	liberar_arbol(&raiz);
	//retornamos la seleccion
	return jugada ;
}
