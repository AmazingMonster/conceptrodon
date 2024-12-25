/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsHailful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<auto...> class...> class...> class...> class Tranquil,
    template<template<template<auto...> class...> class...> class...Melancholy
>
struct IsHailful<Tranquil<Melancholy...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike;

/**** Items ****/
template<template<template<auto...> class...> class...>
struct SailLike_0;

template<template<template<auto...> class...> class...>
struct SailLike_1;

/**** Tests ****/
static_assert(IsHailful<HailLike<SailLike_0, SailLike_1>>::value);
static_assert(! IsHailful<int>::value);