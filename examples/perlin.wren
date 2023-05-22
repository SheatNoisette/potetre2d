var WIDTH = 320
var HEIGHT = 240
var TITLE = "Perlin Noise Demo (Press Space!)"

/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        Engine.init(WIDTH, HEIGHT, TITLE)
        Draw.clear()
    }

    /*
    ** Called every frame
    */
    static tick() {
        if (Input.is_key_pressed(Keycodes.SPACE)) {
            var seed = Random.irange(0,255)
            var scale = 1 << Random.irange(2, 6)
            System.print("Generating... Seed: %(seed) Scale: %(scale)")
            for (x in 0..WIDTH) {
                for (y in 0..HEIGHT) {
                    var perlin_value = Random.perlin(
                        (x/WIDTH) * scale, (y/HEIGHT) * scale, 1.0,
                        scale, scale, scale,
                        seed
                    ) * 255
                    Draw.put_pixel(x, y, perlin_value, perlin_value, perlin_value)
                }
            }
        } else if (Input.is_key_pressed(Keycodes.ESCAPE)) {
            Engine.destroy()
        }
    }
}
