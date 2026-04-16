#include "string_utils.h"
#include <stdio.h>
#include <assert.h>
int main(void){
    char *string = read_line_dynamic();
    custom_len(string);
    assert(custom_len(string) == 5);
}