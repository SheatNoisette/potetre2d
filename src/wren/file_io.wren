
// @class: FileIO
// @class-desc: Interact with files
class FileIO {
    // @ctor: open
    // @desc: Open a file
    construct open(path, mode) {
        _file_path = path
        _fd = FileIO.internal_open(path, mode)
        if (_fd < 0) {
            Fiber.abort("Failed to open file")
        }
        _length = FileIO.internal_length(_fd)
    }

    // @function: close()
    // @desc: Close the file
    close() {
        FileIO.internal_close(_fd)
    }

    // @function: read_byte()
    // @desc: Returns a byte from the file
    read_byte() {
        return FileIO.internal_read_byte(_fd)
    }

    // @function: write_byte(byte)
    // @param: byte - The byte to write
    // @desc: Write a byte to the file
    write_byte(byte) {
        FileIO.internal_write_byte(_fd, byte)
    }

    // @function: read_char()
    // @desc: Returns a string with the char
    read_char() {
        return String.fromByte(read_byte())
    }

    // @function: read()
    // @desc: Returns a string with the whole file
    read() {
        var data = ""
        var byte = FileIO.internal_read_byte(_fd)
        while (byte != 0) {
            data = data + String.fromByte(byte)
            byte = FileIO.internal_read_byte(_fd)
        }
        return data
    }

    // @function: write(data)
    // @param: data - The string to write
    // @desc: Write a string to the file
    write(data) {
        for (c in data) {
            FileIO.internal_write_byte(_fd, c)
        }
    }

    // @function: read_line()
    // @desc: Returns a string with the line
    // We're reading a line, so we need to read until \n or EOF and don't
    // Read the whole file
    read_line() {
        var line = ""
        var byte = FileIO.internal_read_byte(_fd)
        // Read until \n or EOF
        while (byte != 0 && byte != 10) {
            // Ignore \r (Windows)
            if (byte == 13) {
                byte = FileIO.internal_read_byte(_fd)
                continue
            }
            line = line + String.fromByte(byte)
            byte = FileIO.internal_read_byte(_fd)
        }
        return line
    }

    // @function: length
    // @desc: Returns the length of the file
    length {
        return __length
    }

    // To string representation
    toString { "FileIO(%(_fd):\"%(__file_path)\")" }

    // These are internal functions and should not be called by the user
    // Returns a internal fd
    foreign static internal_open(path, mode)
    // Close and free the fd
    foreign static internal_close(fd)
    // Read a byte from the fd
    foreign static internal_read_byte(fd)
    // Write a byte from the fd
    foreign static internal_write_byte(fd, byte)
    // Get the length of the file
    foreign static internal_length(fileid)
}
