<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-erase">To Index</a></p>

## Description

`Pagelivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
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

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateErase<Operation>::Page<1>::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<0, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = CognateErase<Operation>::Page<1, 3>::Page<Args...>;

/**** Result ****/
using Result_1 = Metafunction_1<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `CognateErase` only accepts one index, we want to remove the variable at the index from the list.

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

- In the case where the second layer of `CognateErase` accepts two indices, we want to remove the variables between them.

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
template<template<auto...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiVyptpj2ZQxCBEzEBPk%2BfkENTbmt7QQV0XEJyWkKbR1dhb1TQyNVNRMAlLaoXsTI7BwA9ABUR8cnp2cHeyYaAIKHxwDUACKY6a6MyHiYCvcnlzd350Bpz%2B1yuoLMSQiyG8WHuJiSbi8jlohAAnvDsGDzJCGNCvLD4W5kFN0FgqBisf8TvcAGpMVE/Y4ggiYFjpAwswlMJGoWntPBMWL0Ck3KbELwOPnom4mQIWe4LRzIe5oBhTTCqdLEe7coj3ABuYi8mDhcrpxAFQswsse8PlNrtlNu1OUxEwNFUjKOzNZ7KYnIRBFRr2YbFIOp5Iuuqp26QI91d7rwnvhj3uBHF1qSVhlVKB%2Bd%2BYIBB3uAEk2fQ2IJ/bkvRciwXG/Xc86Ho9CMgEHWfRX/Vm3EGQ6ws5jRRmJfH2wRO6arIFbdmnSzewG3NkAF6YAD6BAAdPvS1GxROnh2EISSSAQBEsKot0oAI7G3H90v73cUpKj0FysH3f/pr6HLWjcAFwgif5gQBy5%2BquuqoO%2BGIqgYCjfAA8q8xA1gIpCQVBCZuh6hKHl%2B74AGLELIAAq7TAJgBAKLhoH4emwaMMOTHXCxrFDmw74WEwyAANY0cQdEMXh4HfmBip4MqqrqoatARnqeDoKitAQKs9wALRIZJex7PcUSoCy6YIP6cIAGwaBhCTYQwJg2fceDfBE%2BqoEJmDoPcsQMkpxoKAZRkahmgksj5VCUSw5kmjBwH3Ok7TDiyxAKB%2BzH/oZ9xUQgrkud88SiF4Sj3AA7iaZV0MpSXCfcmD6gkDKEKywX3KgVDWRo5qWvQ6X7k5GguYIvKDXS6I2RlXEAXZWHNISFHUbR9EKFeAWYO%2B4YCcJoniatIDrYhX6OjK84naCeZHPc2Cal4RgmoWNzxX2hKDuxYY8e9I5gseko3ekd10bODqLi2z2rhu257ge4aQzu74AFJHuOf23fdF4EOgV43hq96YE%2B7yvkd2Cw5j2MMLeeMEy%2BhII8TUayjm03/uDIHM%2BBbiSWBrNcjyxPIUwqH3LNDmcdx2UAOomiVJqDYmREIiR2CIc5epuoJXYEAgJoLB07WdVr0sMGVhgRQa/KCn1U3cfLybERi5GUYIu0rWLLGS9LpVy4RdsIkjpEDarvKMD49lmYb5sWpbXzlZVpvpsHWFKNbLG26otMO/ubv4W9oYbfu20ictEmZVJkmyfJAiKWIKm8mpGlabpUZgdlJnhxZ8aDSL83Ofl7med5vn%2BUaXxtaFWEOIPUWoDFEes4lyVsKl6VtblfeFZgxWlRV5XVQvdUNU1LnLm1HVdT10f9R%2Bvcjef9KDSn/7d7kC1OwQLsMWtI%2Bbfchcf/th0BrHVBj%2BBcTMGwPA8MAZgLJsBJwekyMEPNAxARegieC/NoSC3QphByyNxSSigTAnA8CsS/lLsgtceBNzwyAdJACv14yulMqgZQTAgaMxBuAihqCIbUKhmWCmGpm4MJRkwyiRA2F0WIkI9Ox1S6cNLtzXh/YMH7gvlaIK8j2ZgRKhEYACZ2GyySGmLA0I3pcwAhASx%2BEpydgxljEALAmBeS3DjO8j5nw7BkbeT89DuL/ivPPeutBCTPxwlKQkGi%2BqZw/F%2BLSNj7irHOmBLhTplErn7HDeMgwOiw34Tua6FMRH/jdE%2BPAbpvgQFyZ3CCJiinoGSaXRhBEWFSP7DU8M2BinaNSeQnR0EVG8yIO%2BaJo9eksT0UYQxHD6lmNoBYpRVjElgX%2BoDLJZMnEuO3O4qmXiOnTAIBiUmjjnGuN2Z4wmhJunoB0jUvxKyAJBJUS5dSoSEThIYOGcaUSLaaNiRiBJSz/zJJAX0sB6TBmZOGQhfc1xgBulZIwCSEz/xTIMe08CaZmGSKMYSeFiKqwMXpiAtJLZixNjOCCYs9wyIVKmNdVQrB2QIO9BAyl5wQRYghFCGExiiQCFjCi787KSyfO7EgoZ6C%2BZ0J%2BmI4WuD5qksuiWIQXh0glG8gAJS%2BF4BZEqbjovuGqjVWRtW6v1amBVYcX4Ig0OGMwDrPzcNbFdAAsvRJgVA7oOFrI9a4lC1G7muGJLR34jUeraN63EzQsX3CIX2OBgt%2ByfIxFedphIuBppABmhEIbgBX2dU6GlOqFB6vjP6o1pby1xsjV6n1Sq3D2vuFwB1TrgEuppVRL4FbEFjhrMgLc2CEgEAgJeEAChhxDq0W4E1mr0DVoWeGRdRyvygs7RyoE1LqRCE3gIHyN1mX0ANa6zdwJi07vVfOldJ6jVzrNQui1BAtxcDjamu17bMTKtPfcOt0bfUCBPYGmVwbQ1RgjZ6/9zQX1xoTbA0hHzFW2uwOmvFCJW33CSNm3Nbh82Fo7Reh4N7K3ZGmSumDVq/0NtyC%2BwkzaMOOvuGYIt5LqTdoZf6iu06lAdDHZsydbBp2EnvUoR9ZaFkvuXU%2B2ja67QcHWLQTg/heB%2BA4FoUgqBOCc0sNYBUmxtiywhDwUgBBNDyfWEJAIkhdwaAABxmDMCkFIXB/B2ds1wQIgRpCKY4JIXgLAJAaHtap9TmmOC8FWva0zan5OkDgLAGAiAQCbAIADAg5BKBoDZHQBIURhycFULZqyOkrKSHuMAZAyopC7jMLwbyhASBqT0PwQQIgxDsCkDIQQigVDqBi6QXQraypYXSJwHgCmlMqbMxpzgaEkRpf1vcQrxXSvlcqy26zZh7gQA8Nl%2Bg2psRcFWLwaLWh1gQCQFl9IOWyAUAgFdm7IBgBSEdTQBZCRVoQFiNN2IER2iojG7wX7zBiCojQrEbQm9ovGay0StCDBaAA/61gWIXhgBuDELQVa3BeBYGcUYcQyOKlQ7wI1bH6mNSbyRLsYzEQWQ%2BfUyiWIWFQceCwNNjMeAAs49II1YgsQzXPHx8AFERgzPrCoAYAtNJPhlTsqp4zLXhCiHEJ1pXPW1DTcG/oQwxhrDWH0HgWIq1IDrFQHGXI2OdIklTKYHTlgzChb5xaLAJutJ9BJ84CArhZh%2BFbWECIoxqjjFbSUHIAhfd6DD80JYYxage4Ay0Q5kfW12E90nxYgflgh9sMnzw3Q9C62GFnuPEh1gKH0zsMv%2BhJukBC7wMLS2islbKxVqrm3tu4Aawdozx2TPi/WNrJgWBEju8s5IJIu4UhJC8xoSQZhJA2Q0P4KyaQfN%2BdIAFpIXBdxWS4FZWzKR3NWX8JIFz0%2BrJ1%2Bm2FiLIAovi7i4li7yX5tIgy/dme139t5bYJwdoLB9RAgdImABZpkuAUhdwd8Kd8AiAXdmtZA2tVdpB1clBNd%2BtdBHVhsmBRsccJsOBlMr9%2Bsws5tUskRFtlsW9QCDFwDICbNttdsv8Eg4QIQzA%2B9TtYtn8Ht9t38uDxgsEjBwCuB7U3tl5KBvt%2Btgd/tAdSBJDQdwdIcHBpDYdkV4dEdpsUc0cMdaAsdpC8dddCd1N8A3RfUydptKdkBqdpC6dGhpsmcWdUQ2ddh1NOdudjM%2BcBclAhd9D9EH9Jd2EFAZdMA5cQxpCldECOtkDZANc%2Bt1MMCdcxc7crBLBDdjd4AzcLcq5OBrdMZbd9cHcncEgXcvg0iE9mgXAKYU8QgKZY9g949o9chKj6jygS9ajC9Gh08alKi09E8akaiVhU888Cg/dc9M9KhS8jsNgtgq8JifMCD68ZsOAm8Vsyt%2BDqCICoDO8YCSBmDt82CB9SAh8R9KA8CN8t8IC59Ah/AUhPMkh59F8z9CDQtOBb978Ytzsn8kAUs0seDP8bsf9dh/9VsWAFB9RlR9QaDgIpg6sti4DW0wiVcIiut5BUCYidAQAkhSAsCcDxsa98CpsiDZtX94wz5VAgSQSwSIS%2BwGUdtfj9sdikg9i3i4tLtaSEgfi9txhQSNUtxwSUgtxITn1STkC6BRCvsfs/tQdpDZCwcIcoclCZ44cEckdDDMBUd0dMdsdjM9CCcnDcdicTDij%2BtzDLCedrCGdeA7D/tHCOcLRXDeB3DBdWRvCxcmS/DpdZd5dQiECESJBIjusUStd0T4i9d7cbAmc3d0jmhsc9hLxEjrBHcG9nc1JijTdSjchyj3B89Ch/dqiWj%2BiMgshw88gszhimiGA%2Bic9ujmhOiSy2j%2BgBBei8zKzBiC8BjRig9%2Bjy9K8Os8C5jr9OAlsyTQSDRKSWRqSu9YCdijsTt9jDjxh3d19/MQBHNdwkgkh/BXMz8gs1zAgD9HiG9njbA79%2B83iLMQBJB/Ap8PNAggtbNJBnMuB7MzBL8fMkh8SnjwsTyzs8Dat9yFiZzTzecPt0zJAgA)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_erase/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_erase.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_erase.test.hpp)
