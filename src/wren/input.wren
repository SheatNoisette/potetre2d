
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
}

