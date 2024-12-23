/**********************/
/**** Dependencies ****/
/**********************/

/**** Cotanivore::TypicalPaste ****/
namespace Cotanivore {

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};

}

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Sieve ****/
template<template<typename...> class...Predicates>
struct Sieve
{
    template<typename Element>
    struct Detail 
    { using type = Capsule<>; };

    template<typename Element>
    requires (not (...&&Predicates<Element>::value))
    struct Detail<Element>
    { using type = Capsule<Element>; };

    template<typename...Elements>
    using Mold = Cotanivore::TypicalPaste
    <typename Detail<Elements>::type...>::type;
};

/**** Send ****/
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateFilter
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Send<typename Sieve<Predicates...>::template Mold<Elements...>>
        ::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateFilter<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<1>, Vay<2>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);