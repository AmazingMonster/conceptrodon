/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Sequence>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Sequence<Variables...>`.
    template<auto...Variables>
    struct ProtoMold<Sequence<Variables...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};

/*****************/
/**** Example ****/
/*****************/

/**** Shuttles ****/
template<auto...>
struct Shuttle_0;

template<auto...>
struct Shuttle_1;

/**** PackedVessel ****/
using PackedVessel = Shuttle_0<0, 1, 2, 2>;

/*** Aliases ****/
template<auto...Args>
using Seq_0 = Shuttle_0<Args...>;

template<auto...Args>
using Seq_1 = Shuttle_1<Args...>;

/**** Tests ****/
static_assert(IsSpecializationOf<Seq_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Seq_1>::Mold<PackedVessel>::value);