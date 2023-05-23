var WIDTH = 320
var HEIGHT = 240
var TITLE = "My Game"
var BLOOD_SURFACE = Surface.new(WIDTH, HEIGHT)
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
        Surface.set_target(BLOOD_SURFACE)
            Draw.clear(Color.WHITE)
        Surface.reset_target()
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        Draw.clear(Color.WHITE)
        Surface.set_target(BLOOD_SURFACE)
        if (Input.get_mouse_button() == Input.button_mouse_left) {
            var mouse_pos = Input.mouse_pos()

            var current = 0
            var max_splat = Random.irange(64, 256)
            while (current < max_splat) {
                var radius = Random.irange(1, 64)
                var angle = Random.rand() * Math.PI * 2
                var color_variant = Random.irange(0, 100)
                Draw.put_pixel(
                    mouse_pos.x + radius * Math.cos(angle),
                    mouse_pos.y + radius * Math.sin(angle),
                    255 - color_variant, color_variant, color_variant
                )
                current = current + 1
            }
        }
        Surface.reset_target()

        Surface.draw(BLOOD_SURFACE, 0, 0)
    }
}
