<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRepeat`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-repeat">To Index</a></p>

## Description

`Pagelivore::CognateRepeat` accepts an operation.
Its first layer accepts the times of repetitions and returns a function.
When invoked, the function repeats its argument list the given number of times and uses the result to instantiate the operation.

<pre><code>   Oper
-> N
-> Args...
-> Oper&lt;Args...<sub>1</sub>, Args...<sub>2</sub>, ..., Args...<sub>N</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRepeat
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRepeat
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four iterations of `0, 1`:

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = CognateRepeat<Operation>
::Page<4>
::Page<0, 1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `CognateRepeat` with the help of `TypicalReiterate`, which is implemented using recursion over the total number of parameters.
Each intermediate result will be kept inside a `Shuttle`.
When the iteration completes, we transfer the variables from the final `Shuttle` to the operation.

- **Base Case:** Handle several numbers of times directly.
- **Recursive Case:**
  1. Iterate several times;
  2. Reduce the total times by the same amount;
  3. Invoke the first layer of `TypicalReiterate` with the times left;
  4. Concatenate two results.

We will use `ExtendBack` to concatenate two parts.

```C++
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};
```

We will use `TypicalReiterate` to reiterate the variables.

```C++
template<auto...>
struct Shuttle;

template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

We will use `Send` to transfer variables from the final `Shuttle`.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<auto...> class Operation>
struct CognateRepeat
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = Send
        <
            typename TypicalReiterate<Variables...>
            ::template ProtoPage<Amount>::type
        >
        ::template Rail<Operation>;
    };

    template<size_t...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcyEm6CwVDh2FBoP%2B%2BzuQgQXgIBHo3yOwIImBYaQMZLhbiY%2BNQADomWjQZNiF4HDi8QT6HCrNdMcc7thVGSGOgLExkABrYmHYG7XZ3ADqmDuAHc6LQ7l4lHcCAg8F8qF4GA4cvrUHc0GamGK7WqCOqrWlBgoGaCyRSqZgaQQAJ4vZhsJkewLo65sjkEYWi1ySmWwgDsViTDz5GOuXspDppoLuBf15Jz1PhdKIobR1oMCi%2BQkwAEcvG9MKR84Xy4ymQA1Np4JixegKDHh1kEdmckViiVS6U0%2BtNls03vEfuDz6V0ejgUp9sF7M%2Bmmd0NXYDETDkxgEYfbq6FnVZIx3ZRMYBquEPHGN5tm33wldrkOoakHcp7npegjusyW78iCaYZgKfxCvW4pyucnrFoe8IBkGrCYJuEZXFGnIoegyapumgSwRh3q5thmF0bS9IEdWTC1l%2Bi6/iBx49n2A5DiykbjtGX7ivO35Lv%2BfHrlBYboreJi7tc94HoxqmlkxFbQdgrHsQA8i8xB2jkgl3oWxExk8rR0Hu5G2feuoRMA%2BqBu%2BgSfgZCTGQIy7SUB2kIWZBaKZR1HKYW6l/m4kVHsx2m6bJYEXmwkGmQ5j7OQASkwdCwu5jyYNZtA0klEHXgRIAgDhf7UfBVGZjcQorv6sR4AAbiQ7AgAAKoGeCiLQmWYIQXlkmhwLBp8rrbHczWtR1552YhVwxWWcUMgB/GfKZFl3L1aT9WIQ0jUZ1I7rBKkMRpPFybZu3KMQqBEC%2Bb52XVYU3Eqkp6rSSggLZq2aVaACSaWFueTZ4OeXwQMDeWUZ%2BGgrHdwmcg9T2oC9UWg7e96KRd96Fo5T7VfDXL4oSUUsvV4XBe9DWXbR130ncOOEfeENeFDnx3LD8MfncXDI7Tdz3Y9z2vtjYN0wThMPk5LkvGTuIU7yUmrltsnU7LyahQ1ip3ENyCbFkbVqr97AA1dUWdqz0t3Jz3Mw2YeVuALwPC0FouozG6MS2%2BNJs7Z%2BP2UTGWK25n5TvGs5%2Bq5k3PuLmOS4HdwALR3GYaKVdV9v3jn1vPin6uARuTIgZtMkEYFeP08tjMljb62lSl1728TzlY2TfvJwH8It1eWswRidcgju6bLVigLT%2BhSH3MD3pld5DDjYKM/r8CNGN361uxVpckJXcnmnSZt67R4wDMGSQ0vHaI864DWQAF6YAA%2BjGVwsBsgj22LGNY8HJSXsG5YSBqGSuAlcZy3lk%2BLuAtSKh2CvCRBhNqoJzmu1TqlV9qHUGsNMkp0ooQLLrdEW0C7gFyZmqHuAD%2B5f1NAQbOVVXIoLzoWShjdDY5WKvCY%2By9taAL1vXCKu94TPzfgQE8Z5kqD3buHOB%2BUaHFzcAPSC1caZwSEWPRq68fhr0OLGVglI1R6Lnro%2BUDVzAQjNNCNyCIBDbDSG3BSZjsR8KaKvLMoiwEBSEhOGM7jT4fSxDiLwaRiiYHQENBQXhaAxlMVcDuoTwmZEidE2JMYBaBJ8sgkWGgQJcDbHkgpRSvb5MFqU%2B85SuAjnksEoU6S4meMSeHRpmT8oXyvpgG%2BmA768MMvw28lVaFuEkKZYZyjqkCMnkKbqnx4kkjHMZZAr82JKHaBAJElUFB4VWTeNwbSQJCDCREqJnwMlomRlRDgaxaCcH8LwPwHAtCkFQJwN2lhrCiw2Fsd84IeCkAIJoG5axpQBEkAyDQAAOMwKRkhcH8NCqFXAkxJmkHcjgkheAsAkBofJTyXlvI4LwBQIB8lAueTc0gcBYAwEQCADYBA0j4nIJQNAFI6AJCiHhTgqgoUADY078skHcYAyBkCCwhWYXgkTCAkDwOgPQ/BBAiDEOwKQMhBCKBUOoSlpBdCFPVEZNInAeC3PuY84FrzOB6XxMymMqAqB3D5YK4VorxWSoZC7CAHgOX0GILCf5KxeAUq0GsCASB2UHX9ayiAUbOWJGAFIMwfA6AENJRAWIVrWrMGIP6U1vAc1tH9HpWI2hMAOALaQdlrc9IMFoPmvVWBYheGALSWgtBSXcF4FgFghhgDiCbdzc0Zsu0vMwKoCt%2BIdgAoiGSDFLzaB4FiEZPNHgsBWvHHgHF3bSBm2ILEVJTw%2B1GCXUYYFawqAGGAAobsHx1SeSeQC5VwgBrqukC%2B7VagrUGv0P2lA1hrD6GXaSyAaxUBOJyF2tOSIPymE%2BZYMwhL92riwKBiAaw7AVqaC4cUMw/CFLCBEEYVQxiFOKNkAQ%2BG9AUaaIsUYNRejYf6FMDonguh6Cw%2BaAQAx2j0dI4x%2BY0x2MFEKUJoYxGlhkcwz87YEhzUcAeaQAlvAiXOoFUKkVYqJVSC9bzXAcqA1WKFiGi9awEC9KwIkDDpAwWSECAyZIgQ0UaEkGYSQ/K8X%2BH5akDFWLSA4sCFwBk/KuD8qhckZF/L/CSARU5/lymrVEpJWSwFF7qV0ojQyu1LKKBxtQH6rlPKOBtBYG1JMacmCsSfFwZIDJgvjvwEQVDSrZCqvEBqz9Shv16t0Cmo1TATXdoU0plT1qOC2qZfiO4jr1OupFVCftgs6sNd5r66NCRA2BDMMGtLlLw2RoKxtsgeX43%2BpQAYIwtWuD5JoHEhIGas16qLXmqtL2S1luw1WmtV460Nqtc21t7bO1Vt7f2wdLz8DnhHZ8K1E6p1kirXOhoVql0ruLeunYLyt07oBfuw9Shj3g6culq9r5b33sfVWl97X32avkN13VLy%2Bt/vPfBqwlhgOxHQ%2BByDAhoOwfcuz6wSHVMoYVbDsDTHuN%2BAgK4ajhHxT8eWORzIlHcgiYI%2BkNXdHJMMc4w0ZjPHWMK%2Bl00XjEmKj67EybzXnHWPK%2Bk%2BsTYcmhb6AtYlvVamXWaeq85Wr9XIX6aayQLbJm9thvM5ZsYNm/PYpAIEOrrmkz%2BGSKiwIbmPOxc94SzgKXyXpZpfSxl9rY1naK2wTgpW3UsAUG1CVbUA8%2BkmDKkPLXCk07fRID9sgv1M50An0gA2htmvd4py1XubU5YdU61QNe68N6bw6SYa2jsJq24EXboaqVZfLydtla/zv1/Ca/RvyRX7N4IK/OfH600PcoE9l5723sRGLaW8tlbd0/cEH9xtkPMAtptpiAg67pg6npY49rDqOCjpw6TrGyI67rI4Lq8Bo6rr%2BiY6bqri468D45HrkjE7nr7Z8DXoU6YAPpBjU5tZd6da96M4/qD6XbGCAac5o486vJ84MBdq7BbLC6IbIYJCoaS42ZcY4Zy54Z26K7oCO6Ma0Y5Cm6yFlB64CYG59DG6DCm4iEsYLBKEq62C275Ba7ibSHybO6/ImEYqjZJacDOrz7153Bn4MiX7B6GZh5b5makAWZMBWaUAKb%2BY4opAMiBCBD%2BCIqxZ4pBFJjhY56qZ562Cpbb4rCgogCSD%2BCOYopJh4pQqSDwpcAwpmAJYYqBAT657EoR4gpj7SrRHjamb7ZrD7pZDOCSBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_repeat/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_repeat.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_repeat.test.hpp)
