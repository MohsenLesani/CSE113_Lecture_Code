#include "common.h"

namespace sequential {
#include "main_sequential.cpp"
}

namespace threaded {
#include "main_threaded.cpp"
}

namespace threaded_padded {
#include "main_threaded_padded.cpp"
}


int main() {
   sequential::main();
   threaded::main();
   threaded_padded::main();   
}
