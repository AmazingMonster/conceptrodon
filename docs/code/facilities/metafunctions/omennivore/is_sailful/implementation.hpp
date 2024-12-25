/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsSailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<auto...> class...> class...> class Melancholy,
    template<template<auto...> class...> class...Stockrooms
>
struct IsSailful<Melancholy<Stockrooms...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<auto...> class...> class...>
struct SailLike;

/**** Items ****/
template<template<auto...> class...>
struct RailLike_0;

template<template<auto...> class...>
struct RailLike_1;

/**** Tests ****/
static_assert(IsSailful<SailLike<RailLike_0, RailLike_1>>::value);
static_assert(! IsSailful<int>::value);