<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-bind-front">To Index</a></p>

## Description

`Raillivore::BindFront` accepts an operation.
Its first layer accepts a list of sequences and returns a function.
When invoked, the function adds the sequences to the beginning of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Seqs...
-> Args...
-> Oper&lt;Seqs..., Args...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindFront
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will bind `Seq_0, Seq_1` to the front of `Operation`.

```C++
/**** Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindFront<Operation>
::Rail<Seq_0, Seq_1>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<template<auto...> class...> class Operation>
struct BindFront
{
    template<template<auto...> class...Beginnings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Beginnings..., Sequences...>;
    };

    template<template<auto...> class...Beginnings>
    using Rail = ProtoRail<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCmF4iAA6dFg7AXZAGBQKdGozHY3EKC4AeSS0SeGUxf2GxC8DguFmC6AAYsRZH8TPErKcLgKLpCESDwcLgTDwci0RjQVicUw8QSLJhgMEGMFgApafzBfTGQQLspOUQAEpMOh/QUXHl8k7W63ixFi%2BESpEo1AEokKpXooSYACOXkYq21cqtDoFXjSRgu5roNtBABFyZTiNSBLCVWqGBqjPj0aQLv6gyHMAXCeHQXbrTyk2C7RGBU7RXCoa3pZ7ZfKScrVerNWHsE2LtHNXGLbREynjagzZOs/3c4OvVXG/F69Xue8vp8fh9NhdsKpWHdMC9Dn8D7vL6duWZQcEcV4sIm3GgGKskgQh9uzrsLhOYhgB8RgfwvbYfhbSU3E7Vdh1OfUmRLAB9DQGz/aD3RlSsEJOJDDVQrgMLvU4sKlD14LpAgGWQwMULMEjfjI11nVgyju2o2jCPo0EmKvACKSpZ5Xj%2Bci2xFGC4O7YlFQrHV8Jog1U2Emkt1I/9LiELwkjyTB0FNcsvFoQ1RNOMdY203TUn0wyFGMw0wRTIT0xqWFUI0IsiK8%2BizB8gMUL4tc/wPC4AFlMHqKgvE/ETb3%2BVjW3E6TcNk31USArUFIs4BwsiphotijJp2ZVkOS5cEXIzBgFJAEB41odz6M84t6OI8NTjqhrYUy%2BTgo00K7IciDNh%2BHK4yMkySoiqKYocNS3FQvzWoCoLh3U5jNO2C4ABVy1M%2BLJkcZAULk6ICAgYZ0DqhRWEwU6wzcIaTK8nS9IMyaCExOZ%2BNODgFloThYl4PwOC0UhUE4NxrGsC4FCWFZz3MUEeFIAhNH%2BhYAGs4kkVENAADjMMwAE4Sa4WJCYJrh4niaRAY4SReBYCQNE80HwchjheAUEBPPRsH/tIOBYBgRAQCWAgkhRchKDQW46GiUI7s4VQCYANgAWnVyQLmAZBkAuKRUTMXh9MIEg8Gutp%2BEEEQxHYKQZEERQVHUQXSF0NoAHd0ySTgeABoGQYxiHODJFFpcNVAqAuNWtZ1vWDaNvGzAuCAPAV%2BhiBtB8uDmXgBa0BYICQeWkkVsgKAgcvK5AYApD8mgTOiXmIAiUOImCBoAE8A94LvmGIHuyQibRMAcfvSHlh4CDJBhaD7j2sAiLxgFg2haF57heCwFhDGAcRl7wYgJ8cAA3ctQ8wVQJ5RNZUeCAEGfB2g8AidNh48LBQ5ovAWZ3qQS%2BxAIg2STICA%2Bb8jAYwWFQAwWoABqeBMDeyEqDVGtthCiHEE7TBrs1Chy9voA%2BKAYaWH0O/XmkAFioG/BkbemsrpOVMJYawZhObAOIFbK%2B1D2hnwyC4Bg7hPAtH8EI6Y/QYhtDyOkAQYxWjJFSLIhgEjSgDAmFUfhAguijBEeMPh81tEjB6MEPoaipG2GMfIvQkxGiqNmPnRYyxVgSCDhwYGpAOa8C5nHDW2tdb60NsbNOEBcAWxzsjfOhcYELAQJgJgWAYgQGxiASQoJUQk1BHTDQkgzCSHVmzWI6sSb6E4EzUgLMUaonVlwdWBMSbU3VrESQFNMnq08aHLmPM%2BZoxgcLMWpcJaRxltXWu2dlZsE4A0Fg594iayYLJWMXASaoi4PjM2%2BAiBcOts7LBDsJDSDwUoAhHtdB%2BV9kwf2O83EeK8WHDgEcpYoguDHXxCddYKiWSstZGh06ZwrtnXOoIzAF16YLEuZdUBZ2iLLGuUKAUDE%2BQ3cmnlm4AmIG3DuHtB69ynji4eo9x6T0ATPMC89F6hxXmvDeW8p570gWscG%2BBT7zUvtvcGN874Aink/Kooc34f17t/RlhcuEANRsA0BShwH7yMFA0A4K%2BDwIUEglBaCp6YPtjgw5sh8Hu3Bmc4h0CWFWHIQKqhySIZ0IEAwphyYTVsI4dEbZPDLV2C0X4CArhrFtECKYmY6jFH5AyD6oNyj7GBvdYY2oVi9EKKjTUHRJjiiSJsbG7I8bjERqkQseGzjHY3JDh7Hx8d/GLNyss1Z%2BN05hK2UCqJYLi6xPiYkygbjymVJWTk%2BIsQSa01BLk/JLSOnFs4N0/mfSRbi0llHWFYylYqw4NMxOLAFDn0NufStEphgbPCVbPQmrsGOx1S7Y5%2BqdAgFBKQC5VzA6lPcUWzm4dhnR1jqoFda6N1buhMMP58LK5AtBKCouQtBnzqrnLf92cQDrt0ihTdJMULboIChd9hy6DosxZ3buw88U4ZHmPM%2BU9SWCHJUvJlmBV7rzELSwB9K5UitIMy/hbLr632QPfHlgg%2BUewFZ/Huwrf5iqnpKsBEC5Waj6XApgiDkGoMpOg3gh79m4N1Wewhl6jXGDITYc18AaHWoYNvdYV1SGsMsOw7xnDuEWtzZo6NgjhEZrEegbNuQlE1FDTImobmNEdCMd0UNCbOhZv9amiY6bRERamGF8xrinGI3iwzW5nTOBxw/eui4CHUTIZrZskg9bgMxNIHEhJAxLUMw7SAUmqJQSgliJTFpbM6vxDqSOp93NbA9JA3MFJkhYgZJpvENmBNJDky4ETMw7SGagkfd4sdjbMb3tNu1%2BbnWesLGAWkZwkggA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/bind_front/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/bind_front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/bind_front.test.hpp)
