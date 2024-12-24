/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Container>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Container<Elements...>`.
    template<typename...Elements>
    struct ProtoMold<Container<Elements...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Dummy Containers ****/
template<typename...>
struct Capsule_0;

template<typename...>
struct Capsule_1;

template<typename...Args>
using Con_0 = Capsule_0<Args...>;

template<typename...Args>
using Con_1 = Capsule_1<Args...>;

/**** PackedVessel ****/
using PackedVessel = Capsule_0<int, int*, int**, int***>;

/**** Tests ****/
static_assert(IsSpecializationOf<Con_0>::Mold<PackedVessel>::value);
static_assert(IsSpecializationOf<Capsule_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Con_1>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Capsule_1>::Mold<PackedVessel>::value);