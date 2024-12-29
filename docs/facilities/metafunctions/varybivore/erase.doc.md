<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-erase">To Index</a></p>

## Description

`Varybivore::Erase` accepts a list of variables.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the variable at the index from the list and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>
-> I
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I+1</sub>, ..., V<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the variables of indices within the interval from the list and invokes the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>J-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>J</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase
 :: auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

```C++
template<auto...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 2, 2>;

/**** Result ****/
using Result = Erase<0, 1, 2, 2>::Page<1>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Result ****/
using Result_1 = Erase<0, 1, 2, 2>::Page<1, 3>::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `Erase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> 
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Erase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted variables.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the variables we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() ->
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<auto...> class...Agreements>
        using Rail = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Agreements..., Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZgAzBFkN4sHcTOC3F5HLRCABPeHYUHmSEMaFeWHwtzISboLBUDFYv7HO7KYiYGiqb5HYEETAsNIGVmEgiol7MNikO5MJGoCnXNC454EGl0hlw8EPO4EYheTDwqzXUH/fZ3ABqTFRTMOLLZHKYXIRwqIeraeCYsXoYqukxVDht6M1gQsd3mjmQdwlk0wqjSxCFIruADcxKq4V79cQ7Q61YEHuq42nwRqQVTAXmflrqQBJdn0NiCc05I3nQv5uvA2uHR6EZAIasm0vmtUInl81jdzHXF1eN0PFttkxeyeZ7Og1mdi1uLIAL0wAH0CAA6bdFp3D0fjwkkkAgCJYVRrpQAR1VksJRe3m4p4MHIKn1zun6Vps5ao/X8JUEv2A78F27NwrVQR8MQDAwFC%2BAB5F5iErARSCAkDP1pek8FUe8MUfAAxYhZAAFTaYBMAIBR0P/TDe0YftaKuTDPwY/lMEfCwmGQABrcjiEo6iMM/J1gN9PB/UDVlo1ocNrTwdBUVoCAVjuABaGCRLuXZdjuKJUFZJUEHNOEADYNCQhJUIYEwLLuPAvgiSNUF4zB0DuWJDVk1UFG03S7mDZUeNZDyqBIlhjMwUCzSMtI2n7VliAUJ86J0vTSIQRyHK%2BeJRC8JQ7gAd2ioq6Dk%2BK%2BMCyMEkNQg2X8vTUCocyNATJN6BS7c7I0BzBFQVr9XRCzUpYr8rJQppCWIsiKKohQTx8zjt0Fbi%2BIEoSFpAJboJfdUsVTfbNVzJtsBDLwjGigtrnnWLwPYpilV5Ri2D3ZUR2lM60guyi4ysQ6s0pK5bt/I88FXDdHyLQUV3XLdtwAKTe11PvOy6jwIdATzPYNL0wG83nAh9upfGHMexhhzzxgm7wRBHdsxPbPWzYCQa7bTALS1mf3Zy0RQZ2CmHgu4Jps5jWPSu4AHVooK6Keuwhl8JfaD7OtOkeLbAgEGi%2BZ2juZqoruC6isMUKo1te1OtGiXFdw5XsCIkjBA2%2BbxdYgKZeNwqFdle26YI7q1YGxgfGsoztei6NEytz5itKs2lRDlClBt1i7bwgOVZW7TWeejiuJ4/i5uEtKxK/CSpIEINZPkgbFOU1SNPLz8AoMiOTOlHrRam%2Bzsuc1z3M87yY0%2BRrAtUYKHCH8LUEiyOYt/O54pQtgkpS8fMv73LMHywqSuK8rl6L6raoc%2Bdx8Nnr2tjrqnz7/rBoNHq08/Hucmm52CFd6jFtHx9VpFx/ltHaJNGazgBrOE6OpsApyusyOcPNFyQUfDfZMfkmbOnem6WBQs/xvhZl%2BNmyD%2BZgO0vuaUtJDKoGUEwX6k5/oziBtzMCYMIbSiLJTYMLcfTYMoSRIgtDKL3i4ZnV8wEGG5yIUg%2B6MjCQoLAYLeCj4rjADpGyRgwlMESwKhEYAdwABKTA6DykVFgaEDEpGfggFYkCY4CCtgxljEALAmBuTXDjC815bzbBEeeZ84iJZfhPMQ6KDdaCElUeo8s1EAHukJGgzqgcnwvlUrYlYR0xqiUgcw6RrCESww3HcAY7QYbgzhncbAlMeF0hvHgOkXwIAlK7gieEioqnoAyWlChMpqFCPAs0wUHSeGSK5nku63I5F8yIALaEQs75RMwBowQGDAmYV0UYQxxi5JtLuOY2glixnWNscBL6P1wLHhcW49cnjqY%2BIGVMAgGIybONce4253jCaEg6epZpASTnBJAKEhySkIkIkWcs2JK14kIkSWPbOKTsBpKOXcDJgMy45OOlkxevMIKkM3BCmJqztIbP0f00xvTBF0PAoSzRd9nwQKYVi7UdYzjAm1HcQi9TJiVNUKwDk8DjSNlZWyoGHL34CHbIg/JeKZlkKHHwkWyEbKZOFcUrwaRijuQMZ8LwBypXXFJeqzVmRtW6v1bsiVtkEQaEFGYO1DKxXUh1QoPV0prpXCNS6t1FLcFKEJLau4XA7UOpfCefphIuAYhPEYughIrWOuZdSUinx3UIIVZWZAa55kJAIBAS5Ch%2BzZowW4IQGqtXoG9QcwUVankvjRVAm4Iq8zsupEIXeAgPJnX5fQA1Tbm0AgbNA41Fba19qNWWk1ShK3moIGuLgFKE02tDeAp19wx0eq9bO%2Bdvq4EBsFMGu49qj3RpABGhEh7wSntjWCtwS7V1JvuCmnlHrK7FqUO0fN5MQCFrYMWwkk7R3bsPbW%2BdGIG0cDWLQTg/heB%2BA4FoUgqBOBuGsNYH0GwtjywhDwUgBBNCQbWLxAIkhNwaAABxmBSMkLg/gKPka4IEQI0hoMcEkLwFgEgNC2vg4h5DHBeALVtfhhDkHSBwFgDARAIANgEG%2BgQcglA0DsjoAkKI/ZOCqHI2ZdSZlJB3GAMgf0UhNxmF4O5QgJBFJ6H4IIEQYh2BSBkIIRQKh1CidILoYNRUUJpE4DwKDMG4MEaQ5wBCSJ5MGxalpnTemDNGaDaRswdwIAeBU/QMM2IuArF4CJrQawIBIGU2kVTZAKAQGK6VkAwApD2poAchIC0ICxBC7ECIbRUT%2Bd4G15gxBUQIViNoXeIncPKZiQhBgtBOseawLELwwAIK0FoAtbgvAsCuKMOIGb9Tht4BqitxDwZd5Ih2LhiIrJWOIZRLEFCfWPBYBC8qPAnHVukBqsQWIpqngbeACiIwBG1hUAMMABQuoPhFSsvB3DtnhCiHEE5mHrm1Aha8/oQwxg0OWH0HgWIC1IBrFQGkJoK31IkjaaYSw1gzB8fe4mLAePVK9F284CArgZh%2BGDWECIIwqhjGDcUbIAh2d6AF00RYowahM4cP0R5wvg12GZ80R54veeS71h0TwXQ9Dq5V8sbL6xNjbAkIFjgsHSC8d4Pxu4MXdP6cM8ZpLKXcCWcyzhnLeGAdrB1kwLAiRGfEckOCTcyRwTMY0JIMwkgLIaH8GZVIrH2OkE4%2BCLgm4zJcDMuR5IDGzL%2BEkLRkPZlzchf44JkAwmAfiak4VmTEWkSKYq3PErGX1NsE4G0FgkZAjqSYILTZXBkiblT4d/ARA6c2dkPZ%2BH0hEdKGRx53Q9qfNMD86tk3ZuLehY4OFuTSIovW%2B07bvv%2BiB9D7IyltLzeEhwghGYd3eWxM18qxlhvz%2BxhzKMAPrgtr6vr0oC1jzHrDrLrUgIAvrAbIbBwEAsbTRCbKbELWbebRbZbEA9bdHLbRDfAOkaXfbELI7ZAE7EA87BoELa7W7VEe7HYRDJ7F7XDd7T7JQb7dAvRSvIHOhUHcHSHEAmHKfRzGfWQJHdzRDRfNHf7CnKwLHa7BnAnInHIEnMnBUcQqnGnBIOnT4eANYBXaXFnNnTXAoTnSmXXPndITIQXXIPQjnEwkoHIIwtXBoRXZpOXKXJoZpWw7XWXCw9whYbnJYPnTQzDI3fXVjDfEvTgA/WLfTD/E/QfYfJ3UfEgG/FPe/T3Ugb3X3SgE3RPZPQfcPQIfwZIJjcECPKPfPYvDzUvWwcvD3UTAravJAWTeTV/JvUrVvHYDvOLFgBQSMf0SMU/X8SYczeI8fYNHguHPg5zeQOfIQnQEAcEUgZfVfALfQILMovjMLOvaUQ2VQDoronovorsHlVLZojLRI8EZImo8TIrY4hIJo9LMYbozVNcXo5INcfoudbYmfOgP/ZrVrdrPrEAsA/rQbYbaAuecbSbabTAzAObBbMQFA17NAzbKgtbHbHA9QjzfAwg17Ygy7XgMgjrSgx7RMWg3gegr7NkZg/7C4tgkHMHTACHPkbgyfMYiQfglzKYlHWY0QjHSnSQnHaQpDWQ6uTgXYY8JQywanS3WnRSdQ/HZwnIFwSmJwrnCoCXEXUwpoJw0XGwnwtU%2BXew7QpXQYJwrQlw5XXU1XLw6YTw%2BXc01Uy0/XBQAIxzdfYLcosIj4u4To7oqMfY1kQ453MfRI7LXLFItIsYRnBPDjEAFITccEcEfwOjfPbjeMwITPVYy3TgMvCvGoojEASQfwYPRjQIbjcjSQGjLgSjMwIvVjcEN0tYgTao/LE3MzDMrfUM3Mt7RrBUyQIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/erase.test.hpp)
