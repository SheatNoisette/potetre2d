
/*
** Example of getting arguments from the command line
*/
class Game {
    /*
    ** Called when the game is started
    */
    static init(args) {
        System.print("Arguments:")
        for (arg in args) {
            System.print("- " + arg)
        }
    }
}
