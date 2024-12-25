/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsSnowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<typename...> class...> class...> class...> class Silence,
    template<template<template<typename...> class...> class...> class...Sorrow
>
struct IsSnowful<Silence<Sorrow...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike;

/**** Items ****/
template<template<template<typename...> class...> class...>
struct FlowLike_0;

template<template<template<typename...> class...> class...>
struct FlowLike_1;

/**** Tests ****/
static_assert(IsSnowful<SnowLike<FlowLike_0, FlowLike_1>>::value);
static_assert(! IsSnowful<int>::value);