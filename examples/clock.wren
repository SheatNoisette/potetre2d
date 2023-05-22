var DELTA = 1 / 60

class Game {
    static init(args) {
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

        Draw.clear(Color.BLACK)

        var mouse_pos = Input.mouse_pos()
        var radius = Math.map(Math.sin(__ticks / 10), -1, 1, 2.5, 8.5)

        Draw.circle(mouse_pos, __seconds.length + radius, Color.WHITE, false)
        Draw.line(mouse_pos, mouse_pos + __hours, Color.BLUE)
        Draw.line(mouse_pos, mouse_pos + __minutes, Color.GREEN)
        Draw.line(mouse_pos, mouse_pos + __seconds, Color.RED)
    }
}
