**Snake Game in C**

A fully functional Snake Game implemented in C, featuring a clear terminal interface, dynamic gameplay mechanics, and a persistent scoreboard. The game offers a nostalgic experience while showcasing effective use of classic C programming constructs.

*🎮 Game Features*

Terminal-based Interface: Clear and responsive console graphics.

Dynamic Snake Growth: The snake grows longer each time it eats a fruit.

Increasing Difficulty: Snake speed increases as it grows.

Fruit Spawning: Fruits (F) appear randomly on the screen using rand().

Edge Wrapping: The snake wraps from one screen edge to the opposite.

Collision Detection: The game ends when the snake collides with itself.

Scoreboard: Keeps track of the player's score in real-time.

*🐍 Gameplay Overview*

The snake is represented by a series of characters (O) that move across the screen.

Each fruit collected increases the snake's length and score.

Speed ramps up, making gameplay progressively harder.

The game ends if the snake runs into itself.

*🖥️ Controls*


W — Move Up

S — Move Down

A — Move Left

D — Move Right

*⚙️ How It Works*

Snake Movement: Implemented using a dynamic array or queue-like structure to track the head and tail positions.

Fruit Generation: Uses rand() from <stdlib.h> to generate new fruit coordinates on the board.

Edge Wrapping: Snake reappears on the opposite edge when it crosses screen boundaries.

Collision Logic: Checks if the head position matches any body part.

Speed Control: Utilizes delays (e.g. usleep() or Sleep() depending on platform) that decrease as score increases.

*🧾 Scoreboard*

Real-time scoring is displayed during the game.

High scores can be saved and optionally loaded from a file (if implemented).

Scores are based on the number of fruits collected.
