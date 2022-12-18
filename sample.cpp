#include <iostream>
#include <type_traits>
#include <list>
#include <vector>
#include <string>


// Print string
void PrintIp(const std::string& value)
{
    std::cout << value << std::endl;
}

template <typename>
struct is_vector_or_list : std::false_type {};

template <typename T, typename... Args>
struct is_vector_or_list<std::vector<T, Args...>> : std::true_type {};

template <typename T, typename... Args>
struct is_vector_or_list<std::list<T, Args...>> : std::true_type {};

template <typename T>
void PrintIp(std::enable_if_t<is_vector_or_list<T>::value, const T&> data)
{
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        std::cout << *it;
        if (it != std::prev(data.end()))
            std::cout << ".";
    }
    std::cout << std::endl;
}

// Print int
template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> PrintIp(T value)
{
    static const size_t  _size = sizeof(T);
    std::vector<int> nums;
	for (unsigned int i = 0; i < _size; i++) {
            nums.insert(nums.begin(), value & 0xFF);
		    value >>= 8;
	}
    PrintIp<std::vector<int>>(nums);
}

int main(int, char const **)
{
    try
    {
        PrintIp(-1);

        short addrShort{0};
        PrintIp(addrShort);

        int addrInt{2130706433};
        PrintIp(addrInt);

        int64_t addrLong{8875824491850138409};
        PrintIp(addrLong);

        PrintIp("Hello, World!");

        std::list<short> l{400, 300, 200, 100};
        PrintIp<std::list<short>>(l);

        std::vector<int> v{100, 200, 300, 400};
        PrintIp<std::vector<int>>(v);

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}