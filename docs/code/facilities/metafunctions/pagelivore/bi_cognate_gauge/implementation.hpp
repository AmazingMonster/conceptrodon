/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct BiCognateGauge
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>::value...>;
        };

        // Multiple Sequences
        // One Variable
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class Device>
    struct ProtoRail<Device>
    {
        // One Sequence
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Device<Variables>::value...>;
        };

        template<auto...Agreements>
        using Page = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;

    template<template<typename...> class...Devices>
    struct ProtoRoad
    {
        // Multiple Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Devices<Elements>::value...>;
        };

        // Multiple Containers
        // One Element
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    {
        // One Containers
        // Multiple Elements
        template<typename...Elements>
        struct Detail
        {
            using type = Operation<Device<Elements>::value...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** AddZero ****/
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

/**** AddOne ****/
template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

/**** AddTwo ****/
template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2>;

/**** Result ****/
using Result 
= BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2, 3>;

/**** Result ****/
using Result_1 = BiCognateGauge<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<0, 2, 4>;

/**** Result ****/
using Result_2 = BiCognateGauge<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);

/************************/
/**** Fourth Example ****/
/************************/

/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

/**** SupposedResult ****/
using SupposedResult_3 = Operation<0, 1, 2>;

/**** Result ****/
using Result_3 
= BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);

/***********************/
/**** Fifth Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_4 = Operation<1, 2, 3>;

/**** Result ****/
using Result_4 = BiCognateGauge<Operation>
::Road<TypeAddOne>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);

/***********************/
/**** Sixth Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_5 = Operation<0, 2, 4>;

/**** Result ****/
using Result_5 = BiCognateGauge<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);