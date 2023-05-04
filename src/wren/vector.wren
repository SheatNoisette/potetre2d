
// @class: Vector
// @desc: A class to represent a 2d vector
class Vector {
    x { _x }
    y { _y }
    x=(value) { _x = value }
    y=(value) { _y = value }

    toString { "(%(_x), %(_y))" }

    // @ctor: new()
    // @desc: Returns a new zero vector
    construct new() {
        _x = _y = 0
    }

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

    *(num) { Vector.new(_x * num, _y * num) }
    /(num) { Vector.new(_x / num, _y / num) }

    - { Vector.new(-_x, -_y) }

    // TODO methods
    // angle_to(vector)
    // rotated(angle)
}
