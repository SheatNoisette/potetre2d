var WIDTH = 320
var HEIGHT = 240
var TITLE = "Surface Demo"

/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init() {
        System.print("Picogine Init!")
        Engine.init(WIDTH, HEIGHT, TITLE)
        Draw.clear()

        // Draw to the surface
        __custom_surface = Surface.new_surface(32, 32)
        Surface.set_target(__custom_surface)
            for (x in 0..32) {
                for (y in 0..32) {
                    Draw.put_pixel(x, y,
                        Random.irange(0, 255),
                        Random.irange(0, 255),
                        Random.irange(0, 255)
                    )
                }
            }
        Surface.reset_target()

        __current_rotation = 0
    }

    /*
    ** Called every frame
    */
    static tick() {
        Draw.clear()
        Surface.draw_surface_rotated(__custom_surface, WIDTH / 2, HEIGHT / 2,
            Math.deg2rad(__current_rotation)
        )
        __current_rotation = __current_rotation + 1
    }
}
