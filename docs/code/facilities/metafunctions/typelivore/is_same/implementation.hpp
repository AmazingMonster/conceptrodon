/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<typename Target, typename...Elements>
struct IsSame
{ static constexpr bool value
{(...&&std::is_same_v<Elements, Target>)}; };

template<typename Target, typename...Elements>
constexpr bool IsSame_v 
{(...&&std::is_same_v<Elements, Target>)};

/*****************/
/**** Example ****/
/*****************/

static_assert(IsSame<int, int, int, int>::value);
static_assert(! IsSame<int, double, int>::value);
