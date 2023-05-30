
// @class: Input system
// @class-desc: Handles input from the user
class Input {
    // @function: mouse_x()
    // @desc: Returns the x position of the mouse
    foreign static mouse_x()
    // @function: mouse_y()
    // @desc: Returns the y position of the mouse
    foreign static mouse_y()
    // @function: mouse_pos()
    // @desc: Returns the position of the mouse as a vector
    static mouse_pos() { Vector.new(mouse_x(), mouse_y()) }
    // @function: get_mouse_button()
    // @desc: Returns the state of the mouse button
    // @return: button - The button
    foreign static get_mouse_button()
    // Button constants
    static button_mouse_left { 1 }
    static button_mouse_right { 2 }
    static button_mouse_middle { 4 }
    // @function: Get keycode from key name
    // @desc: Returns the keycode from the key name.
    // @param: key_name - The key name (string)
    // @return: keycode - The keycode (Return 0 if not supported)
    foreign static get_keycode(key_name)
    // @function: is_key_pressed(keycode)
    // @desc: Returns true if the key was just pressed
    // @param: keycode - The keycode
    // @return: pressed - True if the key was just pressed
    foreign static is_key_pressed(keycode)
    // @function: is_key_held(keycode)
    // @desc: Returns true if the key is being held
    // @param: keycode - The keycode
    // @return: held - True if the key is being held
    foreign static is_key_held(keycode)
}

// @class: Keycodes
// @desc: Special keycodes for is_key_*, easier to read than the numbers.
class Keycodes {
    // @const: F1
    static F1 { 144 }
    // @const: F2
    static F2 { 145 }
    // @const: F3
    static F3 { 146 }
    // @const: F4
    static F4 { 147 }
    // @const: F5
    static F5 { 148 }
    // @const: F6
    static F6 { 149 }
    // @const: F7
    static F7 { 150 }
    // @const: F8
    static F8 { 151 }
    // @const: F9
    static F9 { 152 }
    // @const: F10
    static F10 { 153 }
    // @const: F11
    static F11 { 154 }
    // @const: F12
    static F12 { 155 }
    // @const: BACKSPACE
    static BACKSPACE { 156 }
    // @const: TAB
    static TAB { 157 }
    // @const: RETURN
    static RETURN { 158 }
    // @const: SHIFT
    static SHIFT { 159 }
    // @const: CONTROL
    static CONTROL { 160 }
    // @const: ALT
    static ALT { 161 }
    // @const: PAUSE
    static PAUSE { 162 }
    // @const: CAPSLOCK
    static CAPSLOCK { 163 }
    // @const: ESCAPE
    static ESCAPE { 164 }
    // @const: SPACE
    static SPACE { 165 }
    // @const: PAGEUP
    static PAGEUP { 166 }
    // @const: PAGEDOWN
    static PAGEDOWN { 167 }
    // @const: END
    static END { 168 }
    // @const: HOME
    static HOME { 169 }
    // @const: LEFT
    static LEFT { 170 }
    // @const: UP
    static UP { 171 }
    // @const: RIGHT
    static RIGHT { 172 }
    // @const: DOWN
    static DOWN { 173 }
    // @const: INSERT
    static INSERT { 174 }
    // @const: DELETE
    static DELETE { 175 }
    // @const: NUMLOCK
    static NUMLOCK { 176 }
    // @const: SCROLLLOCK
    static SCROLLLOCK { 177 }
    // @const: LEFT_SHIFT
    static LEFT_SHIFT { 178 }
    // @const: RIGHT_SHIFT
    static RIGHT_SHIFT { 179 }
    // @const: LEFT_CONTROL
    static LEFT_CONTROL { 180 }
    // @const: RIGHT_CONTROL
    static RIGHT_CONTROL { 181 }
    // @const: LEFT_ALT
    static LEFT_ALT { 182 }
    // @const: RIGHT_ALT
    static RIGHT_ALT { 183 }
    // @const: SEMICOLON
    static SEMICOLON { 184 }
    // @const: EQUAL
    static EQUAL { 185 }
    // @const: COMMA
    static COMMA { 186 }
    // @const: MINUS
    static MINUS { 187 }
    // @const: DOT
    static DOT { 188 }
    // @const: SLASH
    static SLASH { 189 }
    // @const: BACKTICK
    static BACKTICK { 190 }
    // @const: LEFT_SQUARE_BRACKET
    static LEFT_SQUARE_BRACKET { 191 }
    // @const: BACKSLASH
    static BACKSLASH { 192 }
    // @const: RIGHT_SQUARE_BRACKET
    static RIGHT_SQUARE_BRACKET { 193 }
    // @const: TICK
    static TICK { 194 }
}
