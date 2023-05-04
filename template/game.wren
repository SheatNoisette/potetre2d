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
        Draw.clear(255, 255, 255, 255)
    }

    /*
    ** Called every frame
    */
    static tick() {
        if (Input.get_mouse_button() == Input.button_mouse_left) {
            Draw.put_pixel(Input.mouse_x(), Input.mouse_y(), 0, 0, 0)
        } else if (Input.is_key_pressed(Input.get_keycode("C"))) {
            Draw.clear(255, 255, 255, 255)
        } else if (Input.is_key_pressed(Keycodes.SPACE)) {
            Draw.clear(0, 0, 0, 255)
        }
    }
}
