/**
 * @file TFmini-S_LiDAR.c
 * @author 장현제
 */
#include "LiDAR.h"
#include <stdint.h>
#include <stdio.h>

/**
 * @brief LiDAR 모듈을 활용한 거리 측정 코드
 * @param[in] 모듈에서 UART로 송신하는 값을 저장하는 buffer
 * @return void
 * @retval void
 * @note TFmini-S Micro LiDAR 모듈은 데이터 전송 과정에서 L, H 순서로 값을 송신한다. 따라서 H, L 순서로 데이터를 처리해줘야 한다.
 * @note 모듈에서 전송하는 checksum 값은 보수 계산이 적용되지 않은 값이므로 계산한 checksum 값과 모듈에서 보내준 값의 합이 0임을 확인해야 한다.
 * @bug X
 * 
 */
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