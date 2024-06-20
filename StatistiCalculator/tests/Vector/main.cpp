#include <structures/Vector.h>

#include <string>

typedef Vector<std::string> strVector;
typedef Vector<float> fVector;
typedef Vector<int> intVector;




//////////////////////////////////////

#define TEST1_START 0
#define TEST1_END 0xFFFF
bool test1_create() {

    intVector v;

    // Insert values
    for (int i = 0; i < TEST1_END; i++) {
        v.push(i);
    }

    // Check if it worked
    for (int i = 0; i < TEST1_END; i++) {
        if (v[i] != i) {
            return false;
        }
    }

    return true;
}

//////////////////////////////////////


bool test2_create() {
    const std::string str = "Hello World!";
    strVector v;
    for (size_t i = 0; i < TEST1_END; i++) {
        v.push(str);
        if (v[i] != str) {
            return false;
        }
    }
    return true;
}


//////////////////////////////////////


bool test3_copy() {

    fVector a;
    fVector b;

    for (int i = TEST1_START; i < TEST1_END; i++) {
        a.push((float)i);
    }
    const size_t an = a.size();

    b = a;
    for (int i = TEST1_START; i < TEST1_END; i++) {
        b.push((float)i);
    }
    const size_t bn = b.size();

    return (bn > an);
}


//////////////////////////////////////


bool test4_zero() {
    try {
        intVector v(0);
        return false;
    } catch (const BadAlloc()) {
        return true;
    }
}


/////////////////////////////////////


#define TEST5_SIZE 10
bool test5_oor() {
    intVector a(TEST5_SIZE);
    for (size_t i = 0; i < TEST5_SIZE; i++) {
        a[i] = i + 1;
    }

    const intVector b = a;

    try {
        int t = b[TEST5_SIZE];
        return false;
    } catch (const OutOfRange&) {
        return true;
    }
}


/////////////////////////////////////


#define TEST6_SIZE 10
bool test6_resize() {
    intVector v(TEST6_SIZE);
    v[TEST6_SIZE] = TEST6_SIZE;
    return (v.size() > TEST6_SIZE);
}


/////////////////////////////////////

#define TEST_SIZE 6
typedef bool(*test_func)();

int main() {

    test_func funcs[TEST_SIZE] = { test1_create, test2_create, test3_copy, test4_zero, test5_oor, test6_resize };

    for (int i = 0; i < TEST_SIZE; i++) {
        bool pass = funcs[i];
        if (!pass)
            return (i + 1);
    }

    return 0;
}