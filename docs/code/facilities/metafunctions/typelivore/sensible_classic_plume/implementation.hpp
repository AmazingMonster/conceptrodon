/************************/
/**** Implementation ****/
/************************/

template<typename...Elements> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Elements>::type...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<typename Element>
struct SensibleClassicPlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<typename Cosmetics<Element>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Transformations ****/
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = SensibleClassicPlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = SensibleClassicPlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);