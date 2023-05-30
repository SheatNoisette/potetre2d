
// @class: Math
// @class-desc: A class containing math functions
class Math {
    // @const: PI
    // @desc: The PI constant
    static PI { Num.pi }
    // @function: min(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the minimum of two numbers
    static min(a, b) { a.min(b) }
    // @function: max(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the maximum of two numbers
    static max(a, b) { a.max(b) }
    // @function: clamp(value, min, max)
    // @param: value
    // @param: min
    // @param: max
    // @desc: Clamps a value between a minimum and maximum value
    static clamp(value, min, max) { value.clamp(min, max) }
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
    // @function: map_clamped(value, old_min, old_max, new_min, new_max)
    // @param: value
    // @param: old_min
    // @param: old_max
    // @param: new_min
    // @param: new_max
    // @desc: Re-maps a value from one range to another (clamped to new range)
    static map_clamped(value, old_min, old_max, new_min, new_max) {
        var mapped = (value - old_min) / (old_max - old_min) * (new_max - new_min) + new_min
        return mapped.clamp(new_min, new_max)
    }
    // @function: lerp(value, target, factor)
    // @param: value
    // @param: target
    // @param: factor
    // @desc: Interpolates value towards target by factor
    static lerp(value, target, factor) {
        return value + (target - value) * factor
    }
    // @function: abs(a)
    // @param: a
    // @desc: Returns the absolute value of a number
    static abs(a) { a.abs }
    // @function: floor(a)
    // @param: a
    // @desc: Returns the floor of a number
    static floor(a) { a.floor }
    // @function: ceil(a)
    // @param: a
    // @desc: Returns the ceiling of a number
    static ceil(a) { a.ceil }
    // @function: sqrt(a)
    // @param: a
    // @desc: Returns the square root of a number
    static sqrt(a) { a.sqrt }
    // @function: pow(a, b)
    // @param: a
    // @param: b
    // @desc: Returns a to the power of b
    static pow(a, b) { a.pow(b) }
    // @function: sin(a)
    // @param: a
    // @desc: Returns the sine of a number
    static sin(a) { a.sin }
    // @function: cos(a)
    // @param: a
    // @desc: Returns the cosine of a number
    static cos(a) { a.cos }
    // @function: atan2(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the 2-argument arctangent of a and b
    static atan2(a, b) { a.atan(b) }
    // @function: fmod(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the (positive) float modulo of a and b
    static fmod(a, b) { (a % b + b) % b }
    // @function: rad2deg(a)
    // @param: a
    // @desc: Converts radians to degrees
    static rad2deg(a) { a * 180 / Math.PI }
    // @function: deg2rad(a)
    // @param: a
    // @desc: Converts degrees to radians
    static deg2rad(a) { a * Math.PI / 180 }
}
