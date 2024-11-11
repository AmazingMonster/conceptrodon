<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldLeftFirst`

## Description

`Varybivore::FoldLeftFirst` accepts a list of variables and produces a function.
When invoked by an operation, the function left-folds the list with the first variable as the initiator.
<pre><code>   V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>..., V<sub>n</sub>
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       V<sub>0</sub>, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
FoldLeftFirst ::   auto...
                -> template<template<auto...> class...>
                -> auto
```

## Structure

```C++
template<auto...>
struct FoldLeftFirst
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<template<auto...> class>
    static constexpr auto Rail_v 
    {RESULT};
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<template<auto...> class...Args>
using Metafunction 
= FoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

static_assert(Metafunction<Subtract>::value == -9);
```

## Implementation

We will implement `FoldLeftFirst` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct FoldLeftFirst<Initiator, Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct FoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct FoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            FoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxmpK4AMngMmAByPgBGmMQgABwapAAOqAqETgwe3r566ZmOAmER0SxxCQBsAJy2mPbFDEIETMQEuT5%2BgfWN2S1tBKVRsfFJKQqt7Z35XLZTQ%2BEjFWO1AJS2qF7EyOwcBJgsqQYHJgDMbkxeRAB0dwBqbXhMMfQK59gmGgCCk8ReDgA1AAxTzoEKYKgEYF4YiTQEmADsVkRABFzlYfl9vgB6HGAixMJSAy5KEDY7EHI4nTDnS7XVCAgCSDCyTCIZEBVyIgMexGer1pZ0%2BPz%2BAIIILBEKhMLhBDpLLZHNIvKeL3oHwpyOxgN1gKpx3ZQrcBppdO5qDuNw%2BgOQBgUCkBAHlUvF2dlNT89YCxUDlMRUEQAEpMOg6vVIzHfb3eybu5C2gSTTCqVLELkMwEANzEXkwCK9Md1kedruI7oECtZjnZJBVfIFGuFIBAOe8%2BaR6LOUe9nYxFMLutNRrpw9OFwtVptdqJCit32AxEwh0YBHewvDuq8mSMgJDdARZ1RgP9gdQ%2B9odIXS5Xgjnd013a1XajlMOhvH9J5ipryozPNlSYVQtQEhEwNAGHQT1fgIf4gVBWhwUhaFYUmKslTrEFUIIFUwIgqCNyxbVB31d8zQuMdjUnB9hVte1HRdN0mmg2NYPFE8A2DUNLxIyNNxjONHATCDk1TdMQLbPMEWI6MixjRjy2Yi5%2BLk0smI9ZSSNU70f2eP9APlLS5I%2BFtJMwXDwIEKCjKLEzW1zWkbOkl9%2BL7J8sRIyjRzIkcJwZKdaJnB150XZc2DvFi9W3cJgD3bjD2PU8uLDC5rzC1d72tDd3O%2BNzXx%2BPE93A7ZMizfNSXYAdvi8vzv2rPTMJAgzgMzPCrJa247idAgEHidcRRguCJQQpCZWw9Df0w5rQMsyCVW63q4QCga%2BM8nzPxqr9LRo7A6NnNTFI0gbWKGjizwvVyZNUwS8GEpMDjE/9GTM6Se203URulFC5TpFT3oOisGF%2BpzVIUwHgdk/65N02tOQMv73rssyLPwhHtKRhz5p6vqpxBiNmxASi4pStwwaU47/tMhy0byy6XI8yHSOpXyTXWqj/J2vbgruNLbzXSKtx3WKLwSs7ksvVLQr5zLH1fNF%2BwZnEACoVdVtWcWxZWVYAFWwIRtdVjWCrVk2laN3KsTMM5wjtLwsEPNwIN2VJ%2BcIi3qrZ81M2%2BDrGSsN3fQlIQvBiWCmAcLU3t1G67oYUS0ye7Nqd45FAW%2BABaCxnIV3L5Zyt9mY2z3au2rLdqCzLvmIYB%2BuxaLdwAWUwVoqC8BgHGyAtcqPSVEK%2B%2BGLjmQEzhVaRh7si7UurmXsvymD4wAfVneICAgJuW7bjvKwuYPQ/LCOCZe84u2PdOajWDEOA2WhOH8Xg/A4LRSFQTg3GsawfS2HYOytnhSAITQV8NgAGsAiSBuBoSQXBERnA0P4DQZgqhVDMIkRI%2BhOCSF4CwCQGgUgPyfi/DgvAFAgBSAAx%2BV9SBwFgDARAIAtgEFSNccglA0BHDoPESIrA9iqESFUdOVRJCAmAMgBMUgbhmF4JgfAHI8DoD0PwQQIgxDsCkDIQQigVDqAoaQXQcwADu5ZUicB4NfW%2B99AHP04E6a4TCJSoCoICXh/DBHCNEYCcRZhAQQA8Ow%2Bg6ZzBnC4GsXg5CtAbAgEgNhqQOFkAoBAaJsSQDACkEEGgtADhwkoDESxMRwhtAAJ4mN4Hk5gxAClOhiNocC5C/5sPCgQJ0DBaBFJ0VgGIXhgCXFoLQEh3BeBYBYIYYA4g2mwhqXgMqfSn4pmKgcYp5BBANEsbQPAMRyzlI8FgSxsE8DYP6aQMqxAYgZEwKiQ4wzVlGEARsKgBga73DwJgfRjEH5/0UcIUQ4g1EfM0WoSxej9DDJQO/Sw%2Bg1kkMgBsVALtsh9PTpMAiqJTCWGsGYAhRz%2BRYEhRADYdgJnOAgK4GYfg5ihCWOUSoBQMhZAECS6lRRsjDEpWMOY%2BKt7NAWPStlDQCWcsGMy0YCQ2Vcs8F0PQcZ2iCpWMKvFX9dgSDMRwO%2BpB8G8EIU4vhAihEiLEeArxEBcCEBIAiX%2BIT/43I2L1JgWAEi4tIKAyQZwbg1DOIiSQkCzCSCqLg/wtR0EcEwaQbBQSbhVC4FURINREgRv8FA/wrqqiqssYQ4hpCLUUIibQyJ9DbHMPiYk/xXC2CcDaCwLMiJ05MD2ruLgNQbhcAgVImRJA5EKNkMo750hflKH%2BTo3QQRDFMGMf0pVKq1VWI4DYxh1xAQOK5MQctlbq0zlrfWxtGhvG%2BJif401ZwzDmrCZQnNhb4gsISagPxYwy0VvTqulJNQuApHSZkkhEAck6NKYUhZX7ymVOqQ4BZ9TVxNJaZY9pnTum9IWYMy5ewn74CXB3KZljZnIGuHsP%2B4QDg3x0as9ZhStnwdCfyfZf8jknKUOcoZRgrmgEzXwe5ChHnPNeQsj5nbVHdtkH87RT8B1AuuSiqwYL8M4uhbCpMnAEUECRcJtFGL4hYswOJ3ofKXCQW5cESC0qqVzEKLSnIYrZhpBpU0XTrK1McoGNMYzpKrNNBs4sMoQqJWiryPZyVznlh6bldsBVwSA3jpTZwBdS6q01tinWhtEDvFGo5Hu4JoTLWkGtbaygSqg0hvrZAxECbEQwMkF6wRcwJ2ptsOmo9Wb4A5oYXY89p7iDFr2GW1xLAFBZgTFmaLNJJjNuNVi9tSivlcfUfIXtfGdAgBHkOkdpigsWJ0YQ6ddi52ONa0I9rnXsw9aNPCHxl6d3xD3WcQ9NyqFRMO7EhrV3/GtmQKkVIC9us1AXr1ggS9F2CL4HQV92Tcn5PKT%2BwHFSqk1KA5ehpoHWkIcwB0rpYhoMHNg7R4jpBEMTJQzotDGGFnYeWXhtZGyClEZ2aRhZFHTnUcuTFc7dymAPKeS810bzeAcZGxIbjGiJsAum4J4woKbBifgBJpofScSIpBaiyw6L1WYrkSpkXDnsgafcHZvQ5KXMyoZYZrTBnzMUtczyvoAgnNafZY5hYFnhXzEGObq3hvteBYUPK1RY7FsENCxtwEW2uu7YOPt%2BLJrAlJYzeEq1mAbVjHtbhrLIAzD1rOGcfw8CoG4KT4iSNyalucDTWQlLjr/Auv8IkRBNRJA1BgW6rgI9cNnA9%2Bq3PYegEBskdnz3RDm9rA2EczIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/varybivore/fold_left_first.test.hpp)
