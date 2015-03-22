#include "Tlc5940.h"
#define RGB_MAX 4095

int rgb[] = {0, 0, 0};
float h=0.0, s=1.0, i=1.0;

void setup() {
  // put your setup code here, to run once:
  Tlc.init();
  
  pinMode(XLAT_PIN, OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(10,  OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  h += 0.1;
  if( h > 4095.0 ){
    h = 0.0;
  }
  hsi2rgb(h, s, i, rgb);

  Tlc.clear();
  for( int i = 0; i < 3; i++ ){
    Tlc.set(i, rgb[i]);
  }
  Tlc.update();
  delay(1);
}

void hsi2rgb(float H, float S, float I, int* rgb) {
  int r, g, b;
  H = fmod(H,360); // cycle H around to 0-360 degrees
  H = 3.14159*H/(float)180; // Convert to radians.
  S = S>0?(S<1?S:1):0; // clamp S and I to interval [0,1]
  I = I>0?(I<1?I:1):0;
    
  // Math! Thanks in part to Kyle Miller.
  if(H < 2.09439) {
    r = RGB_MAX*I/3*(1+S*cos(H)/cos(1.047196667-H));
    g = RGB_MAX*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    b = RGB_MAX*I/3*(1-S);
  } else if(H < 4.188787) {
    H = H - 2.09439;
    g = RGB_MAX*I/3*(1+S*cos(H)/cos(1.047196667-H));
    b = RGB_MAX*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    r = RGB_MAX*I/3*(1-S);
  } else {
    H = H - 4.188787;
    b = RGB_MAX*I/3*(1+S*cos(H)/cos(1.047196667-H));
    r = RGB_MAX*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
    g = RGB_MAX*I/3*(1-S);
  }
  rgb[0]=r;
  rgb[1]=g;
  rgb[2]=b;
}
