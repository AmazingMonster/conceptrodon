/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<auto...> class...>
struct RailLike;

/**** Items ****/
template<auto...>
struct PageLike_0;

template<auto...>
struct PageLike_1;

/**** Tests ****/
static_assert(IsRailful<RailLike<PageLike_0, PageLike_1>>::value);
static_assert(! IsRailful<int>::value);