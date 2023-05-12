#ifndef __FILE_IO_H__
#define __FILE_IO_H__

struct pe_file_vector_data {
    FILE *file;
    char *file_name;
    size_t file_size;
};

void pe_close_destroy_file(void *data);
void pe_file_io_register_functions(struct pe_engine_state *engine_state);

#endif