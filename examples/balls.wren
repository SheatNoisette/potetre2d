var WIN_WIDTH = 320
var WIN_HEIGHT = 240
var CENTER = Vector.new(WIN_WIDTH / 2, WIN_HEIGHT / 2)

var ACCEL = 1.03

class Ball {
    construct new(radius, pos, vel, color) {
        _radius = radius
        _pos = pos
        _vel = vel
        _color = color
    }

    tick() {
        _pos = _pos + _vel

        if (_pos.x >= WIN_WIDTH - _radius + 1) {
            _pos.x = WIN_WIDTH - _radius + 1
            _vel.x = -_vel.x * ACCEL
        }
        if (_pos.x < _radius - 1) {
            _pos.x = _radius - 1
            _vel.x = -_vel.x * ACCEL
        }
        if (_pos.y >= WIN_HEIGHT - _radius + 1) {
            _pos.y = WIN_HEIGHT - _radius + 1
            _vel.y = -_vel.y * ACCEL
        }
        if (_pos.y < _radius - 1) {
            _pos.y = _radius - 1
            _vel.y = -_vel.y * ACCEL
        }
    }

    render() {
        var circle_color = Color.new(_color.r, _color.g, _color.b, 80)
        Draw.circle(CENTER, _pos.distance_to(CENTER), circle_color, false)
        Draw.circle(_pos, _radius, _color, true)
    }
}

class Game {
    static get_random_ball() {
        var radius = Random.rand() * 10 + 3
        var x = Random.irange(radius, WIN_WIDTH - radius)
        var y = Random.irange(radius, WIN_HEIGHT - radius)
        var dx = (Random.rand() * 2 - 1) * 2
        var dy = (Random.rand() * 2 - 1) * 2
        var r = Random.irange(0, 128)
        var g = Random.irange(0, 128)
        var b = Random.irange(0, 128)
        return Ball.new(radius, Vector.new(x, y), Vector.new(dx, dy), Color.new(r, g, b))
    }

    static init(args) {
        Engine.init(WIN_WIDTH, WIN_HEIGHT, "balls.")

        __balls = []

        for (i in 1..20) {
            __balls.add(get_random_ball())
        }
    }

    static tick(dt) {
        Draw.clear()

        for (ball in __balls) {
            ball.tick()
            ball.render()
        }

        if (Input.is_key_pressed(Keycodes.RETURN)) {
            __balls.add(get_random_ball())
        }
    }
}
