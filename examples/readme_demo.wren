var WIDTH = 320
var HEIGHT = 240
var TITLE = "Random screen"

class Game {
    /* Called when the game is started */
    static init(args) {
        System.print("Picogine Init!")
        Engine.init(WIDTH, HEIGHT, TITLE)
    }

    /* Called every frame */
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
