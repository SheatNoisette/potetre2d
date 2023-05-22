/*
** Write a string to a file
*/

class Game {
    static init(args) {
        var file = FileIO.open("hello.txt", "w")
        file.write("Hello, world!\n")
        file.close()
    }
}
