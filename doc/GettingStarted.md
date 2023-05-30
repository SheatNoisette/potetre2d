# Getting started with Potetre2D

Potetre2D is a 2D game engine written in C. It is designed to be simple and
compact, and is made to be used with the [Wren](https://wren.io) scripting
language. As some French people may have noticed, the name is a pun on the
French word "Peut-être" (`maybe`), as when the engine was first made, we were
unsure if we could make a game engine that could fit less than 4Mb (And
the orignal name, Picogine, was already taken).

First, you need to download the latest release of Potetre2D. You can find the
latest release on the `Releases` page of the GitHub repository. You can also
build the project yourself, see [BUILDING.md](BUILDING.md) for instructions
on how to build the project.

## Creating a project
The first thing you need to do is to create a project. To do so, you need to
create a folder and copy the `potetre2d` executable in it. Then, you need to
create a `game.wren` file in the same folder. This file will be the entry point
of your game.

Open the `game.wren` file with your favorite text editor, and write the
following code:
```wren
var WIDTH = 320
var HEIGHT = 240
var TITLE = "My Game"

/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        System.print("Picogine Init!")
        Engine.init(WIDTH, HEIGHT, TITLE)
        Draw.clear()
    }

    /*
    ** Called every frame
    */
    static tick(dt) {

    }
}
```

The class `Game` is the entry point of your game. The `init` method is called
when the game is started, and the `tick` method is called every frame if
the engine is initialized (using the `Engine.init` method). If the engine
is not initialized, the `tick` method will not be called and no window will
be created. You can use this to create a command line program that can be
used to generate assets for your game for example.

The `dt` parameter is the time elapsed since the last frame. This is useful
to make your game run at the same speed on every computer. If the engine
can't figure out the screen refresh rate, it will run at the fastest speed
possible. Be careful!

## Running the game
Execute the `potetre2d` executable. If everything went well, you should see
a window with a white background. If the window is too small, you can resize
i, it will automatically scale the game to fit the window.

Nothing happens? You may need to update your graphics drivers, the engine
backend (Tigr) requires OpenGL 3.3 or later.

## Drawing something
Now that you have a window, you may want to draw something on it. To do so,
we're going to use the `Surface` module.

A surface is a 2D canvas that can be drawn on the screen, see this as a
piece of paper that you can draw on. To create a surface, you can use the
`Surface.new` method:
```wren
var surface = Surface.new(32, 32)
```
This will create a 32x32 pixels surface. You can also create a surface from an
image file:
```wren
var surface = Surface.new_from_png("my_image.png")
```
In this case, the engine will load a PNG image from the file `my_image.png` and
create a surface from it. The image will be converted to a 32 bits RGBA image
if it is not already in this format.

Now that we have a surface, we can draw it on the screen. To do so, we need to
use the `draw` method of the Surface module:
```wren
Surface.draw(surface, 0, 0)
```
This will draw the surface at the position (0, 0) on the screen. The position
is relative to the top left corner of the screen. Don't forget to clear the
screen before drawing anything, otherwise you will see the previous frame
drawn on the screen.

Our code now looks like this:
```wren
var WIDTH = 320
var HEIGHT = 240
var TITLE = "My Game"

var surface = Surface.new_from_png("my_image.png")

/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        System.print("Picogine Init!")
        Engine.init(WIDTH, HEIGHT, TITLE)
        Draw.clear()
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        Draw.clear()
        Surface.draw(surface, 0, 0)
    }
}
```

## To infinity and beyond!
Now that you have a window and can draw something on it, you can start making
your game. See the cheat sheet for a list of all the functions available
[here](CheatSheet.md).

