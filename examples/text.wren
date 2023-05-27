var WIDTH = 320
var HEIGHT = 240
var TITLE = "My Game"
var TEXT_SURFACE = Surface.new(WIDTH, HEIGHT)

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

        Surface.set_target(TEXT_SURFACE)
        Draw.clear()
        Draw.text(WIDTH / 2, HEIGHT / 2, "Hello World!", Color.BLACK)
        Surface.reset_target()

        __text_angle = 0
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        __text_angle = __text_angle + (Num.pi / 4 * dt)
        __text_angle = __text_angle % (2 * Num.pi)
        Draw.clear()
        Surface.draw_angle(TEXT_SURFACE, WIDTH / 2 , HEIGHT / 2, __text_angle)
        Draw.text(10, 10, ":^)", Color.BLUE)
    }
}
