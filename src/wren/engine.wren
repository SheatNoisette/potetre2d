
// @class: Engine
// @desc: The engine class is the main class of the engine.
class Engine {
    // @function: init(width, height, title)
    // @param: width - The width of the window.
    // @param: height - The height of the window.
    // @desc: Initializes the engine.
    foreign static init(width, height, title)
    // @function: destroy()
    // @desc: Destroys the engine.
    foreign static destroy()
    // @function: get_os()
    // @desc: Returns the operating system which the VM is running on.
    foreign static get_os()
    // @const: OS_NIX
    // @desc: The operating system is a Unix-like system.
    static OS_NIX { 0 }
    // @const: OS_MACOS
    // @desc: The operating system is a Macintosh system.
    static OS_MACOS { 1 }
    // @const: OS_WINDOWS
    // @desc: The operating system is a Windows system.
    static OS_WINDOWS { 2 }
    // @function: OS_UNKNOWN
    // @desc: The operating system is unknown.
    static OS_UNKNOWN { 3 }
    // @function: get_build_id()
    // @desc: Returns the build ID of the engine.
    foreign static get_build_id()
    // @function: get_build_string()
    // @desc: Returns the build string of the engine.
    foreign static get_build_string()
}
