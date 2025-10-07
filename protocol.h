/*******************************************************
 * Protocolos de Transporte
 * Grado en Ingeniería Telemática
 * Dpto. de Ingeníería de Telecomunicación
 * Universidad de Jaén
 *
 *******************************************************
 * Práctica 1
 * Fichero: protocol.h
 * Versión: 1.0
 * Curso: 2025/2026
 * Descripción: Fichero de encabezado para práctica 3
 * Autor: Juan Carlos Cuevas Martínez
 *
 ******************************************************
 * Alumno 1:
 * Alumno 2:
 *
 ******************************************************/
#ifndef protocolostpte_practicas_headerfile
#define protocolostpte_practicas_headerfile
#endif

// COMANDOS DE APLICACION
#define USER "USER"
#define PASS "PASS"
#define QUIT "QUIT"
#define ECHO "ECHO"


// RESPUESTAS A COMANDOS DE APLICACION
#define OK  "OK"
#define ER  "ER"

//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_INIT 0
#define S_USER 1
#define S_PASS 2
#define S_DATA 3
#define S_QUIT 4


//PUERTO DEL SERVICIO
#define TCP_SERVICE_PORT	25

