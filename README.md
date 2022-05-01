# weathermap

Participant: Elmotacime Omar,Hassen Khalifa


Heroku :
https://wheater-map-elmocatime-khalifa.herokuapp.com/

Mise en place du projet :

Cors

Je vous invite a tout d'abord activer la demo afin de permettre au projet de fetch les donnés présente dans la BDD.

https://cors-anywhere.herokuapp.com/

ESP32

Pour faire fonctionner l'acquisition des données, vous pouvez flasher esp avec le fichier mqtt.ino présent dans le dossier mqtt2/mqtt2.
Bien évidemment, il est possible de modifier les donné envoyer pas esp, tout en respectant la mise en forme du json envoyer par celle-ci, pour des raisons techniques.

Le Projet :

Notre projet est composé de 3 parties distinctes que je vais détailler par la suite.

La Weather Map :

![alt text](https://zupimages.net/up/22/17/tiwm.png)

Ce composant affiche sur une carte la position des esp ainsi que plusieurs donnée que vous pouvez voir cette image ci-dessus.

Le conposant Ville :

![alt text](https://zupimages.net/up/22/17/nj3g.png)

Le composant vile permet d'afficher la météo ainsi que la température d'une localisation (ville, Pays, Continent).

DashBoard :

![alt text](https://zupimages.net/up/22/17/5snd.png)

Le dashboard récence tout les esp présent dans la BDD et affiche les 10 dernière prise de mesure par cette dernière.

Troubleshooting

Si vous avez respecté les consignes dans la partie "Mise en place du projet", tous devrez fonctionner correctement. Cependant, si ce n'est pas le cas, je vous invite à m'envoyer un mail à cette adresse : hassen.khalifa@etu.unice.fr

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
```

### Compiles and minifies for production
```
npm run build
```

### Lints and fixes files
```
npm run lint
```

### Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).
