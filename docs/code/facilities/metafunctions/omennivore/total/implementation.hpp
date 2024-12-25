/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename>
struct Total {};

template
<
    template<typename...> class Container,
    typename...Elements
>
struct Total<Container<Elements...>>
{ static constexpr size_t value = sizeof...(Elements); };

/*****************/
/**** Example ****/
/*****************/

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Test ****/
static_assert(Total<Capsule<int, int*, int**, int**>>::value == 4);