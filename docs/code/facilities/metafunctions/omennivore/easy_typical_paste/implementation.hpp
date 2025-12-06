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

/**** Sequnivore::TypicalPaste ****/
namespace Sequnivore {

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedSequence>
struct TypicalPaste<PackedSequence>
{
    using type = PackedSequence;
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
struct TypicalPaste<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<VariableAs..., VariableBs...>,
        Others...
    >::type;
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
struct TypicalPaste<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    using type = TypicalPaste
    <
        SequenceA<TA, static_cast<TA>(VariableAs)..., static_cast<TA>(VariableBs)...>,
        Others...
    >::type;
};

}

/**** Stockivore::TypicalPaste ****/
namespace Stockivore {

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedStoc>
struct TypicalPaste<PackedStoc>
{
    using type = PackedStoc;
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
struct TypicalPaste<StocA<SequenceAs...>, StocB<SequenceBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        StocA<SequenceAs..., SequenceBs...>,
        Others...
    >::type;
};

}

/**** Warehivore::TypicalPaste ****/
namespace Warehivore {

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedWare>
struct TypicalPaste<PackedWare>
{
    using type = PackedWare;
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
struct TypicalPaste<WareA<ContainerAs...>, WareB<ContainerBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        WareA<ContainerAs..., ContainerBs...>,
        Others...
    >::type;
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
struct EasyTypicalPaste
: public Sequnivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Cotanivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Warehivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Stockivore::TypicalPaste<Packages...>
{};

/***********************/
/**** First Example ****/
/***********************/

#include <tuple>

/**** SupposedResult ****/
using SupposedResult_0 = std::tuple<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyTypicalPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyTypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

template<typename...>
struct Con_0;

/**** Dummy Arguments ****/
template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = Ware_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyTypicalPaste
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);

/************************/
/**** Fourth Example ****/
/************************/

/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = Stoc_0<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyTypicalPaste
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::type;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
