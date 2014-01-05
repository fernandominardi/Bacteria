#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

#ifdef __linux__

//itoa base 10, se agrega para portabilidad 
char *itoa(char *buf, int value, int base) {
    sprintf(buf, "%d", value);
    return buf;
}

#endif

/*crea un archivo xml con la jugada recibida*/
void jugada_xml(char nombre_archivo[],int jugada,int f1, int c1, int f2, int c2){
	/*
	parametros
		nombre_archivo = nombre del archivo (ruta completta)
		jugada = codigo de jugada [ver glosario]
		f1 = fila inicial
		c1 = columna inicial
		f2 = fina final
		c2 = columna final
	*/
	xmlDocPtr doc;		//para abrir el documento				
  	xmlNodePtr tree;	//para crear el arbol
	xmlNodePtr tree2;	//para crear el hermano
	char numero[3];		//buffer para escribir el numero como string
	
	doc = xmlNewDoc("1.0");				//creamos el archivo
 	
	doc->children = xmlNewDocNode(doc, NULL, "jugada", NULL);	//creamos la raiz
	
	switch(jugada){//segun sea la jugada
		case MULTIPLICAR:{
			tree = xmlNewChild(doc->children, NULL, "multiplicar", NULL);	//creamos el hijo	
			tree = xmlNewChild(tree, NULL, "coordenada", NULL);		//creamos el hijo del hijo
				xmlSetProp(tree, "fila", itoa(f2+1,numero,10));		//añadimos atributos
				xmlSetProp(tree, "col", itoa(c2+1,numero,10));		//añadimos atributos
			
			break;
		}
		
		case PROPAGAR:{
			tree = xmlNewChild(doc->children, NULL, "propagar", NULL);	 //creamos el hijo	
			tree2 = xmlNewChild(tree, NULL, "coordenada_inicial", NULL); //creamos el hijo del hijo		
				xmlSetProp(tree2, "fila", itoa(f1+1,numero,10));		 //añadimos atributos					
				xmlSetProp(tree2, "col", itoa(c1+1,numero,10));			 //añadimos atributos
			tree2 = xmlNewChild(tree, NULL, "coordenada_final", NULL);	 //creamos el hhermano	
				xmlSetProp(tree2, "fila", itoa(f2+1,numero,10));		 //añadimos atributos					
				xmlSetProp(tree2, "col", itoa(c2+1,numero,10));          //añadimos atributos
			
			break;
		}
		
		case PASAR:{
			
			tree = xmlNewChild(doc->children, NULL, "paso", NULL);	//creamos el hijo	
			
			break;
		}
	}

	//guardamos el archivo
	if (!xmlSaveFormatFile (nombre_archivo, doc, 1)){		
		allegro_message("no se pudo crear el archivo XML");
	}
	
	//liberamos el arbol de la memoria
	xmlFreeNode(tree);
	if (jugada == PROPAGAR)
		xmlFreeNode(tree2);
	xmlFreeDoc(doc);
}
/**/
int get_jugada_xml(char nombre_archivo[]){
	xmlDocPtr doc = xmlParseFile( nombre_archivo);	//para abrir el documento
	xmlNodePtr actual;					//para recorrer el arbol
	int jugada=0;
	int fila_inicial=0;
	int col_inicial=0;
	int fila_final=0;
	int col_final=0;
	jugada = 0;
	if (doc){//si hay archivo
		actual = xmlDocGetRootElement(doc);	//vamos a la raiz
		actual = actual->xmlChildrenNode;	//voy al primer hijo
		while (actual){
			//voy a los hijos
			if (!xmlStrcmp(actual->name, "multiplicar")) {  //MULTIPLICAR
				printf("\n*MULTIPLICAR");
				actual = actual->xmlChildrenNode;			//voy al nodo hijo (coordenada)
				do{
					actual = actual->next;	
					if (xmlGetProp(actual, "fila")){//si existe el atributo correcto
						//capturamos los datos
						printf("\n%s %s \n", xmlGetProp(actual, "fila"), xmlGetProp(actual, "col"));
						//se crea la jugada con los valores entre 0 y 7
						jugada = crear_int_jugada(MULTIPLICAR,0,0, atoi(xmlGetProp(actual, "fila"))-1, atoi(xmlGetProp(actual, "col"))-1);
					}
				}while (actual->next);							
			}else if(!xmlStrcmp(actual->name, "propagar")){ //PROPAGAR
				printf("\n*PROPAGAR");
				actual = actual->xmlChildrenNode;
				do{
					actual = actual->next;
					if(!xmlStrcmp(actual->name, "coordenada_inicial")){//si existe el nodo correcto
						if (xmlGetProp(actual, "fila")){//si existe el atributo correcto
							//capturamos los datos
							printf("\n%s %s \n", xmlGetProp(actual, "fila"), xmlGetProp(actual, "col"));
							fila_inicial = atoi(xmlGetProp(actual, "fila"));
							col_inicial = atoi(xmlGetProp(actual, "col"));
						}
					}else if(!xmlStrcmp(actual->name, "coordenada_final")){//si existe el nodo correcto
						if (xmlGetProp(actual, "fila")){//si existe el atributo correcto
							//capturamos los datos
							printf("\n%s %s \n", xmlGetProp(actual, "fila"), xmlGetProp(actual, "col"));
							fila_final = atoi(xmlGetProp(actual, "fila"));
							col_final = atoi(xmlGetProp(actual, "col"));
						}
					}
				}while (actual->next);	
				//se crea la jugada con los valores entre 0 y 7
				jugada = crear_int_jugada(PROPAGAR,fila_inicial-1,col_inicial-1,fila_final-1,col_final-1);
			}else if(!xmlStrcmp(actual->name, "paso")){    //PASAR
				jugada = PASAR*100000000;
				printf("\n PASAR");
			}
			
			actual = actual->next;			
		}
	}else{//no se pudo leer el archivo, termina el programa y se informa	
		allegro_message("Archivo XML del otro jugador no se pudo leer");
		exit(1);
	}
	//liberamos el arbol
	xmlFreeDoc(doc);
	xmlFreeNode(actual);
	printf("\nxml_jugada = %d",jugada);
	if(jugada){
		return jugada;
	}else{//si no se cargo una jugada es porq el archivo no estaba bien creado
		allegro_message("ARCHIVO XML DEL OPONENTE MAL FORMADO");
		exit(1);
	}
}
