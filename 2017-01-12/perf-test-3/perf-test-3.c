#include <stdio.h>
#include <time.h>


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

typedef struct
{
	Displacement displacement;
	Velocity velocity;
    Appearance appearance;
} Entity;

#define TEST_SIZE (100000000L)

Entity entity[TEST_SIZE];


int main (int argc, char *argv[])
{
    printf("perf-test-3!\n");
    unsigned long i;
    {
        clock_t begin = clock();
        for ( i=0; i<TEST_SIZE; i++) {
            entity[i].displacement.x = i;
            entity[i].displacement.y = i;
            entity[i].velocity.x = i / 1000.0f;
            entity[i].velocity.y = i / 10000.0f;
            entity[i].appearance.x = 0.001f;
            entity[i].appearance.y = 0.002;
        }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf ("Time: %f\n", time_spent);
    }

    {
        clock_t begin = clock();
        for ( i=0; i<TEST_SIZE; i++) {
            //entity[i].velocity.x += entity[i].appearance.x;
            //entity[i].velocity.y += entity[i].appearance.y;
            entity[i].displacement.x += entity[i].velocity.x;
            entity[i].displacement.y += entity[i].velocity.y;
        }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf ("Time: %f\n", time_spent);
    }
    printf ("%f\n", entity[TEST_SIZE-1].displacement.x);
    return 0;
}