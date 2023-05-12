class FileIO {
    construct open(path, mode) {
        __file_path = path;
        __fd = FileIO.internal_open(path, mode);
        __length = FileIO.internal_length(__fd);
    }

    close() {
        FileIO.internal_close(__fd)
    }

    read_byte() {
        return FileIO.internal_read_byte(__fd)
    }

    length {
        return __length
    }

    // Returns a internal fd
    foreign static internal_open(path, mode)
    // Close and free the fd
    foreign static internal_close(fd)
    // Read a byte from the fd
    foreign static internal_read_byte(fd)
    // Get the length of the file
    foreign static internal_length(fileid)
}