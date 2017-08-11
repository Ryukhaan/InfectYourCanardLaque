# InfectYourCanardLaque
A video game to enhance programming skills.
Naive implementation. A lot remains to be done.

## Release
### Improvements
* PCG for map creation : Snow Field and Vulcano added.
* Weight decrease under stressed state has been adjusted.
* Grass tile has been recolored.

### Bug Corrections
* When a duck was between the border and an impassable tile, it swung between same wrong directions... no more !

# To Do List

* Refactoring

## Data Structure
* Map Structure (use Graph and Vertice/Tile);
* Duck Structure (LTexture as a common texture for ducks : Flyweight pattern. Write State Pattern for state);
* Spatial Data Struture (Reduce O(n^2) for distance beetween ducks in model update);
* Other stuffs

## Useability
* Introduce new food.
* Display Map's timer.
* Display cursor.

## Graphical
* Improve tiles colors.
* Add more tiles.

## IA for Generative Map
~~Improve map creating procedure. See Map/Graph structure.~~

## IA for Fatty Duck
Improve all duck's movements. Decision-Tree or RL algorithm (POMDP) in mind.
