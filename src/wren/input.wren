
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
    static button_mouse_left {
        return 1
    }
    static button_mouse_right {
        return 2
    }
    static button_mouse_middle {
        return 4
    }
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
    static F1 {
        return 144
    }
    static F2 {
        return 145
    }
    static F3 {
        return 146
    }
    static F4 {
        return 147
    }
    static F5 {
        return 148
    }
    static F6 {
        return 149
    }
    static F7 {
        return 150
    }
    static F8 {
        return 151
    }
    static F9 {
        return 152
    }
    static F10 {
        return 153
    }
    static F11 {
        return 154
    }
    static F12 {
        return 155
    }
    static BACKSPACE {
        return 156
    }
    static TAB {
        return 157
    }
    static RETURN {
        return 158
    }
    static SHIFT {
        return 159
    }
    static CONTROL {
        return 160
    }
    static ALT {
        return 161
    }
    static PAUSE {
        return 162
    }
    static CAPSLOCK {
        return 163
    }
    static ESCAPE {
        return 164
    }
    static SPACE {
        return 165
    }
    static PAGEUP {
        return 166
    }
    static PAGEDOWN {
        return 167
    }
    static END {
        return 168
    }
    static HOME {
        return 169
    }
    static LEFT {
        return 170
    }
    static UP {
        return 171
    }
    static RIGHT {
        return 172
    }
    static DOWN {
        return 173
    }
    static INSERT {
        return 174
    }
    static DELETE {
        return 175
    }
    static NUMLOCK {
        return 176
    }
    static SCROLLLOCK {
        return 177
    }
    static LEFT_SHIFT {
        return 178
    }
    static RIGHT_SHIFT {
        return 179
    }
    static LEFT_CONTROL {
        return 180
    }
    static RIGHT_CONTROL {
        return 181
    }
    static LEFT_ALT {
        return 182
    }
    static RIGHT_ALT {
        return 183
    }
    static SEMICOLON {
        return 184
    }
    static EQUAL {
        return 185
    }
    static COMMA {
        return 186
    }
    static  MINUS {
        return 187
    }
    static DOT {
        return 188
    }
    static SLASH {
        return 189
    }
    static BACKTICK {
        return 190
    }
    static LEFT_SQUARE_BRACKET {
        return 191
    }
    static BACKSLASH {
        return 192
    }
    static RIGHT_SQUARE_BRACKET {
        return 193
    }
    static TICK {
        return 194
    }
}
