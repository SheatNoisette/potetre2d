/*
** Example of a basic CSV reader
*/

class CSVLoader {
    construct new(path, delimiter) {
        __delimiter = delimiter
        __header = []
        __header_size = 0
        __data = []

        var file = FileIO.open(path, "r")
        __content = file.read()
        file.close()
        this.parse()
    }

    parse() {
        __data = []
        var line = 0
        var current_line = ""
        for (ch in __content) {
            if (ch == "\n") {
                var data = current_line.split(__delimiter)

                if (line == 0) {
                    __header = data
                    __header_size = data.count
                } else if (data.count != __header_size) {
                    Fiber.abort("The CSV is invalid!")
                } else {
                    __data.add(data)
                }

                current_line = ""
                line = line + 1
            } else {
                current_line = current_line + ch
            }
        }
    }

    // Get a string representation
    toString {
        if (__header_size == 0) {
            return "CSVLoader{}"
        }

        var index = 0
        var output = "CSVLoader{\n" + " " * 4 + "header{ "

        for (h in __header) {
            output = output + h
            if (index < (__header_size - 1)) {
                output = output + __delimiter
            }
            index = index + 1
        }

        index = 0
        output = output + " }\n\n" + " " * 4 + "data {\n"
        for (line in __data) {
            index = 0
            output = output + " " * 9
            for (item in line) {
                output = output + item
                if (index < (line.count - 1)) {
                    output = output + __delimiter
                }
                index = index + 1
            }
            output = output + "\n"
        }

        return output + " " * 4 + "}\n}"
    }

    data {
        return __data
    }

    header {
        return __header
    }
}

class Game {
    static init(args) {
        var csv = CSVLoader.new("files/test.csv", ",")
        System.print(csv)
        System.print(csv.header)
        System.print(csv.data)
    }
}
