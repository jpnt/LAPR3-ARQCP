#ifndef DIR_H
#define DIR_H

int dir_exists(const char* dir_name);
int dir_create(const char* dir_name);
void dir_configure(const char* dir_name);

#endif // !DIR_H
