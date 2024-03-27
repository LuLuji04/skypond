#include<skypond.h>

int main()
{
    skypond_init();

    while(1) {
        skypond_update();
    }
    skypond_quit();
}