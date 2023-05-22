// ====================================================================================================================

void init_par_leds() {
  byte master_dimmer_brightness{127};
  DMX.beginTransmission();
  DMX.write(1, master_dimmer_brightness);
  DMX.write(5, 0);
  DMX.write(6, 0);
  DMX.write(7, master_dimmer_brightness);
  DMX.write(11, 0);
  DMX.write(12, 0);
  DMX.write(13, master_dimmer_brightness);
  DMX.write(17, 0);
  DMX.write(18, 0);
  DMX.write(19, master_dimmer_brightness);
  DMX.write(23, 0);
  DMX.write(24, 0);
  DMX.endTransmission();
}

// ====================================================================================================================

// Message mapping
// ch1 = MASTER BRIGHTNESS we will ignore that and initialize to a fixed value in the setup;
// ch2 = RED;
// ch3 = GREEN;
// ch4 = BLUE;
// ch5 = program ? at least it will move through the lights when value is 100, we ignore this and initially set it to 0;
// ch6 = strobo lights the higher the value the quicker it will be, we ignore this and set it 0;
typedef struct ParLedMessage {
  int lamp;
  byte red;
  byte green;
  byte blue;
} ParLedMessage;

// --------------------------------------------------------------------------------------------------------------------

int lampToChannel(int lamp) {
  switch (lamp) {
    case 1: return 1;
    case 2: return 7;
    case 3: return 13;
    case 4: return 19;
  }
  return 506;
}

// --------------------------------------------------------------------------------------------------------------------

#ifdef TESTING
test(lampToChannel) {
  assertEqual(lampToChannel(1), (int) 1);
  assertEqual(lampToChannel(2), (int) 7);
  assertEqual(lampToChannel(3), (int) 13);
  assertEqual(lampToChannel(4), (int) 19);
}
#endif

// --------------------------------------------------------------------------------------------------------------------

void write_message(struct ParLedMessage message) {
  int start_channel = lampToChannel(message.lamp);
  DMX.write(start_channel + 1, message.red);
  DMX.write(start_channel + 2, message.green);
  DMX.write(start_channel + 3, message.blue);
}

// --------------------------------------------------------------------------------------------------------------------

#define LAMP_COUNT 4

// --------------------------------------------------------------------------------------------------------------------

typedef struct ParLedMessages {
  ParLedMessage messages[LAMP_COUNT];
} ParLedMessages;

// --------------------------------------------------------------------------------------------------------------------

struct ParLedMessages all_lamps(byte red, byte green, byte blue) {
  return ParLedMessages{
    {
      {1, red, green, blue},
      {2, red, green, blue},
      {3, red, green, blue},
      {4, red, green, blue},
    }
  };
}

// --------------------------------------------------------------------------------------------------------------------

struct RGB {
  byte red;
  byte green;
  byte blue;
};

struct ParLedMessages lamps_with(struct RGB l1, struct RGB l2, struct RGB l3, struct RGB l4) {
  return ParLedMessages{
    {
      {1, l1.red, l1.green, l1.blue},
      {2, l2.red, l2.green, l2.blue},
      {3, l3.red, l3.green, l3.blue},
      {4, l4.red, l4.green, l4.blue},
    }
  };
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_write_par_led(struct ParLedMessages messages) {
  DMX.beginTransmission();
  for (int i = 0; i < LAMP_COUNT; i++) {
    write_message(messages.messages[i]);
  }
  DMX.endTransmission();
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_par_wave1() {
  // fade on
  for (byte i = 0; i < 250; i += 5) {
    dmx_write_par_led(lamps_with({i, 0, 0}, {i, 0, 0}, {i, 0, 0}, {i, 0, 0}));
  }
  for (byte i = 0; i < 250; i += 5) {
    dmx_write_par_led(lamps_with({255, i, 0}, {255, i, 0}, {255, i, 0}, {255, i, 0}));
  }
  for (byte i = 0; i < 250; i += 5) {
    dmx_write_par_led(lamps_with({255, 255, i}, {255, 255, i}, {255, 255, i}, {255, 255, i}));
  }

  // fade off
  for (byte i = 255; i > 0; i -= 5) {
    dmx_write_par_led(lamps_with({i, 255, 255}, {i, 255, 255}, {i, 255, 255}, {i, 255, 255}));
  }
  for (byte i = 255; i > 0; i -= 5 ) {
    dmx_write_par_led(lamps_with({0, i, 255}, {0, i, 255}, {0, i, 255}, {0, i, 255}));
  }
  for (byte i = 255; i > 0; i -= 5) {
    dmx_write_par_led(lamps_with({0, 0, i}, {0, 0, i}, {0, 0, i}, {0, 0, i}));
  }

  dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_par_wave2() {
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, i, i}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, 255, 255}, {0, i, i}, {0, 0, 0}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, 255, 255}, {0, 255, 255}, {0, i, i}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, 255, 255}, {0, 255, 255}, {0, 255, 255}, {0, i, i}));
    }

    for (byte i = 255; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({0, i, i}, {0, 255, 255}, {0, 255, 255}, {0, 255, 255}));
    }
    for (byte i = 255; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {0, i, i}, {0, 255, 255}, {0, 255, 255}));
    }
    for (byte i = 255; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, i, i}, {0, 255, 255}));
    }
    for (byte i = 255; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, i, i}));
    }
    dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_par_wave3() {
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({i, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({255, i, 0}, {i, 0, 0}, {0, 0, 0}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({255, 255, i}, {255, i, 0}, {i, 0, 0}, {0, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({255, 255, 255}, {255, 255, i}, {255, i, 0}, {i, 0, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({255, 255, 255}, {255, 255, 255}, {255, 255, i}, {255, i, 0}));
    }
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, i}));
    }
    for (byte i = 255; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({i, i, i}, {i, i, i}, {i, i, i}, {i, i, i}));
    }
    dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
}

// --------------------------------------------------------------------------------------------------------------------

void dmx_par_wave4() {
    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({i, i, i}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
    }

    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({250 - i, 250 - i, 250 - i}, {i, i, i}, {0, 0, 0}, {0, 0, 0}));
    }

    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {250 - i, 250 - i, 250 - i}, {i, i, i}, {0, 0, 0}));
    }

    for (byte i = 0; i < 250; i += 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {250 - i, 250 - i, 250 - i}, {i, i, i}));
    }

    for (byte i = 25; i > 0; i -= 5) {
        dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {i, i, i}));
    }

    dmx_write_par_led(lamps_with({0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
}

// --------------------------------------------------------------------------------------------------------------------

void par_wave() {
  // long program = random(4);
  // switch (program) {
  //   case 0: dmx_par_wave1(); break;
  //   case 1: dmx_par_wave2(); break;
  //   case 2: dmx_par_wave3(); break;
  //   case 3: dmx_par_wave4(); break;
  // }
  dmx_par_wave4();
}
