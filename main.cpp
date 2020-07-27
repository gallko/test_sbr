#include <iostream>
#include "List_impl.h"

/**
 * 1.
 */
void print_bit(unsigned int x, int bit_num) {
    if(bit_num < 0) {
        return;
    }
    printf("%u", (x&(1<<bit_num))>>bit_num);
    print_bit(x, --bit_num); // tail recursion
}

void print_int(int x) {
    constexpr int SIZE_INT = sizeof(int)*8;
    print_bit(x, SIZE_INT - 1);
}

/**
 * 2.
 * 'A' and 'a' are different symbols
 */
void RemoveDups(char* str) {
    if (!str || *str == '\0') {
        return;
    }

    for (char* i = str + 1; *i != '\0'; ++i) {
        if (*str != *i) {
            ++str;
            if (str != i) {
                *str = *i;
            }
        }
    }
    *++str = '\0';
}

int main() {
    print_int(-153);
    std::cout << std::endl;
    print_int(694);
    std::cout << std::endl;
    char data[] = "\n\n\n\n44      DeeeeeR\n\n\n\n\n\n\n\n\n";
    RemoveDups(data);
    std::cout << data << std::endl;

    List list;
    FILE* file = fopen("text.bin", "wb");
    list.Serialize(file);
    fclose(file);

    List list2;
    FILE* file2 = fopen("text.bin", "rb");
    list2.Deserialize(file2);
    fclose(file2);
    return 0;
}
