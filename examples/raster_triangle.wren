var WIDTH = 640
var HEIGHT = 480
var TITLE = "Triangle Demo"

/*
** Main game entry point
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        __current_rotation = 0

        Engine.init(WIDTH, HEIGHT, TITLE)
        Draw.clear()
    }

    static raster_triangle(vertex_1, vertex_2, vertex_3, color) {
        // Loosely based on http://sw-shader.sourceforge.net/rasterizer.html
        var x1 = vertex_1.x
        var x2 = vertex_2.x
        var x3 = vertex_3.x

        var y1 = vertex_1.y
        var y2 = vertex_2.y
        var y3 = vertex_3.y

        var minx = Math.min(x1, Math.min(x2, x3))
        var maxx = Math.max(x1, Math.max(x2, x3))
        var miny = Math.min(y1, Math.min(y2, y3))
        var maxy = Math.max(y1, Math.max(y2, y3))

        for (y in miny..maxy) {
            for (x in minx..maxx) {
                if (((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0) &&
                ((x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0) &&
                ((x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0)) {
                    Draw.put_pixel(Vector.new(x, y), color)
                }
            }
        }
    }

    /*
    ** Called every frame
    */
    static tick(dt) {
        Draw.clear()

        var radius = 50
        var screen_center = Vector.new(WIDTH / 2, HEIGHT / 2)

        // Draw a triangle and rotate it
        var vertex_1 = Vector.new(
                                    Math.cos(__current_rotation) * radius,
                                    Math.sin(__current_rotation) * radius
                                ) + screen_center
        var vertex_2 = Vector.new(
                                    Math.cos(__current_rotation + 30) * radius,
                                    Math.sin(__current_rotation + 30) * radius
                                ) + screen_center
        var vertex_3 = screen_center

        Game.raster_triangle(vertex_1, vertex_2, vertex_3, Color.GREEN)


        // Update the rotation
        __current_rotation = __current_rotation + 1 * dt
        if (__current_rotation > 360) {
            __current_rotation = 0
        }
    }
}
