#include <stdio.h>
#include <time.h>
#include <xmmintrin.h>

#define TEST_SIZE (1000000L)

float PositionX[TEST_SIZE];
float PositionY[TEST_SIZE];
float PositionZ[TEST_SIZE];
float VelocityX[TEST_SIZE];
float VelocityY[TEST_SIZE];
float VelocityZ[TEST_SIZE];
float AccelerationX[TEST_SIZE];
float AccelerationY[TEST_SIZE];
float AccelerationZ[TEST_SIZE];

void perf0()
{
    for(int i=0;i<TEST_SIZE; i++) {
        AccelerationX = 0.1f;
        AccelerationY = 0.98f;
        AccelerationZ = 0.0f;
    }
}
void perf1()
{
    for(int i=0;i<TEST_SIZE; i+=4) {
        __m128 x = _mm_set4_ps(0.1f,0.1f,0.1f,0.1f);
        __m128 y = _mm_set4_ps(0.98f,0.98f,0.98f,0.98f);
        __m128 z = _mm_set4_ps(0.0f,0.0f,0.0f,0.0f);
    }
}


int main (int argc, char *argv[])
{
    printf("perf-test > ");

    double avg = 0.0, max = 0.0, min = 999999.0;
    int j;
    for(j=0; j<5; j++)
    {
        clock_t begin = clock();
        for ( i=0; i<TEST_SIZE; i++) {
            __m128 M0 = _mm_set1_ps(0);
            velocity[i].x += appearance[i].x;
            velocity[i].y += appearance[i].y;
            displacement[i].x += velocity[i].x;
            displacement[i].y += velocity[i].y;
        }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        //printf ("Time: %f\n", time_spent);
        avg += time_spent;
        max = max > time_spent ? max : time_spent;
        min = min < time_spent ? min : time_spent;
    }
    printf ("AVG: %f | MIN: %f | MAX: %f\n", avg / j, min, max);
    return 0;
}
