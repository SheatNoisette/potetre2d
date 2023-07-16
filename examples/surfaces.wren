var WIDTH = 320
var HEIGHT = 240
var TITLE = "Surface Demo"

var BACKGROUND_SURFACE = Surface.new(WIDTH / 2, HEIGHT / 2)
var SPRITE_SURFACE = Surface.new_from_png("files/sprite.png")

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

        // Get pixel data from a surface
        var color = Draw.get_pixel(0, 0)
        System.print("Color: %(color)")

        // Draw to the surface
        __custom_surface = Surface.new(32, 32)
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

        // Resize surface, because why not
        Surface.resize(__custom_surface, 64, 32)

        __current_rotation = 0
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        Draw.clear()

        // On the fly surface modification
        Surface.set_target(BACKGROUND_SURFACE)
            for (x in 0..WIDTH) {
                for (y in 0..HEIGHT) {
                    Draw.put_pixel(x, y,
                        (__current_rotation * 2) % 255,
                        (__current_rotation * 3) % 255,
                        (__current_rotation * 4) % 255
                    )
                }
            }
        Surface.reset_target()

        // Draw the surfaces
        Surface.draw_angle(BACKGROUND_SURFACE,  WIDTH / 2, HEIGHT / 2, __current_rotation / 2)
        Surface.draw_angle(__custom_surface, WIDTH / 2, HEIGHT / 2,
            Math.deg2rad(__current_rotation)
        )
        Surface.draw(SPRITE_SURFACE, WIDTH / 2, HEIGHT / 2, (__current_rotation / 360))

        // Update the rotation
        __current_rotation = __current_rotation + 1
        if (__current_rotation > 360) {
            __current_rotation = 0
        }
    }
}
