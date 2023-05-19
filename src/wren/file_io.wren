
// @class: File IO
// @description: Interact with files
class FileIO {
    // @ctor: open
    // @desc: Open a file
    construct open(path, mode) {
        __file_path = path
        __fd = FileIO.internal_open(path, mode)
        if (__fd < 0) {
            Fiber.abort("Failed to open file")
        }
        __length = FileIO.internal_length(__fd)
    }

    // @function: Close the file
    close() {
        FileIO.internal_close(__fd)
    }

    // @function: Read a byte from the file
    read_byte() {
        return FileIO.internal_read_byte(__fd)
    }

    // @function: Write a byte to the file
    write_byte(byte) {
        FileIO.internal_write_byte(__fd, byte)
    }

    // @function: Read a char
    read_char() {
        return String.fromByte(read_byte())
    }

    // @function: Read the whole file
    read() {
        var data = ""
        var byte = FileIO.internal_read_byte(__fd)
        while (byte != 0) {
            data = data + String.fromByte(byte)
            byte = FileIO.internal_read_byte(__fd)
        }
        return data
    }

    // @function: Write a string to the file
    write(data) {
        for (c in data) {
            FileIO.internal_write_byte(__fd, c)
        }
    }

    // @function: Read a line
    // We're reading a line, so we need to read until \n or EOF and don't
    // Read the whole file
    read_line() {
        var line = ""
        var byte = FileIO.internal_read_byte(__fd)
        // Read until \n or EOF
        while (byte != 0 && byte != 10) {
            // Ignore \r (Windows)
            if (byte == 13) {
                byte = FileIO.internal_read_byte(__fd)
                continue
            }
            line = line + String.fromByte(byte)
            byte = FileIO.internal_read_byte(__fd)
        }
        return line
    }

    // @function: Get the length of the file
    length {
        return __length
    }

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
