/*
** Read a simple text file and print it out.
*/

class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        var file = FileIO.open("fileio.wren", "r")
        var line = 0
        var current_line = ""
        for (ch in file.read()) {
            if (ch == "\n") {
                System.print("%(line): %(current_line)")
                current_line = ""
                line = line + 1
            } else {
                current_line = current_line + ch
            }
        }
        file.close()
    }
}
