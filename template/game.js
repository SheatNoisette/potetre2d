/*
** Base template for a game using the Picogine
*/

var window_width = 320;
var window_height = 240;
var window_title = "Picogine Template";
var target_fps = 60;

function init() {
    pg_init(window_width, window_height, window_title, target_fps);
}

function update() {
    // pg_clear_screen(0, 0, 0);
    for (var x = 0; x < window_width; x++) {
        for (var y = 0; y < window_height; y++) {
            pg_set_pixel(x, y, Math.random() * 255, Math.random() * 255, Math.random() * 255);
        }
    }
}
