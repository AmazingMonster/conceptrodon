/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>


/************************/
/**** Implementation ****/
/************************/

template<typename Element, template<typename...> class Predicate>
concept Real = Predicate<Element>::value;

/*****************/
/**** Example ****/
/*****************/

/**** SameAsInt ****/
template<typename...>
struct SameAsInt
{ static constexpr bool value {false}; };

template<>
struct SameAsInt<int>
{ static constexpr bool value {true}; };

/**** fun ****/
std::true_type fun(Real<SameAsInt> auto);
std::false_type fun(auto);

/**** Test ****/
static_assert(decltype(fun(1))::value);
static_assert(! decltype(fun(1.1))::value);
