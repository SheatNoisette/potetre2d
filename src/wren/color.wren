
// @class: Color
// @desc: A class to represent a color (r, g, b, a)
class Color {
    // @const: BLACK
    static BLACK { Color.new(0, 0, 0) }
    // @const: WHITE
    static WHITE { Color.new(255, 255, 255) }
    // @const: RED
    static RED { Color.new(255, 0, 0) }
    // @const: GREEN
    static GREEN { Color.new(0, 255, 0) }
    // @const: BLUE
    static BLUE { Color.new(0, 0, 255) }

    r { _r }
    g { _g }
    b { _b }
    a { _a }
    r=(value) { _r = value }
    g=(value) { _g = value }
    b=(value) { _b = value }
    a=(value) { _a = value }

    toString { "Color(%(_r), %(_g), %(_b), %(_a))" }

    clamp(value) { value.clamp(0, 255) }

    // @ctor: new(r, g, b, a)
    // @desc: Constructs a color with r, g, b, a
    construct new(r, g, b, a) {
        _r = clamp(r)
        _g = clamp(g)
        _b = clamp(b)
        _a = clamp(a)
    }

    // @ctor: new(r, g, b)
    // @desc: Constructs a color with r, g, b (alpha = 255)
    construct new(r, g, b) {
        _r = clamp(r)
        _g = clamp(g)
        _b = clamp(b)
        _a = 255
    }

    // @ctor: new(rgb)
    // @desc: Constructs a grayscale color with brightness = rgb (alpha = 255)
    construct new(rgb) {
        _r = _g = _b = clamp(rgb)
        _a = 255
    }

    ==(c) { _r == c.r && _g == c.g && _b == c.b && _a == c.a }
    !=(c) { _r != c.r || _g != c.g || _b != c.b || _a != c.a }

    +(c) { Color.new(_r + c.r, _g + c.g, _b + c.b, _a + c.a) }
    -(c) { Color.new(_r - c.r, _g - c.g, _b - c.b, _a - c.a) }
    *(c) { Color.new(_r * c.r, _g * c.g, _b * c.b, _a * c.a) }
}
