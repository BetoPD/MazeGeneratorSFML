<h1>¿Cómo usar?</h1>
<p>Guía paso a paso de como instalar la librería</p>
<a>https://www.sfml-dev.org/tutorials/2.6/</a>
<p>Para ejecutar en VSCODE</p>


<h3>Mac Os</h3>
<p>
clang++ main.cpp -I/Library/Frameworks/SDL2.framework/Headers -I./glad/include -F/Library/Frameworks -framework SDL2

g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

g++ main.cpp Maze.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
</p>