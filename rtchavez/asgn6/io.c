//io.c

#include "code.h"
#include "defines.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

extern uint8_t *write_buffer[BLOCK];
extern uint64_t write_index;

//Refrences:
//  https://www.kite.com/python/answers/how-to-read-bytes-from-a-binary-file-in-python
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int count = 0; // takes note of the number of bytes read int his one pass
    int r_bytes = nbytes;// create temp that stors neccesarry bytes

    // while count is less than the aimed nbytes or greater than zero
    while(count <= nbytes || count > 0 ){
        count += read(infile, &buf[count], r_bytes); // set bytes output of read
        if(count <= 0){// if out put is greater than zero theer's no more bytes in the 
            fprintf(stderr, "No more bytes to read from the file\n");
            return -1;
        }
        r_bytes -= count;// decrement r_bytes to count
    }
    printf("bytes_read : count\n");

    bytes_written += count;//add count to bytes_read
    return count; // return bytes read
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {

    int count = 0; // takes note of the number of bytes read int his one pass
    int w_bytes = nbytes;// create temp that stors neccesarry bytes

    // while count  is less than nbytes 
    while(count <= nbytes || count > 0){
        count += write(outfile, &buf[count], w_bytes); // set bytes output of read
        if(count <= 0){
            fprintf(stderr, "No more bytes to read from the file\n");
            return -1;
        }
        w_bytes -= count;// decrement r_bytes to count

    }
    printf("bytes_ written: %d\n", count);


    bytes_written += count;//add count to bytes_read
    return count; // return bytes written
}

bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buffer[BLOCK] = {0}; // Inintialize static buffer with BLOCK bytes
    static uint64_t index = 0;

    if (index == 0) { // when buffer has no more bits to read get next block

        uint8_t bytes = read_bytes(infile, buffer, BLOCK); //fill buffer with bytes from infile

        //implemntation of wrapper function
        if (bytes <= 0) {
            return false;
        }
        

        bit = &buffer[index/8];
        bit |= bit << ((uint8_t)index % 8);// set bit 
    }

    index = (index + 1 ) % (4096 * 8);// increment  index by 1


    return true; // returns true if bits can still be read
}

void write_code(int outfile, Code *c) {
    static uint8_t buffer[BLOCK] = write_buffer;
    static uint64_t index = write_index = 0;

    // for each index in c 
    for (uint32_t i = 0; i != c->top; i++) {
        code_pop_bit(c,(uint32_t)i);//pop current i in code
        &buffer[i/8] |= i << (i % 8);// set current i in buffer
        index += 1;// increment index
    }
    //if we need to fill our buffer
    if ((write_index % 8) == 0) {
        write_bytes(outfile,buffer, BLOCK);// write next bytes
        write_index = 0;// reset in
    }
    return;
}
void flush_codes(int outfile) {

    static uint8_t buffer[BLOCK] = write_buffer;
    static uint64_t index = write_index;

    //if the current byte is 0 return
    if (write_buffer[index / 8] == 0) {
            write_bytes(outfile, write_buffer, BLOCK);
            return;
        }
    index++; // increment index
    write_bytes(outfile, write_buffer[index],BLOCK);//write bytes starting from next index
    
    write_buffer = buffer;
    write index = index;
    return;
}
