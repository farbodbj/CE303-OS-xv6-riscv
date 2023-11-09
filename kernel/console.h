#define MAX_HISTORY 16
#define INPUT_BUF 128

// Special keycodes
#define KEY_HOME        0xE0
#define KEY_END         0xE1
#define KEY_UP          0xE2
#define KEY_DN          0xE3
#define KEY_LF          0xE4
#define KEY_RT          0xE5
#define KEY_PGUP        0xE6
#define KEY_PGDN        0xE7
#define KEY_INS         0xE8
#define KEY_DEL         0xE9





struct {
    char bufferArr[MAX_HISTORY][INPUT_BUF];
    uint lengthArr[MAX_HISTORY];
    int numOfCommandsInMem;
    int currentHistory;
} historyBufferArray; 