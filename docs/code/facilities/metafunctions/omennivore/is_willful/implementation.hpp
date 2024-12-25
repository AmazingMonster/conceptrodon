/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsWillful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<auto...> class...> class...> class...> class...> class...Perseverance
>
struct IsWillful<Sunshine<Perseverance...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike;

/**** Items ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct CalmLike_1;

/**** Tests ****/
static_assert(IsWillful<WillLike<CalmLike_0, CalmLike_1>>::value);
static_assert(! IsWillful<int>::value);