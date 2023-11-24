# Proyecto
Este es un intento de clon del juego Asteroids (1979) de Atari creado por alguien que en la vida habia programado c++, pero es muy terco como para hacer algo facil.

## Consideraciones
Solo corre en sistema operativo winwows esta version.

## Requisitos

1. Instalar SFML del siguiene link
   NOTA: si estas usando distro de linux o mac descarga la version correspondiente, si eres winwdows has descarga normal
- [SFML](https://www.sfml-dev.org/download.php)

2. [Instalar visual studio](https://visualstudio.microsoft.com/es/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&passive=false&cid=2030)

3. configurar las variables de entorno de  VC++ directories
* agregar en "include directories " la dirección de la ruta de SFML/INCLUDE
* agregar en "library directories " la dirección de la ruta de SFML/LIB
* Mover los archivos .dll de la carpeta SFML/ BIN a la ruta raíz del proyecto

[tutorial para mas ayuda](https://youtu.be/EVnmVdEPyUQ?feature=shared)

## Que tiene que hacer?
Este es el ultimo avance y por mas que nos peleamos (mi amigo que me ayuda, yo y el visual) las coliciones entre la nave y los asteroides sigue sin funcionar por el momento.

Cuando le disparas a un asteroide, este debe de desaparecer con la bala y el marcador debe de sumar 100 puntos y el texto de las cordenadas se actualiza constantemente mostrando la posicion de la nave.

## Como se debe de usar?
Flechas arriba, izquierda y derecha para moverse y girar.
Espacio para disparar.
