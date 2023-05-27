// @class: Surface
// @desc: A surface is a canvas that can be drawn to and then drawn to the screen.
class Surface {
    // @function: new(width, height)
    // @param: width - the width of the surface
    // @param: height - the height of the surface
    // @desc: Creates a new surface with the given width and height.
    // @returns: the id of the surface
    foreign static new(width, height)
    // @function: new_from_png(path)
    // @param: path - the path to the png file
    // @desc: Creates a new surface from the given png file.
    // @returns: the id of the surface
    foreign static new_from_png(path)
    // @function: set_target(surfaceid)
    // @param: surfaceid - the id of the surface to set as the target
    // @desc: Sets the target surface to the given surface to draw to.
    foreign static set_target(surfaceid)
    // @function: reset_target()
    // @desc: Resets the target surface to the screen.
    foreign static reset_target()
    // @function: draw(surfaceid, x, y)
    // @param: surfaceid - the id of the surface to draw
    // @param: x - the x position to draw the surface at
    // @param: y - the y position to draw the surface at
    // @param: alpha - the alpha to draw the surface with
    // @desc: Draws the given surface at the given position.
    foreign static draw(surfaceid, x, y, alpha)
    // @function: draw_angle(surfaceid, x, y, angle)
    // @param: surfaceid - the id of the surface to draw
    // @param: x - the x position to draw the surface at
    // @param: y - the y position to draw the surface at
    // @param: angle - the angle to rotate the surface by
    // @desc: Draws the given surface at the given position rotated by the given angle. This is slower than draw_surface.
    foreign static draw_angle(surfaceid, x, y, angle)
    // @function: get_width(surfaceid)
    // @param: surfaceid - the id of the surface to get the width of
    // @desc: Gets the width of the given surface.
    // @returns: the width of the surface
    foreign static get_width(surfaceid)
    // @function: get_height(surfaceid)
    // @param: surfaceid - the id of the surface to get the height of
    // @desc: Gets the height of the given surface.
    // @returns: the height of the surface
    foreign static get_height(surfaceid)
}
