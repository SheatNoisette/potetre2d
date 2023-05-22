var WIDTH = 320
var HEIGHT = 240
var TITLE = "My Game"

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

    /*
    ** Called every frame
    */
    static tick() {

    }
}
