TEMPLATE = '''
#include <iostream>

using namespace std;

int main()
{
    /* code */
    return 0;
}
'''

# n = int(input('Cuantos ejercicios quiere señor: '))

for i in range(1, 15):
    with open(f'03_{i:02}.cpp', 'w') as f:
        f.write(TEMPLATE)