
// @class: Vector
// @class-desc: A class to represent a 2d vector
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

    // @function: length_squared
    // @desc: Returns the squared length of the vector
    length_squared { _x * _x + _y * _y }
    // @function: length
    // @desc: Returns the length of the vector
    length { length_squared.sqrt }
    // @function: normalized
    // @desc: Returns a new vector with the same angle and a length of 1
    normalized { this / length }
    // @function: angle
    // @desc: Returns the angle of the vector
    angle { (-_y).atan(_x) }

    ==(vec) { _x == vec.x && _y == vec.y }
    !=(vec) { _x != vec.x || _y != vec.y }

    +(vec) { Vector.new(_x + vec.x, _y + vec.y) }
    -(vec) { Vector.new(_x - vec.x, _y - vec.y) }

    *(num) { Vector.new(_x * num, _y * num) }
    /(num) { Vector.new(_x / num, _y / num) }

    - { Vector.new(-_x, -_y) }

    // @function: distance_to(vec)
    // @param: vec
    // @desc: Returns the distance between this vector and vec
    distance_to(vec) { (vec - this).length }

    // @function: dot(vec)
    // @param: vec
    // @desc: Returns the dot product between this vector and vec
    dot(vec) { _x * vec.x + _y * vec.y }

    // @function: distance_to_line(vec1, vec2)
    // @param: vec1
    // @param: vec2
    // @desc: Returns the distance between this vector and a line
    distance_to_line(vec1, vec2) {
        var l2 = (vec2 - vec1).length_squared

        var t = ((this - vec1).dot(vec2 - vec1) / l2).clamp(0, 1)
        var projection = vec1 + (vec2 - vec1) * t
        return this.distance_to(projection)
    }

    // @function: angle_to(vec)
    // @param: vec
    // @desc: Returns the angle between this vector and vec (radians)
    angle_to(vec) {
        var a = vec.angle - angle
        return Math.fmod(a + Num.pi, 2*Num.pi) - Num.pi
    }

    // @function: rotated(angle)
    // @param: angle
    // @desc: Returns a new vector rotated by angle (radians)
    rotated(angle) {
        var cos = (-angle).cos
        var sin = (-angle).sin

        return Vector.new(cos * _x - sin * _y, sin * _x + cos * _y)
    }

    // @function: clamped(min, max)
    // @param: min - vector
    // @param: max - vector
    // @desc: Clamps coordinates between the two given vectors
    clamped(min, max) {
        return Vector.new(
            _x.clamp(min.x, max.x),
            _y.clamp(min.y, max.y)
        )
    }
}
