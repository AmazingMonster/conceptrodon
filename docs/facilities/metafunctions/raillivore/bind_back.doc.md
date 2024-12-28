<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-bind-back">To Index</a></p>

## Description

`Raillivore::BindBack` accepts an operation.
Its first layer accepts a list of sequences and returns a function.
When invoked, the function adds the sequences to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Seqs...
-> Args...
-> Oper&lt;Args..., Seqs...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct BindBack
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

We will bind `Seq_0, Seq_1` to the back of `Operation`.

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
using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = BindBack<Operation>
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
struct BindBack
{
    template<template<auto...> class...Endings>
    struct ProtoRail
    {
        template<template<auto...> class...Sequences>
        using Rail = Operation<Sequences..., Endings...>;
    };

    template<template<auto...> class...Endings>
    using Rail = ProtoRail<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJgAzG4AUCnpgwRDAXdobCmF4iAA6dFg7AXZAGBQKdGozHY3EKC4AeSS0SeGUxf2GxC8DguFmC6AsTGQAGs/iZ4lZThdBRdIQiQeCRcCYeDkWiMaCsTimHiCdgGPgjApaQKhfTGQQLspiKgiAAlJh0P5Ci68/knK1WiWI8XwyVIlGoAlExXK9FCTAARy8jFWmvllvtgq8aSMFzNdGtoIAIuTKcRqQJYX7A8HMPj0aQLqr1cA84Sw6DbVbeYmwbbw4LHWK4VCmzKPXKFSSVWrgiWtXahVHe7HzbQE8nDcbUHHaLCi73S7SKzz4jXl6c/h8vnsflvC6pWHdMC9Dpvt98eRuzKDgjivFgE240AxVkkCKHsJezrsLidiMAfEYd8T22H5GylNw209MNTl1JkswAfQ0Wsv3At1ZTLT9YIIBl4IDBCuBQjdTjQ6V3WgrCTjg/VELMIjfhIl0nUg8iOzpHC9QuRDQXos9LgpKlnleP5SObUUIKgjtiSVRcYKojimQEtMal494fyELwkjyTB0BNXMvFofVhNOIcYw0rTUh0vSFAM/UwWTJT0wYTN8LMAtuPc/CNE8/0CKXOs1MuABZTB6ioLwXyE09GJbCDRMkzDpJ9VE/z7OTTOAC4QrCiKHAycdmVZdkuVhRyVLkkAQBnFzfO8rj8MIiqqtHWFUtkz91wY79Lms2yQM2H4MtjfTDIK7KmHCyKaXBWifIQnjywC7rtguAAVXMjOi%2BTqWQBCZOiAgIGGdBKoUVhMD20M3F6wz3M07TdJGghMTmVSTg4BZaE4WJeD8DgtFIVBODcaxrAuBQlhWY9zFBHhSAITQPoWTk4kkVENAADjMMwAE4ca4WJMYxrh4niaQvo4SReBYCQNG8v6AaBjheAUEBvIR/6PtIOBYBgRAQCWAgkhRchKDQW46GiUJzs4VQMYANgAWnlyQLmAZBkAuKRUTMXgdMIEg8BOtp%2BEEEQxHYKQZEERQVHUTnSF0NoAHc0ySTgeE%2B77fsRwHODJFFhf1VAqAuOWlZVtWNa1tGzAuCAPAl%2BhiGta8uDmXgOa0BYICQcWkklsgKAgfPC5AYApDcmhDOiVmIAiX2ImCBoAE8Pd4JvmGIFuyQibRMAcdvSHFh4CDJBhaDbh2sAiLxgEg2haFZ7heCwFhDGAcRp7wYgB8cAA3XNfcwVQB5RNY4eCAEKYB2g8AiNNu48LBfZwvAaZX0hD%2BICJLMTQEN53yMIjBYVADAlgAGp4EwM7ASf04am2EKIcQVtEG2zUL7J2%2BgN4oFBpYfQ99WaQAWKgN8GRl6K2OvZUwlhrBmEZt/YgRsj7EPaHvDILg1RjFaKQQIwQ%2BilAGG0PI6QBDcNyKkURDBpj9BiBMKo7CBBdFGJ4Foeg7CKNqCMHo/CZhCNsNo8RExtEyMEXIhYENlirAkF7DgP1SAM14EzMOCtlaq3VprbWccIC4ANinGG6dM4gIWAgTATAsAxAgMjEAkhQSohxqCMmGhJBmEkPLOmsR5Y430JwKmpAaaw1RPLLg8sMY42JvLWIkgCYJPlg432TMWZs3hiA7mfNc4C0DiLYupdk7SzYJwBoLB97xEVkwaSMYuA41RFwdGet8BECYcba2SCLYSGkGgpQGCHa6Dcq7Jg7sV62PsY4v2HAA5CxRBcEOLiI6q0VJM6ZsyNDx0TgXZOqdQRmAzi0zmOc86oCTtEUWJdAXvIGA8iu%2BNvLVwBMQOuDcHad1bkPZF3de790Hp/EeQFx6T19jPOeC8l5DzXoAtYAN8C7zyofZeAMT5nwBEPK%2BVRfZ3wfq3Z%2BFLM5MI/nDb%2Bv8lD/3XkYIBoA/l8HAQoKBMC4FD0QebFBGzZDoPtgDXZ2DgE0KsPg9lRComAzIQIChVCkzaroQw6ISyWEGo0XlZwEBXBGN4WqUxsxhGSJqM6kRNQ3X6LtTUZRTRVHjDYfarRUxdGyPUYYkNPDJiND9eYxYVjLbHJ9g7Zx4c3ETMylMmZ6N46%2BMWZ8wJvzs4hLCREygti8kFOmck%2BIsQcak1BCktJ1T6mZs4E09mrSeb80FkHEFvSpYyw4EMyOLAFD701vvfNkphjzL8UbPQCrkGW2VTbLZaqdAgFBKQfZhzPY5LsRmxm/sunB1DqoKdM650LuhMMV5YLC6fNBD8rOXMOmjqLmLV9ycQCzq0ghedOMEKLoIAhW9Gy6BwoRY3Zu3dUVIZ7n3PeQ8cWCDxVPSlmBZ7zzECSz%2BZLRXctIFS9htLj6n2QOfZlghWUO3ZY/FuXLX68qHgKv%2BADRW9laWApgkDoGwMpPA3g661moJVTuzB%2B7NXGDwTYPV8ASFGoYMvdYx1cG0MsPQpxjDmH6osQo8NnD3Bxv8K6qNZiJH5AyN6z1GQk3qNM4G2N2R41uc6CYmz7qDHdGdQmnRxRo3pxTVDGxp6TkNM4GHO9s6LhgdRJBotCySCls/cE0goTwkDANRTOtIBcaolBKCWIhNql0zK/EUpXaL3M1sM0r9cxomSFiPEkm8Q6YY0kPjLgWMzB1IpqCc9Tie3lqRqe3W9XxuNZawsb%2BaRnCSCAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/bind_back.test.hpp)
