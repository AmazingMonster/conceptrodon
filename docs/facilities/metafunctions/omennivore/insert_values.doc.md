<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertValues`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-insert-values">To Index</a></p>

## Description

`Omennivore::InsertValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of variables and returns a function.
When invoked, the function inserts the variables to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, V<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, V<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, V<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertValues
 :: typename...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct InsertValues
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will insert `-1, -3, -5` to indices `1, 2, 3` of `0, 2, 4`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertValues`.

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = InsertValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Page<-1, -3, -5>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<0, -1, 2, -3, 4, -5>;

/**** Result ****/
using Result = Metafunction<0, 2, 4>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `InsertValues` is similar to that of `Varybivore::Inject`. However, since now we must deal with a variadic number of indices, we will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

We will use `Prefix` to enumerate arguments like in `Varybivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct InsertValues {};

/**** Base Case ****/
template<auto...I>
struct InsertValues<std::index_sequence<I...>>
{
    template<auto NewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        // `NewVariable` is injected in the return type.
        // Note that `Shuttle` is instantiated by values
        // extracted from the template parameters.
        // This is because we will pack every variable
        // into `Vay`.
        -> Shuttle
        <
            FrontTargets::value...,
            NewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto...I, auto...J>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Shuttle
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable,
            BackTargets::value...
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<auto FirstNewVariable, auto SecondNewVariable, auto...OtherNewVariables>
    struct ProtoPage
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename InsertValues<OtherSequences...>
            ::template Page<OtherNewVariables...>
            ::template Page<BackTargets::value...>
        >
        ::template Page
        <
            FrontTargets::value...,
            FirstNewVariable,
            MiddleTargets::value...,
            SecondNewVariable
        >;

        template<auto...Agreements>
        using Page = decltype(idyl<Vay<Agreements>...>());
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIA7NIADqgKhE4MHt6%2BekkpjgJBIeEsUTFc8baY9nkMQgRMxAQZPn5cFVVptfUEBWGR0XHSCnUNTVmtQ109RSUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimAmujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW4vI5aIQAJ4Q7B/cxAhggrxgiFuZBDdBYKiI5HvHbnZTETA0VQvbY/AiYFgJAx0rEEOG3ZhsUjnFIAL0wAH0CISTmg0TcCKTyZTwQDLucCMQvJgIVYTn8PhtzkIENCCPRqVtafTGUxmZCmNDUAA6G3C45DRUOLU6gh65UA1W/YkXABqTDhBoOfzpDKZ7rcFqI5z9xDwTAi9DtDq8Tr9CLVsQs3LqjmQ51FQ0wqgSxHOkdQ5wAbmIleDMzG4wnlbFLiq662PUTTiTsKo6Qx0AAxYiyQNG0Om8Os9msTA2q1JhUpiW9/tDkeCOtWFsqrshk1mtz7sNY8vzxH5gwKZ5CTAARyVYq5Z5tDfj9AUi8dK77rmHsixW8H3ucM3ybBRzwBJEoORTM/nOBD5WNE9zUtedQkwAB3MCPztRDzi8FIjFJJhgEwGU5SAx8VixDDsPqRsP3nLkcKeSDoM9Ewd07NVvS%2BfiaXVEkAElQ3pRgczSMchIE2SfmDZDJxZNlGFndi/mTJ1hIYJQGj9bwni3LiO04vjNQsJglHOCMrNeBSJ0PF8rWEr9l3ObTdIIfSlU/SFcRAEBgiwVR%2BSUYCxSxYT1JgjNPXw48lNQqM6NY580NtGLjnwzSJTJVAiGUUjlROfCuLi/DEIS5kSoqhCsXg2qKrWNZzgAdXIwjyJMAA2DQyQpPBVEixFz16%2BUK0YHxokncFev/QQABV6jIghP16hcasaxD%2BspYaoPneaCCW4gVoUUgGq2hDp1Uth5ws5AAGtjtOi6KrwxqJlzfMBELataDLS1zjwdA4VoCBZle/DmtmjQUoY99lTGvBnmCbRMAcTB0CBhh5QQcjyQIJYceujassa6HQny8iCAQU0Ye1XVEyRlGdLqQQ4zpLGIgDP6fMhxDoaLBUmAxrGqBHFhcepxS6XOBJ6lnOliAg/mEOhhaEGRoHniiUROvOTDyMwuh/vlx7zkwStoh5%2BGm1V85oeCKMeo0NMXdJraAFoLwZ11E02t7IXt/DDuezBVoC3m5xtc6A62uHYwR2Oycu857qe5bw4USOa2jj3GsJHivRTiqqvDJzjmAclxMEXykTjxDCOCYASLIijziwEFrogYHQaxN3IUr6u2FrkaMuwcGIaL0ruNMkuy9PdKrSHzAa9W96EKb4jCrbiE5TygqiqxFe14g8fdwzEy9xl8ul%2BEtKiHnAApVytJ06IvNz3y3H8wKByLUK95qLhiiuPLkv8goALCsArET9or11%2BHBAOC8koVkHHgZWBAE6MUwA/Cst5RToGwUnAGj9z4BxypKfKqAd7FRLmVe2C8G51SDswpqLV2oESsi7Hag09rYFGhocaFsGBTWIDNF2odM7r3WsHbaUo%2BGQhcvtG0UiTpZ2TqnNWHCOrcN6rwoakIX4qIXGNKMwAKwixHNeKWHdkZsxomwqGLUogEENoweUmEKzDFOvnVOBjYFjytAAWWBugegYdVqaK0ddDked06RM/GwjeFVPp4DzAWOkf1SEVl7mDCGbDvZQWdIzOhW16pOMQmo06OcDLMTkQhdBmDiFNmianUJeIInSOziAKO9TKkIQIQIIhWFUoNLTiLDO6iI69NzueZJMEi6MJvovMhy8q6rxHuvTKW0t4t1oe3TutBu55P7v6Y%2BGzT5BMRJPC%2B9DZ5dniis1B84T5bLrq9PZrcuqyioYfMiFzh4STPguRZnEHm8W7BcAASujJYKQrbWUsuROyJwUERjvng5%2BXJYlqRtAAeRptEKiIEPknEoR5D%2B3knhYggf/EK0CQKRXYuAgg6AAqQIZUAplRiWXnEJXjYgJKxQgrtAw5BzyMVRiaUMFp9A8FanRsMuVuCcnzgFdEFVZKS6UIPjQo%2BAdxUlyeQ5MpBdWHGvJjorhXV9EKMMW4ZRAjbRmImqItg4jZaSI3Edbp7txkBKUUE6pGjxnQ04frHh9rAkmJdsIixZZkDWOeESuxEwIoDIdi48O7jiZePlN0vxl1A1uGMc6kJYSunTLOuM3Ft0bQJL9QshBW00kZJ%2BlksQOSgYg3yfbIp2Bzirj/D6%2B2FTLW1TreRSlekv5Yg1UK7lIr1KZoCmXb586iXEC1SuidFU103w3ZCRt1balKl3eUnZjUD2mo3Qstw4yQ0zL6THR9GDZWjNtvK8ZHTwmYESWevObTLpDIHCqsdYLHmNXRRXS57yUn4S%2BQcveHd0bHJUj3XtZyESDzg8C65UFbnT0QsZO5r0YNLzefhq9m8iL7KKu3PVtDAWbOBdFcFV9IUalkkGMyQ7VCsEZCiwSZkePyTVICYEoIfnYgECsBI2yEEyS2CUv2wnDT2QPLfNZr8JS%2BzdGRvjwTw5MCoF4NE1RpJoslRXE62qvnGbqGZizUkUMzs/gZJJvwLXZTZQFFgTAHoCk5YA8KNFIRcERMB3%2BAWgv8hC4yiKkIzCe0i1BaLfmQCxeC/S0LMDIQAk9mYMVmUArMchKlrknsARVYAKx2jK0fQedn2Ndg1FqLwCQciY1hQoLwxyrPHC%2BUITr3X0C9f6xKFD%2BnEyQg0FV1o5wzBVZq%2BcaQ5xPb1cg1xkkE2BuoqG3R84e2pu/Mc6Z8zDg0hYnm0trkkhC5z3awtJ4EoDttv5JZTyEBf4KFnJ97%2BI2uvJB608SbXITuIinp6Dg8xaCcFq7wPwHAtCkFQJwB9lhrDckWMsLqgIeCkAIJoWH8wHogFq5IK0GgAAcZgzAAE4GdcFq7TmnZRyjw44JIXgLAJAaHm8j1H6OOC8GzvN4nKPYekDgLAGAiAQCLAIAkaE5BKBoAZHQTVs5OCqBp91T23VJDnGAMgPMUgrRmF4JjQgJBgZ6H4IIEQYh2BSBkIIRQKh1BS9ILoVomFxEJE4DwOHCOkck7R5wfF0IVcSlQFQc4euDdG5N2b84FuzDnAgB4TX9BSwoi4LMXgkutDzAgEgDXCQtdkAoBASv1eQDACkMtmgxzojZwgBECPERgj1DhMH3gPfmDEDhPiiIaMHAD9IBrrZ%2BKGC0H7z7rAEQvDAAjLQWg2duC8CwAFow4gl8YPRo4K2W/UdFjhXSKfTtKgR9hBEcRI%2BPBYAjwqPAfPt%2BkCtsQCIIPrh7%2BAFhCMBJ3mCoAMGAAUB9EeEwnxXZCn0d2EFEHEDdwQM9zUAjz930EMGMGsGsH0DwAiGzkgHmFQAUzSC309lxD3lMCx0sDMGF2/1jCwCIPBjaGPzSBcAHFGBaFIECGCF6GKH6FaByFSAEG4OyGSFEIYCmD6FKDYKuwEE6BGE8GaD0DsHYMUOGG6H4OmCENsC0PEPGC0JkMENKHmAUFxxWAkFDw4ER1ICF14BF0T310N2N1N3Nyp0zwgFwFt3zwJyLyJxAPmDxiYCwBiFYPJ0kABCtAZwBHiA0EkDMEkF6g0Fq26gZ30E4B51ID5wBC4CtG6i4G6hpwZ3Z26kpxZ1iO6nsIjxFzFxAAlxAJl3l3L0Vxj1V1r3rzz1CB1w4HqBYErFiE9iYEvGwPTwZytHyPP3wCICYId1kGd2QOkFQKUHQJ910GWwDyYCD23xsLsIcMjw4Gj2V2hHOHj2cOT2NxBDGK4AmKmKzxzyrzz3BEBDMACJL2l1aK6OiDVzr1QFz36GuKMFuK4Hm1byVg7y7x9yHz7ynxhJHzHwn0l0JxnwkjnwXwj2X1X3X03yn132wIP1R3wHJCu1Pwjwv2QGhFWEJxvy51R3v0fzhGf1WFRzfw/0J2/1/yUH/wJObiaLANIkgOgNgMYHgIWKQNd2WNkDQO91Rw2KwOAJoKsEsHwMIPgBILIJ%2Bk4EoLZWoNwLoIYOiCYKeHVPkOqE4PcBULGF4IHBMJmGEMkOqEMNIBEOqDtL0PUIUJqAMKtJ4M9OqCUO0MKFkLUJ9MyD9OMJ0JDMLwWCWCsJjK532NqM4AuNcNGOIluMmOpyzx8NmJeLyPeKCNIBCLCMoBsOyNyImISNiFqwZ1iFiABESOSMkFaAOLqNsAaMCKlzLxaKQCV1j1%2BO%2BO3V6P6JTxYAUErDzErEzLDCGGtxmLt3ZVaAQMWMlPd3kFWNlJ0BABqy2J2JD0yNsPDx9xF2ONjzOIT1UDHInKnJnMnCGAeP%2BKeOiHzIBELO7JlwryfOr0HO/Lz16WQC635GnIZ35FnIIH5CvOWLoAhMoChNR3hMX0J0QsROPyn1RMEHRMXyJMwBXzXzEFxM/3xP3xZJ3yP1JJNJ9wpKpOv0EFvx9wZL72ZNf1jHZN4E5L/3pF5OAI/IFIgKgKwhFOR0JxXIlIkClI903IwJ3IVJwNoJsHvxYI1OqC3zWH8iVOsHoMcMYOBhNOILNI4IgFcGdL4ODNMIkNyDSGdNdLSHdLkP9I6DDNUPGEqA0O9MmCjPMqMK6GdImAaDsusNjLx0CsTOPOFxTKgvOHHMnKrDvLpAfO8IXL8ILOLyLJLP6FYK5wrJAEZytABABFq1ZxbIF3ytiGKJqJPM4HqMaO7LJxAEkFqxiI5wFxp0kGZy4DpzMGqK5wBDCscKqq7NLxsKtwqvCtF0GtJy/3bw4MkCAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/insert_values/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/insert_values.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/insert_values.test.hpp)
