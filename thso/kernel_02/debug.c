const char hex_digits[] = "0123456789ABCDEF";

// base should be max 16
void int_to_string(unsigned long val, char base, char* buffer) {
    for(int i = sizeof(val)*2-1; i >= 0; i--) {
        buffer[i] = hex_digits[val % base];
        val /= base;
    }
    buffer[sizeof(val)*2] = '\0';
}

void pointer_to_hex_string(void* ptr, char* buffer) {
    unsigned long val = (unsigned long)ptr;
    return int_to_string(val, 16, buffer);
}
