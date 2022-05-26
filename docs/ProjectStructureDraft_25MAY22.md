# project outliner

## details
- started sometime around 9:30am 25th may 2022
- junked soemtime around 11:30am 25th may 2022

------------------------
------------------------

##  Classes/Objects/Modules

------------------------
------------------------

### Lattice
- has 2d array of `Cell` pointers
- mediator pattern for `Cell`
    - https://refactoring.guru/design-patterns/mediator
- mediator pattern for `CellList` ?? (assuming we use `CellList`)

------------------------

### Cell
- has draw location/dimensions
    - maybe yoink from `Shape` or `Rectangle`
    `int x;`
    `int y;`
    `int width;`
    `int height;`
- had location/coordination information

------------------------

### Tile
- has information for painting/drawing
- maybe it's a strategy pattern and is just a tile behaviour + shape
`char *name`
- have `TilePrefList` which is list of `TilePref`
    
------------------------

#### CellList
- list with iterable thingy for cells
- able to `operator+=(Cell c)` to add

------------------------

#### TilePref
`[enumType],[TileAttribute],[prefValue]`
- has a preference with a type, which tile attribute this effects, and how
    e.g.: `pref(PrefType::minDistanceFrom, TileAttribute::waterTile, 1)`
    --> would specify that a tile cant be within 1 space(s) of a tile with attribute `waterTile`

------------------------



------------------------



------------------------



------------------------
------------------------
