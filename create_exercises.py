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

for i in range(11, 21):
    with open(f'exercise_{i}.cpp', 'w') as f:
        f.write(TEMPLATE)