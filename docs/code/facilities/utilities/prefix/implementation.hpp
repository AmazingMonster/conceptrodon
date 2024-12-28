/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename, size_t>
concept Prefix = true;

/*****************/
/**** Example ****/
/*****************/

#include <utility>

/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};

/**** TheFourth_v ****/
template<auto...Args>
constexpr auto TheFourth_v
= Midst<std::make_index_sequence<3>>::idyl(Args...);

/**** Tests ****/
static_assert(TheFourth_v<0, 1, 2, 3, 4> == 3);
static_assert(TheFourth_v<0, 1, 2, -3, 4> == -3);