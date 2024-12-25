/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsDawnful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsDawnful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct DawnLike;

/**** Items ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_0;

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct WillLike_1;

/**** Tests ****/
static_assert(IsDawnful<DawnLike<WillLike_0, WillLike_1>>::value);
static_assert(! IsDawnful<int>::value);
