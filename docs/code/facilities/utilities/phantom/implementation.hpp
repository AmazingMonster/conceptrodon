/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class...Stockrooms>
struct Phantom
{
    static constexpr size_t size()
    { return sizeof...(Stockrooms); }

    template<template<template<template<auto...> class...> class...> class Melancholy>
    struct Detail { using type = Melancholy<Stockrooms...>; };

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = Detail<Melancholy...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<template<auto...> class...>
struct Stockroom_3;

/**** Operation ****/
template<template<template<auto...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPhantom = Phantom
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** Result ****/
using Result = PackedPhantom::Hail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedPhantom::size() == 4);