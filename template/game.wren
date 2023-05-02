/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init() {
        System.print("Picogine Init!")
        Engine.init(320, 240, "My Game")
    }

    /*
    ** Called every frame
    */
    static tick() {
        var x = 0
        var y = 0
        while (y < 240) {
            while (x < 320) {
                Engine.put_pixel(x, y,
                    Random.irange(0, 255),
                    Random.irange(0, 255),
                    Random.irange(0, 255)
                )
                x = x + 1
            }
            x = 0
            y = y + 1
        }
    }
}
