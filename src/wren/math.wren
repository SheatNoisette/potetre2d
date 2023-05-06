
// @class: Math
// @desc: A class containing math functions
class Math {
    // @const: PI
    // @desc: The PI constant
    static PI { 3.141592653589793 }
    // @function: min(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the minimum of two numbers
    static min(a, b) { a < b ? a : b }
    // @function: max(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the maximum of two numbers
    static max(a, b) { a > b ? a : b }
    // @function: clamp(value, min, max)
    // @param: value
    // @param: min
    // @param: max
    // @desc: Clamps a value between a minimum and maximum value
    static clamp(value, min, max) { Math.max(min, Math.min(max, value)) }
    // @function: map(value, old_min, old_max, new_min, new_max)
    // @param: value
    // @param: old_min
    // @param: old_max
    // @param: new_min
    // @param: new_max
    // @desc: Re-maps a value from one range to another
    static map(value, old_min, old_max, new_min, new_max) {
        return (value - old_min) / (old_max - old_min) * (new_max - new_min) + new_min
    }
    // @function: abs(a)
    // @param: a
    // @desc: Returns the absolute value of a number
    static abs(a) { a < 0 ? -a : a }
    // @function: floor(a)
    // @param: a
    // @desc: Returns the floor of a number
    static floor(a) { a - a % 1 }
    // @function: ceil(a)
    // @param: a
    // @desc: Returns the ceiling of a number
    static ceil(a) { a - a % 1 + 1 }
    // @function: sqrt(a)
    // @param: a
    // @desc: Returns the square root of a number
    foreign static sqrt(a)
    // @function: pow(a, b)
    // @param: a
    // @param: b
    // @desc: Returns a to the power of b
    foreign static pow(a, b)
    // @function: sin(a)
    // @param: a
    // @desc: Returns the sine of a number
    foreign static sin(a)
    // @function: cos(a)
    // @param: a
    // @desc: Returns the cosine of a number
    foreign static cos(a)
    // @function: atan2(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the 2-argument arctangent of a and b
    foreign static atan2(a, b)
    // @function: rad2deg(a)
    // @param: a
    // @desc: Converts radians to degrees
    static rad2deg(a) { a * 180 / Math.PI }
    // @function: deg2rad(a)
    // @param: a
    // @desc: Converts degrees to radians
    static deg2rad(a) { a * Math.PI / 180 }
}
