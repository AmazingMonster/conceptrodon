/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsCoolful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct IsCoolful<Consistency<Silence...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike;

/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_0;

template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_1;

/**** Tests ****/
static_assert(IsCoolful<CoolLike<SnowLike_0, SnowLike_1>>::value);
static_assert(! IsCoolful<int>::value);
