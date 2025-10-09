# Práctica 3. Implementación de un cliente socket TCP basado en un estándar en C
* TITULACIÓN: Grado en Ingeniería telemática (14512011)
* TITULACIÓN: Doble Grado Ing. de tecnologías de la telecomunicación e Ing. telemática (15212023)
* CENTRO: ESCUELA POLITÉCNICA SUPERIOR (LINARES)
* CURSO ACADÉMICO: 2025-2026
## Descripción
Realizar un cliente SMTP [1] en lenguaje C con una interfaz sencilla basada en texto, empleando las primitivas Sockets [2]. El cliente se implementará como una aplicación de consola guiada a través de la entrada estándar (teclado) y deberá seguir la RFC 5321 [1] y la RFC 5322 [3]. La aplicación desarrollada permitirá el envío de correos electrónicos a cualquier servidor SMTP de Internet  que admita el comando HELO. Téngase en cuenta que la especificación del protocolo sigue la nomenclatura ABNF [3]. La presente práctica deberá cumplir los siguientes requisitos:
1.	Se deberá dar soporte a los comandos HELO, MAIL, RCPT, DATA, QUIT y RSET.
2.	Se deberá guiar al usuario durante toda la sesión de envío de correos, además de informarle del estado o fase en la que se encuentre el cliente en todo momento.
3.	El interfaz de usuario de la aplicación deberá ocultar al usuario los comandos del protocolo necesarios para la operación.
4.	Se deberá poder añadir más de un destinatario al correo.
5.	Redacción de correos en formato ASCII.
6.	Los correos deberán tener un número ilimitado de líneas.
7.	Se deberá preservar la longitud máxima de línea especificada para SMTP.
8.	Se deberá poder enviar más de un correo en la misma sesión.
## Material a entregar
### Código de la aplicación
#### Plataforma de docencia
Se deberá subir en la tarea reservada para la entrega en la plataforma de docencia virtual un fichero comprimido con todos aquellos ficheros de código fuente en C necesarios para la adecuada compilación y construcción del código (.c y/o .h), nunca los ficheros del proyecto, ficheros ejecutables o de código objeto.
•	El nombre del fichero deberá comenzar por práctica3_ y estar seguido por el identificador de quién/quiénes hayan realizado la práctica. Ejemplo: práctica3_estudiante1 o práctica3_estudiante1_estudiante2 para dos estudiantes.
•	El código entregado deberá cumplir con los objetivos concretos descritos en la práctica, tener comentarios que ayuden a su seguimiento y corrección además de no tener errores de sintaxis, ni de ejecución.
•	En el caso de que la práctica se realice en pareja, cada estudiante deberá entregar el mismo material por separado en la plataforma de docencia de la UJA.
El no cumplir con los requisitos de entrega podrá conllevar una penalización en la calificación final de la práctica de hasta 1 punto.
#### Plataforma GitHub
Todo el código deberá estar accesible al profesor/a a través de la herramienta de control de versiones GitHub, para lo cual se deberá añadir a éste/a como colaborador al repositorio que contenga la práctica. Cada sesión de trabajo deberá contar con al menos una actualización significativa del trabajo desarrollado en la misma.
