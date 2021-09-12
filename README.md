# DINODUDE

This project represents the life of a dinosaur. It was completed in September 2021 as part of the 42 school cursus. The goal was to develop a 2D game, with MiniLibX, in which the player needed to collect collectibles before going to the exit.

All modifications must respect the [42 norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

## How to play

You start out as a green dinosaur with the objective of collecting/eating all the chickens and only then you find a partner to share the meal. You can choose any one of them if there is more than one red dinosaur. The goal is to finish with as few moves as possible.

  - DinoDude - <img alt="DinoDude" width="3%" src="https://github.com/Magueija/dinodude/blob/main/sprite/dino_right.png" />
  - Chicken - <img alt="Chicken" width="3%" src="https://github.com/Magueija/dinodude/blob/main/sprite/chicken.png" />
  - Other Dinosaur - <img alt="Other Dinosaur" width="3%" src="https://github.com/Magueija/dinodude/blob/main/sprite/dino_girl.png" />

You move using `W`, `A`, `S`, `D` and you can quit the game using `Esq`.

You can use the maps in *./test/* folder, but they can also be created by you. So create your maps and challenge your friends!
If you have created a map, feel free to add it to the program or contact me and I will gladly add it. :)

Here is an example of gameplay :
<div>
  <img alt="Gameplay" width="45%" src="https://github.com/Magueija/gameplay/blob/main/sprite/dinodude_gameplay.mkv" />
</div>

### Map rules

The program must take as an argument a map description file with the '.ber' extension.
  - The map must be composed of only 5 possible characters: **0** for an empty space, **1** for a wall, **C** for a collectible, **E** for map exit and **P** for the player’s starting position.
  - This is a simple valid map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```
  - The map must be closed/surrounded by walls.
  - The map must have at least one exit, one collectible, and one starting position.
  - The map must be rectangular.

## Getting Started

Run the command `make` to create the **dinodude** executable. See the exemple bellow :
```
git clone https://github.com/Magueija/dinodude.git dinodude
cd dinodude
git submodule update --init --recursive
make
./dinodude <path-to-map-file.ber>
```

## Authors

  - **[Magueija](https://github.com/Magueija)**

## Map Creators

  - **[Magueija](https://github.com/Magueija)**
