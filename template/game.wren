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
        Engine.put_pixel(10, 10, 255, 0, 0)
    }
}
