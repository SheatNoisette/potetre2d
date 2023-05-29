var WIDTH = 320
var HEIGHT = 240
var TITLE = "line distance"

class Game {
    static init(args) {
        Engine.init(WIDTH, HEIGHT, TITLE)

        __start = Vector.new(WIDTH / 3, HEIGHT / 2 - 20)
        __end = Vector.new(2 * WIDTH / 3, HEIGHT / 2 + 20)
    }

    static tick(dt) {
        Draw.clear(Color.BLACK)

        Draw.line(__start, __end, Color.WHITE)

        var mouse_pos = Input.mouse_pos()
        Draw.circle(mouse_pos, 1, Color.WHITE, true)

        var distance = mouse_pos.distance_to_line(__start, __end)
        Draw.circle(mouse_pos, distance, Color.RED, false)

        Draw.text(4, 4, "fps: %((1/dt).round)", Color.WHITE)
    }
}
