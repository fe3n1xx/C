#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

char localTime[256];
char currentTime[256];
bool SRunning;

int main() {
    //
    SRunning = true;
    while (SRunning) {
        time_t rawtime;
        struct tm * timeinfo;

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        // TIME: "%s", asctime(timeinfo), e.g. "Sat Nov  7 17:55:18 2026"

        snprintf(currentTime, sizeof(currentTime), "%s", asctime(timeinfo));

        if (strcmp(localTime, currentTime) != 0) {
            printf("%s", currentTime);

            snprintf(localTime, sizeof(localTime), "%s", currentTime);
        }

        sleep(1);
    }
    return 0;
}