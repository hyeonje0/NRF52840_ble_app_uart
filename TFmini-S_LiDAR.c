#include "LiDAR.h"
#include <stdint.h>
#include <stdio.h>

void TFLiDAR(uint8_t *buf){

  uint16_t dist = 0;
  uint16_t strength = 0;
  uint16_t temp = 0;

  uint8_t checksum = 0;
   
  for(int i=0;i<8;i++){
      checksum += buf[i];
  }

  checksum = ~checksum;
  checksum += 1;

  checksum += buf[8];
  dist = (buf[3] << 8) | buf[2];
  strength = (buf[5] << 8) | buf[4];
  temp = ((buf[7] << 8) | buf[6])/8-256;

  if(checksum == 0){
      if(dist >= 10 && dist <= 1200){
            printf("d : [%d] s : [%d] t : [%d]\r\n", dist, strength, temp);
      }
  }
  else{
      printf("=====%d %d=====\r\n", checksum, buf[8]);
  }
  checksum = 0;

}