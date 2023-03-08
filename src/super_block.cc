#include "super_block.h"
#include "const_variable.h"
super_block::super_block() {
    i_map_blocks = 1;
    d_map_blocks = 5;
    i_blocks = 1 * BLK_SIZE;
    d_blocks = 5 * BLK_SIZE;
}