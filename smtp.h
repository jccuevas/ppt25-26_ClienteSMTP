#pragma once
char* smtpSM(int status);
// COMANDOS DE APLICACION
#define HELO "HELO"
#define MAIL "MAIL FROM:"
#define RCPT "RCPT TO:"
#define DATA "DATA"
#define RSET "RSET"
#define QUIT "QUIT"

//Un cambio de línea
//Otro cambio

// RESPUESTAS A COMANDOS DE APLICACION
<<<<<<< HEAD
#define SC220	"220"
#define SC250	"250"
#define SC354	"354"
#define SC500	"500"
#define SC221   "221"
=======
#define R220	"220"
#define R250	"250"
#define R354	"354"
#define R500	"500"
#define R221    "221"
>>>>>>> 8f36e86645329c9b57ec3d1f118918318b5a0459

//FIN DE RESPUESTA
#define CRLF "\r\n"

//ESTADOS
#define S_INIT 0
#define S_HELO 1
#define S_MAIL 2
#define S_RCPT 3
#define S_DATA 4
#define S_QUIT 5
