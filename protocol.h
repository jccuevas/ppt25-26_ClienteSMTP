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
#define HELO "HELO"
#define MAIL "MAIL FROM:"
#define RCPT "RCPT TO:"
#define DATA "DATA"
#define RSET "RSET"
#define QUIT "QUIT"



// RESPUESTAS A COMANDOS DE APLICACION
#define R220	"202"
#define R250	"250"
#define R354	"354"
#define R500	"500"
#define R221   "221"

//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_INIT 0
#define S_HELO 1
#define S_MAIL 2
#define S_RCPT 3
#define S_DATA 4
#define S_QUIT 5


//PUERTO DEL SERVICIO SMTP
#define TCP_SERVICE_PORT	25

