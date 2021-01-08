#include <Arduino.h>
#include <Encoder_ctm.h>
#include <Core.h>


#define ENCODEROUTPUT 663

//The sample code for driving one way motor encoder


EncoderData::EncoderData() {
    EncoderData::encoderValue = 0;
}


double EncoderData::calcRPM() {   
  if (currentpulsetime==0)
  {
    return 0;
  }
  return 60000/(((currentpulsetime)/1000.0)*562.215);
}

void EncoderData::updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}