/**********************/
/**** Dependencies ****/
/**********************/

#include <algorithm>
#include <array>

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Minimum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::min(array);
        }()
    }; 
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Minimum<1, 2, 3>::value == 1);
static_assert(Minimum<1.0, 2.5, 3.5>::value == 1.0);