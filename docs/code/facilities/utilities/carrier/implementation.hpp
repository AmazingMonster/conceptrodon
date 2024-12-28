/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Sequences>
struct Carrier
{
    static constexpr size_t size()
    { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Detail<Stockrooms...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Items ****/
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** Result ****/
using Result = PackedCarrier::Sail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedCarrier::size() == 4);