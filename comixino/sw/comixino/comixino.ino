// Description: COMIXINO plays COMiX files using High Speed Direct Connection
// Author: issalig
// Date: 10/06/2005
// Acknowledgements: TZXDuino, HDSC project
//
// Dependencies:
// U8glib version 1.19.1,  SdFat version 1.1.4, SoftwareSerial version 1.0
//
// Warnings: This code is only tested on Arduino Nano
//           Memory usage higher than 80% may cause problems with u8glib (oled) library
//           Record function is not properly working. It misses bytes!!!!

// Q is used as output and /EF4 as input (see HDSC project documentation)

#include <SdFat.h>

#define COMIXINO_VERSION "1.0.0"
#define COMIXINO_BUILD_DATE __DATE__ " " __TIME__

//#define SERIALSCREEN  1  // print text on serial, mainly for debug
#define OLED1306      1  // oled display enabled
//#define SW_SERIAL     1  // use software serial instead of hardware serial

#ifdef SW_SERIAL
    #include <SoftwareSerial.h>
    //#include <AltSoftSerial.h>
    //#include <NeoSWSerial.h>
#endif

#ifdef SW_SERIAL
// pins for rx/tx software serial
#define SW_RX 8
#define SW_TX 9
SoftwareSerial sw_serial(SW_RX, SW_TX, false); // RX, TX
//AltSoftSerial  sw_serial;
//NeoSWSerial sw_serial(SW_RX, SW_TX);
#endif

#ifdef OLED1306
    #include <U8glib.h> //using this because it is smaller than U8g2
    U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
    //U8GLIB_SSD1306_128X632 u8g(U8G_I2C_OPT_NONE); //for smaller screens
    char line0[17] = {0};
    char line1[17] = {0};
    char line2[17] = {0};
    char line3[17] = {0};
#endif

// comx simple test program generated with emma02 emulator
// total size array is 47
// size can be computed as byte [10] + 6
const unsigned char sample_program[] PROGMEM = {
    0x06, // [0] type (see below)
    0x43, 0x4f, 0x4d, 0x58, // [1-4] header "COMX"
    0x00, 0x0c, // [5-6] DEFUS value (ram starts at 0x4400, DEFUS is the offset)
    0x00, 0x20, // [7-8] End of program address. size info 0x20 is 32
    0x00, 0x29, // [9-10] String start address size info 0x29 is 41, byte [41] is before 0xff 0xff marker
    0x00, 0x29, // [11-12] Array start address
    0x00, 0x29, // [13-14] End of data address
    0x00, 0x00, 0x20, // [15] is first byte in RAM
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, // beginning of line
    0x0a, // line number 10
    0x0d, // line length 13
    0x86, // Token for PRINT
    0xcf, // Token for string beginning
    0x43, 0x4f, 0x4d, 0x49, 0x58, 0x49, 0x4e, 0x4f, // COMIXINO string
    0xce, // Token for string end
    0x0d, // end of line
    0xff, 0xff,
    0x03, 0x84,
    0x0d // final terminator
};

// COMX formats. Specfied in first byte
// 1 - format 1: Byte 1-4: as you state COMX, Byte 5-6: start address, Byte 7-8: end address, Byte 9-10: execution address
// 2 - old BASIC
// 3 - F&M BASIC
// 4 - old data (faulty)
// 5 - data (Byte 1-2 "CO", Byte 3/4 data length, 5/6 array length
// 6 - BASIC

//128x22px / 8 = 352 bytes
const unsigned char logo_comixino[] PROGMEM={
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xf8, 0x1f, 0xe0, 0x7f, 0xe0, 0x03, 0xe0, 0xe3, 0x70, 0x00, 0x8f, 0xe3, 0x03, 0x1c, 0xf8, 0x1f, 
0xfe, 0x7f, 0xf8, 0xff, 0xe1, 0x07, 0xe0, 0xe3, 0xf0, 0x80, 0x87, 0xe3, 0x07, 0x1c, 0xfe, 0x7f, 
0xfe, 0xff, 0xf8, 0xff, 0xe3, 0x07, 0xf0, 0xe3, 0xe0, 0xc1, 0x83, 0xe3, 0x0f, 0x1c, 0xff, 0x7f, 
0x1f, 0xf0, 0x7c, 0xc0, 0xe3, 0x0f, 0xf8, 0xe3, 0xc0, 0xe3, 0x81, 0xe3, 0x1f, 0x1c, 0x0f, 0xf8, 
0x0f, 0xe0, 0x3c, 0x80, 0xe3, 0x0f, 0xf8, 0xe3, 0x80, 0xf7, 0x80, 0xe3, 0x3f, 0x1c, 0x07, 0xf0, 
0x07, 0x00, 0x1c, 0x80, 0xe3, 0x1e, 0xbc, 0xe3, 0x00, 0x7f, 0x80, 0xe3, 0x7c, 0x1c, 0x07, 0xe0, 
0x07, 0x00, 0x1c, 0x80, 0xe3, 0x1c, 0xbc, 0xe3, 0x00, 0x3e, 0x80, 0xe3, 0x78, 0x1c, 0x07, 0xe0, 
0x07, 0x00, 0x1c, 0x80, 0xe3, 0x3c, 0x9e, 0xe3, 0x00, 0x7f, 0x80, 0xe3, 0xf0, 0x1c, 0x07, 0xe0, 
0x07, 0x00, 0x1c, 0x80, 0xe3, 0x38, 0x8e, 0xe3, 0x80, 0xff, 0x80, 0xe3, 0xe0, 0x1d, 0x07, 0xe0, 
0x0f, 0xe0, 0x3c, 0x80, 0xe3, 0x78, 0x8f, 0xe3, 0xc0, 0xe7, 0x81, 0xe3, 0xc0, 0x1f, 0x07, 0xe0, 
0x0f, 0xf0, 0x3c, 0xc0, 0xe3, 0xf0, 0x87, 0xe3, 0xe0, 0xc3, 0x83, 0xe3, 0xc0, 0x1f, 0x0f, 0xf0, 
0xfe, 0xff, 0xf8, 0xff, 0xe3, 0xf0, 0x87, 0xe3, 0xf0, 0x81, 0x87, 0xe3, 0x80, 0x1f, 0xff, 0xff, 
0xfe, 0xff, 0xf8, 0xff, 0xe1, 0xe0, 0x83, 0xe3, 0xf8, 0x00, 0x8f, 0xe3, 0x00, 0x1f, 0xfe, 0x7f, 
0xf8, 0x3f, 0xe0, 0xff, 0xe0, 0xc0, 0x81, 0xe3, 0x38, 0x00, 0x9e, 0xe3, 0x00, 0x1e, 0xfc, 0x1f, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff  
}; 

unsigned char is_stopped = false;
unsigned long bytes_read = 0;

#define BUFF_SIZE 64
byte end_of_file = false;

SdFat sd;                           // Initialise Sd card
SdFile entry;                       // SD card file

#define FILENAME_LENGTH 64         // Maximum length for scrolling filename

char file_name[FILENAME_LENGTH + 1];  // Current filename
char sfile_name[13];                 // Short filename variable
unsigned long file_size;             // filesize used for dimensioning AY files

// Directory navigation
//#define MAX_DIR_DEPTH 8
//#define MAX_DIR_NAME_LEN 32
//char dir_stack[MAX_DIR_DEPTH][MAX_DIR_NAME_LEN];
//int dir_depth = 0;  // Current depth in directory tree (0 = root)

// Pin definitions
#define SD_CS     10                 // Sd card chip select pin

#define BTN_UP     4                 // Up button
#define BTN_DOWN   3                 // Down button
#define BTN_PLAY   2                 // Play Button
#define BTN_STOP   5                 // Stop Button
#define BTN_ROOT   6                 // Return to SD card root
#define BTN_RECORD 7                 // Record Button


//scroll
#define SCROLL_SPEED 250             // text scroll delay
#define SCROLL_WAIT 3000             // Delay before scrolling starts

unsigned char scroll_pos = 0;        // Stores scrolling text position
unsigned long scroll_time = millis() + SCROLL_WAIT;

unsigned char start = 0;             // Currently playing flag
unsigned char pause_on = 0;          // Pause state
unsigned int current_file = 1;       // Current position in directory
unsigned int max_file = 0;           // Total number of files in directory
unsigned char is_dir = 0;            // Is the current file a directory
unsigned long time_diff = 0;         // button debounce

bool sd_present = true;              // SD card present flag
unsigned long last_sd_check = 0;
SPISettings sd_speed = SPI_FULL_SPEED;      // SD card speed, other values are SPI_HALF_SPEED and SPI_QUARTER_SPEED

// baudrate settings
const long baudrates[] = {1200, 4800, 9600, 19200};
const int NUM_BAUDRATES = sizeof(baudrates) / sizeof(baudrates[0]);
int baudrate_index = 2; // Default to 9600

// strings
const char fmt1_str[] PROGMEM = "Fmt1";
const char old_basic_str[] PROGMEM = "Old BASIC";
const char fm_basic_str[] PROGMEM = "FM BASIC";
const char old_data_str[] PROGMEM = "Old Data";
const char data_str[] PROGMEM = "Data";
const char basic_str[] PROGMEM = "BASIC";
const char unknown_str[] PROGMEM = "Unknown";

// function prototypes, the band that make this work
void show_splashscreen();

void check_sd();
void handle_buttons();
void handle_scrolling();

void print_text(const char* text, int l);  // Print text to screen
void print_text(const __FlashStringHelper* text, int l);  // Overloaded function for F() macro
void scroll_text(const char* text);  // Scroll text on screen

void seek_file(int pos);             // Move to a set position in the directory
void get_max_file();                 // Get the total number of files in the directory
void change_dir();                   // Change directory
void get_next_record_filename(char* out_name, size_t out_size);
void up_file();                      // Move up a file in the directory
void down_file();                    // Move down a file in the directory

void stop_file();                    // Stop playback
void play_file();                    // Play selected file

void comix_play(const char* filename);     // Play a file
void comix_play_sample();
void comix_stop();                   // Stop 
void comix_record(const char* filename, unsigned long max_bytes, unsigned long pre_timeout_ms, unsigned long post_timeout_ms);
void settings_mode();

void flush_serial();


// setting this up for the first time
void setup() {
    Serial.begin(baudrates[baudrate_index]);

    show_splashscreen();        
    
    #ifdef SW_SERIAL
    pinMode(SW_RX, INPUT_PULLUP);
    pinMode(SW_TX, OUTPUT);
    sw_serial.begin(baudrates[baudrate_index]); // Set the baud rate for sw_serial
    #endif 

    //comix_play_sample();
    
    pinMode(SD_CS, OUTPUT); 
    digitalWrite(SD_CS, HIGH);
    
    delay(100);
    while (!sd.begin(SD_CS, sd_speed)) {
        print_text(F("No SD"), 0);    
        delay(100);
        //return;
    }

    sd.chdir();                        // set SD to root directory    
    is_stopped = true;
  
    // General Pin settings
    pinMode(BTN_PLAY, INPUT_PULLUP);
    digitalWrite(BTN_PLAY, HIGH);

    pinMode(BTN_STOP, INPUT_PULLUP);
    digitalWrite(BTN_STOP, HIGH);
    
    pinMode(BTN_UP, INPUT_PULLUP);
    digitalWrite(BTN_UP, HIGH);
    
    pinMode(BTN_DOWN, INPUT_PULLUP);
    digitalWrite(BTN_DOWN, HIGH);
    
    pinMode(BTN_RECORD, INPUT_PULLUP);
    digitalWrite(BTN_RECORD, HIGH);
    
    pinMode(BTN_ROOT, INPUT_PULLUP);
    digitalWrite(BTN_ROOT, HIGH);

    get_max_file();                     // get the total number of files in the directory
    seek_file(current_file);            // move to the first file in the directory
    print_text(F("Ready"), 0);
}

// let the fun begin
void loop(void) {
    check_sd();
    handle_scrolling();
    handle_buttons();
}

// utility functions

void show_splashscreen() {
  #ifdef OLED1306
    u8g.firstPage();
    do {        
        u8g.drawXBMP(0, 21, 128, 22, logo_comixino);
    } while (u8g.nextPage());
    delay(1500);

  #endif
}

void check_sd(){
    // Check SD card every second
    if (millis() - last_sd_check > 1000) {
        last_sd_check = millis();
        
        // Only check if SD card was previously missing
        if (!sd_present) {
            if (sd.begin(SD_CS, sd_speed)) {
                print_text(F("SD Card OK"), 0);
                sd.chdir("/");  // Explicitly go to root
                get_max_file();
                seek_file(current_file);
                print_text(F("Ready"), 0);
                sd_present = true;
            }
        } else {
            // SD card was present, just check if it's still there
            // Use a lightweight check instead of sd.begin()
            SdFile test_file;
            if (!test_file.open("/", O_READ)) {
                // SD card is no longer accessible
                test_file.close();
                print_text(F("No SD Card"), 0);
                print_text("", 1);  // Clear filename line
                print_text("", 2);  // Clear info line
                print_text("", 3);  // Clear status line
                sd_present = false;
            } else {
                test_file.close();
                // SD card is still present, don't call sd.begin()
            }
        }
    }
}

void handle_scrolling() {
    // Don't scroll if SD card is not present or no files
    if (!sd_present || max_file == 0) {
        return;
    }

    if ((millis() >= scroll_time) && start == 0 && (strlen(file_name) > 15)) {
        scroll_time = millis() + SCROLL_SPEED;
        scroll_text(file_name);
        scroll_pos += 1;
        if (scroll_pos > strlen(file_name)) {
            scroll_pos = 0;
            scroll_time = millis() + SCROLL_WAIT;
            scroll_text(file_name);
        }
    }
}

void handle_buttons() {
    if (millis() - time_diff > 50) {   // check every 50ms
        time_diff = millis();

        // --- Print key name when pressed ---
        // if (digitalRead(BTN_UP) == LOW) {
        //     print_text("UP", 3);
        // }
        // if (digitalRead(BTN_DOWN) == LOW) {
        //     print_text("DWN", 3);
        // }
        // if (digitalRead(BTN_PLAY) == LOW) {
        //     print_text("PLAY", 3);
        // }
        // if (digitalRead(BTN_STOP) == LOW) {
        //     print_text("STOP", 3);
        // }
        // if (digitalRead(BTN_ROOT) == LOW) {
        //     print_text("ROOT", 3);
        // }
        // if (digitalRead(BTN_RECORD) == LOW) {
        //     print_text("REC", 3);
        // }



static unsigned long stop_press_time = 0;
static bool stop_long_handled = false;

if (digitalRead(BTN_STOP) == LOW) {
    if (stop_press_time == 0) {
        stop_press_time = millis();
        stop_long_handled = false;
    }
    // Long press: >1.5s and not playing/recording
    if (!stop_long_handled && (millis() - stop_press_time > 1500) && start == 0) {
        settings_mode();
        stop_long_handled = true;
        // Wait for release to avoid double trigger
        while (digitalRead(BTN_STOP) == LOW) delay(50);
        stop_press_time = 0;
        return;
    }
} else if (stop_press_time != 0) {
    // Button released before long press threshold
    if (!stop_long_handled) {
        if (start == 1) {
            is_stopped = true;  // Stop playback/recording
        } else {
            // Go to root if not playing or recording            
            sd.chdir("/");
            get_max_file();
            current_file = 1;
            seek_file(current_file);
        }
    }
    stop_press_time = 0;
    stop_long_handled = false;
}
        if (digitalRead(BTN_PLAY) == LOW) {
            if (start == 0) {
                play_file();
                delay(200);
            } else {
                if (pause_on == 0) {
                    print_text(F("Paused"), 0);
                    pause_on = 1;
                } else {
                    print_text(F("Playing"), 0);
                    pause_on = 0;
                }
            }
            while (digitalRead(BTN_PLAY) == LOW) {
                delay(50);
            }
        }
        if (digitalRead(BTN_ROOT) == LOW && start == 0) {
            sd.chdir("/");
            get_max_file();
            current_file = 1;
            seek_file(current_file);
            while (digitalRead(BTN_ROOT) == LOW) {
                delay(50);
            }
        }

        if (digitalRead(BTN_UP) == LOW && start == 0) {
            scroll_time = millis() + SCROLL_WAIT;
            scroll_pos = 0;
            up_file();
            while (digitalRead(BTN_UP) == LOW) {
                delay(50);
            }
        }
        if (digitalRead(BTN_DOWN) == LOW && start == 0) {
            scroll_time = millis() + SCROLL_WAIT;
            scroll_pos = 0;
            down_file();
            while (digitalRead(BTN_DOWN) == LOW) {
                delay(50);
            }
        }

        if (digitalRead(BTN_RECORD) == LOW && start == 0) {
            while (digitalRead(BTN_RECORD) == LOW) {
                delay(50);
            }            
            char rec_name[20]; // cmxXXXX.comx
            get_next_record_filename(rec_name, sizeof(rec_name));
            flush_serial();
            comix_record(rec_name, 65536, 5000, 1500);  // 5s for sync, 1s for end
            //update dir
            get_max_file();
            seek_file(current_file);
        }
    }
}

void flush_serial(){
    // Flush serial buffer before starting to read new data
    #ifdef SW_SERIAL
    while (sw_serial.available()) {
        sw_serial.read();
    }
    #else
    while (Serial.available()) {
      Serial.read();
    }
    #endif
}

void up_file() {
    //if (max_file == 0) return; // No files

    current_file--;
    if (current_file < 1) {
        get_max_file();
        current_file = max_file;
    }
    seek_file(current_file);
}

void down_file() {
    //if (max_file == 0) return; // No files

    current_file++;
    if (current_file > max_file) {
        current_file = 1;
    }
    seek_file(current_file);
}

void seek_file(int pos) {
    entry.cwd()->rewind();
    for (unsigned int i = 1; i <= current_file; i++) {
        entry.openNext(entry.cwd(), O_READ);
        entry.getName(file_name, FILENAME_LENGTH);
        entry.getSFN(sfile_name);
        file_size = entry.fileSize();
        if (entry.isDir()) {
            is_dir = 1;            
        } else {
            is_dir = 0;
        }
        entry.close();
    }

     // Show file size on first line
    char line[17];
    if (is_dir) {
        snprintf(line, sizeof(line), "<DIR>");
    } else {
        snprintf(line, sizeof(line), "Size: %lu", file_size);
    } 
    print_text(line, 0);

    // Show COMX type on line 2 if applicable
    if (!is_dir && is_comx_file(file_name)) {
        SdFile temp_file;
        if (temp_file.open(sfile_name, O_READ)) {
            unsigned char first_byte = 0;
            int read_result = temp_file.read(&first_byte, 1);
            temp_file.close();
            if (read_result == 1) {
                char type_str[12];// = "Unknown";
                switch (first_byte) {
                    case 1: strcpy_P(type_str, fmt1_str); break;
                    case 2: strcpy_P(type_str, old_basic_str); break;
                    case 3: strcpy_P(type_str, fm_basic_str); break;
                    case 4: strcpy_P(type_str, old_data_str); break;
                    case 5: strcpy_P(type_str, data_str); break;
                    case 6: strcpy_P(type_str, basic_str); break;
                    default: strcpy_P(type_str, unknown_str); break;
                }
                snprintf(line, sizeof(line), "%s", type_str);                
            } else {
                snprintf(line, sizeof(line), "Read Err");
            }
            print_text(line, 2);
        } else {
            print_text(F("Open Err"), 2);
        }
    } else {
        print_text("", 2); //clear line if not a comx file        
    }
    //end comx type

    scroll_pos = 0;
    scroll_text(file_name);
}

void stop_file() {
    comix_stop();
    if (start == 1) {
        print_text(F("Stopped"), 0);
        delay(1000); // Wait 2 seconds
        print_text("", 0); // Clear the first line
        start = 0;
    }
}

void play_file() {
    if (is_dir == 1) {
        change_dir();
    } else {
        if (entry.cwd()->exists(sfile_name)) {
            print_text(F("Playing"), 0);
            scroll_pos = 0;
            pause_on = 0;
            scroll_text(file_name);
            start = 1;
            comix_play(sfile_name); // Play the file using the short filename
        } else {
            print_text(F("No File"), 1);
        }
    }
}

void get_max_file() {

    entry.cwd()->rewind();
    max_file = 0;
    while (entry.openNext(entry.cwd(), O_READ)) {
        entry.getName(file_name, FILENAME_LENGTH);
        entry.close();
        max_file++;
    }

    entry.cwd()->rewind();
}

void change_dir() {
    sd.chdir(file_name, true);    
    get_max_file();
    current_file = 1;
    seek_file(current_file);
}

void scroll_text(const char* text) {
    if (scroll_pos < 0) {
        scroll_pos = 0;
    }
    char outtext[17];
    size_t text_len = strlen(text); // Store length as size_t
    
    if (is_dir) {
        outtext[0] = 0x3E;
        for (int i = 1; i < 16; i++) {
            int p = i + scroll_pos - 1;
            if (p >= 0 && (size_t)p < text_len) { // Cast p to size_t for comparison
                outtext[i] = text[p];
            } else {
                outtext[i] = '\0';
            }
        }
    } else {
        for (int i = 0; i < 16; i++) {
            int p = i + scroll_pos;
            if (p >= 0 && (size_t)p < text_len) { // Cast p to size_t for comparison
                outtext[i] = text[p];
            } else {
                outtext[i] = '\0';
            }
        }
    }
    outtext[16] = '\0';
    print_text(outtext, 1);
}

void print_text(const char* text, int l) {
    #ifdef SERIALSCREEN
    Serial.println(text);
    #endif

    #ifdef OLED1306
    if (l == 0) {
        strncpy(line0, text, 16);
        line0[16] = '\0';
    } else if (l == 1) {
        strncpy(line1, text, 16);
        line1[16] = '\0';
    } else if (l == 2) {
        strncpy(line2, text, 16);
        line2[16] = '\0';
    } else if (l == 3) {
        strncpy(line3, text, 16);
        line3[16] = '\0';
    }

    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_7x14);
        u8g.drawStr(0, 15, line0);
        u8g.drawStr(0, 30, line1);
        if (line2[0]) {
            u8g.drawStr(0, 45, line2);
        }

        if (line3[0]) {
            u8g.drawStr(0, 60, line3);
        }
    } while (u8g.nextPage());
    #endif
}

void print_text(const __FlashStringHelper* text, int l) {
    char buf[17];
    strncpy_P(buf, (PGM_P)text, 16);
    buf[16] = '\0';
    print_text(buf, l); // Call original function
}

void clear_screen_text() {
    for(unsigned int i = 0; i < 4; i++) {     
        print_text("", i);
    }
}    
void clear_screen_graph(){
    #ifdef OLED1306
    u8g.firstPage();
    do {
        u8g.setColorIndex(0); // 0 = Black
        u8g.drawBox(0, 0, 128, 64); // Fill the whole screen with black
        u8g.setColorIndex(1); // 1 = White (for subsequent drawing)
    } while (u8g.nextPage());
    #endif
}


void comix_stop() {
    is_stopped = true;
    entry.close();
    bytes_read = 0;
}

void comix_pause() {
    is_stopped = pause_on;
}

bool is_comx_file(const char* filename) {
    int len = strlen(filename);
    if (len < 5) return false;
    const char* ext = filename + (len - 5);
    // Case-insensitive compare
    return (strcasecmp(ext, ".comx") == 0);
}

void comix_play_sample() {
    for (unsigned int i = 0; i < sizeof(sample_program); i++) {
        #ifdef SW_SERIAL
        sw_serial.write(sample_program[i]);
        #else
        Serial.write(sample_program[i]);
        #endif
    }
}

void comix_play(const char* filename) {
    //print_text(F("Comix play"),2);
    if (entry.isOpen()) {
        entry.close();
    }

    if (!entry.open(filename, O_READ)) {
        print_text(F("Open error"), 0);
        return;
    }
    bytes_read = 0;
    print_text(F("Playing"), 0);

    is_stopped = false;
    end_of_file = false;

    int buffsize = 32;  // Increased buffer size for better performance
    char mybuffer[buffsize];
    int bytes_read_count;

    unsigned long total_size = entry.fileSize();
    unsigned long last_button_check = millis();
    unsigned long last_progress_update = millis();
    char progress_line[32];

    while (!end_of_file && !is_stopped) {
        // Check for stop button press every 50ms
        if (millis() - last_button_check > 50) {
            last_button_check = millis();
            if (digitalRead(BTN_STOP) == LOW) {
                is_stopped = true;
                print_text(F("Stopping"), 0);
                delay(100);
                break;
            }
            
            // Handle pause functionality
            if (pause_on) {
                delay(50);  // Small delay to avoid busy waiting
                continue;   // Skip processing while paused
            }
        }
        
        bytes_read_count = entry.read(mybuffer, buffsize);

        if (bytes_read_count > 0) {
            // write to serial or software serial
            #ifdef SW_SERIAL
            sw_serial.write(mybuffer, bytes_read_count);
            #else
            Serial.write(mybuffer, bytes_read_count);
            #endif
            bytes_read += bytes_read_count;

            // Show progress every 1 second
            if (millis() - last_progress_update > 1000) {
                last_progress_update = millis();
                int percent = (total_size > 0) ? ((100 * bytes_read) / total_size) : 0;
                snprintf(progress_line, sizeof(progress_line), "Playing (%d%%)", percent);
                print_text(progress_line, 0);
            }

            if (bytes_read_count < buffsize && bytes_read_count > 0) {
                end_of_file = true;
            }
        } else {
            end_of_file = true;
        }
    }

    if (end_of_file) {
        print_text(F("Complete"), 0);
    } 
    
    delay(700); 
    stop_file();
}

void comix_record(const char* filename, unsigned long max_bytes, unsigned long pre_timeout_ms, unsigned long post_timeout_ms) {
    SdFile record_file;
    unsigned long bytes_written = 0;
    unsigned long start_time = millis();
    const int RAM_BUF_SIZE = 128;
    unsigned char ram_buffer[RAM_BUF_SIZE];
    int ram_buf_pos = 0;

    if (!record_file.open(filename, O_WRITE | O_CREAT | O_TRUNC)) {
        print_text(F("Open error"), 0);
        return;
    }

    print_text(F("Recording"), 0);
    print_text(filename, 1);

    while (bytes_written < max_bytes && (millis() - start_time) < post_timeout_ms) {
        // Stop recording if STOP button is pressed
        if (digitalRead(BTN_STOP) == LOW) {
            print_text(F("Stopped"), 0);
            break;
        }
        #ifdef SW_SERIAL
        while (sw_serial.available() && bytes_written < max_bytes)
        #else
        while (Serial.available() && bytes_written < max_bytes)
        #endif        
        {
            unsigned char b;
            #ifdef SW_SERIAL
            b = sw_serial.read();
            #else
            b = Serial.read();
            #endif
            ram_buffer[ram_buf_pos++] = b;
            bytes_written++;
            start_time = millis();
            if (ram_buf_pos == RAM_BUF_SIZE) {
                record_file.write(ram_buffer, RAM_BUF_SIZE);
                record_file.flush();
                ram_buf_pos = 0;
            }
        }
    }

    // write remaining bytes
    if (ram_buf_pos > 0) {
        record_file.write(ram_buffer, ram_buf_pos);
    }

    record_file.flush();
    record_file.close();
    char buffer[17];
    snprintf(buffer, sizeof(buffer), "Written: %lu", bytes_written);
    print_text(buffer, 0);
    delay(1000);
}

// Function to get the next available filename for recording
// It will search for the first available filename in the format "cmxXXX.comx"
void get_next_record_filename(char* out_name, size_t out_size) {
    for (int i = 0; i < 100; i++) {
        snprintf(out_name, out_size, "cmx%03d.comx", i);
        if (!sd.exists(out_name)) {
            return;
        }
    }
    snprintf(out_name, out_size, "cmx999.comx");
}

void settings_mode() {
    bool in_settings = true;
    unsigned long last_action = millis();

    print_text(F("COMIXINO " COMIXINO_VERSION), 0);    
    print_text(F(__DATE__), 1);
    print_text(F("PLAY Sample"),2);
    print_text(F("STOP Exit"), 3);

    while (in_settings) {
        // Play sample when PLAY button is pressed
        if (digitalRead(BTN_PLAY) == LOW) {
            print_text(F("Sample Out"), 0);
            comix_play_sample();
            delay(800); // Prevent repeated triggers
            while (digitalRead(BTN_PLAY) == LOW) delay(50); // Wait for release
            
            // Restore info display
            print_text(F("COMIXINO " COMIXINO_VERSION), 0);    
            print_text(F(__DATE__), 1);
            print_text(F("PLAY Sample"),2);
            print_text(F("STOP Exit"), 3);
            last_action = millis();
        }

        // Exit settings
        if (digitalRead(BTN_STOP) == LOW) {
            print_text(F("Settings Exit"), 0);
            delay(800);
            in_settings = false;
            break;
        }

        // --- Timeout after 10 seconds of inactivity ---
        if (millis() - last_action > 10000) {
            print_text(F("Timeout"), 0);            
            delay(800);
            clear_screen_text();
            in_settings = false;
            break;
        }

        delay(50);
    }

    clear_screen_text();
    print_text(F("Ready"), 0);
}
