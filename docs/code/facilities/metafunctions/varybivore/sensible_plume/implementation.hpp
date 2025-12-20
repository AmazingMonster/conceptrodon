/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
        };

        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto Variable>
struct SensiblePlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        template<template<auto...> class...Cosmetics>
        using Rail = Operation<Cosmetics<Variable>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>
#include <concepts>

/**** Transformations ****/
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = SensiblePlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = SensiblePlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);