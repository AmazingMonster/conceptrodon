/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {false};
};

template<typename FP>
struct IsFunctionPointer<FP*>
{
    static constexpr bool value
    {std::is_function_v<FP>};
};

template<typename FP>
constexpr bool IsFunctionPointer_v
{
    IsFunctionPointer<FP>::value
};

/*****************/
/**** Example ****/
/*****************/

static_assert(IsFunctionPointer<void(*)()>::value);
static_assert(not IsFunctionPointer<void()>::value);
