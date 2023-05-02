
// @class: Math
// @desc: A class containing math functions
class Math {
    // @const: PI
    // @desc: The PI constant
    static PI {
        return 3.141592653589793
    }
    // @function: min(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the minimum of two numbers
    static min(a, b) {
        if (a < b) {
            return a
        } else {
            return b
        }
    }
    // @function: max(a, b)
    // @param: a
    // @param: b
    // @desc: Returns the maximum of two numbers
    static max(a, b) {
        if (a > b) {
            return a
        } else {
            return b
        }
    }
    // @function: clamp(value, min, max)
    // @param: value
    // @param: min
    // @param: max
    // @desc: Clamps a value between a minimum and maximum value
    static clamp(value, min, max) {
        return Math.max(min, Math.min(max, value))
    }
    // @function: abs(a)
    // @param: a
    // @desc: Returns the absolute value of a number
    static abs(a) {
        if (a < 0) {
            return -a
        } else {
            return a
        }
    }
}

