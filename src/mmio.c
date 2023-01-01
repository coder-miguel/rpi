//=========================================//
//   Title:  io.c                          //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#include <mmio.h>

void mmio_init(){ }
void write(piaddr32_t addr, pireg32_t data){
    *(volatile piaddr32_t*)(addr) = data;
}
pireg32_t read(piaddr32_t addr){
    return *(volatile piaddr32_t*)(addr);
}
