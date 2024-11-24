<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRepack`

## Description

`Pagelivore::CognateRepack` accepts an operation and returns a function.
When invoked by a list of packed sequences, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Operation
-> ...Sequence<sub><i>i</i></sub>&lt;Variables<sub><i>i</i></sub>...&gt;...
-> Operation&lt;Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

`Pagelivore::CognateRepack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Type<sub><i>i</i></sub>, Variables<sub><i>i</i></sub>...&gt;...
-> Operation
-> Operation&lt;(size_t)Variables<sub><i>0</i></sub>..., (size_t)Variables<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
CognateRepack ::   template<auto...> class...
                -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRepack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

using SupposedResult = Sequence<0, 1, 2, 3>;

using Result = CognateRepack<Sequence>
::Mold<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Pagelivore::CognateRepack` is implemented similarly to `Sequnivore::TypicalPaste`. Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<template<auto...> class Operation>
struct CognateRepack
{

    template<typename...>
    struct Detail {};

// Base Case:

    template<template<auto...> class Sequence, auto...Variables>
    struct Detail<Sequence<Variables...>>
    {
        using type = Operation<Variables...>;
    };

    template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
    struct Detail<Sequence<Type, Variables...>>
    {
        using type = Operation<Variables...>;
    };

// Recursive Case:

    template
    <
        template<auto...> class SequenceA,
        template<auto...> class SequenceB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
    {
        using type = Detail
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::type;
    };

    template
    <
        template<typename, auto...> class SequenceA,
        template<typename, auto...> class SequenceB,
        typename TA,
        typename TB,
        auto...VariableAs, 
        auto...VariableBs,
        typename...Others
    >
    struct Detail<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
    {
        using type = Detail
        <
            std::integer_sequence<std::make_signed_t<std::size_t>, VariableAs..., VariableBs...>,
            Others...
        >::type;
    };

    template<typename...PackedSequences>
    using Mold = Detail<PackedSequences...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM6SuADJ4DJgAcj4ARpjEIAAcpAAOqAqETgwe3r7%2ByanpAiFhkSwxcYl2mA4ZQgRMxARZPn4BldUCtfUERRHRsQm2dQ1NOa1D3aG9pf3xAJS2qF7EyOwc5gDMocjeWADUJutuXo60hACeB9gmGgCC1zcEmCxJBo8HbkzHqAB0v5f3CgIxC8Dl2QgQxwI9AOVlu90ez1emHeCJeTDeh0%2BRF%2B30uu22TAUCl2AHkkrF0Rl/rdAcDQR5gMxHgAlTBJJjIADW9xMAHZYTddkLdqikSizuTmGwcdTBcLaSCCLsACKYOp0fb8vnKmE824Aen1uwshMwuw%2BShAerlQtF6ORhztGI%2BXxl62w%2BIMRLBmAAjl5GCtSLssT9fgA1ep4JhRegKWXC3YK0Gq9W0d5CP0Bhgrd6R4jR2OYBRuq7u%2B6JvkCxOJrxpIwiiVmg7K0nk4iUgR5qMxuOl3W3Su8nXrAUV4VOh1uSfiyWsTDB0Olz2E4mZ/2BheNudsXYAFSbi9dEZ7Rfj5cH8qBipVaqYdAzWc37wP5OD%2BcLfb%2B5YvNs11ZrIU61CYBt2bdZWzJClHC7Q4P17Yt%2B1HcchW1Ac7gNI1WWQJY0gANzNC12GtRMZ0vVDDhQmsZ0xY9cXdFdvXXbMVhuUgqNIp40WdJdvw9AkmKfHNMBsDjhV4754KLG4FGDMShQkqT6AsWT5LAqVMBxEkCAQWJ43I/Zf0TZMlVTe900OZjNzuODT3oGTS2DKzhKsWyCwQlTHNJHS9P7AyqzU4CGwIJtDNbMyHwMytKKiwCwQhAgoSnJTMAc353zskSSz49jYsA7TdOIbLcTywzsBAEAQvJdChxHMcDLIv93jUmjpybDSj2xPjGLXITWNyv9OMRe1Z0YedOrDej%2BK9XqNxcga4vU%2Bd9zYlr2uWvdRNKxTMpkuTtrolKVIWuKqrG6VfgKvSqITK86VMu8H0svrUpfNjdhStKpqcl7XLcTaMvcotPJy7zCuK27UK1UqgtAs6wtvNM1Oa0rjIIdAKtCR5gFiAB9JQ5tzQ5AQxkAWCYTlMHxvBGUwdBcYId4SYqtIAC8qcZ91Ac/VLiu5jyIa5tTEyuoqZVKy4KrOmrhTQ5C4QarixUddaLu%2BZQOUp9BnJWc8rgM2HdgAWU8dAEYiiy3A1rk6Z1xC%2BKlpt0Ll%2Bqbn1AAqT2ve9/V7g9z292wIQ9y932DW9iP3bDjCHiVkbifRirycp6nafpzm3GZkA2Y5y4cRuYhgD1%2B5iCzPBS%2BJCAc9QKgcQgAui9mMKW12SRZgBa9QTt53bkNoQvCSFIlHQVkFC8WglRb7vDg0YMuGDAJdnWf55Zjw3R/HyeIPNVBGXtVl2S5R9CYdfWbgqk3aHQFG/yzrHMBx4h8Ze94seDDRLn22/E5AUIsFUZ%2BJ93jz12GYT%2BVE74MH/oAliU5l6/hXq7QElJkC41XLEAgVcf4KHnGg88bgN4TycgPIedNCGc2wO3UcHB5i0E4AAVl4H4DgWhSCoE4G4aw1gkyLGWM2Mw6weCkAIJoGh8xOQgHofQ746x6FcDMPEDQ6wABsvJlEAE56HrEkPQ/QnBJC8BYBIDQs9mGsPYRwXgCgQCzxESwmhpA4CwBgIgEAiwCBJGOOQSgaBnh0FiOEecnBVDxGUQAWmUZIXYwBkDIF2FIb4ZheB00ICQPAGN578EECIMQ7ApAyEEIoFQ6h7GkF0PPAA7h2JInAeC0IYUw0RbDOAkmOJ4pUNddghPCZE6JsT4mSESbsCAHg/H0GIPsARXBZi8DsVoeYEAkC%2BKSP4sgFAIDLNWSAYAUgAg0AnnpSgUQmlRFCPUM4tTeCnOYMQM4JIojaCqHYoRvi2CCBJAwWgFzSlYCiF4YAHxaC0GsdwXgWByZGHED88uTy8AERBawzAqgqjHFWEI%2B%2BdDSmnCiB2W5HgsBNKBHgIxoLSAEWIFEVImBVQQuAKcIwoj5hUAMEXcMeBMAVKgswoRWThCiHEPk3lRS1BNPKfoQwxguGWH0HgKI1jIDzFQEkGCDAQVhJJi2UwlhrBmHMeSgsWB5UQHmG0FVLgoEjD8PPYIkwShlD0EPAomRPDNAdfkFVPQ7X9Hnqamo4xLV6F9R0cYnq%2BhxB9f6l1OQI1dFDdMcNJreErAkPUjgjDSBmN4BYrpoSIlRJiXEhJZhhm4FSRMjY0zZmMvmLpJgWA4jGtIBIyQ6xvjqPWLySQGhJBmEkMokx9CNF6I4AY0gRjBHfGUVwZR8R1HxGnfQyQXB6HtuURmppFirE2OEYyxxLjFluLaV49ZmzxmBLYJweoLA8K8jCUwFcDYuDqO%2BFwb4iL8BEANXoXlOSBXSCFUoEVpTdABCqUwGpoLU3pszc0jgrSPHHF2J0q9N670PtAk%2Bl9b7hmjJWeMyZ6wzAzJ3fYhZSzUBjNiN4jZFG8P9BQ7egkRgn1cFnvsx4RUjknLObcy5pBrnnPuY8hwfHXmMAIB8r5TTfn/MBcCvj4KJVQtYfgUu1R4VNKRSix4fGMVNOxbis4%2BLVisKJSSoR5LKVKBpUpkCu7mVMFZeyzlko%2BM/v5Xk/9shhUlNYSB8VDKtVWGldio1irlUZDVRqiCQWdV6tiAa4s8ATWYHsGaiArgA3WqgXG%2B189HUqqy3kNIHrbVhsDal2FwauhFaDQwToDRcvesGDVqNVqWuNbK/GlNCwljJumcO6DG7OAhmINe2996mMYefa%2BjQJaP0kAI5Wkj8ya2YDrf0RtmLR3jufd23kK7eS8m0b2yJ88YObtsNuuZDinGuPce06jp6AlBI4Fe3pLAFB4TiXhTDSJATJIW1%2BzJshf2eYKfIQDvmdAgHWKQMDEG6mDcaaUix8H2lIaoKNlgH2vs/b%2B/aQEOHaOrII%2BsYjN2yMoBJ%2BMp7NP%2BjfcHrjX76jcb/YIGgsbkS%2BB0A49YiAxzSkCd46S4XdyHlPNExRt5EnPnfJU5gP5AKxDydJYpyFJmwUwvU0l0pWmcI6dJXprFsrDPGcJQWczvBLNUps5CuzpG%2BAsoUGyjlXK3Og48xILzhSoeithwFyV2qQuyrC2wiLAgQX6mZrFywuqs36vSUlhVthKvtD8Bli1bW9A2uKOV/L7qMhFYKxkJr4bU9pb9a17I7W6sNYmHn7rMbhjZ%2Bbw3qYeXE19byVBlH5iRvvaiZ977uwWffHZ/NstS2KfVtILW%2BtlBU07f8M%2B9Ysj6HdtY0ojtM712o84Fu2xs/m2DMifEXkT7lGEfWN25RUjh3rD71mg/K2xHDqSXv/vljX%2BzHmOStIzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_repack.test.hpp)
