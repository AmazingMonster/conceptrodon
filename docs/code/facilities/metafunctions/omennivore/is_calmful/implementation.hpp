/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsCalmful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<auto...> class...> class...> class...> class...> class Perseverance,
    template<template<template<template<auto...> class...> class...> class...> class...Tranquil
>
struct IsCalmful<Perseverance<Tranquil...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike;

/**** Items ****/
template<template<template<template<auto...> class...> class...> class...>
struct HailLike_0;

template<template<template<template<auto...> class...> class...> class...>
struct HailLike_1;

/**** Tests ****/
static_assert(IsCalmful<CalmLike<HailLike_0, HailLike_1>>::value);
static_assert(! IsCalmful<int>::value);
