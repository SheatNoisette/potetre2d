var WIDTH = 320
var HEIGHT = 240
var TITLE = "Press space to play sound!"
var MY_SOUND = Sound.load_ogg("files/sound.ogg")

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

    static tick(dt) {
        if (Input.is_key_pressed(Keycodes.SPACE)) {
            MY_SOUND.play(
                Random.rand(),
                Random.rand(),
                Random.rand()
            )
        }
    }
}
