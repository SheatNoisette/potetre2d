
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
    // @function: floor(a)
    // @param: a
    // @desc: Returns the floor of a number
    static floor(a) {
        return a - a % 1
    }
    // @function: ceil(a)
    // @param: a
    // @desc: Returns the ceiling of a number
    static ceil(a) {
        return a - a % 1 + 1
    }
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
    static rad2deg(a) {
        return a * 180 / Math.PI
    }
    // @function: deg2rad(a)
    // @param: a
    // @desc: Converts degrees to radians
    static deg2rad(a) {
        return a * Math.PI / 180
    }
}

