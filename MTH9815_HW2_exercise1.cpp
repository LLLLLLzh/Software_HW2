#include <iostream>
#include <thread>
#include <chrono>

#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>


namespace ipc = boost::interprocess;
using namespace std;

class test {
public:
    test(int value) :m_value(value) {}
    ~test() = default;
    int get_value() { return m_value; }
    void set_value(int value) { m_value = value; }
private:
    int m_value = 1000;
};

int main(int argc, char* argv[])
{
    ipc::shared_memory_object::remove("test");

    boost::shared_ptr<int> iPtr = boost::make_shared<int>(10);
    cout << *iPtr << endl;

    ipc::managed_shared_memory shm(ipc::open_or_create, "test", 64 * 1024);

    int* pint = static_cast<int*>(shm.allocate(sizeof(int)));
    cout << *pint << endl;
    *pint = 100;
    cout << *pint << endl;
    shm.deallocate(pint);

    for (int i = 0; i < 10; ++i) {
        cout << "test:" << i << " count" << endl;
        test* ptest = shm.construct<test>("test_value")[10](i);
        cout << "ptest->get_value():" << ptest->get_value() << endl;
        ptest->set_value(-100);
        cout << "free memory:" << shm.get_free_memory() << endl;

        auto pdata = shm.find<test>("test_value");
        ptest = pdata.first;
        cout << "shm has:" << pdata.second << " objects" << endl;
        cout << "find ptest->get_value():" << ptest->get_value() << endl;
        shm.destroy_ptr(ptest++);
        cout << "destory " << pdata.second << " objects" << endl << endl;;
        cout << "free memory:" << shm.get_free_memory() << endl;

        this_thread::sleep_for(std::chrono::seconds(1));
    }

    getchar();
    ipc::shared_memory_object::remove("test");
}