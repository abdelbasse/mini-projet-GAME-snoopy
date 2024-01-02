# Version FR
---

**Introduction à Snoopy's Magic Show (1990)**

Bienvenue dans "Snoopy's Magic Show", un jeu captivant et nostalgique qui vous ramène dans le monde magique des années 1990. Développé en utilisant le langage de programmation C avec la bibliothèque SDL, ce jeu met en avant le personnage bien-aimé de Peanuts, Snoopy, dans une aventure enchanteresse et whimsique.

**Concept du jeu :**
"Snoopy's Magic Show" plonge les joueurs dans le monde charmant de Snoopy, où la magie et le mystère abondent. Situé contre un décor inspiré de la bande dessinée emblématique Peanuts, les joueurs naviguent Snoopy à travers un environnement basé sur une grille, rencontrant des défis magiques et des surprises délicieuses.

**Objectif :**
En tant que Snoopy, votre mission est de fasciner le public avec un spectacle de magie spectaculaire. Pour ce faire, vous devez guider Snoopy à travers la grille magique, résoudre des énigmes, collecter des artefacts magiques et éviter les obstacles. L'objectif du jeu est d'enthousiasmer et de captiver le public en accomplissant avec succès des tours de magie dans un laps de temps donné.

**Caractéristiques du gameplay :**
- **Exploration basée sur une grille :** Traversez un monde basé sur une grille plein de fantaisie, rappelant les jeux de puzzle classiques des années 1990.
- **Tours de magie :** Participez à une variété de tours de magie et d'illusions, nécessitant une navigation habile et une résolution de problèmes.
- **Univers Peanuts :** Plongez-vous dans l'univers charmant de Peanuts, avec des personnages emblématiques et des visuels vibrants et nostalgiques.
- **Gestion du temps :** Défiez-vous avec une horloge de jeu dynamique, ajoutant un élément d'urgence au spectacle de magie. Accomplissez avec succès des tours avant que le temps ne s'épuise pour impressionner le public.

**Détails de développement :**
Développé en utilisant le langage de programmation C et la bibliothèque SDL, "Snoopy's Magic Show" rend hommage à l'ère rétro du jeu des années 1990. L'utilisation de SDL facilite le rendu graphique fluide et la gestion des événements, assurant une expérience de jeu engageante et réactive.

**Rejoignez Snoopy dans un voyage magique :**
Lancez-vous dans un voyage magique avec Snoopy alors que vous explorez le monde enchanteur de "Snoopy's Magic Show". Ce jeu capture non seulement l'esprit des jeux d'aventure classiques, mais il ramène également le charme intemporel de Peanuts à la vie dans une expérience de jeu délicieuse. Préparez-vous pour une présentation magique qui vous transportera dans l'ère dorée des jeux des années 1990 !

**Variables du Programme :**
1. **box :** Représente la taille de chaque case de la grille sur l'écran du jeu.
2. **HIEGHT, WIDTH :** Définissent la hauteur et la largeur de la grille du jeu en termes de cases de grille. Ils déterminent la taille globale de la zone de jeu.
3. **playing :** Une variable booléenne indiquant si le jeu est actuellement en cours. Lorsqu'elle est définie sur `true`, la boucle de jeu continue ; sinon, elle se termine.
4. **Frame :** Spécifie le délai entre les images dans la boucle de jeu. Il contrôle la fréquence d'images et influence la vitesse des animations et des mises à jour.
5. **timerColor :** Un tableau 2D stockant les valeurs RGB pour différentes couleurs de minuterie. Il permet à la minuterie de changer de couleur en fonction du temps restant.
6. **indexTimerColor :** Un indice utilisé pour sélectionner la couleur appropriée dans `timerColor` en fonction du temps restant. Il assure une transition en douceur des couleurs.
7. **window, render :** Objets SDL window et renderer. La fenêtre représente la fenêtre de jeu, tandis que le renderer est responsable du dessin graphique sur la fenêtre.
8. **Snoppy :** Une structure représentant le joueur. Elle contient la position du joueur (`pos`), le nombre de vies restantes (`lives`), et la dernière direction empruntée (`lastDirection`).
9. **GameTimer :** Une structure représentant la minuterie du jeu. Elle comprend des propriétés telles que le temps total (`Totale

`), la valeur de décrémentation de temps (`dec`), les dimensions (`h` et `w`), et le temps actuel restant (`time`).
10. **blockMap :** Une structure stockant les positions des blocs sur la grille de jeu. Elle contient un tableau de structures `Position` (`pos`) et le nombre de blocs (`nbr`).
11. **totaleTime :** Représente le temps total pour un cycle de jeu. Il diminue à mesure que le jeu progresse.

**Fonctions :**

### `EndGame()`

La fonction `EndGame()` est essentielle pour orchestrer la fermeture élégante du jeu. En tant qu'acte final dans le cycle de vie du jeu, son objectif principal est de gérer correctement et de vider les ressources SDL. La fonction commence par exécuter `SDL_RenderClear(render)`, effaçant le contenu du renderer. Ensuite, elle appelle `SDL_DestroyRenderer(render)` et `SDL_DestroyWindow(window)`, détruisant méticuleusement le renderer et la fenêtre, respectivement. Cette déconstruction étape par étape des composants graphiques garantit l'absence d'artefacts résiduels. Enfin, la fonction se termine par `SDL_Quit()`, indiquant la cessation complète de SDL et libérant toutes les ressources globales qu'il aurait pu acquérir. L'exécution méticuleuse de `EndGame()` garantit une fermeture propre, évitant les fuites de mémoire potentielles et les problèmes liés aux ressources.

### `makeTimer()`

La fonction `makeTimer()` a pour tâche de représenter visuellement la minuterie du jeu à l'écran. Elle dessine dynamiquement la minuterie en configurant différentes rectangles avec des couleurs variées, créant une représentation visuelle du temps restant dans le cycle de jeu. La fonction utilise les valeurs RGB stockées dans `timerColor` pour différencier les intervalles de temps, effectuant une transition en douceur à mesure que la minuterie diminue. En rendant ces rectangles à l'écran, `makeTimer()` fournit aux joueurs une indication visuelle claire et intuitive sur le passage du temps dans le jeu.

### `makeGread()`

Dans la fonction `makeGread()`, les éléments visuels de l'environnement de jeu prennent vie. Son objectif va au-delà de l'esthétique, car elle dessine méticuleusement la grille de jeu, la minuterie, la carte et le joueur à l'écran. La fonction commence par charger une image de grille en utilisant `SDL_LoadBMP()` et crée une texture à partir de la surface. Ensuite, elle rend la grille, en utilisant des boucles imbriquées pour dessiner d'autres éléments visuels tels que des rectangles blancs et la minuterie du jeu. En combinant ces composants visuels, `makeGread()` crée un environnement visuellement immersif, préparant le terrain pour l'interaction du joueur.

### `RenderMap()`

`RenderMap()` est responsable du rendu des blocs sur la grille de jeu en fonction des positions spécifiées dans la structure `blockMap`. En utilisant `SDL_LoadBMP()` et `SDL_CreateTextureFromSurface()`, la fonction charge des images de bloc et crée des textures pour le rendu. Elle itère ensuite sur les positions de `blockMap`, dessinant des blocs individuels à l'écran. En rendant dynamiquement ces blocs, `RenderMap()` communique visuellement la disposition des obstacles ou des défis dans le jeu, contribuant à l'expérience de jeu globale.

### `GameTimeClock()`

La fonction `GameTimeClock()` joue un rôle crucial dans la gestion de la minuterie du jeu. Elle met à jour le temps total restant dans le cycle de jeu, le décrémentant en fonction du temps écoulé. En évaluant la variable `totaleTime` et en ajustant la propriété `GameTimer.Totale`, la fonction s'assure que la minuterie reflète avec précision la progression du temps dans le jeu. Cette gestion du temps est vitale pour déclencher des événements ou des transitions en fonction des contraintes temporelles, contribuant à la dynamique globale du gameplay.

### `GetPlayerPosition()`

La fonction `GetPlayerPosition()` sert d'utilitaire pour récupérer la position actuelle du joueur dans la grille de jeu. En calculant les coordonnées de la grille à partir des coordonnées de pixels du joueur, la fonction renvoie une structure `Position` contenant l'emplacement du joueur dans la grille de jeu. Ces informations sont cruciales pour divers éléments de logique de jeu qui dépendent de la position du joueur.

### `SetPlayerPositionTo(int nextX, int nextY)`

La fonction `SetPlayerPositionTo()` est responsable de mettre à jour la position du joueur dans la grille de jeu. Elle prend les paramètres `nextX` et `nextY`, représentant les coordonnées de grille souhaitées pour le joueur. Avant de mettre à jour la position, la fonction peut effectuer une logique supplémentaire, telle que la vérification des limites pour s'assurer que le joueur reste dans la zone de jeu valide. Après vérification, la position du joueur est mise à jour, et la fonction contribue au mouvement dynamique du personnage du joueur dans le jeu.

### `SetUp()`

La fonction `SetUp()` est une configuration cruciale pour initialiser l'état initial du jeu. Elle configure divers aspects du jeu, y compris les propriétés de la minuterie du jeu (`GameTimer`), les positions initiales des blocs (`blockMap`) et la position de départ du joueur (`Snoppy`). De plus, elle alloue de la mémoire pour les positions des blocs en utilisant `calloc()` et configure la position initiale du joueur. En exécutant ces étapes d'initialisation, `SetUp()` établit les éléments fondamentaux nécessaires à une expérience de jeu cohérente et captivante.

### `RenderGame()`

`RenderGame()` orchestre le rendu de l'ensemble de l'écran de jeu. En coordonnant diverses fonctions de rendu telles que `makeGread()`, `RenderMap()` et `drowPlayer()`, elle garantit que l'environnement de jeu complet est présenté visuellement au joueur. Ce processus de rendu complet contribue à la visualisation en temps réel des éléments du jeu, maintenant un affichage dynamique et réactif qui reflète l'évolution de l'état du jeu.

### `Update()`

La fonction `Update()` joue un rôle central dans la gestion des aspects dynamiques de la logique du jeu. Bien que les détails spécifiques de la logique dépendent de la conception du jeu, `Update()` gère généralement la progression des événements in-game et met à jour des éléments critiques tels que le chronomètre du jeu. Cette fonction assure l'évolution de l'état du jeu au fil du temps, en réagissant aux entrées du joueur et en déclenchant des événements ou transitions pertinents.

### `HandelEvents()`

`HandelEvents()` est responsable de la gestion des événements SDL, en particulier des entrées utilisateur depuis le clavier. Dans la boucle d'événements SDL, elle écoute des événements tels que les pressions de touches et y répond en conséquence. Dans le contexte du code fourni, elle vérifie les événements SDL_QUIT, indiquant une demande de fermeture du jeu, et les événements SDL_KEYDOWN, permettant au joueur de contrôler le mouvement du personnage. En traitant ces événements, `HandelEvents()` permet l'interaction utilisateur avec le jeu, traduisant les entrées du clavier en actions significatives dans le monde du jeu.

### `main()`

La fonction `main()` sert de point d'entrée et de battement de cœur de l'ensemble du programme, constituant la boucle de jeu. Elle commence par initialiser SDL, créer la fenêtre du jeu et configurer le rendu. La fonction `SetUp()` est ensuite appelée pour initialiser l'état initial du jeu. Par la suite, le programme entre dans une boucle de jeu continue (`while (playing) { ... }`), où les événements sont traités (`HandelEvents()`), la logique du jeu est mise à jour (`Update()`) et l'écran de jeu complet est rendu (`RenderGame()`). La boucle est contrôlée par la variable `playing`, et la fonction SDL_Delay(Frame) introduit un délai entre les images, contrôlant le taux d'images par seconde. La boucle de jeu continue tant que la variable `playing` reste à `true`. Enfin, la fonction `EndGame()` est appelée pour assurer une fermeture correcte et propre du jeu.
### Structure de la fonction `main()` :

La fonction `main()` sert de point d'entrée et d'orchestrateur central de l'ensemble du jeu. Sa structure définit les phases d'initialisation, de boucle de jeu et de terminaison, créant un cadre cohérent pour l'expérience de jeu.

1. **Phase d'initialisation :**
   ```c
   int main(int argc, char **argv) {
       // Initialisation de SDL et de la fenêtre de jeu
       if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
           // Gérer l'échec de l'initialisation de SDL
           // ...
           return 1;
       }

       // Créer la fenêtre de jeu
       window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, box * WIDTH, HIEGHT * box, SDL_WINDOW_SHOWN);
       // Vérifier la création de la fenêtre
       if (window == NULL) {
           // Gérer l'échec de la création de la fenêtre
           // ...
           return 1;
       }

       // Créer le rendu
       render = SDL_CreateRenderer(window, -1, 0);
       // Vérifier la création du rendu
       if (render == NULL) {
           // Gérer l'échec de la création du rendu
           // ...
           return 1;
       }

       // Configurer l'état initial du jeu
       SetUp();

       // Entrer dans la boucle de jeu
       while (playing) {
           // Traitement des événements
           HandelEvents();

           // Mise à jour de la logique du jeu
           Update();

           // Rendre l'écran de jeu
           RenderGame();

           // Introduire un délai pour le contrôle du taux d'images
           SDL_Delay(Frame);
       }

       // Terminer le jeu
       EndGame();

       return 0;
   }
   ```
Bien sûr ! Plongeons plus profondément dans chaque fonction, fournissant des explications plus détaillées :

### 1. `GetPlayerPosition()`
   - **Description :** Cette fonction récupère la position actuelle du joueur dans le jeu. Elle sert d'utilitaire crucial pour obtenir les coordonnées du joueur à l'écran, permettant aux autres systèmes et mécaniques du jeu d'accéder et de réagir à la position du joueur de manière dynamique. La position est généralement représentée sous la forme d'une structure ou d'un objet contenant les coordonnées X et Y.

### 2. `SetPlayerPositionTo(int x, int y)`
   - **Description :** La fonction `SetPlayerPositionTo` est responsable de la mise à jour et du changement de la position du joueur dans le jeu aux coordonnées spécifiées (x, y). Cette fonction joue un rôle essentiel dans la gestion de divers événements in-game nécessitant le déplacement ou le repositionnement du personnage du joueur.

### 3. `getStringUrlLevelByIndex(int index)`
   - **Description :** Cette fonction facilite le chargement dynamique des niveaux en récupérant l'URL associée à un index donné. Elle est instrumentale pour obtenir les données ou ressources nécessaires au niveau en fonction d'un index, permettant au jeu de charger différents niveaux sans coder en dur des chemins de fichiers spécifiques. Cela améliore la flexibilité et la scalabilité du jeu.

### 4. `EndGame()`
   - **Description :** La fonction `EndGame` termine gracieusement l'exécution du jeu. Elle est généralement appelée lorsque le joueur décide de quitter le jeu ou lorsque certaines conditions sont remplies. Cette fonction est responsable d'effectuer des tâches de nettoyage, de libérer les ressources allouées et d'assurer une sortie fluide du jeu.

### 5. `renderDigit(int digit, int x, int y)`
   - **Description :** La fonction `renderDigit` est responsable du rendu d'un chiffre unique à l'écran aux coordonnées spécifiées (x, y). Elle contribue à la représentation visuelle des valeurs numériques, souvent utilisée pour afficher le score du joueur ou d'autres informations numériques pendant le gameplay.

### 6. `renderScore(int score, int x, int y, int width)`
   - **Description :** Cette fonction est cruciale pour le rendu du score du joueur à l'écran. En spécifiant la valeur du score et la position (x, y), elle affiche visuellement le score actuel du joueur. Le paramètre supplémentaire, width, pourrait être lié à des aspects de formatage ou d'alignement du score rendu.

### 7. `makeTimer()`
   - **Description :** La fonction `makeTimer` est responsable de l'initialisation et de la configuration d'une minuterie qui suit le temps de jeu. Il s'agit d'un composant essentiel pour les mécanismes de jeu basés sur le temps, permettant au jeu de surveiller le temps écoulé pendant le gameplay, influençant éventuellement des événements, des défis ou des transitions.

### 8. `makeGrid()`
   - **Description :** La fonction `makeGrid` est cruciale pour établir la structure fondamentale du jeu. Elle crée et configure la grille de jeu, définissant la zone de jeu et la disposition. La grille est fondamentale pour organiser les éléments du jeu, faciliter la détection de collisions et fournir un environnement structuré pour le gameplay.

### 9. `makeMenu()`
   - **Description :** Cette fonction gère le rendu du menu principal dans le jeu. Elle est responsable de présenter visuellement les options de menu, permettant aux joueurs de naviguer et d'interagir avec différentes sections du jeu, comme commencer une nouvelle partie, accéder aux paramètres ou quitter le jeu.

### 10. `RenderMap()`
   - **Description :** La fonction `RenderMap` est responsable du rendu de la carte du jeu pendant le gameplay. Elle visualise la disposition actuelle du niveau, y compris les obstacles, les plates-formes ou d'autres structures pertinentes. Le rendu de la carte est crucial pour donner aux joueurs une compréhension claire de l'environnement et des défis du jeu.

### 11. `GameTimeClock()`
   - **Description :** En gérant l'horloge du jeu et les fonctions liées au temps, `GameTimeClock` joue un rôle central dans le suivi et la mise à jour de l'horloge du jeu. Elle est essentielle pour les mécanismes de jeu basés sur le temps, y compris les défis limités dans le temps, les événements ou la détermination de la durée totale du gameplay.

### 12. `drawPlayer()`
   - **Description :** La fonction `drawPlayer` est responsable du rendu du personnage du joueur à l'écran. Elle joue un rôle vital dans la visualisation de l'avatar du joueur pendant le gameplay, contribuant à l'expérience utilisateur globale et à l'immersion dans le monde du jeu.

### 13. `SetUp()`
   - **Description :** La fonction `SetUp` sert de point de configuration initial pour le jeu. Elle est appelée au début de l'exécution du jeu pour établir des conditions et des paramètres essentiels, tels que l'initialisation des variables du jeu, la configuration de l'état initial du jeu et la préparation de l'environnement pour le gameplay.

### 14. `drawBall()`
   - **Description :** Cette fonction est responsable du rendu de la balle de jeu à l'écran. Elle contribue à la représentation visuelle des éléments de gameplay, affichant spécifiquement la position et le mouvement de la balle pendant le jeu

.

### 15. `drawBird(Position position)`
   - **Description :** La fonction `drawBird` rend un oiseau à la position spécifiée à l'écran. Cette fonction est probablement associée à des éléments visuels tels que des sprites animés, améliorant l'esthétique et la diversité des personnages dans le jeu.

### 16. `drawCurserAction(Position position)`
   - **Description :** Responsable du rendu de l'action du curseur en fonction de la position donnée, `drawCurserAction` représente visuellement la rétroaction ou l'action associée à l'emplacement actuel du curseur. Cette fonction améliore les interactions de l'interface utilisateur, fournissant des indices visuels au joueur.

### 17. `PauseEvents(SDL_Event event)`
   - **Description :** La fonction `PauseEvents` gère les événements liés à la mise en pause du jeu. Elle est cruciale pour la gestion des événements liés à l'entrée utilisateur pendant l'état de pause, permettant aux joueurs d'interagir avec les menus de pause ou d'effectuer des actions spécifiques pendant que le jeu est temporairement arrêté.

### 18. `Menu_1_Events(SDL_Event event)`
   - **Description :** Conçue spécifiquement pour gérer les événements liés à la navigation et à la sélection du menu, `Menu_1_Events` gère les événements d'entrée utilisateur dans le menu principal. Elle joue un rôle central dans la réponse aux interactions du joueur, facilitant une navigation fluide à travers les options de menu.

### 19. `ListMenuEventsSelect(SDL_Event event)`
   - **Description :** La fonction `ListMenuEventsSelect` est dédiée à la gestion des événements liés à la sélection d'options dans le menu des niveaux. Elle répond aux événements d'entrée utilisateur, permettant aux joueurs de naviguer et de choisir des niveaux ou des options spécifiques présentés dans le menu.

### 20. `PauseGameRender()`
   - **Description :** Responsable du rendu de l'écran de pause pendant le jeu, `PauseGameRender` présente visuellement la superposition de pause et les éléments associés. Cette fonction contribue à créer une représentation visuelle distincte pendant l'état de pause, améliorant l'interface utilisateur globale.

### 21. `CheckCollision(Position a, Position b, float width, float height)`
   - **Description :** La fonction `CheckCollision` joue un rôle crucial dans la détection de collisions. Elle vérifie la collision entre deux objets en fonction de leurs positions et dimensions. Les paramètres de largeur et de hauteur représentent probablement les dimensions des objets en collision, et la fonction renvoie un booléen indiquant si une collision s'est produite.

### 22. `CheckBlockCollision(Position nextPosition)`
   - **Description :** Axée sur la vérification de la collision avec un bloc à la prochaine position spécifiée, `CheckBlockCollision` fait partie du système de détection de collisions. Elle est spécifiquement conçue pour détecter des interactions ou des collisions impliquant des blocs dans l'environnement de jeu.

### 23. `IndexToRealPos(int index)`
   - **Description :** La fonction `IndexToRealPos` sert de convertisseur, traduisant une valeur d'index en la position réelle correspondante. Cette conversion est cruciale pour associer des valeurs d'index abstraites à des coordonnées ou positions réelles dans l'environnement de jeu.

### 24. `ballCollision()`
   - **Description :** La fonction `ballCollision` gère les collisions impliquant la balle de jeu. Elle gère probablement la physique ou la logique associée aux interactions de la balle, déterminant le résultat des collisions avec d'autres éléments de jeu, tels que le joueur ou les obstacles.

### 25. `SpriteUpdateAnimation(Sprite *sprite)`
   - **Description :** Axée sur la mise à jour de l'animation d'un sprite donné, `SpriteUpdateAnimation` contribue à la représentation visuelle dynamique des éléments de jeu animés. Elle est probablement associée à la gestion de feuilles de sprites ou de séquences, améliorant la fluidité et le réalisme des animations basées sur les sprites.

### 26. `RenderLevelsMenu()`
   - **Description :** La fonction `RenderLevelsMenu` est dédiée au rendu du menu des niveaux, affichant les niveaux disponibles et les options associées. Elle contribue au système de menu global, permettant aux joueurs de parcourir et de sélectionner des niveaux spécifiques ou de naviguer à travers du contenu lié aux niveaux supplémentaires.

### 27. `drawSprite(Sprite *sprite)`
   - **Description :** Responsable du rendu d'un sprite à l'écran, `drawSprite` présente visuellement un sprite à la position spécifiée. Elle est essentielle pour mettre en valeur divers éléments de jeu, personnages ou objets, ajoutant une dimension graphique à l'expérience de jeu globale.

### 28. `renderReachedStage(int stage)`
   - **Description :** La fonction `renderReachedStage` est responsable du rendu des informations sur le stage ou le niveau atteint dans le jeu. Elle contribue probablement à afficher des détails pertinents ou des retours d'information, améliorant la conscience du joueur de sa progression dans le jeu.

### 29. `GamePlayUpdate()`
   - **Description :** Axée sur la mise à jour des éléments liés au gameplay, `GamePlayUpdate` est une fonction distincte qui gère spécifiquement les éléments liés au gameplay principal. Elle inclut probablement la mise à jour des scores, la vérification des collisions et la gestion d'autres mécaniques essentielles pour les éléments interactifs du jeu.

### 30. `MenuUpdate()`
   - **Description :** Servant de contrepartie à `GamePlayUpdate`, la fonction `MenuUpdate` est conçue pour mettre à jour les éléments liés au menu. Cela inclut la gestion des animations, le traitement de l'entrée utilisateur dans les menus et la mise à jour des éléments visuels associés au système de menus du jeu.

### 31. `LevelData *loadLevelDataFromFile(const char *filename)`
   - **Description :** La fonction `loadLevelDataFromFile` est essentielle au système de chargement de niveaux du jeu. Elle lit et analyse les données du niveau à partir d'un fichier spécifié, renvoyant une structure de données (probablement `LevelData`) contenant des informations sur la disposition, les obstacles et d'autres détails pertinents du niveau chargé.

### 32. `cJSON *loadJSONFromFile(const
char *filename)`
   - **Description :** Axée sur le chargement des données JSON à partir d'un fichier, la fonction `loadJSONFromFile` est essentielle pour gérer les fichiers de configuration ou de données au format JSON. Elle utilise probablement une bibliothèque d'analyse JSON (comme cJSON) pour lire et interpréter les données, fournissant une représentation structurée pour une utilisation ultérieure dans le jeu.

### 33. `renderScoreScreen()`
   - **Description :** La fonction `renderScoreScreen` est responsable du rendu de l'écran qui affiche le score du joueur. Elle inclut probablement des informations supplémentaires ou des éléments visuels liés à la performance du joueur, créant un affichage complet à la fin du gameplay.

### 34. `renderScoreOnWinScreen(int score, int x, int y)`
   - **Description :** Similaire à `renderScore`, cette fonction se spécialise dans le rendu du score du joueur sur l'écran de victoire. Elle permet un rendu personnalisé du score à des coordonnées spécifiques (x, y) pendant des états de jeu spécifiques, améliorant la présentation visuelle des réalisations du joueur.

### 35. `saveHighestScore()`
   - **Description :** La fonction `saveHighestScore` est responsable de la persistance du score le plus élevé atteint par le joueur. Elle implique probablement l'écriture du score le plus élevé sur un support de stockage (comme un fichier ou une base de données) pour conserver l'accomplissement du joueur à travers plusieurs sessions de jeu.

### 36. `int loadHighScores()`
   - **Description :** Axée sur le chargement et la récupération des meilleurs scores, la fonction `loadHighScores` lit probablement et renvoie une liste de meilleurs scores à partir d'un support de stockage. Cette fonction joue un rôle dans le maintien et l'affichage d'un classement ou d'un tableau des meilleurs scores dans le jeu, offrant une notion de compétition et de réussite aux joueurs.

### 37. `HandelEvents()`
   - **Description :** Servant de centre central pour la gestion des événements, `HandelEvents` gère divers événements de jeu, y compris les événements d'entrée pendant le gameplay et les menus. Elle joue un rôle central dans la réponse aux actions des joueurs, facilitant une interaction fluide et assurant que le jeu réponde de manière appropriée à l'entrée utilisateur.

### 38. `RenderGame()`
   - **Description :** La fonction `RenderGame` est responsable du rendu de l'ensemble de l'écran de jeu. Elle englobe la présentation visuelle de tous les éléments du jeu, y compris les personnages, les obstacles, les menus et d'autres composants pertinents. Cette fonction contribue à créer une expérience de jeu immersive et visuellement attrayante.

### 39. `Update()`
   - **Description :** En tant que fonction centrale pour la mise à jour de l'état du jeu, `Update` est responsable de la gestion de la logique globale du jeu et des transitions d'état. Elle joue un rôle crucial dans la coordination des mises à jour de gameplay et de menus, assurant une expérience de jeu cohésive et dynamique.

### 40. `float TimeLeft()`
   - **Description :** La fonction `TimeLeft` calcule et renvoie le temps restant dans le jeu. Elle est essentielle pour les mécanismes de jeu basés sur le temps, permettant au jeu de suivre et d'afficher le temps restant pendant le gameplay. Cette fonction influence les événements et les défis liés au temps dans le jeu.

### 41. `gameOverScreen()`
   - **Description :** La fonction `gameOverScreen` est responsable de l'affichage de l'écran de fin de jeu. Elle présente probablement des informations pertinentes, telles que le score final du joueur, les réalisations et les options pour continuer ou redémarrer le jeu. Cette fonction contribue à une conclusion satisfaisante et informative de l'expérience de jeu.


1. **Boucle de jeu :**
   - La boucle de jeu est encapsulée dans `while (playing)` et sert de battement de cœur du programme. Tant que la variable `playing` reste à `true`, la boucle continue à s'exécuter.
   - À l'intérieur de la boucle, les événements sont traités (`HandelEvents()`), la logique du jeu est mise à jour (`Update()`) et l'écran de jeu est rendu (`RenderGame()`).
   - Le délai contrôlé (`SDL_Delay(Frame)`) régule le taux d'images, empêchant la boucle de s'exécuter trop rapidement.

2. **Traitement des événements

 (`HandelEvents()`):**
   - La fonction `HandelEvents()` est responsable de la capture et de la réponse aux événements SDL. Elle inclut une logique pour gérer les événements de sortie (`SDL_QUIT`) et les pressions de touches (`SDL_KEYDOWN`).
   - La gestion des événements est cruciale pour l'interaction du joueur et la direction du personnage du jeu.

4. **Mise à jour de la logique du jeu (`Update()`):**
   - La fonction `Update()` gère les aspects dynamiques de la logique du jeu. Dans le code fourni, elle inclut la progression des événements in-game et les mises à jour du chronomètre du jeu (`GameTimeClock()`).
   - La logique du jeu est responsable de garantir que l'état du jeu évolue au fil du temps.

5. **Rendu (`RenderGame()`):**
   - `RenderGame()` coordonne le rendu de l'ensemble de l'écran de jeu. Elle appelle d'autres fonctions de rendu (`makeGread()`, `RenderMap()`, `drowPlayer()`) pour représenter visuellement le monde du jeu.
   - Le rendu se produit après le traitement des événements et les mises à jour de la logique du jeu, assurant que le joueur voit l'état de jeu le plus récent.

6. **Phase de terminaison (`EndGame()`):**
   - Une fois que la boucle de jeu se termine (lorsque `playing` devient `false`), la fonction `EndGame()` est appelée pour effectuer des tâches de nettoyage. Elle libère les ressources SDL, garantissant une fermeture propre du jeu.
   - L'instruction `return 0;` signifie une exécution réussie du programme.

La structure de la fonction `main()` établit une séquence bien définie d'actions, de l'initialisation à la terminaison, fournissant un flux clair et organisé pour l'exécution du jeu. Cette conception garantit une expérience de jeu réactive et visuellement cohérente pour le joueur.


# Version ENG
---

# Introduction to Snoopy's Magic Show (1990)

Welcome to "Snoopy's Magic Show," a captivating and nostalgic game that takes you back to the magical world of the 1990s. Developed using the C programming language with the SDL library, this game brings the beloved Peanuts character, Snoopy, to the forefront in an enchanting and whimsical adventure.

**Game Concept:**
"Snoopy's Magic Show" immerses players in the charming world of Snoopy, where magic and mystery abound. Set against a backdrop inspired by the iconic Peanuts comic strip, players navigate Snoopy through a grid-based environment, encountering magical challenges and delightful surprises.

**Objective:**
As Snoopy, your mission is to dazzle the audience with a spectacular magic show. To achieve this, you must navigate Snoopy through the magical grid, solving puzzles, collecting magical artifacts, and avoiding obstacles. The game's objective is to entertain and captivate the audience by successfully completing magic tricks within a given time frame.

**Development Details:**
Developed using the C programming language and the SDL library, "Snoopy's Magic Show" pays homage to the retro gaming era of the 1990s. The utilization of SDL facilitates smooth graphics rendering and event handling, ensuring an engaging and responsive gameplay experience.

# Programe :

## Variables:

1. **box**: Represents the size of each grid box on the game screen.

2. **HIEGHT, WIDTH**: Define the height and width of the game grid in terms of grid boxes. They determine the overall size of the game area.

3. **playing**: A boolean variable that indicates whether the game is currently running. When set to `true`, the game loop continues; otherwise, it ends.

4. **Frame**: Specifies the delay between frames in the game loop. It controls the frame rate and influences the speed of animations and updates.

5. **timerColor**: A 2D array storing RGB values for different timer colors. It allows the timer to change color based on the remaining time.

6. **indexTimerColor**: An index used to select the appropriate color from `timerColor` based on the remaining time. It ensures a smooth transition of colors.

7. **window, render**: SDL window and renderer objects. The window represents the game window, while the renderer is responsible for drawing graphics on the window.

8. **Snoppy**: A structure representing the player. It contains the player's position (`pos`), remaining lives (`lives`), and the last direction moved (`lastDirection`).

9. **GameTimer**: A structure representing the game timer. It includes properties such as total time (`Totale`), time decrement value (`dec`), dimensions (`h` and `w`), and the current time remaining (`time`).

10. **blockMap**: A structure storing block positions on the game grid. It contains an array of `Position` structures (`pos`) and the number of blocks (`nbr`).

11. **totaleTime**: Represents the total time for a game cycle. It decreases as the game progresses.

## Functions:

### `EndGame()`

The `EndGame()` function is pivotal for orchestrating the graceful closure of the game. As the final act in the game's lifecycle, its primary purpose is to properly manage and clear SDL resources. The function begins by executing `SDL_RenderClear(render)`, erasing the contents of the renderer. Subsequently, it calls `SDL_DestroyRenderer(render)` and `SDL_DestroyWindow(window)`, meticulously clearing the renderer and window, respectively. This step-by-step dismantling of graphical components ensures that no lingering artifacts remain. Finally, the function culminates with `SDL_Quit()`, signaling the comprehensive termination of SDL and releasing any global resources it may have acquired. The meticulous execution of `EndGame()` guarantees a clean shutdown, averting potential memory leaks and resource-related issues.

### `makeTimer()`

The `makeTimer()` function is tasked with visually representing the game timer on the screen. It dynamically draws the timer by configuring different rectangles with varying colors, creating a visual representation of the time remaining in the game cycle. The function utilizes RGB values stored in `timerColor` to differentiate between different time intervals, transitioning smoothly as the timer decreases. By rendering these rectangles on the screen, `makeTimer()` provides players with a clear and intuitive visual cue regarding the passage of time within the game.

### `makeGread()`

In the `makeGread()` function, the visual elements of the game environment come to life. Its purpose extends beyond mere aesthetics, as it meticulously draws the game grid, timer, map, and player on the screen. The function begins by loading a grid image using SDL_LoadBMP() and creates a texture from the surface. Subsequently, it renders the grid, employing nested loops to draw additional visual elements, such as white rectangles and the game timer. By combining these visual components, `makeGread()` creates a visually immersive game environment, setting the stage for player interaction.

### `RenderMap()`

`RenderMap()` is responsible for rendering blocks on the game grid based on the positions specified in the `blockMap` structure. Using SDL_LoadBMP() and SDL_CreateTextureFromSurface(), the function loads block images and creates textures for rendering. It then iterates through the positions in `blockMap`, drawing individual blocks on the screen. By dynamically rendering these blocks, `RenderMap()` visually communicates the layout of obstacles or challenges within the game, contributing to the overall gameplay experience.

### `GameTimeClock()`

The `GameTimeClock()` function plays a crucial role in managing the game timer. It updates the total time remaining in the game cycle, decrementing it based on elapsed time. By evaluating the variable `totaleTime` and adjusting the `GameTimer.Totale` property, the function ensures that the timer accurately reflects the progression of time within the game. This time management is vital for triggering events or transitions based on time constraints, contributing to the overall dynamics of the gameplay.

### `GetPlayerPosition()`

The `GetPlayerPosition()` function serves as a utility for retrieving the current grid position of the player. By calculating grid coordinates from the player's pixel coordinates, the function returns a `Position` structure containing the player's location within the game grid. This information is crucial for various game logic elements that rely on the player's position.

### `SetPlayerPositionTo(int nextX, int nextY)`

The `SetPlayerPositionTo()` function is responsible for updating the player's position within the game grid. It takes parameters `nextX` and `nextY`, representing the desired grid coordinates for the player. Before updating the position, the function may perform additional logic, such as checking boundaries to ensure the player remains within the valid game area. Upon verification, the player's position is updated, and the function contributes to the dynamic movement of the player character within the game.

### `SetUp()`

The `SetUp()` function is a crucial setup routine for initializing the initial game state. It configures various aspects of the game, including the properties of the game timer (`GameTimer`), the initial block positions (`blockMap`), and the starting position of the player (`Snoppy`). Additionally, it allocates memory for the block positions using `calloc()` and sets up the initial position for the player. By executing these initialization steps, `SetUp()` establishes the foundational elements required for a coherent and engaging gameplay experience.

### `RenderGame()`

`RenderGame()` orchestrates the rendering of the entire game screen. By coordinating various rendering functions, such as `makeGread()`, `RenderMap()`, and `drowPlayer()`, it ensures that the complete game environment is visually presented to the player. This comprehensive rendering process contributes to the real-time visualization of game elements, maintaining a dynamic and responsive display that reflects the evolving game state.

### `Update()`

The `Update()` function plays a central role in managing the dynamic aspects of the game logic. While the specifics of the logic depend on the game's design, `Update()` typically handles the progression of in-game events and updates critical elements such as the game timer. This function ensures that the game state evolves over time, responding to player input and triggering relevant events or transitions.

### `HandelEvents()`

`HandelEvents()` is responsible for handling SDL events, particularly user input from the keyboard. Within the SDL event loop, it listens for events such as key presses and responds accordingly. In the context of the provided code, it checks for SDL_QUIT events, indicating a request to close the game, and SDL_KEYDOWN events, allowing the player to control the movement of the character. By processing these events, `HandelEvents()` enables user interaction with the game, translating keyboard input into meaningful actions within the game world.

### `main()`

The `main()` function serves as the entry point and heartbeat of the entire program, constituting the game loop. It begins by initializing SDL, creating the game window, and setting up the renderer. The `SetUp()` function is then called to initialize the initial game state. Subsequently, the program enters a continuous game loop (`while (playing) { ... }`), where events are handled (`HandelEvents()`), game logic is updated (`Update()`), and the complete game screen is rendered (`RenderGame()`). The loop is controlled by the `playing` variable, and the SDL_Delay(Frame) function introduces a delay between frames, controlling the frame rate. The game loop continues until the `playing` variable is set to `false`. Finally, the `EndGame()` function is called to ensure a proper and clean shutdown of the game.
### `main()` Function Structure:

The `main()` function serves as the entry point and central orchestrator of the entire game. Its structure defines the initialization, game loop, and termination phases, creating a cohesive framework for the gameplay experience.

1. **Initialization Phase:**
   ```c
   int main(int argc, char **argv) {
       // Initialization of SDL and game window
       if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
           // Handle SDL initialization failure
           // ...
           return 1;
       }

       // Create the game window
       window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, box * WIDTH, HIEGHT * box, SDL_WINDOW_SHOWN);
       // Check window creation success
       if (window == NULL) {
           // Handle window creation failure
           // ...
           return 1;
       }

       // Create the renderer
       render = SDL_CreateRenderer(window, -1, 0);
       // Check renderer creation success
       if (render == NULL) {
           // Handle renderer creation failure
           // ...
           return 1;
       }

       // Set Up the initial game state
       SetUp();

       // Enter the game loop
       while (playing) {
           // Event handling
           HandelEvents();

           // Update game logic
           Update();

           // Render the game screen
           RenderGame();

           // Introduce delay for frame rate control
           SDL_Delay(Frame);
       }

       // End the game
       EndGame();

       return 0;
   }
   ```

### 1. `GetPlayerPosition()`
   - **Description:** This function retrieves the current position of the player within the game. It serves as a crucial utility for obtaining the player's coordinates on the screen, enabling other game systems and mechanics to access and react to the player's position dynamically. The position is typically represented as a structure or object containing X and Y coordinates.

### 2. `SetPlayerPositionTo(int x, int y)`
   - **Description:** The `SetPlayerPositionTo` function is responsible for updating and changing the player's position in the game to the specified coordinates (x, y). This function plays a vital role in handling various in-game events that necessitate the movement or repositioning of the player character.

### 3. `getStringUrlLevelByIndex(int index)`
   - **Description:** This function facilitates dynamic level loading by retrieving the URL associated with a given index. It is instrumental in obtaining the necessary level data or assets based on an index, allowing the game to seamlessly load different levels without hardcoding specific file paths. This enhances the flexibility and scalability of the game.

### 4. `EndGame()`
   - **Description:** The `EndGame` function gracefully terminates the game execution. It is typically called when the player decides to exit the game or when certain conditions are met. This function is responsible for performing cleanup tasks, releasing allocated resources, and ensuring a smooth exit from the game.

### 5. `renderDigit(int digit, int x, int y)`
   - **Description:** The `renderDigit` function is responsible for rendering a single digit on the screen at the specified coordinates (x, y). It contributes to the visual representation of numerical values, often used in rendering the player's score or other numeric information during gameplay.

### 6. `renderScore(int score, int x, int y, int width)`
   - **Description:** This function is pivotal in rendering the player's score on the game screen. By specifying the score value and the position (x, y), it visually displays the player's current score. The additional parameter, width, might be related to formatting or alignment aspects of the rendered score.

### 7. `makeTimer()`
   - **Description:** The `makeTimer` function is responsible for initializing and setting up a timer that tracks game time. It is an essential component for time-based game mechanics, enabling the game to monitor elapsed time during gameplay, possibly influencing events, challenges, or transitions.

### 8. `makeGrid()`
   - **Description:** The `makeGrid` function is crucial for establishing the foundational structure of the game. It creates and sets up the game grid, defining the playing area and layout. The grid is fundamental for organizing game elements, facilitating collision detection, and providing a structured environment for gameplay.

### 9. `makeMenu()`
   - **Description:** This function handles the rendering of the main menu in the game. It is responsible for visually presenting menu options, allowing players to navigate and interact with different sections of the game, such as starting a new game, accessing settings, or exiting the game.

### 10. `RenderMap()`
   - **Description:** The `RenderMap` function is responsible for rendering the game map during gameplay. It visualizes the current level layout, including obstacles, platforms, or other relevant structures. Rendering the map is crucial for providing players with a clear understanding of the game environment and challenges.

### 11. `GameTimeClock()`
   - **Description:** Managing the in-game clock and time-related functions, `GameTimeClock` plays a central role in tracking and updating the game clock. It is essential for time-based game mechanics, including time-limited challenges, events, or determining the overall duration of gameplay.

### 12. `drawPlayer()`
   - **Description:** The `drawPlayer` function is responsible for rendering the player character on the screen. It plays a vital role in visualizing the player's avatar during gameplay, contributing to the overall user experience and immersion in the game world.

### 13. `SetUp()`
   - **Description:** The `SetUp` function serves as the initial setup point for the game. It is called at the beginning of the game execution to establish essential conditions and parameters, such as initializing game variables, setting up the initial game state, and preparing the environment for gameplay.

### 14. `drawBall()`
   - **Description:** This function is responsible for rendering the game ball on the screen. It contributes to the visual representation of the gameplay elements, specifically displaying the ball's position and movement during the game.

### 15. `drawBird(Position position)`
   - **Description:** The `drawBird` function renders a bird at the specified position on the screen. This function is likely associated with visual elements such as animated sprites, enhancing the aesthetics and diversity of characters within the game.

### 16. `drawCurserAction(Position position)`
   - **Description:** Responsible for rendering the cursor action based on the given position, `drawCurserAction` visually represents the feedback or action associated with the cursor's current location. This function enhances user interface interactions, providing visual cues to the player.

### 17. `PauseEvents(SDL_Event event)`
   - **Description:** The `PauseEvents` function handles events related to pausing the game. It is crucial for managing user input events during the pause state, allowing players to interact with pause menus or perform specific actions while the game is temporarily halted.

### 18. `Menu_1_Events(SDL_Event event)`
   - **Description:** Specifically designed for handling events related to menu navigation and selection, `Menu_1_Events` manages user input events within the main menu. It plays a central role in responding to player interactions, facilitating smooth navigation through menu options.

### 19. `ListMenuEventsSelect(SDL_Event event)`
   - **Description:** The `ListMenuEventsSelect` function is dedicated to handling events related to selecting options within the levels menu. It responds to user input events, allowing players to navigate and choose specific levels or options presented in the menu.

### 20. `PauseGameRender()`
   - **Description:** Responsible for rendering the pause screen during the game, `PauseGameRender` visually presents the pause overlay and associated elements. This function contributes to creating a distinct visual representation during the pause state, enhancing the overall user interface.

### 21. `CheckCollision(Position a, Position b, float width, float height)`
   - **Description:** The `CheckCollision` function plays a critical role in collision detection. It checks for collision between two objects based on their positions and dimensions. The width and height parameters likely represent the dimensions of the colliding objects, and the function returns a boolean indicating whether a collision has occurred.

### 22. `CheckBlockCollision(Position nextPosition)`
   - **Description:** Focused on checking for collision with a block at the next specified position, `CheckBlockCollision` is part of the collision detection system. It is specifically tailored for detecting interactions or collisions involving blocks within the game environment.

### 23. `IndexToRealPos(int index)`
   - **Description:** The `IndexToRealPos` function serves as a converter, translating an index value into the corresponding real position. This conversion is crucial for associating abstract index values with actual coordinates or positions within the game environment.

### 24

. `ballCollision()`
   - **Description:** The `ballCollision` function handles collisions involving the game ball. It likely manages the physics or logic associated with ball interactions, determining the outcome of collisions with other game elements, such as the player or obstacles.

### 25. `SpriteUpdateAnimation(Sprite *sprite)`
   - **Description:** Focused on updating the animation of a given sprite, `SpriteUpdateAnimation` contributes to the dynamic visual representation of animated game elements. It is likely associated with managing sprite sheets or sequences, enhancing the fluidity and realism of sprite-based animations.

### 26. `RenderLevelsMenu()`
   - **Description:** The `RenderLevelsMenu` function is dedicated to rendering the levels menu, displaying available levels and associated options. It contributes to the overall menu system, allowing players to browse and select specific levels or navigate through additional level-related content.

### 27. `drawSprite(Sprite *sprite)`
   - **Description:** Responsible for rendering a sprite on the screen, `drawSprite` visually presents a sprite at the specified position. It is essential for showcasing various game elements, characters, or objects, adding a graphical dimension to the overall gameplay experience.

### 28. `renderReachedStage(int stage)`
   - **Description:** The `renderReachedStage` function is responsible for rendering information about the reached stage or level within the game. It likely contributes to displaying relevant details or feedback, enhancing the player's awareness of their progress in the game.

### 29. `GamePlayUpdate()`
   - **Description:** Focused on updating gameplay-related elements, `GamePlayUpdate` is a distinct update function that specifically manages elements pertinent to the core gameplay. It likely includes updating scores, checking for collisions, and handling other mechanics essential for the game's interactive elements.

### 30. `MenuUpdate()`
   - **Description:** Serving as a counterpart to `GamePlayUpdate`, the `MenuUpdate` function is designed to update menu-related elements. This includes managing animations, handling user input within menus, and updating visual elements associated with the game's menu system.

### 31. `LevelData *loadLevelDataFromFile(const char *filename)`
   - **Description:** The `loadLevelDataFromFile` function is integral to the game's level-loading system. It reads and parses level data from a specified file, returning a data structure (likely `LevelData`) containing information about the layout, obstacles, and other relevant details of the loaded level.

### 32. `cJSON *loadJSONFromFile(const char *filename)`
   - **Description:** Focused on loading JSON data from a file, the `loadJSONFromFile` function is essential for handling configuration or data files in JSON format. It likely utilizes a JSON parsing library (such as cJSON) to read and interpret data, providing a structured representation for further use in the game.

### 33. `renderScoreScreen()`
   - **Description:** The `renderScoreScreen` function is responsible for rendering the screen that displays the player's score. It likely includes additional information or visual elements related to the player's performance, creating a comprehensive display at the end of gameplay.

### 34. `renderScoreOnWinScreen(int score, int x, int y)`
   - **Description:** Similar to `renderScore`, this function specializes in rendering the player's score on the win screen. It allows for customized rendering of the score at specific coordinates (x, y) during specific game states, enhancing the visual presentation of the player's achievements.

### 35. `saveHighestScore()`
   - **Description:** The `saveHighestScore` function is responsible for persisting the highest score achieved by the player. It likely involves writing the highest score to a storage medium (such as a file or database) to retain the player's accomplishment across multiple game sessions.

### 36. `int loadHighScores()`
   - **Description:** Focused on loading and retrieving high scores, the `loadHighScores` function likely reads and returns a list of high scores from a storage medium. This function plays a role in maintaining and displaying a leaderboard or high-score table within the game, providing a sense of competition and achievement for players.

### 37. `HandelEvents()`
   - **Description:** Serving as the central hub for event handling, `HandelEvents` manages various game events, including input events during gameplay and menus. It plays a pivotal role in responding to player actions, facilitating smooth interaction, and ensuring the game responds appropriately to user input.

### 38. `RenderGame()`
   - **Description:** The `RenderGame` function is responsible for rendering the entire game screen. It encompasses the visual presentation of all game elements, including characters, obstacles, menus, and other relevant components. This function contributes to creating an immersive and visually engaging gaming experience.

### 39. `Update()`
   - **Description:** As the central function for updating the game state, `Update` is responsible for managing the overall game logic and state transitions. It plays a crucial role in coordinating gameplay and menu updates, ensuring a cohesive and dynamic gaming experience.

### 40. `float TimeLeft()`
   - **Description:** The `TimeLeft` function calculates and returns the remaining time in the game. It is integral for time-based game mechanics, allowing the game to track and display the time remaining during gameplay. This function influences time-sensitive events and challenges within the game.

### 41. `gameOverScreen()`
   - **Description:** The `gameOverScreen` function is responsible for displaying the game over screen. It likely presents relevant information, such as the player's final score, achievements, and options for continuing or restarting the game. This function contributes to a satisfying and informative conclusion to the gaming experience.

2. **Game Loop:**
   - The game loop is encapsulated within `while (playing)` and serves as the heartbeat of the program. As long as the `playing` variable remains `true`, the loop continues to execute.
   - Within the loop, events are handled (`HandelEvents()`), the game logic is updated (`Update()`), and the game screen is rendered (`RenderGame()`).
   - The controlled delay (`SDL_Delay(Frame)`) regulates the frame rate, preventing the loop from executing too quickly.

3. **Event Handling (`HandelEvents()`):**
   - The `HandelEvents()` function is responsible for capturing and responding to SDL events. It includes logic for handling quit events (`SDL_QUIT`) and key presses (`SDL_KEYDOWN`).
   - Event handling is crucial for player interaction and steering the game character.

4. **Game Logic Update (`Update()`):**
   - The `Update()` function manages the dynamic aspects of the game logic. In the provided code, it includes the progression of in-game events and updates to the game timer (`GameTimeClock()`).
   - The game logic is responsible for ensuring the game state evolves over time.

5. **Rendering (`RenderGame()`):**
   - `RenderGame()` coordinates the rendering of the entire game screen. It calls other rendering functions (`makeGread()`, `RenderMap()`, `drowPlayer()`) to visually represent the game world.
   - Rendering occurs after event handling and game logic updates, ensuring that the player sees the most up-to-date game state.

6. **Termination Phase (`EndGame()`):**
   - Once the game loop exits (when `playing` becomes `false`), the `EndGame()` function is called to perform cleanup tasks. It clears SDL resources, ensuring a clean shutdown of the game.
   - The `return 0;` statement signifies a successful program execution.

The structure of the `main()` function establishes a well-defined sequence of actions, from initialization to termination, providing a clear and organized flow for the execution of the game. This design ensures a responsive and visually coherent gameplay experience for the player.
