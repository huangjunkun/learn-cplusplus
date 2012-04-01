#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

/// 测试不同类型指针转化，涉及计算不同成员变量在类型对象不同的偏移地址。
struct overlapped_data
{
    overlapped_data()
    : data(0), data_len(0)
    {}
    ~overlapped_data()
    {
        if (data)
            delete[] data;
    }
    unsigned char* data;
    size_t data_len;
    // ... more ...
    std::string to_str() const
    {
        ostringstream oss;
        oss << " [&data]" << &data << " [data_len]" << data_len;
        return oss.str();
    }
};

class asyn_io_operation
{
public:
    asyn_io_operation()
    : lparam(0), rparam(0) {}

    /// member data
    overlapped_data data;
    int lparam;
    int rparam;
    // overlapped_data data; // define it here also ok. as the following OVERLAPPED_DATA2ASYN_IO_OPERATION.
    std::string to_str() const
    {
        ostringstream oss;
        oss << data.to_str() << " [lparam]" << lparam << " [rparam]" << rparam;
        return oss.str();
    }
    const overlapped_data* data_ptr() const { return &data; }
    overlapped_data* data_ptr() { return &data; }
    // ... more ...
};

#define OVERLAPPED_DATA2ASYN_IO_OPERATION(ptr) (asyn_io_operation*) ((char*)(ptr) - (char*)(&((static_cast<asyn_io_operation*>(0))->data)))

void do_handle_io_operation(asyn_io_operation* io_operation)
{
    std::cout << io_operation->to_str() << "\n";
    // ... more ...
}
overlapped_data* do_handle_overlapped_data(overlapped_data* data)//overlapped_data&
{
    // ... more ...
    if (data->data)
        delete[] data;
    const size_t SET_DATA_LEN = 100;
    data->data = new unsigned char [SET_DATA_LEN];
    data->data_len = SET_DATA_LEN;
    memset(data->data, '1', data->data_len );

    asyn_io_operation* io_opration = OVERLAPPED_DATA2ASYN_IO_OPERATION(data);
    io_opration->lparam = SET_DATA_LEN;
    io_opration->rparam = SET_DATA_LEN;
    return data;
}


int main()
{
    /// 测试不同类型指针转化，涉及计算不同成员变量在类型对象不同的偏移地址。
    {
    std::cout << " " << &((static_cast<asyn_io_operation*>(0))->data) << "\n";
    std::cout << " " << &((static_cast<asyn_io_operation*>(0))->lparam) << "\n";
    std::cout << " " << &((static_cast<asyn_io_operation*>(0))->rparam) << "\n";

    asyn_io_operation io_op;
    do_handle_io_operation((&io_op));

    do_handle_overlapped_data(io_op.data_ptr());
    do_handle_io_operation((&io_op));
    }

    /*********/
    //assert (!" assert false here.");
    cout << " Hello world!" << endl;
    return 0;
}
