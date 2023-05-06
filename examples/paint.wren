class Game {
    static init() {
        Engine.init(640, 480, "Paint")
        Draw.clear()

        __mouse_down = false
    }

    static tick() {
        if (Input.get_mouse_button() == Input.button_mouse_left) {
            var mouse_pos = Input.mouse_pos()

            if (!__mouse_down) {
                __prev_pos = mouse_pos
            }
            Draw.line(__prev_pos, mouse_pos, Color.BLACK)

            __prev_pos = mouse_pos
            __mouse_down = true
        } else {
            __mouse_down = false
        }

        if (Input.is_key_pressed(Input.get_keycode("C"))) {
            Draw.clear()
        }
        if (Input.is_key_pressed(Keycodes.SPACE)) {
            Draw.clear(Color.BLACK)
        }
    }
}
