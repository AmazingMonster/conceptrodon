/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<typename Target, typename...Elements>
struct IsDifferent
{ static constexpr bool value
{(...&&(not std::is_same_v<Elements, Target>))}; };

template<typename Target, typename...Elements>
constexpr bool IsDifferent_v 
{(...&&(not std::is_same_v<Elements, Target>))};

/*****************/
/**** Example ****/
/*****************/

static_assert(IsDifferent<int, int*, int**, int**>::value);
static_assert(! IsDifferent<int, int, int*>::value);