/************************/
/**** Implementation ****/
/************************/

/**** Primary template ****/
template<typename PackedVessel>
struct Send {};

/**** Partial template specialization ****/
// We extract `Elements...` from a `PackedVessel`.
template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation {};

template<>
struct Operation<int, int*, int**, int***>
{ static constexpr bool value {true}; };

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Send<Args...>::template Road<Operation>;

/**** Test ****/
static_assert(Metafunction<Capsule<int, int*, int**, int***>>::value);