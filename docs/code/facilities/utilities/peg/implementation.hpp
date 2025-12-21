/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template <std::make_signed_t<size_t> I>
struct Peg
{ static constexpr std::make_signed_t<size_t> value {I}; };

/*****************/
/**** Example ****/
/*****************/

/**** Tests ****/
static_assert(Peg<1>::value == 1);
static_assert(Peg<1>::value != 2);
static_assert(Peg<static_cast<size_t>(1)>::value == 1);