#include <stdio.h>
#include <time.h>
#include <xmmintrin.h>

typedef struct
{
	float x;
	float y;
} Displacement;

typedef struct
{
	float x;
	float y;
} Velocity;

typedef struct
{
	float x;
	float y;
} Appearance;

#define TEST_SIZE (1000000L)

Displacement displacement[TEST_SIZE];
Velocity velocity[TEST_SIZE];
Appearance appearance[TEST_SIZE];



int main (int argc, char *argv[])
{
    printf("perf-test-1 > ");
    unsigned long i;
    {
        clock_t begin = clock();
        for ( i=0; i<TEST_SIZE; i++) {
            displacement[i].x = i;
            displacement[i].y = i;
            velocity[i].x = i / 1000.0f;
            velocity[i].y = i / 10000.0f;
            appearance[i].x = 0.001f;
            appearance[i].y = 0.002;
        }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        //printf ("Time: %f\n", time_spent);
    }

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
