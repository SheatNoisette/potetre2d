
// @class: Input system
// @desc: Handles input from the user
class Input {
    // @function: mouse_x()
    // @desc: Returns the x position of the mouse
    foreign static mouse_x()
    // @function: mouse_y()
    // @desc: Returns the y position of the mouse
    foreign static mouse_y()
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
    // @function: is_pressed(keycode)
    // @desc: Returns true if the key is pressed
    // @param: keycode - The keycode
    // @return: pressed - True if the key is pressed
    foreign static is_key_pressed(keycode)
}

// @class: Special keycodes
// @desc: Contains special keycodes
class Keycodes {
    static F1 { 144 }
    static F2 { 145 }
    static F3 { 146 }
    static F4 { 147 }
    static F5 { 148 }
    static F6 { 149 }
    static F7 { 150 }
    static F8 { 151 }
    static F9 { 152 }
    static F10 { 153 }
    static F11 { 154 }
    static F12 { 155 }
    static BACKSPACE { 156 }
    static TAB { 157 }
    static RETURN { 158 }
    static SHIFT { 159 }
    static CONTROL { 160 }
    static ALT { 161 }
    static PAUSE { 162 }
    static CAPSLOCK { 163 }
    static ESCAPE { 164 }
    static SPACE { 165 }
    static PAGEUP { 166 }
    static PAGEDOWN { 167 }
    static END { 168 }
    static HOME { 169 }
    static LEFT { 170 }
    static UP { 171 }
    static RIGHT { 172 }
    static DOWN { 173 }
    static INSERT { 174 }
    static DELETE { 175 }
    static NUMLOCK { 176 }
    static SCROLLLOCK { 177 }
    static LEFT_SHIFT { 178 }
    static RIGHT_SHIFT { 179 }
    static LEFT_CONTROL { 180 }
    static RIGHT_CONTROL { 181 }
    static LEFT_ALT { 182 }
    static RIGHT_ALT { 183 }
    static SEMICOLON { 184 }
    static EQUAL { 185 }
    static COMMA { 186 }
    static MINUS { 187 }
    static DOT { 188 }
    static SLASH { 189 }
    static BACKTICK { 190 }
    static LEFT_SQUARE_BRACKET { 191 }
    static BACKSLASH { 192 }
    static RIGHT_SQUARE_BRACKET { 193 }
    static TICK { 194 }
}
