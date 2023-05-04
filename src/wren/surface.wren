
class Surface {
    foreign static new_surface(width, height)
    foreign static new_surface_from_png(path)
    foreign static set_target(surfaceid)
    foreign static reset_target()
    foreign static draw_surface(surfaceid, x, y)
}
