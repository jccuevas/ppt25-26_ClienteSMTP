/*******************************************************
 * Protocolos de Transporte
 * Grado en Ingeniería Telemática
 * Dpto. de Ingeníería de Telecomunicación
 * Universidad de Jaén
 *
 *******************************************************
 * Práctica 3
 * Fichero: cliente.c
 * Versión: 1.0
 * Curso: 2025/2026
 * Descripción: Cliente SMTP sencillo sobre IPv4 o IPv6
 * Autor: Juan Carlos Cuevas Martínez
 *
 ******************************************************
 * Alumno 1: Juan Carlos Cuevas Martínez
 * Alumno 2:
 *
 ******************************************************/
#include <stdio.h>		// Biblioteca estándar de entrada y salida
#include <ws2tcpip.h>	// Necesaria para las funciones IPv6
#include <conio.h>		// Biblioteca de entrada salida básica
#include <locale.h>		// Para establecer el idioma de la codificación de texto, números, etc.
#include "protocol.h"	// Declarar constantes y funciones de la práctica
#include "smtp.h"		// Funcionamiento del protocolo SMTP

#pragma comment(lib, "Ws2_32.lib")//Inserta en la vinculación (linking) la biblioteca Ws2_32.lib

int main(int* argc, char* argv[])
{
	SOCKET sockfd;
	struct sockaddr* server_in = NULL;
	struct sockaddr_in server_in4;
	struct sockaddr_in6 server_in6;
	int address_size = sizeof(server_in4);
	char buffer_in[1024], buffer_out[1024];//Eliminada al extraer la función smtpSM: , input[1024];
	int received = 0, sent = 0;
	int status;
	char option;
	int ipversion = AF_INET;//IPv4 por defecto
	char ipdest[256];
	char default_ip4[16] = "150.214.179.118"; //Dirección IP del servidor SMTP de la UJA";
	char default_ip6[64] = "::1";

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	//Inicialización de idioma
	setlocale(LC_ALL, "es_ES.UTF8");


	//Inicialización Windows sockets - SOLO WINDOWS
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		return(0);
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return(0);
	}
	//Fin: Inicialización Windows sockets

	printf("**************\r\nCLIENTE TCP SENCILLO SOBRE IPv4 o IPv6\r\n*************\r\n");

	do {
		printf("CLIENTE> ¿Qué versión de IP desea usar? 6 para IPv6, 4 para IPv4 [por defecto] ");
		gets_s(ipdest, sizeof(ipdest));

		if (strcmp(ipdest, "6") == 0) {
			//Si se introduce 6 se empleará IPv6
			ipversion = AF_INET6;

		}
		else { //Distinto de 6 se elige la versión IPv4
			ipversion = AF_INET;
		}

		sockfd = socket(ipversion, SOCK_STREAM, 0);
		if (sockfd == INVALID_SOCKET) {
			printf("CLIENTE> ERROR\r\n");
			exit(-1);
		}
		else {
			printf("CLIENTE> Introduzca la IP destino (pulsar enter para IP por defecto): ");
			gets_s(ipdest, sizeof(ipdest));

			//Dirección por defecto según la familia
			if (strcmp(ipdest, "") == 0 && ipversion == AF_INET)
				strcpy_s(ipdest, sizeof(ipdest), default_ip4);

			if (strcmp(ipdest, "") == 0 && ipversion == AF_INET6)
				strcpy_s(ipdest, sizeof(ipdest), default_ip6);

			if (ipversion == AF_INET) {
				server_in4.sin_family = AF_INET;
				server_in4.sin_port = htons(TCP_SERVICE_PORT);
				inet_pton(ipversion, ipdest, &server_in4.sin_addr.s_addr);
				server_in = (struct sockaddr*) & server_in4;
				address_size = sizeof(server_in4);
			}

			if (ipversion == AF_INET6) {
				memset(&server_in6, 0, sizeof(server_in6));
				server_in6.sin6_family = AF_INET6;
				server_in6.sin6_port = htons(TCP_SERVICE_PORT);
				inet_pton(ipversion, ipdest, &server_in6.sin6_addr);
				server_in = (struct sockaddr*) & server_in6;
				address_size = sizeof(server_in6);
			}

			//Cada nueva conexión establece el estado incial en
			status = S_INIT;

			if (connect(sockfd, server_in, address_size) == 0) {
				printf("CLIENTE> CONEXION ESTABLECIDA CON %s:%d\r\n", ipdest, TCP_SERVICE_PORT);

				//Inicio de la máquina de estados
				do {
					//CAPA DE APLICACIÓN
					smtpSM(status, buffer_out, sizeof(buffer_out));

					if (status != S_INIT) {
						//CAPA DE TRANSPORTE
						sent = send(sockfd, buffer_out, (int)strlen(buffer_out), 0);
						if (sent == SOCKET_ERROR) {
							status = S_QUIT;
							continue;// La sentencia continue hace que la ejecución dentro de un
									 // bucle salte hasta la comprobación del mismo.
						}
					}

					//CAPA DE TRANSPORTE
					if (status != S_MSG || /* ENVIADO el .CRLF*/ (status == S_MSG && strcmp(buffer_out, ".\r\n")==0)) {
						received = recv(sockfd, buffer_in, 512, 0);
						if (received <= 0) {
							DWORD error = GetLastError();
							if (received < 0) {
								printf("CLIENTE> Error %d en la recepción de datos\r\n", error);
								status = S_QUIT;
							}
							else {
								printf("CLIENTE> Conexión con el servidor cerrada\r\n");
								status = S_QUIT;
							}
						}
						else {
							//CAPA DE APLICACIÓN
							buffer_in[received] = 0x00;
							printf(buffer_in);
							switch (status) {
							case S_INIT:
								if (strncmp(buffer_in, R220, 3) == 0) {
									status = S_HELO;
								}
								else {
									//Tarea opcional: gestionar el error que devuelve el servidor si no es 220
									status = S_QUIT;
								}
								break;

								/* Sesión 3*/
							case S_HELO:
							case S_MAIL:
								if (strncmp(buffer_in, R250, 3) == 0) {
									status++;
								}
								break;
							case S_RCPT:
								if (strncmp(buffer_in, R250, 3) == 0) {

									printf("¿Quieres enviar a otro destinatario? (S/N)");
									option = _getch();
									if (option != 's' && option != 'S') {
										status++;
									}
								}
								//Si hay un error se mantiene el estado actual para reintentarlo o que el usuario envíe QUIT para salir
								//por lo tanto no hace falta añadir nada en el else

								break;
							case S_DATA:
								if (strncmp(buffer_in, R354, 3) == 0) {
									status = S_MSG;
								}
								else {
									//Tarea opcional: gestionar el error que devuelve el servidor si no es 354
									status = S_QUIT;
								}
								break;
							case S_MSG:
								if (strncmp(buffer_in, R250, 3) == 0) {
									status = S_MAIL;
								}
								else {
									//Tarea opcional: gestionar el error que devuelve el servidor si no es 250
									status = S_QUIT;
								}
								break;
								/* Fin sesión 3*/
							}
						}
					}

				} while (status != S_QUIT);
			}
			else {
				int error_code = GetLastError();
				printf("CLIENTE> ERROR AL CONECTAR CON %s:%d\r\n", ipdest, TCP_SERVICE_PORT);
			}
			closesocket(sockfd);

		}
		printf("-----------------------\r\n\r\nCLIENTE> Volver a conectar (S/N)\r\n");
		option = _getche();

	} while (option != 'n' && option != 'N');

	return(0);
}

