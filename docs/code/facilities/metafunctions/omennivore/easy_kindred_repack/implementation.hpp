/**********************/
/**** Dependencies ****/
/**********************/

#include <cstddef>
#include <utility>

/**** Cotanivore::KindredRepack ****/
namespace Cotanivore {

template<typename...>
struct Capsule;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<typename...> class Container, typename...Elements>
struct KindredRepack<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
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
struct KindredRepack<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

}

/**** Sequnivore::KindredRepack ****/
namespace Sequnivore {

template<auto...>
struct Shuttle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

}

/**** Stockivore::KindredRepack ****/
namespace Stockivore {

template<template<auto...> class...>
struct Carrier;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<auto...> class...> class Stoc, template<auto...> class...Sequences>
struct KindredRepack<Stoc<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Sequences...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StocA,
    template<template<auto...> class...> class StocB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct KindredRepack<StocA<SequenceAs...>, StocB<SequenceBs...>, Others...>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Carrier<SequenceAs..., SequenceBs...>,
            Others...
        >::template Sail<Operation>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

}

/**** Warehivore::KindredRepack ****/
namespace Warehivore {

template<template<typename...> class...>
struct Vehicle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Ware, template<typename...> class...Containers>
struct KindredRepack<Ware<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WareA,
    template<template<typename...> class...> class WareB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct KindredRepack<WareA<ContainerAs...>, WareB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

}

/**** IsMoldful ****/
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

/**** IsPageful ****/
// Detect packed `Page`
template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };

/**** IsRoadful ****/
// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Ware,
    template<typename...> class...Containers
>
struct IsRoadful<Ware<Containers...>>
{ static constexpr bool value {true}; };

/**** IsRailful ****/
// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stoc,
    template<auto...> class...Sequences
>
struct IsRailful<Stoc<Sequences...>>
{ static constexpr bool value {true}; };

/************************/
/**** Implementation ****/
/************************/

template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** NewContainer ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewContainer;

/**** SupposedResult ****/
using SupposedResult_0 = NewContainer<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyKindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewContainer>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);

/************************/
/**** Second Example ****/
/************************/

/**** NewSequence ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewSequence;

/**** SupposedResult ****/
using SupposedResult_1 = NewSequence<0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyKindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<NewSequence>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** NewWarehouse ****/
template<template<typename...> class...>
struct NewWarehouse;

/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = NewWarehouse<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyKindredRepack
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::Flow<NewWarehouse>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);

/************************/
/**** Fourth Example ****/
/************************/

/**** NewStockroom ****/
template<template<auto...> class...>
struct NewStockroom;

/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = NewStockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyKindredRepack
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::Sail<NewStockroom>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
