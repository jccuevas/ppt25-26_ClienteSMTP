#include "smtp.h"

char* smtpSM(int status) {
	char buffer_out[1024] = "", input[1024] = "";

	switch (status) {
	case S_INIT:
		// Se recibe el mensaje de bienvenida
		break;
	case S_HELO:
		// establece la sesión de envío de correos 
		printf("CLIENTE> Introduzca su dominio (enter para salir): ");
		gets_s(input, sizeof(input));
		if (strlen(input) == 0) {
			sprintf_s(buffer_out, sizeof(buffer_out), "%s%s", QUIT, CRLF);
			status = S_QUIT;
		}
		else {
			sprintf_s(buffer_out, sizeof(buffer_out), "%s %s%s", HELO, input, CRLF);
		}
		break;

	case S_DATA:

		break;

	}

	return buffer_out;
}