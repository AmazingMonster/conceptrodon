/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsGritful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class Sunshine,
    template<template<template<template<template<typename...> class...> class...> class...> class...> class...Consistency
>
struct IsGritful<Sunshine<Consistency...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike;

/**** Items ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike_1;

/**** Tests ****/
static_assert(IsGritful<GritLike<CoolLike_0, CoolLike_1>>::value);
static_assert(! IsGritful<int>::value);