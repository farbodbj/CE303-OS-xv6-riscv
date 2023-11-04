#define MAX_HISTORY 16
#define INPUT_BUF 128

struct {
    char bufferArr[MAX_HISTORY][INPUT_BUF];
    uint lengthArr[MAX_HISTORY];
    int numOfCommandsInMem;
    int currentHistory;
} historyBufferArray; 