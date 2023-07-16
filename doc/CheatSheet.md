# Potetre2d Cheatset
This list every documented classes, methods and constants of the engine.
You don't need to import any module to use them and they are available
everywhere.

Please note that this cheatset is generated from the engine source code
and may change in the future. If you find any error, please report it
on the Potetre2d repository.

This document is licensed under the CC-BY-SA 4.0 license.

## Audio
### Sound
**A class that handles audio playback**

#### Constructor: Sound.open a ogg file
Open a file

#### play
Plays the audio, default settings

#### play
 * volume - the volume to play the audio at
 * pitch - the pitch to play the audio at
 * pan - the pan to play the audio at
Plays the audio, with settings


## Color
### Color
**A class to represent a color (r, g, b, a)**

#### Constant: Color.BLACK
A color with r, g, b = 0 (alpha = 255)

#### Constant: Color.WHITE
A color with r, g, b = 255 (alpha = 255)

#### Constant: Color.RED
A color with r = 255 (g, b = 0) (alpha = 255)

#### Constant: Color.GREEN
A color with g = 255 (r, b = 0) (alpha = 255)

#### Constant: Color.BLUE
A color with b = 255 (r, g = 0) (alpha = 255)

#### Constructor: Color.new(r, g, b, a)
Constructs a color with r, g, b, a

#### Constructor: Color.new(r, g, b)
Constructs a color with r, g, b (alpha = 255)

#### Constructor: Color.new(rgb)
Constructs a grayscale color with brightness = rgb (alpha = 255)


## Draw
### Draw
**Drawing primitives.**

#### Draw.rectangle(x, y, width, height, r, g, b, a, fill)
 * x - x coordinate of the rectangle
 * y - y coordinate of the rectangle
 * width - width of the rectangle
 * height - height of the rectangle
 * r - red component of the rectangle
 * g - green component of the rectangle
 * b - blue component of the rectangle
 * a - alpha component of the rectangle
 * fill - whether to fill the rectangle (boolean)
Draws a rectangle.

#### Draw.rectangle(pos, size, color, fill)
 * pos - coordinate vector of the rectangle
 * size - size vector of the rectangle
 * color - color of the rectangle
 * fill - whether to fill the rectangle (boolean)
Draws a rectangle.

#### Draw.rectangle(x, y, width, height, color, fill)
 * x - x coordinate of the rectangle
 * y - y coordinate of the rectangle
 * width - width of the rectangle
 * height - height of the rectangle
 * color - color of the rectangle
 * fill - whether to fill the rectangle (boolean)
Draws a rectangle.

#### Draw.circle(x, y, radius, r, g, b, a, fill)
 * x - x coordinate of the circle
 * y - y coordinate of the circle
 * radius - radius of the circle
 * r - red component of the circle
 * g - green component of the circle
 * b - blue component of the circle
 * a - alpha component of the circle
 * fill - whether to fill the circle (boolean)
Draws a circle.

#### Draw.circle(pos, radius, color, fill)
 * pos - coordinate vector of the circle
 * radius - radius of the circle
 * color - color of the circle
 * fill - whether to fill the circle (boolean)
Draws a circle.

#### Draw.line(x1, y1, x2, y2, r, g, b, a)
 * x1 - x coordinate of the first point
 * y1 - y coordinate of the first point
 * x2 - x coordinate of the second point
 * y2 - y coordinate of the second point
 * r - red component of the line
 * g - green component of the line
 * b - blue component of the line
 * a - alpha component of the line
Draws a line.

#### Draw.line(start, end, color)
 * start - coordinate vector of the first point
 * end - coordinate vector of the second point
 * color - color of the line
Draws a line.

#### Draw.put_pixel(x, y, r, g, b)
 * x - The x coordinate of the pixel
 * y - The y coordinate of the pixel
 * r - The red value of the pixel
 * g - The green value of the pixel
 * b - The blue value of the pixel
Puts a pixel on the screen

#### Draw.put_pixel(pos, color)
 * pos - coordinate vector of the pixel
 * color - color of the pixel (ignores alpha)
Puts a pixel on the screen

#### Draw.get_pixel(x, y)
 * x - The x coordinate of the pixel
 * y - The y coordinate of the pixel
 * @return: The color of the pixel Color(r, g, b, a)
Gets a pixel from the screen or surface

#### Draw.get_pixel(pos)
 * pos - coordinate vector of the pixel
 * @return: The color of the pixel Color(r, g, b, a)
Gets a pixel from the screen or surface

#### Draw.clear(r, g, b, a)
 * r - The red value of the pixel
 * g - The green value of the pixel
 * b - The blue value of the pixel
 * a - The alpha value of the pixel
Clears the screen

#### Draw.clear(r, g, b)
 * r - The red value of the pixel
 * g - The green value of the pixel
 * b - The blue value of the pixel
Clears the screen (no alpha)

#### Draw.clear(color)
 * color - The color to clear the screen with
Clears the screen

#### Draw.clear()
Clears the screen (white)

#### Draw.text(x, y, text, r, g, b, a)
 * x - The x coordinate of the text
 * y - The y coordinate of the text
 * msg - The text to draw
 * r - The red value of the text
 * g - The green value of the text
 * b - The blue value of the text
 * a - The alpha value of the text
Draws text on the screen

#### Draw.text(pos, text, color)
 * pos - coordinate vector of the text
 * msg - The text to draw
 * color - The color of the text
Draws text on the screen

#### Draw.text(x, y, text, color)
 * x - The x coordinate of the text
 * y - The y coordinate of the text
 * msg - The text to draw
 * color - The color of the text
Draws text on the screen


## Engine
### Engine
**The engine class is the main class of the engine.**

#### Engine.init(width, height, title)
 * width - The width of the window.
 * height - The height of the window.
 * title - The title of the window.
Initializes the engine.

#### Engine.destroy()
Destroys the engine.

#### Engine.get_os()
Returns the operating system which the VM is running on.

#### Constant: Engine.OS_NIX
The operating system is a Unix-like system.

#### Constant: Engine.OS_MACOS
The operating system is a Macintosh system.

#### Constant: Engine.OS_WINDOWS
The operating system is a Windows system.

#### Engine.OS_UNKNOWN
The operating system is unknown.

#### Engine.get_build_id()
Returns the build ID of the engine.

#### Engine.get_build_string()
Returns the build string of the engine.


## File_io
### FileIO
**Interact with files**

#### Constructor: FileIO.open
Open a file

#### FileIO.close()
Close the file

#### FileIO.read_byte()
Returns a byte from the file

#### FileIO.write_byte(byte)
 * byte - The byte to write
Write a byte to the file

#### FileIO.read_char()
Returns a string with the char

#### FileIO.read()
Returns a string with the whole file

#### FileIO.write(data)
 * data - The string to write
Write a string to the file

#### FileIO.read_line()
Returns a string with the line

#### FileIO.length
Returns the length of the file


## Input
### Input system
**Handles input from the user**

#### Input system.mouse_x()
Returns the x position of the mouse

#### Input system.mouse_y()
Returns the y position of the mouse

#### Input system.mouse_pos()
Returns the position of the mouse as a vector

#### Input system.get_mouse_button()
Returns the state of the mouse button

 * @return: button - The button
#### Input system.Get keycode from key name
Returns the keycode from the key name.

 * key_name - The key name (string)
 * @return: keycode - The keycode (Return 0 if not supported)
#### Input system.is_key_pressed(keycode)
Returns true if the key was just pressed

 * keycode - The keycode
 * @return: pressed - True if the key was just pressed
#### Input system.is_key_held(keycode)
Returns true if the key is being held

 * keycode - The keycode
 * @return: held - True if the key is being held
### Keycodes
Special keycodes for is_key_*, easier to read than the numbers.

#### Constant: Keycodes.F1
#### Constant: Keycodes.F2
#### Constant: Keycodes.F3
#### Constant: Keycodes.F4
#### Constant: Keycodes.F5
#### Constant: Keycodes.F6
#### Constant: Keycodes.F7
#### Constant: Keycodes.F8
#### Constant: Keycodes.F9
#### Constant: Keycodes.F10
#### Constant: Keycodes.F11
#### Constant: Keycodes.F12
#### Constant: Keycodes.BACKSPACE
#### Constant: Keycodes.TAB
#### Constant: Keycodes.RETURN
#### Constant: Keycodes.SHIFT
#### Constant: Keycodes.CONTROL
#### Constant: Keycodes.ALT
#### Constant: Keycodes.PAUSE
#### Constant: Keycodes.CAPSLOCK
#### Constant: Keycodes.ESCAPE
#### Constant: Keycodes.SPACE
#### Constant: Keycodes.PAGEUP
#### Constant: Keycodes.PAGEDOWN
#### Constant: Keycodes.END
#### Constant: Keycodes.HOME
#### Constant: Keycodes.LEFT
#### Constant: Keycodes.UP
#### Constant: Keycodes.RIGHT
#### Constant: Keycodes.DOWN
#### Constant: Keycodes.INSERT
#### Constant: Keycodes.DELETE
#### Constant: Keycodes.NUMLOCK
#### Constant: Keycodes.SCROLLLOCK
#### Constant: Keycodes.LEFT_SHIFT
#### Constant: Keycodes.RIGHT_SHIFT
#### Constant: Keycodes.LEFT_CONTROL
#### Constant: Keycodes.RIGHT_CONTROL
#### Constant: Keycodes.LEFT_ALT
#### Constant: Keycodes.RIGHT_ALT
#### Constant: Keycodes.SEMICOLON
#### Constant: Keycodes.EQUAL
#### Constant: Keycodes.COMMA
#### Constant: Keycodes.MINUS
#### Constant: Keycodes.DOT
#### Constant: Keycodes.SLASH
#### Constant: Keycodes.BACKTICK
#### Constant: Keycodes.LEFT_SQUARE_BRACKET
#### Constant: Keycodes.BACKSLASH
#### Constant: Keycodes.RIGHT_SQUARE_BRACKET
#### Constant: Keycodes.TICK

## Math
### Math
**A class containing math functions**

#### Constant: Math.PI
The PI constant

#### Math.min(a, b)
 * a
 * b
Returns the minimum of two numbers

#### Math.max(a, b)
 * a
 * b
Returns the maximum of two numbers

#### Math.clamp(value, min, max)
 * value
 * min
 * max
Clamps a value between a minimum and maximum value

#### Math.map(value, old_min, old_max, new_min, new_max)
 * value
 * old_min
 * old_max
 * new_min
 * new_max
Re-maps a value from one range to another

#### Math.map_clamped(value, old_min, old_max, new_min, new_max)
 * value
 * old_min
 * old_max
 * new_min
 * new_max
Re-maps a value from one range to another (clamped to new range)

#### Math.lerp(value, target, factor)
 * value
 * target
 * factor
Interpolates value towards target by factor

#### Math.abs(a)
 * a
Returns the absolute value of a number

#### Math.floor(a)
 * a
Returns the floor of a number

#### Math.ceil(a)
 * a
Returns the ceiling of a number

#### Math.sqrt(a)
 * a
Returns the square root of a number

#### Math.pow(a, b)
 * a
 * b
Returns a to the power of b

#### Math.sin(a)
 * a
Returns the sine of a number

#### Math.cos(a)
 * a
Returns the cosine of a number

#### Math.atan2(a, b)
 * a
 * b
Returns the 2-argument arctangent of a and b

#### Math.fmod(a, b)
 * a
 * b
Returns the (positive) float modulo of a and b

#### Math.rad2deg(a)
 * a
Converts radians to degrees

#### Math.deg2rad(a)
 * a
Converts degrees to radians


## Random
### Random
**A random number generator**

#### Random.seed(seed)
 * seed - The seed to use
Seeds the random number generator

#### Random.rand()
 * @return: A random number between 0 and 1
#### Random.irange(min, max)
 * min - The minimum value
 * max - The maximum value
 * @return: A random integer between min and max
Returns a random integer between min and max

#### Random.perlin(x,y,z,x_wrap,y_wrap,z_wrap,seed)
 * x - X position
 * y - y position
 * z - z position
 * x_wrap - Wrap around noise (Power of two, 0
 * y_wrap - Wrap around noise (Power of two, 0
 * z_wrap - Wrap around noise (Power of two, 0
 * seed - The seed used

## Surface
### Surface
**A surface is a canvas that can be drawn to and then drawn to the screen.**

#### Surface.new(width, height)
 * width - the width of the surface
 * height - the height of the surface
Creates a new surface with the given width and height.

 * @returns: the id of the surface
#### Surface.new_from_png(path)
 * path - the path to the png file
Creates a new surface from the given png file.

 * @returns: the id of the surface
#### Surface.set_target(surfaceid)
 * surfaceid - the id of the surface to set as the target
Sets the target surface to the given surface to draw to.

#### Surface.reset_target()
Resets the target surface to the screen.

#### Surface.draw(surfaceid, x, y)
 * surfaceid - the id of the surface to draw
 * x - the x position to draw the surface at
 * y - the y position to draw the surface at
 * alpha - the alpha to draw the surface with
Draws the given surface at the given position.

#### Surface.draw_angle(surfaceid, x, y, angle)
 * surfaceid - the id of the surface to draw
 * x - the x position to draw the surface at
 * y - the y position to draw the surface at
 * angle - the angle to rotate the surface by
Draws the given surface at the given position rotated by the given angle. This is slower than draw_surface.

#### Surface.get_width(surfaceid)
 * surfaceid - the id of the surface to get the width of
Gets the width of the given surface.

 * @returns: the width of the surface
#### Surface.get_height(surfaceid)
 * surfaceid - the id of the surface to get the height of
Gets the height of the given surface.

 * @returns: the height of the surface
#### Surface.destroy(surfaceid)
 * surfaceid - the id of the surface to destroy from memory
Destroys the given surface from memory.

#### Surface.resize(surfaceid, width, height)
 * surfaceid - the id of the surface to resize
 * width - the new width of the surface
 * height - the new height of the surface
Resizes the given surface to the given width and height. This is not designed to be called once per frame.


## Vector
### Vector
**A class to represent a 2d vector**

#### Constant: Vector.ZERO
The zero vector

#### Constant: Vector.UP
A vector pointing up

#### Constant: Vector.DOWN
A vector pointing down

#### Constant: Vector.LEFT
A vector pointing left

#### Constant: Vector.RIGHT
A vector pointing right

#### Constructor: Vector.new(x, y)
Returns a new vector with coordinates x,y

#### Vector.length_squared
Returns the squared length of the vector

#### Vector.length
Returns the length of the vector

#### Vector.normalized
Returns a new vector with the same angle and a length of 1

#### Vector.angle
Returns the angle of the vector

#### Vector.distance_to(vec)
 * vec
Returns the distance between this vector and vec

#### Vector.dot(vec)
 * vec
Returns the dot product between this vector and vec

#### Vector.distance_to_line(vec1, vec2)
 * vec1
 * vec2
Returns the distance between this vector and a line

#### Vector.angle_to(vec)
 * vec
Returns the angle between this vector and vec (radians)

#### Vector.rotated(angle)
 * angle
Returns a new vector rotated by angle (radians)

#### Vector.clamped(min, max)
 * min - vector
 * max - vector
Clamps coordinates between the two given vectors

