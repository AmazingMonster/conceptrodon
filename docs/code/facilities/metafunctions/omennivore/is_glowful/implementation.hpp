/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsGlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsGlowful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct GlowLike;

/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_1;

/**** Tests ****/
static_assert(IsGlowful<GlowLike<GritLike_0, GritLike_1>>::value);
static_assert(! IsGlowful<int>::value);
