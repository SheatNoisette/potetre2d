
// @class: Random
// @class-desc: A random number generator
class Random {
    // @function: seed(seed)
    // @param: seed - The seed to use
    // @desc: Seeds the random number generator
    foreign static seed(seed)
    // @function: rand()
    // @return: A random number between 0 and 1
    foreign static rand()
    // @function: irange(min, max)
    // @param: min - The minimum value
    // @param: max - The maximum value
    // @return: A random integer between min and max
    // @desc: Returns a random integer between min and max
    foreign static irange(min, max)
    // @function: perlin(x,y,z,x_wrap,y_wrap,z_wrap,seed)
    // @param: x - X position
    // @param: y - y position
    // @param: z - z position
    // @param: x_wrap - Wrap around noise (Power of two, 0: don't care)
    // @param: y_wrap - Wrap around noise (Power of two, 0: don't care)
    // @param: z_wrap - Wrap around noise (Power of two, 0: don't care)
    // @param: seed - The seed used
    foreign static perlin(x, y, z, x_wrap, y_wrap, z_wrap, seed)
}
