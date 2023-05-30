// @class: Surface
// @class-desc: A surface is a canvas that can be drawn to and then drawn to the screen.
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
    static draw_centered(surfaceid, pos, alpha) {
        var w = get_width(surfaceid)
        var h = get_height(surfaceid)
        draw(surfaceid, pos.x - w/2, pos.y - h/2, alpha)
    }
    // @function: draw_angle(surfaceid, x, y, angle)
    // @param: surfaceid - the id of the surface to draw
    // @param: x - the x position to draw the surface at
    // @param: y - the y position to draw the surface at
    // @param: angle - the angle to rotate the surface by
    // @desc: Draws the given surface at the given position rotated by the given angle. This is slower than draw_surface.
    foreign static draw_angle(surfaceid, x, y, angle)
    static draw_angle(surfaceid, pos, angle) {
        draw_angle(surfaceid, pos.x, pos.y, angle)
    }
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
    // @function: destroy(surfaceid)
    // @param: surfaceid - the id of the surface to destroy from memory
    // @desc: Destroys the given surface from memory.
    foreign static destroy(surfaceid)
    // @function: resize(surfaceid, width, height)
    // @param: surfaceid - the id of the surface to resize
    // @param: width - the new width of the surface
    // @param: height - the new height of the surface
    // @desc: Resizes the given surface to the given width and height.
    foreign static resize(surfaceid, width, height)
}
