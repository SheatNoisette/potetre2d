
// @class: Vector
// @desc: A class to represent a 2d vector
class Vector {
    // @const: ZERO
    // @desc: The zero vector
    static ZERO { Vector.new(0, 0) }
    // @const: UP
    // @desc: A vector pointing up
    static UP { Vector.new(0, -1) }
    // @const: DOWN
    // @desc: A vector pointing down
    static DOWN { Vector.new(0, 1) }
    // @const: LEFT
    // @desc: A vector pointing left
    static LEFT { Vector.new(-1, 0) }
    // @const: RIGHT
    // @desc: A vector pointing right
    static RIGHT { Vector.new(1, 0) }

    x { _x }
    y { _y }
    x=(value) { _x = value }
    y=(value) { _y = value }

    toString { "(%(_x), %(_y))" }

    // @ctor: new(x, y)
    // @desc: Returns a new vector with coordinates x,y
    construct new(x, y) {
        _x = x
        _y = y
    }

    length_squared { _x * _x + _y * _y }
    length { Math.sqrt(length_squared) }
    normalized { this / length }

    // TODO getters
    // angle
    // rotated

    ==(vec) { _x == vec.x && _y == vec.y }
    !=(vec) { _x != vec.x || _y != vec.y }

    +(vec) { Vector.new(_x + vec.x, _y + vec.y) }
    -(vec) { Vector.new(_x - vec.x, _y - vec.y) }

    *(num) { Vector.new(_x * num, _y * num) }
    /(num) { Vector.new(_x / num, _y / num) }

    - { Vector.new(-_x, -_y) }

    distance_to(vec) {
        var difference = vec - this
        return difference.length
    }

    // TODO methods
    // angle_to(vector)
    // rotated(angle)
}
