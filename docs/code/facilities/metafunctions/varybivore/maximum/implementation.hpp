/**********************/
/**** Dependencies ****/
/**********************/

#include <algorithm>
#include <array>

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Maximum
{ 
    static constexpr auto value 
    {
        []()
        {
            std::array array {Variables...};
            return std::ranges::max(array);
        }()
    }; 
};

/*****************/
/**** Example ****/
/*****************/

static_assert(Maximum<1, 2, 3>::value == 3);
static_assert(Maximum<1.0, 2.5, 3.5>::value == 3.5);