
// @class: Vector
// @desc: A class to represent a 2d vector
class Vector {
    // @getter: x
    x { _x }
    // @getter: y
    y { _y }

    /* TODO getters
       normalized
       length_squared
       length
       angle
    */

    // @setter: x
    x=(value) { _x = value }
    // @setter: y
    y=(value) { _y = value }

    // @ctor: new()
    // @desc: Returns a new zero vector
    construct new() {
        _x = 0
        _y = 0
    }

    // @ctor: new(x, y)
    // @desc: Returns a new vector with coordinates x,y
    construct new(x, y) {
        _x = x
        _y = y
    }

    /* TODO methods
       normalize()
       negative operator
       multiply num operator
       add(vector)
       angle_to(vector)
       rotated(angle)
    */
}
