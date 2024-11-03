<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Contains`

## Description

`Typelivore::Contains` accepts a variable number of arguments and returns a predicate that checks if an element is in the previously provided arguments.
<pre><code>   Arguments...
->&nbsp;Element
->&nbsp;Element&nbsp;&in;&nbsp;Arguments...&nbsp;?
   true : false</code></pre>

## Type Signature

```Haskell
Contains ::   typename...
           -> typename...
           -> auto
```

## Structure

```C++
template<typename...>
struct Contains
{
    template<typename...>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Example

We will check whether `int*` or `void`  is inside `int`, `int*`, `int**`, `int**`.

```C++
template<typename...Args>
using Metafunction = Contains<int, int*, int**, int**>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

`Typelivore::Contains` uses `std::is_same_v` to compare elements and the fold expression to combine results.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename Inspecting>
    static constexpr bool Mold_v 
    {(...||(std::is_same_v<Elements, Inspecting>))};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEIADMZqQADqgKhE4MHt6%2B/tKp6Y4CIWGRLDFxibaY9kUMQgRMxATZPn4B1bWZDU0EJRHRsQlJCo3Nrbkdo739ZRXDAJS2qF7EyOwc5vGhyN5YANQm8W4EAJ7JmAD6BMRMhApH2CYaAILPLwSYLMkGn0cn50YrEwADowdh6GxBA94k9XqNiF4HPsPII7gwHq8TAB2KyvfYE/afb6/TD/M4XZhsfYASQxFwcoWAj3ehP2CKRBH2ymIqCIAFlPOhWYScRZRfi2YTpo5kPs0BjPqpksR9lFUJ59gA3MReTCHSVSw64iBgkE4twWiCjdAgEB4BSXBTAy5a/4Qr6MAgKUi0%2BmYRlGR4LBY4gAiRzxLzZ4cj7xFBOJPyYf2OFKBbDNL2AxEwnuhLMN%2By86SM%2B0FtHQh3iYe5vIFQv%2B2dz%2Be9ZpZ8SjCaJX2TqYBlOBfoUDMcQdh3ZleDlCtGmGVqvVmor6FdBujopN7exlp31oItvtjudbFd7shXp9w9HTODoexEc78YfcaxrwA9AAqb8/3/v95ft%2BAAq2BCEBP7/h%2Bv7QZ%2BkFvFiZjbAwuxeAc/wKusyTeoW8EfL2pLkoCVKgmCLzEMAMJwi8JZMuWmCNFQXjIXU1a1qijShDCbihAQvo8Z%2BfGCN%2BgkEN%2BOF2iuTbkQo7YTk%2Bb4vFOyCXEwChKM0ED8vRTCMcxmT/Pxjx2jq3iYKG8mKY0soqWpsQEBAYBgHRDFMYyAj/FqqB4MKsLGbqZmRhwSy0JwACsvB%2BNwvCoJwlqWNY7IrGs%2BpbDwpAEJoQVLAA1iAoWSCCGiSFw2LxBooUaGYABsVVmAAHHV%2BicJIvAsBIGgaKQkVaKQMUcLwCggJ1GUcFoSxwLAMCICAKwEMkXi8RQEBoN8dCxOEwKcKodVVQAtFVkj7MAyBylIIJmLwmD4EQxDeXo/CCCIYjsFIMiCIoKjqKNOh6AA7rcyScDwwVhRFmW9ZwADyC3zVyqBUPs217QdR0nfsZ1mPsEAeKt9CqqlCy8CNY2kBASArcka1kEtFNUyAwBSEkNC0J8xCDRAUTg1EoRNKcQO8NzzDEKckNRNoAYjWlK1QgQkMMLQfPfaQWBRF4wBuGItCDVFytfIYwDiEr%2BC5oyWqYNrPXzgGC0bGlPE1ODtB4FEtzCx4WDgzceBtTrZvEOqShhnrRhO0YmVLFQBgUQAangmC/ZDlL829wiiOIr0PfIShqODuhcPo%2BsoNY1j6M7g2QEsqBYZk2u7TaRxhqY8WWGYPWoH7t1YOXEBLHYEuZC4DDuJ4bR6MEoQDOUQz5wUGQCBMfgz2kc8MLMgxxPnfdufUYwtCPuSbzU/cCD0zRr1PG%2B2LvC96NMZ8T3M0%2B90l6wSCDHDhV14N9YjO37Ydx1ToFUxhAXAhASCHEQlwQm6Vw5LAQJgJgWA4g91ILlSQ8QQQAE54jYkkEVMwkgqodVClVLBTUOAtVIG1eIXAQRVS4FVOqWC6qMPylwUKOCqpfyVn1AaQ1YHfXGlNMmM0YYLXIJQWmeMNpsE4E0FgWpsS7SYPKAwZYuBYJBHQy210SB3XzpnJ66dpCZw%2BjnJWugkj/SYIDKK79P7dWilDcRcMEYKKUSotR%2Bt0ZaJ0VjHGlM8aQMSDA4mQVSbk1QLjWIkjlrRKCUMDxyjdj600VwTqzNWbs05krQWvNk75OFqLcWDhk7Sy9HLBW4MVZqw1rQLWycsAsH1obHqxt%2B5mwtpdVQ1tPjJ3tiFJWTsXa83dhsHqXsfZpT9gHTAQcWkhyZOHPgUcFCx3jonRgycjFpxeqY2Q5ivo9SsQXMOTcrCWFLlEbuldq4CFrvXGsFzrCt2ih3by5t4C9yPtvQew8ciL1IOPUo689CzzqDfJehRMjn3mIfLoJ9r77yBVvOop8%2BgPzBZvZFgLb67zhU/ZYqxX7QIoY47%2BnB9jJK8akjRfjCpYzATdEJ0CiZwNIAgpBQxUFDKoTQrRRVsScOxKVSQhCDr5ycRDfqtgBHhOEfAURs1YZxOketTaHAFEoxYAoLUcotSaJBKSUYl09Gd3urIYx%2ByU5HNzgkUgNi7HA3JWDXhLi5oLX2PDalxAWA6r1Qao1JquTYwSVTEJ8QwkrNEeq6mUjw14xAPq5IyRXSaMuCGlSfqDp8DoNkyguSepFMVmlEtJSJblOiTLKpit2mYFVurTW2s0rNNaRM3gHTTZfKVlbZANsBmCAdsM52rtTjjM9rdaZvBZlpHmcHA2yyhGrKYDHOOCck4612c9CQBz3rZ2OT9eIZzjDFyuSM25vV7kYk4O%2BG0Rdm4WDeb1D5XdvmdGPn4CArgoXAqHoSy%2BELMi/qA8ULFF9b6/PRbi0eCLP0YoA/i3ov676YtBRBslCgX4vQcW6tuVLtWHV1fq7UwaUzm1DcyiBBN2VCPgYg5BlB378pAGYLR8R4ihQqsVDqHHsRMJ4fh2Vg1hocvQaFbBoU6rVSwZILBpVcFcGPUM%2BIeHnGyoVe/C6gn1O0bGksP26RnCSCAA)

## Links

- [source code](../../../../conceptrodon/typelivore/contains.hpp)
- [unit test](../../../../tests/unit/typelivore/contains.test.hpp)
