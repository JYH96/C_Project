#include <iostream>
#include <string>

using namespace std;


#include "hero.h"



int main()

{

    Hero Tracer("Tracer", 150), Pharah("Pharah", 200), Mercy;

    Pharah.info();



    Mercy.set_info("Mercy", 200);

    Mercy.info();

}