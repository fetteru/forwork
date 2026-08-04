#include <iostream>
using namespace std;

int main() {
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;          // 在这行打个断点
        cout << "i=" << i << ", sum=" << sum << endl;
    }
    cout << "最终结果: " << sum << endl;
    return 0;
}
