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