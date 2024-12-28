/************************/
/**** Implementation ****/
/************************/

template<auto Variable>
struct Vay
{
    static constexpr auto value
    {Variable};
};

/***********************/
/**** First Example ****/
/***********************/

/**** fun ****/
constexpr bool fun(Vay<0>) { return false; }

constexpr bool fun(Vay<1>) { return true; }

/**** Tests ****/
static_assert(not fun(Vay<0>{}));
static_assert(fun(Vay<1>{}));

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

/**** gun ****/
constexpr auto gun(Vay<0>) -> std::false_type;

constexpr auto gun(Vay<1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Vay<0>>()))::value);
static_assert(decltype(gun(std::declval<Vay<1>>()))::value);