var DELTA = 1 / 60

class Game {
    static init() {
        Engine.init(200, 200, "test")

        __seconds = Vector.UP * 80
        __minutes = Vector.UP * 70
        __hours = Vector.UP * 50

        __ticks = 0
    }

    static tick() {
        __ticks = __ticks + 1

        // 60 times faster than an actual clock
        __seconds = __seconds.rotated(-2 * Math.PI * DELTA)
        __minutes = __minutes.rotated(-2 * Math.PI * DELTA / 60)
        __hours = __hours.rotated(-2 * Math.PI * DELTA / 60 / 12)

        Draw.clear(255, 255, 255)

        var radius = Math.map(Math.sin(__ticks / 10), -1, 1, 2.5, 8.5)

        var mouse_pos = Input.mouse_pos()
        Draw.circle(mouse_pos.x, mouse_pos.y, __seconds.length + radius, 0, 0, 0, 255, false)
        Draw.line(mouse_pos, mouse_pos + __hours, 0, 0, 255, 255)
        Draw.line(mouse_pos, mouse_pos + __minutes, 0, 255, 0, 255)
        Draw.line(mouse_pos, mouse_pos + __seconds, 255, 0, 0, 255)
    }
}
