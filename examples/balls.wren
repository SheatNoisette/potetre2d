var WIN_WIDTH = 320
var WIN_HEIGHT = 240
var CENTER = Vector.new(WIN_WIDTH / 2, WIN_HEIGHT / 2)

var ACCEL = 1.03

class Ball {
    construct new(radius, x, y, dx, dy, r, g, b) {
        _radius = radius
        _pos = Vector.new(x, y)
        _vel = Vector.new(dx, dy)
        _r = r
        _g = g
        _b = b
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
        Draw.circle(CENTER.x, CENTER.y, _pos.distance_to(CENTER), _r, _g, _b, 80, false)
        Draw.circle(_pos.x, _pos.y, _radius, _r, _g, _b, 255, true)
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
        return Ball.new(radius, x, y, dx, dy, r, g, b)
    }

    static init() {
        Engine.init(WIN_WIDTH, WIN_HEIGHT, "balls.")

        __balls = []

        for (i in 1..20) {
            __balls.add(get_random_ball())
        }
    }

    static tick() {
        Draw.clear(255, 255, 255, 255)

        for (ball in __balls) {
            ball.tick()
            ball.render()
        }
    }
}
