/*
** Get the OS which is running the game
*/

class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        var os = Engine.get_os()
        if (os == Engine.OS_WINDOWS) {
            System.print("Running on Windows")
        } else if (os == Engine.OS_NIX) {
            System.print("Running on Unix (Linux, BSD like, except macOS)...")
        } else if (os == Engine.OS_MACOS) {
            System.print("Running on MacOS")
        } else {
            System.print("Running on a unknown OS")
        }

        System.print("The engine build is %(Engine.get_build_id())")
        System.print("The engine version string is " + Engine.get_build_string())
    }
}
