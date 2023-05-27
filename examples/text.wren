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

        __y_text = 0
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        __y_text = __y_text + (5 * dt)
        __y_text = __y_text % 360
        Draw.clear()
        Surface.draw_angle(TEXT_SURFACE, WIDTH / 2 , HEIGHT / 2, __y_text)
    }
}
