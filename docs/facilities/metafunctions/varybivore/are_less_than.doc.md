<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreLessThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-less-than">To Index</a></p>

## Description

`Varybivore::AreLessThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are less than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &lt; Target) && (V<sub>1</sub> &lt; Target) && ... && (V<sub>n</sub> &lt; Target)</code></pre>

## Type Signature

```Haskell
AreLessThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreLessThan
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto Target>
struct AreLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Variables < Target)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Variables < Target)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgAMwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuABVWsBMAQodhgRNiF4HLdLsRMCFMAoFAiEIZgSYAlYrrc6bdQeD3pgoTC4agAHRcgBqrTwTBi9AU6OB9NuWJxBFuymIqCIyiYKNF9KpNMuYrFc0cyFuaAYE0wqjSxFuMVQnluADcxF4WbSNXTVbcIFyOeYAGweiC84j8wXE26sxHI1HLZaBgIAESharFVOjiVjKvtdMZz2ZrNhRFdl2ABLBjAIwsSGJTty8WSM0sVmEDiUj0tl8prrNz%2BdeRddIsTlLLaYhLOhWc5PL5AqFIrLWrwOr1BqNJrNFoVKIA%2BpblY7qc6u2ZPXvvWP/Qo625g8QUQQwxGE2r4zHe9d/n9Ab89rdsKpWM9a19gW/nzOR831uABZVEmCoLwGAcHJPiAq5%2BwzId2RzC9i1LS4K3CYAwIgqCYMaSl6zxAkiRJMkKWhZJJ0uEAQBXQc3HxYAFC7EsHyuf8jkRYkpT/K5p2QVcmBJeICAgcCWgI2CBFZMxSFuRJFMkdF6OtbxMGWTjLiEkSxLaCAwDAPDpOg2SGFZd1FIUpS1JADTbW0xMOFWWhOGSXg/A4LRSFQTg3GsaxxXWTZa3MRIeFIAhNFc1YAGsQGSSQOQ0AAOMwzAATiyrhknStKuACAJpHcjhJF4FgJA0DRSG83z/I4XgFBAWqYp81zSDgWAYEQEB1gINI4XISg0CeOh4kiVhtlUNL3QAWndSRbmAZAdSkDkzF4TB8CIX10D0fhBBEMR2CkGRBEUFR1A60hdC4UgAHdiCYNJOB4NyPK82K/M4AB5OEhqlVAqFuWaFqWla1tuDazGdDxxvoE0Iq4ZZeHarRVggJAxrSCayAoCBcfxkBgCkBSaFoUFiBaiAYh%2BmJwlaABPd7eEZ5hiGZv6Ym0TAHDZ0gxo7P6GFoVnbqwGIvGAGFaFoFruF4LAWEMYBxElvACVgy1iR%2Bw1%2BbhbYovCUEyt82g8BiF6uY8LAfoIX0qqV0hdeIM0lEjME1ctoxYtWKgDFY7k8EwR6/rSRhBaO4RRHEc6Y6utQfvu/Q1ZQILLH0K2WsgVZUDSRpFfmiZ0ChSNTEsawzAat39r1vOen5xoXAYdxPE6PRQnCYYqlGB7imyARpj8AfMiHhgFhGBIHrsZu%2BkmdoO4KWf6nngR%2BjaKe%2B5n2xF5HvQ5i3nvFn71YFFCrYJE%2BjhPLqn7GrBubFuW1b1pSuGIFwQgSEDMxIrRtFf2qwECYCYFgBIEAEr%2BESByLKiQSoaEkGYSQ7oarJHdFlfQnAKqkCqpFDk7ouDujSllQq7pkp5XgdZeqvBGrNVakAjqWNerY36oDYahNiZIymmwTgrQWCWgCPNJguoDBVi4FlDkXBUrbV2iQPAB0HoxxOvHaQiclDJ1uroBSz1XpsxvnfWhv0OAA0GnCW4IMn4Q2WsgcRuFJHSNSvDVAiN4h/0SGYQBGNOpsO4fEEaRNXF4yRigexkiuC1UptTWm9NbocxZoLBJXMeZ8wFi7YWhZRbix%2BlLGWcsFaCxVj7bYvl8Da0cLrRWvkDbICNoLU29QfqW2tizO2pT0ZO0Fm7D2mAvaqyML7UAzC%2BBBwUCHMOEco4uxUXHM66jZBJxur5HRac/aVysFnFpucoF%2BULjkYupdy4bOrrXeI9cdnnzXhZVu7d8ij2CG3beSwx4lByAfV5E9nn9ybhZTeS97mH2uY0f53zd5HwBZ3Wei8wXXzWBsK%2BqNsG32%2BrdR%2B4MX5iLVjDKRMiNDOm/ntDxqN0bANIKA8BoxdllVwfgqRSCAjJCysVRIyDUGSAesY%2BhthGE%2BJYfANhA0gaBP8cQXh2wBGQxYAoS0OpLSOIHBMORP99qHVkKo%2BZF15CaOWToJIT0XpvSVoY1FDV/ocOBqDVQUqZVyoVcyCYLi3HI3/okbx/suo42CfjEV3rQmyrSGkdckjVyKoIKua16i6AxMoHE3yySJZRQTak5ugtMmCGyRLMpmBpayzEIUl2xTBkdNIOU%2BeVT9aqENqCBpggmm3RaTbZm7SHZdJdj0zIfTvaDJwh6wOipxmh3DpHbyUVZmnQkAsy6OqU76vsRnKuWyc7wHzvsgQisdilwXZsiwNc6F10UQ3XZc8bkQFcB8x56BYWfMaBewejRr2/JBfvZeDyT3PvmCfaeh8X2AuhZ%2Bio36kUXwRWdE1980WcDBja2VVp7WgkdV/eRLqAGkuYSAsBEDKA31pSAbKHJEgpHyhymqhGAgkIg2apqPK2pksSpIZIcCioBBqmlSQuUuAZT3MixIpq6GcDQ5jG%2BW1KP8eo3y1YbssjOEkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_less_than/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_less_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_less_than.test.hpp)
