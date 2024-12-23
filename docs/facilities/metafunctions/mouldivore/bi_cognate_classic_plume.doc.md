<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BiCognateClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bi-cognate-classic-plume">To Index</a></p>

## Description

`Mouldivore::BiCognateClassicPlume` accepts an operation.
Its first layer accepts a list of transformations and returns a function.
When invoked, the function instantiates the transformations using its arguments via a process similar to pack expansion;
then, it invokes the operation by the type results collected from the instantiated transformations.

Check out **Examples** for more information.

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg
-> Oper&lt;Transfs<sub>0</sub>&lt;Arg&gt;::type, Transfs<sub>1</sub>&lt;Arg&gt;::type, ..., Transfs<sub>n</sub>&lt;Arg&gt;::type&gt;</code></pre>

<pre><code>   Oper
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf&lt;Arg<sub>0</sub>&gt;::type, Transf&lt;Arg<sub>1</sub>&gt;::type, ..., Transf&lt;Arg<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;Arg<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;Arg<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;Arg<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
BiCognateClassicPlume
 :: template<typename...> class...
 -> template<auto...> class...
 -> template<auto...>

BiCognateClassicPlume
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
// Plume `Rail`s
template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Plume `Road`s
template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

template<template<typename...> class>
struct BiCognateClassicPlume
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will see six examples that present different use cases of `Mouldivore::BiCognateClassicPlume`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Vay ****/
template<auto>
struct Vay;

/**** AddZero ****/
template<auto I>
struct AddZero 
{ 
    using type = Vay<I>; 
};

/**** AddOne ****/
template<auto I>
struct AddOne
{ 
    using type = Vay<I + 1>;
};

/**** AddTwo ****/
template<auto I>
struct AddTwo
{
    using type = Vay<I + 2>;
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result 
= BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result */
using SupposedResult_1 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_1 = BiCognateClassicPlume<Operation>
::Rail<AddOne>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_2 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_2 = BiCognateClassicPlume<Operation>
::Rail<AddZero, AddOne, AddTwo>
::Page<0, 1, 2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We will pack `std::integral_constant<int, 0>` into `TypeAddZero`, `TypeAddOne` and `TypeAddTwo`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** TypeAddZero ****/
template<typename Element>
struct TypeAddZero 
{ 
    using type = Vay<Element::value>; 
};

/**** TypeAddOne ****/
template<typename Element>
struct TypeAddOne
{ 
    using type = Vay<Element::value + 1>; 
};

/**** TypeAddTwo ****/
template<typename Element>
struct TypeAddTwo
{ 
    using type = Vay<Element::value + 2>; 
};

/**** Supposed Result ****/
using SupposedResult_3 = Operation<Vay<0>, Vay<1>, Vay<2>>;

/**** Result ****/
using Result_3 
= BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold<std::integral_constant<int, 0>>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

- We will use `TypeAddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_4 = Operation<Vay<1>, Vay<2>, Vay<3>>;

/**** Result ****/
using Result_4 = BiCognateClassicPlume<Operation>
::Road<TypeAddOne>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_4, SupposedResult_4>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `TypeAddZero`, `TypeAddOne`, and `TypeAddTwo` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Supposed Result ****/
using SupposedResult_5 = Operation<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result_5 = BiCognateClassicPlume<Operation>
::Road<TypeAddZero, TypeAddOne, TypeAddTwo>
::Mold
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result_5, SupposedResult_5>);
```

## Implementation

`Mouldivore::BiCognateClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BiCognateClassicPlume
{
    template<template<auto...> class...Devices>
    struct ProtoRail
    {
        // Multiple Sequences
        // Multiple Variables
        template<auto...Variables>
        struct Detail
        {
            using type = Operation<typename Devices<Variables>::type...>;
        };

        // Multiple Sequences
        // One Variables
        template<auto Variable>
        struct Detail<Variable>
        {
            using type = Operation<typename Devices<Variable>::type...>;
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
            using type = Operation<typename Device<Variables>::type...>;
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
            using type = Operation<typename Devices<Elements>::type...>;
        };

        // Multiple Containers
        // One Elements
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<typename Devices<Element>::type...>;
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
            using type = Operation<typename Device<Elements>::type...>;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGaSAMykAA6oCoRODB7evgHBmdmOAuGRMSzxiclpdpgOuUIETMQE%2BT5%2BQbaY9mUMLW0EFdFxCUmptq3tnYU9CjMjEWPVE3UAlLaoXsTI7BwA9ABUp2fnF5dnhyYaAIInZwDUAJIs6fRsgkwDT%2Bc390eV2BVwBd1udwImHeBihJhSbihMJ%2BmHhiIAnulGKxMAA6fHw7BPZAGBQKJ4AeSxxB%2BuUJEMWxC8DieFjwHmAzChblJ2WQygKqPuJkCVnuTwlTyRHxRaOlsNRCKYXiI%2BNxhOJvLVABFMAA3PD7BT08WSxnMghPZTEVBEABKTDoEMlTxFYruLpdh0OTwAsl5aI4PpgnkJMABHLyMI3Oz0S71%2BgNB%2BhPABqbTwTFi9GNprj8tlSpVqDV6eImezmGNKWwsbj5pZutaTrznrddbjkq82SMUsxIfh2sp1NpAjl/eYbCeuoNMYRZYrOcJIBABH7avpKXdnddgW18PdHa9Pv9gbwwdDEajDBjrePlMiaYzWaXd8lBbhRaIT/LL8VtbfCUG0tJtHVoNEFz/E0PU7dtAM9bsImAPssVdFIhypBJRwYccsUnEMZ0NKsIOfStl1XdcCRrA8j0lEV9y3CFaIlD9FTcZVVXxO5gGITBoUYAhqwAmC40Q3tlCYYAB3Q6dMGbcCEW43j%2BMEBQNxrFc1yxGjW3onTwVbVi5WhGVP3Y4t1KJEkmDJWTZ3/DtgKtG17TAtFCP2aCXTgkTPQTClHzDSNoyFXz71PZMQ0gytczC98TIVNEOJLfFoqXaj4Kc0CWziiUfJ3F0xOQrTpIwkcBlw7Epw8ti0uIjSKKxSz9J3PTGOFeCjK/FLcSUvivkErzOyKq1JNK2T5LRPqVMEyzNP7Fq6L3fSOy6xEEsLczOPVGtNRstSuJ4/qBKEjsRodOg0KHa1bVQC6FLcaaBoOnba3agzfLWr6JxxSy9rJHV9SI07Wycm77VQJh0A7fLOwTCLzxTDxvhWYhYp3eGk0RkNsE%2BE7mKlDazJK/C1VxmaQdyp4srktz4NhgqnhGkqruHLCKoREmcTs4G0XJ57yJK5r3ta5b3oJzGzwvZHm0iNGJZ9AKcbx1SCe%2BvDuf5gShvrAgmUbWmnQRLXBB1ttRQJwqe2K/tWcwmkOYxDXqqBuc3BNghBco17FrjNrD06om2K5tg1Se/GMqpkbfU8dBWeyh7w9UubGsVbcloYgPPqD4zkWJn7Q6oqzeR5zzI5dMGXLuyHoYRGqzYZvzFcfGXHTl9G4ZPLGLw9jv8xzzmC7xfFe7Niu9YtCa6apxud2Z23BzZh26UH52CNdtjR4aoWi9983M6YwO8%2BDoew6Oimx67a2/Vj%2BPDcT8/npTkq9/9w/s%2BP3PTJPte/usgHDrKQFuXK%2BSEnh2hrqzcG1coZTUfidYWh4xZZyBCCNBxwwSoKeAAMTwGjS02BVCsAvP8CEqD0HAjBExMwKQIgki8FgNCbg0A3kwOkQakcyHnCfOiP41wIRrWStBJy6Z0QrUBNwu46B0AAC0EioD4acMEgjiyvGERPFkUjZHyNdMKUUujfLz1QovURaIXibgsAYt%2BHUHiSOkUrRRGCBEDy2go8xkcnJaKVkxfRZ1r4sxMUwMRCIXiuksE8LgFifEHxsVgrRAAVAA7go0h9wVHfnccJTx0ikmoB8enCURjxqmJCWEyxZgol6JiR9LB9tsKOOUS4kOw8fb3CcnUjmKDuFCC8OkEomB0B2irEmBpEIRo9L6VkAZQyFAjMXh0lebgSluA0ISUgPC0SRJrOs5ZFTqL7K6c8GZIzUl3HOsMwMViZJsg5FyTAPJ9qGgFD4NiCyxyRxXPdKa0i5E2nWV4yI/ycnJOgiuCSUk0SrIOe/LB8SqyWlOYsWkyAAD6%2B0EgEAgIsdAK4FA4jRdWNwxzAzrImf0wZFzPY1g2OI2xFD0GYO6Y0AQcdCHEJTKc8h9LLhUIkc8MlUy47EoRWCcZvTyXCpRVwO25VFnLK2dgHZQS0R7MVRshEKRNxvUOaccBlLRn3HObMwMUrWY3NQJyFEDyyRPMFGiN5OEPkgC%2BYpexkRQUgHBWxDQ6yuDrNVbS2F8KDV3CRY4VF6L2hYoIDikAeK2AErRJKv1oZxWCuTYSGl4s%2BXctBFw548SEB4NZUQmEIZOW5soTC7paalBCv1acsVky62SrMDK9mcrlUIihWq3Zaz1VuEkFqwN3DhUhqNUmFFbbF7mstdyXktqXn2tle84Sny3Kuu0X8p4ALMBAvQLkj1XrIW%2Bv9ZUmp3C4WLBDWGw0BKlBRuxbi/FNkk2UqnaS2t0z32qqzTqytFxGXPGwTsdoCAnhsrLSGrlAGnGxMvf2LRvyUn8LSU0oeEGVZUqyRoy08TEM/J0fkgxVswEBJkssj2K49RiCjBYqxyDq0FoI%2BgBxpz1ZVWVjNdR%2Bs8Mse8XoyxfiyMLwo1292WHqO0YHOEhVB4GPVPzbq/DWIEnJJDRx/CmHuMeNw08FTmA1N5MEyR0BvZyNDko5JkANHvAyfKfR6JI7%2BVfvrcahFqGznXwFS299KR23L3eUs8TPalXBLcAqsLKrh3Zrpbqsdjbr6Sv80xa57ILV3OtXyZ5bBl0dtXRCT5Nc0QGaQ/I9ZpW3V7v0yxw9TqY60Frm4J9IAIhQh4mIFFLCkWmwRG19ZPbz1KeOPp4NiLWjhvvRi6Nsb42YETQiZLn7m3fvcyizV1LnOwc81g3BVACDgcgyQnb23TnDdTSttzJzPNNole%2ByQAXsIkXC5Fgdqqosapi/%2BvV7nx1Jfu2a9Lc77kLv5HahEDqPUQNgQiSrrH3X1djqltwjkY0rja5gDrtAusCB61Stw/WnihdR7GjHWOccMDx2iQnkWSfo8EJjmk2PuutF6wTwQZ7OHQvgwWsbnnb0RrJNNlrc2FtEvu8tu7a2h2bdizBytQHdVCDwKoA7EHS3HaUcN7bvK4sjZ8wMn712teGu865yV/hHuO2WaFt7/blky7etqpj8WG03f%2B2ty3M6geZdBzl15K7HVrudcV2HLHkMVf44CmrqngV5MR415HdPWsM/Jyzww%2BPCfE9BmjlP7WmcU6p31jnES1nJ7JwX9PbPCcBuFNzi9vPr3jeRVNx9ufRevsW%2B%2B/wkv03d8zQeDgWxaCcH8LwPwHAtCkFQJwFHlhrDU1A/sMJKQeCkAIJoIfWwADWARJC4g0JILggQUgaH8BoMwAA2S/ZgAAct/9CcEkLwFgEgNA%2Bon1PmfHBeAKBAD6jfSfIfUgOAWAGARAEAHYAgdIFUcgSgNAd4OgBIKIHETgVQW/S/AAWkvwe2AGQGQAiX3zMF4AGUIBIDwBxT9X4EEBEDEHYCkBkEEEUBUHUCANIF0D9USRpHSE4B4GH1H3H032n04ApBVBgMtFQCoCeHQKwJwKeDwIIKkFxDbQgA8EQPoGIBXy4A2F4EAK0C2AgCQAQPSCQLIAoAgGMNMJAGACkDMD4DoChDRkoFiCENiAiDaHRF4N4DcOYGIHRApFiG0EaEALXwQIGgCloE8LYKwFiC8GAHYloFoD/24F4CwBYEMGAHEGiLwWCLwD1CrCEMwFUEaBVAODXwxxHzYNoDwFiBpD8I8CwCEL1jwFfxSNIHyOIFiCmV1HSKMGqKME3y2CoAMGAAUFTDwEwESUwgnzX2oOEFEHEAYLmOYLUCEI4P0AyJQGsGsH0BqL/0gC2FQHYVyGSMwOxUHFMHn0sDMC/w6PLCwH2IgC2AaCaGcAgFcDmD8D9TCBWCqBqD0BKByAEE%2BIBKyCBIYFGD%2BImD9ReIGCGFmE8C6D0FhOaCWEhPGESBhKWBBKxOGHRLWExOeKX3oP4I4DH1IE/14G/2kIwOwNwPwMIOUKeAgFwDIM0PMFXx0PX0GK2AQEwChgmCeNIF31SFxAAE4UhAhJBD9khL939/BL8xTH8OBn9SBX9V9cRL8uBL9b8xTb9tT/Aj9/AJTL8KShDv9f9/9uSgCDDwDDDICxDYDzDLCNCUC2BOA2gWA9RAhMCmA9pewuAxTcQuAD8SD8AiB7i9A5jaDFjpBlilBVi2DdA7CuCmAeCUjSTyTKThCOBRDoCVQnhJCaTZCHtrIAygyQyNBmS1CTCNCV8zAuS9DgD7SXSEg4CLDUB1CJgyybCxSuAfUaBAwEg/8IAXC2CfCPCvDSAJy/CAigiHApywiBIIioip8Yi4iEikipy0iMisi1ycimh8jkip8iiSioQpyKihDqjaiPCGiDgp9mjWi18OiuilAejdykJBi%2BARixiJipi8IpzoyFj6C4zZAVjWCp9kyNiBjLirBLBdjYhHjDjjjcdOAziY0LjtjrjbiEh7iCiDjeh%2BhcgXAGB3BETChvjSL8T/i/VASBgcSMgwSBhqLoTCLciBB4SOhyKvi2LXjBg0TfiMTkTsTuLhK8TBKCSJAiTdh9gpLlSszzTOBiy6T/TkJAzgyD9mTWSIytDGyeTSA%2BSBTEghTKjVT1SgzD9AhjTAgT9JBZSj8zS2CLTbArSmzbT4B7SoDxD2zWziA3SDhPS5CWAFA9QCC9R1KFRFgwy2SKCozZAYyQLGD5AEyIKdAQA0hUz0y%2BD5LBCnKRDHSJCpDVAgqQqwqIqURr1VDOzayEgV8Ug9KbSQCjDqrTCfKWqNCbNkA%2BkUVwqxSUVIqCAUViq4yHDhznDXD3C/CpyZz/DAjgjFzOzwiGBIihD1z4ixAty2idy%2Bj7zUiDzHAjzCjijkBSiLyGdKip9ry6j0Q7ymjywnzeAXzujoQPyBjGrhjJJfzJjpjAL4rgKJBQKmCUq1j0roLjAsKbBrykLp8ULKdOBDgn1YLrAbiqS7iKD8KhSUS3iPjRLKL0AWLMTGLShcgGK6LcgCbkS%2Bh2L%2BLhgGKsaab2gKbcSESCgeKkVGaJKaLpK9gSScrHKv8lLhqnhgrQqnhercQBqtLwySBdLdD9LDKsBjLSSzKkggyUgUh/Bz8j9391bAgdT%2BaqTOBLSAD9KRT/BxT/Bb8r8xTJAxST9JSuA0hKiUhcqBaf9rT9DSTiCDacy5abStgOjshnBJAgA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bi_cognate_classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bi_cognate_classic_plume.test.hpp)
