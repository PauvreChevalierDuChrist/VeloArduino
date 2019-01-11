# Rapport du 11 janvier 2019 :

Aujourd'hui je me suis principalement concentré sur la mise en place du gyroscope. J'ai d'abord soudé un petit truc permettant de le relier à l'arduino (un ensemble de prises femelles), première soudure de ma vie au passage. Le problème des caractères spéciaux incompréhensibles était bien lié à une différence de vitesse de communication entre le progremme arduino et le moniteur série. Problème qui fut vite réglé. 

J'ai ensuite trouvé sur internet un programme qui permettait de calibrer le gyroscope MPU6050 (programme qui semble être une référence dans le domaine, tout le monde l'utilise, merci Luis Rodenas). 

Le cours bien que rédigé avec une grande minutie par notre professeur contient une coquille, il faut remplacer le texte à la fin de la page 44 du cours sur les accéromètres par le suivant :

**SDA pour Serial DAta (I/O n° A4 de l’arduino)**
**SCL pour Serial CLock (I/O n° A5 de l’arduino)**

Le programme de calibration nous donne donc le résultat suivant :

>Sensor readings with offsets:	-20	8	16384	-2	0	0
>Your offsets:	-789	-1130	1222	91	31	15

On peut maintenant, dans nos programmes rajouter les lignes suivantes pour que nos mesures soient précises :

>accelgyro.setXAccelOffset(-789);
>accelgyro.setYAccelOffset(-1130);
>accelgyro.setZAccelOffset(1222);
>accelgyro.setXGyroOffset(91);
>accelgyro.setYGyroOffset(31);
>accelgyro.setZGyroOffset(15);

J'ai ensuite rapidement aidé Enzo à faire des choix concernants la structure du vélo. Nous avons décidé de la réaliser avec des pièces Mecano étant données qu'elles sont bien plus "maléables" que des LEGO. Voilà ce que nous avons pour le moment : 

![alt text](../roue.jpg "C'est beau.")

Voici à quoi ressemble mon montage pour l'instant : 

![alt text](../montage.jpg "C'est beau.")

J'ai trouvé sur internet un exemple de PID (https://www.instructables.com/id/Inverted-Pendulum-Robot-Using-a-Reaction-Wheel/). J'ai addapté le code donné à ce que nous avions (l'auteur utilisait des servomoteurs, pas nous.). Mais je ne peux pour l'instant pas vraiment savoir si le programme est foncitonnel (on ne peut pas encore savoir s'il permet d'équilibrer le vélo). En tout cas, le moteur réagit en fonction des mouvements du gyroscope, c'est bon signe.

Merci de m'avoir lu.

Bonne journée.

