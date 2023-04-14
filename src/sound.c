#include "sound.h"


int _playsound(Sound sound, int frames, int not_playing){
  if(not_playing == 0){
    PlaySound(sound);
    return 1;
  } else {
    if(frames % 25 == 0) return 0;
  }
  return 2;
}