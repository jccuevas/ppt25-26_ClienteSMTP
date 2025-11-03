#include "smtp.h"
#include <stdio.h>		// Biblioteca estándar de entrada y salida
#include <conio.h>	
#include <string.h>

//Comentar el cambio de los parámetros de la función smtpSM
int smtpSM(int status, char *buffer_out,size_t sbout) {
	char input[1024] = "";
	//SEsión 3. variable subjetc
	char subject[2014] = "";

	switch (status) {
	case S_INIT:
		// Se recibe el mensaje de bienvenida
		break;
	case S_HELO:
		// establece la sesión de envío de correos 
		printf("CLIENTE> Introduzca su dominio (enter para salir): ");
		gets_s(input, sizeof(input));
		if (strlen(input) == 0) {
			sprintf_s(buffer_out, sbout, "%s%s", QUIT, CRLF);
			status = S_QUIT;
		}
		else {
			sprintf_s(buffer_out, sbout, "%s %s%s", HELO, input, CRLF);
		}
		break;
	/* SESIÓN 3*/
	case S_MAIL:
		
		printf("CLIENTE> Introduzca el remitente (enter para salir): ");
		gets_s(input, sizeof(input));
		if (strlen(input) == 0) {
			sprintf_s(buffer_out, sbout, "%s%s", QUIT, CRLF);
			status = S_QUIT;
		}
		else {
			sprintf_s(buffer_out, sbout, "%s %s%s", MAIL, input, CRLF);
		}
		break;
	case S_RCPT:
		// Sesión 3: Solicita el destinatario del correo
		printf("CLIENTE> Introduzca el destinatario (enter para salir): ");
		gets_s(input, sizeof(input));
		if (strlen(input) == 0) {
			sprintf_s(buffer_out, sbout, "%s%s", QUIT, CRLF);
			status = S_QUIT;
		}
		else {
			sprintf_s(buffer_out, sbout, "%s %s%s", RCPT, input, CRLF);
		}
		break;
		// Añadir los caso para RCPT TO:

	case S_DATA:
		// Sesión 3: Solicita el remitente del correo
		//Envíe el comando DATA, no se necesita entrada del usuario
		sprintf_s(buffer_out, sbout, "%s%s", DATA, CRLF);
		break;
	case S_MSG:
		//Tratar como si fuera un solo comando, en tareas posteriores se deberán pedir más líneas:
		// - Pida el asunto del correo
		// - Pida una cadena de texto (línea del correo)
		// - Concatene en buffer_out la cadena introducida + CRLF + "." + CRLF
		// - Aquí no se puede enviar QUIT, ya que se está en medio del envío del mensaje
		printf("CLIENTE> Introduzca el asunto del correo: ");
		gets_s(subject, sizeof(subject));
		printf("CLIENTE> Introduzca el mensaje: ");
		gets_s(input, sizeof(input));
		sprintf_s(buffer_out, sbout, "Subject: %s%s%s%s%s.%s", subject, CRLF, CRLF, input, CRLF, CRLF);
		break; 
		/* SESIÓN 3*/
	}

	return 1;
}