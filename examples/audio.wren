var WIDTH = 320
var HEIGHT = 240
var TITLE = "Press space to play sound!"

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
    }

    static tick(dt) {}
}
