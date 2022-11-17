#include "file.h"

// Open existing database file or create one if it doesn't exist
int file_open_database_file(const char* pathname) { return 0; }

// Allocate an on-disk page from the free page list
pagenum_t file_alloc_page(int fd) { return 0; }

// Free an on-disk page to the free page list
void file_free_page(int fd, pagenum_t pagenum) {}

// Read an on-disk page into the in-memory page structure(dest)
void file_read_page(int fd, pagenum_t pagenum, page_t* dest) {}

// Write an in-memory page(src) to the on-disk page
void file_write_page(int fd, pagenum_t pagenum, const page_t* src) {}

// Close the database file
void file_close_database_file() {}
