#include <stdio.h>

#define SAMPLE_SIZE 3000

struct Sensor_Data {
    float time;
    double probability;
};
struct Sensor {
    int id;
    double threshold;
    struct Sensor_Data data[SAMPLE_SIZE];
    int  object_detection[300000];
};
int main(void){
    FILE *stream = fopen("sensor1.txt", "r");
    if (stream == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    FILE *stream2 = fopen("sensor2.txt", "r");
     if (stream2 == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    struct Sensor_Data *str = malloc(SAMPLE_SIZE * sizeof(struct Sensor_Data));

    fegts(str, SAMPLE_SIZE, stream);
    fegts(str, SAMPLE_SIZE, stream2);
    Sensor sensor1 = {}

};