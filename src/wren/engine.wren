
// @class: Engine
// @desc: The engine class is the main class of the engine.
class Engine {
    // @function: init(width, height, title)
    // @param: width - The width of the window.
    // @param: height - The height of the window.
    // @desc: Initializes the engine.
    foreign static init(width, height, title)
    // @function: put_pixel(x, y, r, g, b)
    // @param: x - The x coordinate of the pixel.
    // @param: y - The y coordinate of the pixel.
    // @param: r - The red value of the pixel.
    // @param: g - The green value of the pixel.
    // @param: b - The blue value of the pixel.
    // @desc: Puts a pixel on the screen.
    foreign static put_pixel(x, y, r, g, b)
    // @function: destroy()
    // @desc: Destroys the engine.
    foreign static destroy()
}
