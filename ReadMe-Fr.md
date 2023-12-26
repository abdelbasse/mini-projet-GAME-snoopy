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

2. **Boucle de jeu :**
   - La boucle de jeu est encapsulée dans `while (playing)` et sert de battement de cœur du programme. Tant que la variable `playing` reste à `true`, la boucle continue à s'exécuter.
   - À l'intérieur de la boucle, les événements sont traités (`HandelEvents()`), la logique du jeu est mise à jour (`Update()`) et l'écran de jeu est rendu (`RenderGame()`).
   - Le délai contrôlé (`SDL_Delay(Frame)`) régule le taux d'images, empêchant la boucle de s'exécuter trop rapidement.

3. **Traitement des événements

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