#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola! Soy un log");


	config = iniciar_config();

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	//Loggear valor de config

	valor = config_get_string_value(config, "CLAVE");
	log_info(logger, "El valor de la clave es: %s", valor);

	ip = config_get_string_value(config, "IP");
	log_info(logger, "El valor de la IP es: %s", ip);

	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, "El valor del Puerto es: %s", puerto);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor

	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor, conexion);
	log_info(logger, "Se envió la clave al servidor", puerto);
	free(valor);

	//agregar_a_paquete(paquete,"unString",strlen("unString"));

	t_paquete* paquete = crear_super_paquete();
	leer_consola(logger, paquete);
	enviar_paquete(paquete, conexion);
	log_info(logger, "Se enviaron los valores al servidor", puerto);
	eliminar_paquete(paquete);

	//paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/

}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("/home/utnso/TP0/client/cliente.log", "cliente", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("/home/utnso/TP0/client/cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger, t_paquete* paquete)
{
		printf("Ingrese valores a enviar al servidor: \n");
	    while(1){
	    	char* leido;
	        leido = readline(">");

	        if (strcmp(leido,"") == 0){
	            //free(leido);
	            break;
	        }

	        log_info(logger, "Se ingresó por consola '%s'",leido);
	        agregar_a_paquete(paquete, leido, strlen(leido)+1);
	        free(leido);
	    }

}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	//char* leido;
	t_paquete* paquete = crear_paquete();

	agregar_a_paquete(paquete,"unString",strlen("unString"));

	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_info(logger, "Finalizando modulo");

	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);

}
