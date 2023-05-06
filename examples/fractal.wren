var WIDTH = 800
var HEIGHT = 450

var MIN_DISTANCE = 1
var MAX_DEPTH = 12 // increasing this causes exponential lag

class Game {
    static init() {
        Engine.init(WIDTH, HEIGHT, "fractal")
    }

    static tick() {
        Draw.clear()
        fun(Vector.new(WIDTH / 2, HEIGHT * 1.1), -Math.PI / 2, HEIGHT / 3, 1)
    }

    static fun(pos, angle, distance, i) {
        if (distance < MIN_DISTANCE || i > MAX_DEPTH) {
            return
        }

        var new_pos = Vector.new(
            pos.x + distance * Math.cos(angle),
            pos.y + distance * Math.sin(angle)
        )

        Draw.line(pos, new_pos, Color.BLACK)

        var new_distance = distance * mouse_to_factor()
        var angle_deviance = mouse_to_angle()
        fun(new_pos, angle - angle_deviance, new_distance, i + 1)
        fun(new_pos, angle + angle_deviance, new_distance, i + 1)
    }

    static mouse_to_angle() {
        return Math.map(Input.mouse_x(), 0, WIDTH, 0, Math.PI)
    }

    static mouse_to_factor() {
        return Math.map(Input.mouse_y(), HEIGHT, 0, -0.1, 0.8)
    }
}
