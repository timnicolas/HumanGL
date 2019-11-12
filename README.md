# humanGL [[42](https://www.42.fr/) project]

![](../media/walk.gif?raw=true)

## Project
A first introduction to hierarchical modeling and model animation with OpenGL.

We used `glfw3` API for creating windows and manage input and events,
and `Assimp` to load the model.

## Installation

- Install `glfw` with brew

	```brew install glfw3```

- Install `assimp` with brew

	```brew install assimp```

- Compile the project

	```make -j8```
- Run the project

	```./humanGL 3dFile```

## Controls

- use `WASD QE` / `arrow` to move and `mouse` to look around
- use `Enter` to change **animation** if there is multiples
- use `mouse wheel` to change **animation speed**
- use `P` to **play/pause** animation
- use `M` to toggle **model** visibility
- use `N` to toggle **bones cubes** visibility
- use `Space` to unlock the cursor
- use `R` to reset position and speed
- use `esc` to quit

## Exemples

<!-- ![42.png](../media/42.png?raw=true) -->
paladin:

![](../media/paladin.png?raw=true)

paladin animation with cubes to show bones joints:

![](../media/fightBones.gif?raw=true)

---

See more on the school [subject](humangl.fr.pdf).
