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

        __mouse_down = false
    }

    /*
    ** Called every frame
    */
    static tick() {
        if (Input.get_mouse_button() == Input.button_mouse_left) {
            var mouse_pos = Input.mouse_pos()

            if (!__mouse_down) {
                __prev_pos = mouse_pos
            }
            Draw.line(__prev_pos, mouse_pos, 0, 0, 0, 255)

            __prev_pos = mouse_pos
            __mouse_down = true
        } else {
            __mouse_down = false
        }

        if (Input.is_key_pressed(Input.get_keycode("C"))) {
            Draw.clear(255, 255, 255, 255)
        }
        if (Input.is_key_pressed(Keycodes.SPACE)) {
            Draw.clear(0, 0, 0, 255)
        }
    }
}
