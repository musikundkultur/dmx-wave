// ====================================================================================================================

// Write the given light levels to channel 1 to 4
// @param ch1_val Light level for channel 1
// @param ch2_val Light level for channel 2
// @param ch3_val Light level for channel 3
// @param ch4_val Light level for channel 4
void dmx_write(byte ch1_val, byte ch2_val, byte ch3_val, byte ch4_val) {
  DMX.beginTransmission();
  DMX.write(1, ch1_val);
  DMX.write(2, ch2_val);
  DMX.write(3, ch3_val);
  DMX.write(4, ch4_val);
  DMX.endTransmission();
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave1() {
  for (int i = 0; i < 2; i++) {
    dmx_write(255, 0, 0, 0);
    delay(500);
    dmx_write(255, 255, 0, 0);
    delay(500);
    dmx_write(255, 255, 255, 0);
    delay(500);
    dmx_write(255, 255, 255, 255);
    delay(500);
    dmx_write(0, 255, 255, 255);
    delay(500);
    dmx_write(0, 0, 255, 255);
    delay(500);
    dmx_write(0, 0, 0, 255);
    delay(500);
    dmx_write(0, 0, 0, 0);
    delay(500);
  }
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave2() {
  dmx_write(255, 0, 0, 0);
  delay(500);
  dmx_write(255, 255, 0, 0);
  delay(500);
  dmx_write(255, 255, 255, 0);
  delay(500);
  dmx_write(255, 255, 255, 255);
  delay(500);
  dmx_write(0, 255, 255, 255);
  delay(500);
  dmx_write(0, 0, 255, 255);
  delay(500);
  dmx_write(0, 0, 0, 255);
  delay(500);
  dmx_write(0, 0, 0, 0);
  delay(500);
  dmx_write(0, 0, 0, 255);
  delay(500);
  dmx_write(0, 0, 255, 255);
  delay(500);
  dmx_write(0, 255, 255, 255);
  delay(500);
  dmx_write(255, 255, 255, 255);
  delay(500);
  dmx_write(255, 255, 255, 0);
  delay(500);
  dmx_write(255, 255, 0, 0);
  delay(500);
  dmx_write(255, 0, 0, 0);
  delay(500);
  dmx_write(0, 0, 0, 0);
  delay(500);
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave3() {
  for (int i = 0; i < 2; i++) {
    dmx_write(255, 0, 0, 0);
    delay(500);
    dmx_write(0, 255, 0, 0);
    delay(500);
    dmx_write(0, 0, 255, 0);
    delay(500);
    dmx_write(0, 0, 0, 255);
    delay(500);
    dmx_write(0, 0, 0, 0);
    delay(500);
  }
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave4() {
  dmx_write(255, 0, 0, 0);
  delay(500);
  dmx_write(0, 255, 0, 0);
  delay(500);
  dmx_write(0, 0, 255, 0);
  delay(500);
  dmx_write(0, 0, 0, 255);
  delay(500);
  dmx_write(0, 0, 255, 0);
  delay(500);
  dmx_write(0, 255, 0, 0);
  delay(500);
  dmx_write(255, 0, 0, 0);
  delay(500);
  dmx_write(0, 0, 0, 0);
  delay(500);
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave5() {
  for (int i = 0; i < 4; i++) {
    dmx_write(255, 0, 255, 0);
    delay(500);
    dmx_write(0, 255, 0, 255);
    delay(500);
  }
  dmx_write(0, 0, 0, 0);
  delay(500);
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave6() {
  for (int i = 0; i < 10; i++) {
    long channel = random(4);
    switch (channel) {
      case 0: dmx_write(255, 0, 0, 0); break;
      case 1: dmx_write(0, 255, 0, 0); break;
      case 2: dmx_write(0, 0, 255, 0); break;
      case 3: dmx_write(0, 0, 0, 255); break;
    }
    delay(500);
  }
  dmx_write(0, 0, 0, 0);
  delay(500);
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_wave7() {
  dmx_write(255, 0, 0, 0);
  delay(250);
  dmx_write(0, 255, 0, 0);
  delay(250);
  dmx_write(255, 255, 0, 0);
  delay(250);
  dmx_write(0, 0, 255, 0);
  delay(250);
  dmx_write(255, 0, 255, 0);
  delay(250);
  dmx_write(0, 255, 255, 0);
  delay(250);
  dmx_write(255, 255, 255, 0);
  delay(250);
  dmx_write(0, 0, 0, 255);
  delay(250);
  dmx_write(255, 0, 0, 255);
  delay(250);
  dmx_write(0, 255, 0, 255);
  delay(250);
  dmx_write(255, 255, 0, 255);
  delay(250);
  dmx_write(0, 0, 255, 255);
  delay(250);
  dmx_write(255, 0, 255, 255);
  delay(250);
  dmx_write(0, 255, 255, 255);
  delay(250);
  dmx_write(255, 255, 255, 0);
  delay(250);
  dmx_write(0, 0, 0, 0);
  delay(250);
}

// --------------------------------------------------------------------------------------------------------------------

void dimmer_wave() {
  long program = random(7);
  switch (program) {
    case 0: dmx_wave1(); break;
    case 1: dmx_wave2(); break;
    case 2: dmx_wave3(); break;
    case 3: dmx_wave4(); break;
    case 4: dmx_wave5(); break;
    case 5: dmx_wave6(); break;
    case 6: dmx_wave7(); break;
  }
}
