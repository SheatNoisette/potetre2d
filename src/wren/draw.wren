
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
    // @param: fill - whether to fill the rectangle (boolean)
    // @desc: Draws a rectangle.
    foreign static rectangle(x, y, width, height, r, g, b, a, fill)
    // @function: rectangle(pos, size, color, fill)
    // @param: pos - coordinate vector of the rectangle
    // @param: size - size vector of the rectangle
    // @param: color - color of the rectangle
    // @param: fill - whether to fill the rectangle (boolean)
    // @desc: Draws a rectangle.
    static rectangle(pos, size, color, fill) {
        rectangle(pos.x, pos.y, size.x, size.y, color.r, color.g, color.b, color.a, fill)
    }
    // @function: rectangle(x, y, width, height, color, fill)
    // @param: x - x coordinate of the rectangle
    // @param: y - y coordinate of the rectangle
    // @param: width - width of the rectangle
    // @param: height - height of the rectangle
    // @param: color - color of the rectangle
    // @param: fill - whether to fill the rectangle (boolean)
    // @desc: Draws a rectangle.
    static rectangle(x, y, width, height, color, fill) {
        rectangle(x, y, width, height, color.r, color.g, color.b, color.a, fill)
    }

    // @function: circle(x, y, radius, r, g, b, a, fill)
    // @param: x - x coordinate of the circle
    // @param: y - y coordinate of the circle
    // @param: radius - radius of the circle
    // @param: r - red component of the circle
    // @param: g - green component of the circle
    // @param: b - blue component of the circle
    // @param: a - alpha component of the circle
    // @param: fill - whether to fill the circle (boolean)
    // @desc: Draws a circle.
    foreign static circle(x, y, radius, r, g, b, a, fill)
    // @function: circle(pos, radius, color, fill)
    // @param: pos - coordinate vector of the circle
    // @param: radius - radius of the circle
    // @param: color - color of the circle
    // @param: fill - whether to fill the circle (boolean)
    // @desc: Draws a circle.
    static circle(pos, radius, color, fill) {
        circle(pos.x, pos.y, radius, color.r, color.g, color.b, color.a, fill)
    }

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
    // @function: line(start, end, color)
    // @param: start - coordinate vector of the first point
    // @param: end - coordinate vector of the second point
    // @param: color - color of the line
    // @desc: Draws a line.
    static line(start, end, color) {
        line(start.x, start.y, end.x, end.y, color.r, color.g, color.b, color.a)
    }

    // @function: put_pixel(x, y, r, g, b)
    // @param: x - The x coordinate of the pixel
    // @param: y - The y coordinate of the pixel
    // @param: r - The red value of the pixel
    // @param: g - The green value of the pixel
    // @param: b - The blue value of the pixel
    // @desc: Puts a pixel on the screen
    foreign static put_pixel(x, y, r, g, b)
    // @function: put_pixel(pos, color)
    // @param: pos - coordinate vector of the pixel
    // @param: color - color of the pixel (ignores alpha)
    // @desc: Puts a pixel on the screen
    static put_pixel(pos, color) {
        put_pixel(pos.x, pos.y, color.r, color.g, color.b)
    }

    // This is a internal functio to get the pixel from the screen
    // it returns a list of [r, g, b, a].
    foreign static internal_get_pixel(x, y)
    // @function: get_pixel(x, y)
    // @param: x - The x coordinate of the pixel
    // @param: y - The y coordinate of the pixel
    // @return: The color of the pixel Color(r, g, b, a)
    // @desc: Gets a pixel from the screen or surface
    static get_pixel(x, y) {
        var color = internal_get_pixel(x, y)
        return Color.new(color[0], color[1], color[2], color[3])
    }
    // @function: get_pixel(pos)
    // @param: pos - coordinate vector of the pixel
    // @return: The color of the pixel Color(r, g, b, a)
    // @desc: Gets a pixel from the screen or surface
    static get_pixel(pos) {
        var color = internal_get_pixel(pos.x, pos.y)
        return Color.new(color[0], color[1], color[2], color[3])
    }

    // @function: clear(r, g, b, a)
    // @param: r - The red value of the pixel
    // @param: g - The green value of the pixel
    // @param: b - The blue value of the pixel
    // @param: a - The alpha value of the pixel
    // @desc: Clears the screen
    foreign static clear(r, g, b, a)
    // @function: clear(r, g, b)
    // @param: r - The red value of the pixel
    // @param: g - The green value of the pixel
    // @param: b - The blue value of the pixel
    // @desc: Clears the screen (no alpha)
    static clear(r, g, b) { clear(r, g, b, 255) }
    // @function: clear(color)
    // @param: color - The color to clear the screen with
    // @desc: Clears the screen
    static clear(color) { clear(color.r, color.g, color.b, color.a) }
    // @function: clear()
    // @desc: Clears the screen (white)
    static clear() { clear(Color.WHITE) }
    // @function: text(x, y, text, r, g, b, a)
    // @param: x - The x coordinate of the text
    // @param: y - The y coordinate of the text
    // @param: msg - The text to draw
    // @param: r - The red value of the text
    // @param: g - The green value of the text
    // @param: b - The blue value of the text
    // @param: a - The alpha value of the text
    // @desc: Draws text on the screen
    foreign static text(x, y, msg, r, g, b, a)
    // @function: text(pos, text, color)
    // @param: pos - coordinate vector of the text
    // @param: msg - The text to draw
    // @param: color - The color of the text
    // @desc: Draws text on the screen
    static text(pos, msg, color) {
        text(pos.x, pos.y, msg, color.r, color.g, color.b, color.a)
    }
    // @function: text(x, y, text, color)
    // @param: x - The x coordinate of the text
    // @param: y - The y coordinate of the text
    // @param: msg - The text to draw
    // @param: color - The color of the text
    // @desc: Draws text on the screen
    static text(x, y, msg, color) {
        text(x, y, msg, color.r, color.g, color.b, color.a)
    }
}
