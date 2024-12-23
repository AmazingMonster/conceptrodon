/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct BiCognatePlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<Devices<Variables>...>;
        };

        // Multiple Sequences
        // One Variables
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<Devices<Variable>...>;
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
            using type = Operation<Device<Variables>...>;
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
            using type = Operation<Devices<Elements>...>;
        };

        // Multiple Containers
        // One Elements
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Devices<Element>...>;
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
            using type = Operation<Device<Elements>...>;
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

/**** Vay ****/
template<auto>
struct Vay;

/**** AddZero ****/
template<auto I>
struct AddZeroHelper
{ 
    using type = Vay<I>; 
};

template<auto...Args>
using AddZero = AddZeroHelper<Args...>::type;

/**** AddOne ****/
template<auto I>
struct AddOneHelper
{ 
    using type = Vay<I + 1>;
};

template<auto...Args>
using AddOne = AddOneHelper<Args...>::type;

/**** AddTwo ****/
template<auto I>
struct AddTwoHelper
{
    using type = Vay<I + 2>;
};

template<auto...Args>
using AddTwo = AddTwoHelper<Args...>::type;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result 
= BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** Supposed Result */
using SupposedResult_1 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_1 = BiCognatePlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** Supposed Result ****/
using SupposedResult_2 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_2 = BiCognatePlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);

/************************/
/**** Fourth Example ****/
/************************/

/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZeroHelper
{ 
    using type = Vay<Element::value>; 
};

template<typename...Args>
using TypeAddZero = TypeAddZeroHelper<Args...>::type;

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOneHelper
{ 
    using type = Vay<Element::value + 1>; 
};

template<typename...Args>
using TypeAddOne = TypeAddOneHelper<Args...>::type;

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwoHelper
{ 
    using type = Vay<Element::value + 2>; 
};

template<typename...Args>
using TypeAddTwo = TypeAddTwoHelper<Args...>::type;

/**** Supposed Result ****/
using SupposedResult_3 = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result_3 
= BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);

/***********************/
/**** Fifth Example ****/
/***********************/

/**** Supposed Result ****/
using SupposedResult_4 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_4 = BiCognatePlume<Operation>
::Road<TypeAddOne>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);

/***********************/
/**** Sixth Example ****/
/***********************/

/**** Supposed Result ****/
using SupposedResult_5 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_5 = BiCognatePlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);