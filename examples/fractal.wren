var WIDTH = 800
var HEIGHT = 450

var MIN_DISTANCE = 1
var MAX_DEPTH = 12 // increasing this causes exponential lag

class Game {
    static init() {
        Engine.init(WIDTH, HEIGHT, "fractal")
    }

    static tick() {
        Draw.clear(255, 255, 255)
        fun(WIDTH / 2, HEIGHT * 1.1, -Math.PI / 2, HEIGHT / 3)
    }

    static fun(x, y, angle, distance) {
        fun(x, y, angle, distance, 1)
    }

    static fun(x, y, angle, distance, i) {
        if (distance < MIN_DISTANCE || i > MAX_DEPTH) {
            return
        }

        var new_x = x + distance * Math.cos(angle)
        var new_y = y + distance * Math.sin(angle)

        Draw.line(x, y, new_x, new_y, 0, 0, 0, 255)

        var new_distance = distance * mouse_to_factor()
        var angle_deviance = mouse_to_angle()
        fun(new_x, new_y, angle - angle_deviance, new_distance, i + 1)
        fun(new_x, new_y, angle + angle_deviance, new_distance, i + 1)
    }

    static mouse_to_angle() {
        return Math.map(Input.mouse_x(), 0, WIDTH, 0, Math.PI)
    }

    static mouse_to_factor() {
        return Math.map(Input.mouse_y(), HEIGHT, 0, -0.1, 0.8)
    }
}
