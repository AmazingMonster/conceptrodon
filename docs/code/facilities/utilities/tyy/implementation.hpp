/************************/
/**** Implementation ****/
/************************/

template<typename Element>
struct Tyy
{
    using type = Element;
};

/***********************/
/**** First Example ****/
/***********************/

/**** fun ****/
constexpr bool fun(Tyy<int>) { return false; }

constexpr bool fun(Tyy<int*>) { return true; }

/**** Tests ****/
static_assert(not fun(Tyy<int>{}));
static_assert(fun(Tyy<int*>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Tyy<int>) -> std::false_type;

constexpr auto gun(Tyy<int*>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Tyy<int>>()))::value);
static_assert(decltype(gun(std::declval<Tyy<int*>>()))::value);