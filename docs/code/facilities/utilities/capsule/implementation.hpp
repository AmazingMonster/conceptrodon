/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Capsule
{
    static constexpr size_t size()
    { return sizeof...(Elements); }

    template<template<typename...> class Container>
    struct Detail { using type = Container<Elements...>; };

    template<template<typename...> class...Containers>
    using Road = Detail<Containers...>::type;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct NewPacker;

/**** PackedVessel ****/
using PackedCapsule = Capsule<int, int*, int**, int**>;

/**** SupposedResult ****/
using SupposedResult = NewPacker<int, int*, int**, int**>;

/**** Result ****/
using Result = PackedCapsule::Road<NewPacker>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

static_assert(PackedCapsule::size() == 4);