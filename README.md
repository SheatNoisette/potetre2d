# Potetre2d

L'as tu faite? Potetre
---

A really small (in size) game engine for 2D games, made originally for the
4Mb Game Jam. We were disappointed by the lack of 2D game engine that could
fit in 4Mb, so we made one. The objective of this project is to make a Löve2D
like engine, but with a smaller footprint. We didn't wanted to write bare
C code, so any game written with this engine are written in Wren.

Features:
- Around 128kb of executable size
- Cross platform: Windows (7+) x86_64, macOS 11.0+ ARM/x86_64 and Linux
- Wren scripting
- PNG File loading
- File compression
- File reading/writing
- Perlin Noise generation
- Headless mode (No window, no graphics, only scripting)

Quick example of the API:
```wren
var WIDTH = 320
var HEIGHT = 240
var TITLE = "Random screen"

class Game {
    /* Called when the game is started */
    static init(args) {
        System.print("Picogine Init!")
        Engine.init(WIDTH, HEIGHT, TITLE)
    }

    /* Called every frame if Engine the engine is initialized */
    static tick(dt) {
        if (Input.is_key_pressed(Keycodes.ESCAPE)) {
            Engine.destroy()
        } else {
            // Random pixel
            for (x in 0..WIDTH) {
                for (y in 0..HEIGHT) {
                    Draw.put_pixel(x, y,
                        Random.rand() * 255,
                        Random.rand() * 255,
                        Random.rand() * 255
                    )
                }
            }
        }
    }
}
```

## Building

See [BUILDING.md](BUILDING.md) for instructions on how to build the project.

## License
This project is licensed under the LGPLv3-only License - see the
[LICENSE](LICENSE) file for details.

Only exception are examples (in the `examples/` folder) are public domain.
