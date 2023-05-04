
// @class: Draw
// @desc: Drawing primitives.
class Draw {
    // @function: rectangle(x, y, width, height, r, g, b, a, fill)
    // @param: x - x coordinate of the rectangle
    // @param: y - y coordinate of the rectangle
    // @param: width - width of the rectangle
    // @param: height - height of the rectangle
    // @param: r - red component of the rectangle
    // @param: g - green component of the rectangle
    // @param: b - blue component of the rectangle
    // @param: a - alpha component of the rectangle
    // @param: fill - whether or not to fill the rectangle (boolean)
    // @desc: Draws a rectangle.
    foreign static rectangle(x, y, width, height, r, g, b, a, fill)
    // @function: circle(x, y, radius, r, g, b, a, fill)
    // @param: x - x coordinate of the circle
    // @param: y - y coordinate of the circle
    // @param: radius - radius of the circle
    // @param: r - red component of the circle
    // @param: g - green component of the circle
    // @param: b - blue component of the circle
    // @param: a - alpha component of the circle
    // @param: fill - whether or not to fill the circle (boolean)
    // @desc: Draws a circle.
    foreign static circle(x, y, radius, r, g, b, a, fill)
    // @function: line(x1, y1, x2, y2, r, g, b, a)
    // @param: x1 - x coordinate of the first point
    // @param: y1 - y coordinate of the first point
    // @param: x2 - x coordinate of the second point
    // @param: y2 - y coordinate of the second point
    // @param: r - red component of the line
    // @param: g - green component of the line
    // @param: b - blue component of the line
    // @param: a - alpha component of the line
    // @desc: Draws a line.
    foreign static line(x1, y1, x2, y2, r, g, b, a)
    // @function: put_pixel(x, y, r, g, b)
    // @param: x - The x coordinate of the pixel.
    // @param: y - The y coordinate of the pixel.
    // @param: r - The red value of the pixel.
    // @param: g - The green value of the pixel.
    // @param: b - The blue value of the pixel.
    // @desc: Puts a pixel on the screen.
    foreign static put_pixel(x, y, r, g, b)
    // @function: clear(r, g, b)
    // @param: r - The red value of the pixel.
    // @param: g - The green value of the pixel.
    // @param: b - The blue value of the pixel.
    // @param: a - The alpha value of the pixel.
    // @desc: Clears the screen.
    foreign static clear(r, g, b, a)
}
