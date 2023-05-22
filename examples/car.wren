var WIDTH = 640
var HEIGHT = 480
var TITLE = "vroom vroom"

var FRICTION = 0.025
var ENGINE_POWER = 8
var ENGINE_TORQUE = 0.02
var ANGULAR_SPEED = 0.08
var ANGULAR_TORQUE = 0.05
var BRAKE_POWER = 0.05

class Car {
    construct new() {
        _pos = Vector.new(WIDTH / 2, HEIGHT / 2)
        _vel = Vector.ZERO
        _angle = Random.rand() * Math.PI * 2
        _angvel = 0
    }

    tick() {
        var up = Input.is_key_held(Keycodes.UP)
        var down = Input.is_key_held(Keycodes.DOWN)
        var left = Input.is_key_held(Keycodes.LEFT)
        var right = Input.is_key_held(Keycodes.RIGHT)
        var current_speed = _vel.length

        if (up) { // forward
            if (down) { // braking + accelerating
                _vel = Math.lerp(_vel, Vector.ZERO, BRAKE_POWER)
            } else {
                var target_vel = Vector.new(ENGINE_POWER, 0).rotated(_angle)
                _vel = Math.lerp(_vel, target_vel, ENGINE_TORQUE)
            }
        } else if (down) { // braking
            _vel = Math.lerp(_vel, Vector.ZERO, BRAKE_POWER)
        } else {
            _vel = Math.lerp(_vel, Vector.ZERO, FRICTION)
        }

        if (left && current_speed > 1) { // turning
            _angvel = Math.lerp(_angvel, ANGULAR_SPEED, ANGULAR_TORQUE)
        } else if (right && current_speed > 1) {
            _angvel = Math.lerp(_angvel, -ANGULAR_SPEED, ANGULAR_TORQUE)
        } else {
            _angvel = Math.lerp(_angvel, 0, ANGULAR_TORQUE)
        }

        _angle = _angle + _angvel
        _pos = _pos + _vel
        _pos.x = Math.clamp(_pos.x, 0, WIDTH)
        _pos.y = Math.clamp(_pos.y, 0, HEIGHT)
    }

    render() {
        var forward = Vector.RIGHT.rotated(_angle)
        var right = Vector.DOWN.rotated(_angle)

        var length = 32
        var width = 16

        // dirty hardcoded lines instead of rotating :^)
        Draw.line(_pos + forward*length/2 + right*width/2, _pos + forward*length/2 - right*width/2, Color.BLACK)
        Draw.line(_pos + forward*length/2 + right*width/2, _pos - forward*length/2 + right*width/2, Color.BLACK)
        Draw.line(_pos - forward*length/2 + right*width/2, _pos - forward*length/2 - right*width/2, Color.BLACK)
        Draw.line(_pos - forward*length/2 - right*width/2, _pos + forward*length/2 - right*width/2, Color.BLACK)
        Draw.circle(_pos + forward*length/2.5 + right*width/3, 2, Color.BLACK, false)
        Draw.circle(_pos + forward*length/2.5 - right*width/3, 2, Color.BLACK, false)
    }
}

class Game {
    static init(args) {
        Engine.init(WIDTH, HEIGHT, TITLE)
        __car = Car.new()
        Draw.clear()
    }

    static tick() {
        Draw.clear()
        __car.tick()
        __car.render()
    }
}
