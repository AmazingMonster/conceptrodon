<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IsSpecializationOf`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-is-specialization-of">To Index</a></p>

## Description

`Pagelivore::IsSpecializationOf` accepts a sequence and returns a function.
When invoked by a type, the function returns true if the type is created by an instantiation of the sequence and returns false if otherwise.

<pre><code>   Sequence
-> Entity
-> Entity == Sequence&lt;Vs...&gt; ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSpecializationOf
 :: template<auto...> class...
 -> typename...
 -> auto 
```

## Structure

```C++
template<template<auto...> class>
struct IsSpecializationOf
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check if `PackedVessel` is a specialization of `Seq_0` or `Seq_1`.

```C++
/**** Shuttles ****/
template<auto...>
struct Shuttle_0;

template<auto...>
struct Shuttle_1;

/**** PackedVessel ****/
using PackedVessel = Shuttle_0<0, 1, 2, 2>;

/*** Aliases ****/
template<auto...Args>
using Seq_0 = Shuttle_0<Args...>;

template<auto...Args>
using Seq_1 = Shuttle_1<Args...>;

/**** Tests ****/
static_assert(IsSpecializationOf<Seq_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Seq_1>::Mold<PackedVessel>::value);
```

## Implementation

We will use partial template specialization to dissect a type.

Suppose the compiler discovers that the type is a packed vessel and deduces the vessel as the given sequence. In that case, the compiler will select the partial specialization instead of the primary template.

```C++
template<template<auto...> class Sequence>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Sequence<Variables...>`.
    template<auto...Variables>
    struct ProtoMold<Sequence<Variables...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOxcpK4AMngMmAByPgBGmMQgkgAcpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4QWC3pgoW4mF4iAA6dFQ7A3ZAGBQKG5CTAARy8jE2mKB42IXgc9wUQlSmGQeDEeAAXm9sgB5KhAkz%2BKyXG7Cm6wp7wxEEACejOYbBuABUZQjIdggSKblSaQQbspiKgiABZTzodUi/kWTXNRzIbECcaYVSpYg3GKoTw3ABuYlJNyhABEblQxEooZb%2Bf6w3yhSLtttFQg8PjUv0WbRNYzmayOe8AO50dNxbEIDKMM3CuM3PBUP0ANg0SsZJnrVfxWHQNMw6BuTHxzY0hJJZJVbgAai0WTF6Ap0aiKfW5zHhWLwSPkWj0ePiJPpxSl1bqbS9QbUMbaKboYPSQxydCtzvMDOMaq9xcNRarZzbWgGA6nS63Q9b1vEwP1IUDAhqRVcN/EjSFBUBfcVwlaFpVlVhMFnC5gGITBQUYAgFFfDUvEyIwbjPbsA11fUjRNRFsNw/DBCfOcX3g6M3xFZCIVQ5U5Uw9ELmIYAiJffdZhtO1fxBf9XXddNKIAfU9MDA2POjzwYkTWMxEAQGA0ko0uCNjMQq4/l%2BAEfl2G5sFUVgnlAz4gRsyzTk4myCQQFECGnD4PMuHi1xRVBZ1fLVaSEHyCD8zAlI0MygWCxF1zC581UuSKdWi3z6CUrgku%2BQ5dSYZAAGsu1HR87AC/YAVI8JgFKiqqpquo1O8vL4sS6ENFIG4ghuMwBrMCkOJM4r9huC5aBZJR8RcoLQXFXikVCrCdNfRryMHBLOty2L8t6txhNE8L2IQ5KVtXVKNqErbxIuHbmr2rgDpiuKCu086MqKizbgVR9CLq3YAUkvBkCU3slFaCA7npTM03ZTkBB5RE9t67B9MoxFlDKyr0GqvE6j0gyfUwJYzIhqGYfiAgIDAMA6QZJlkZzbleUvYlvtVHH6OhfHWqJ9raDJwzKbDDgVloTgAFZeD8DgtFIVBODcaxrE1NYNlA8xIR4UgCE0aWVnKkA5ckVENCSMwzAATntrg5ZtpIuH8fxpFljhJF4FgJA0fqlZVtWOF4BQQH643lel0g4FgGBEBANYCFSFFyEoNBHjoeJIgwzhVCSWsAFpa0kG5gGQW0pFRMxeC7QgSDwdA9H4QQRDEdgpBkQRFBUdQY9IXQglzYgmFSTgeBl%2BXFZN1XOC5FE051VAa0Lkuy4rqvBqtswbggDxs/oF19a4JZeGjrQVggJAs9SHOyAoCA74fkBgCkEaaFoEFiAjiAYjnjEcILQpST14EA5gxApRchiNoJk0dDZZxeAQLkDBaCgMHlgGIXhgBIloLQCO3BeBYBYIYYA4hMF4Fwg4PAnpHxz0dEyFEWxDbhBBN7FWc0YhjygR4LAc9IJ4H9kQ0gdDiBuiUP6UEZC5pGBNisKgBhRKjjwJgXMXJZRgJ7sIUQ4hu5t3kEoNQc9h76DISgTWlh9B4BiBHSAKxUCpAaIQ4u4wLz%2BlMJYawZgQ5iO3FgOxEAVh2HgdkFwDB3CeA6HoUI4QhiVBGIUDIWQBBTD8Ek4o2R5jDASEEEJNCBB9EmFE/IeS6ihMKRMAYcSFiJNsFUtJehZitGyQk3JwSdabAkNPDgCtSDB14KHG469S7l0rtXXe%2B9cCNxPmYA258jbyJWAgTATAsAJCCaQc2khISontpCT2GhJBmEkPWDQctaz230JwX2pB/YG1RLWLgtYkj2zdrWS2zt9m1n6XPUO4dI6LJjtfRON9k5L3Tk/F%2Bx885sE4C0Fgnp/DFyYNiAw5EuD21RFwa29d8BEH8a3WQHc9HSAMX3Yxg9dAjVHuPMBPS%2BkDPnhwReqcUQ3FXsMouoy0VkMGlinFGh96H3vsfP0cyzALMvrHMF0L4gZ2fqgI%2BIwcRkMxVwfqX8f5/wAYPCBICtH6qgTAuBDgtFIIIqg9Bc8sE4LwQQrRJCZFbBVvgahjg6GEJVow5AzCtFsLqHPLhPCpR8JdRfbcwjDZiIkZgKRpCjCyNAMCvgSiFAqLURoxgWiDEkq7mS2QFKB4q2pWYuRnirBWK4YEhxTjsguLcQGCt3jfHxH8fQ%2Bx3QKl%2BAgK4RpQRYnlByXoIoKScglPSWkZJDRWmLDKT0Sp/R%2B1doKY0Kps66nNLaBOpp66anDrPqsdYXTD3e0ZX8zgXKN7l1VRigV1spn4pIOK%2BZF8lmkBWWskYmzva3PuVio5/g5b2w9pCY5pzJBBCZf82wgLpUgvgGClOy8FVyuILCrYCLN4sAUJ6W0npMWolXOMPFMzm5Evbro/N2ii0mJAJCUgtKJ5EIZbPQeodWXLw5WvbDuH8OEeIzqA%2BSrRXxBfZCKV8i463xEw/VDsnj4GWQKkVIKlMVKUE0pVQZc%2BB0G1ZQXVKsjUYMNsZk18DzVKuQVajBrrMDYNwWIB1IinWJvDaQN1oTPUMNUEwkE/rBCBsHsGkBYaBGRq0TG0s8aZFNSk4opgyjVHqM0SI3NVGJAFt7kY4tOh6NluMJYmw1b4C1ucZwbYbiLFeMsD4wZfjm4ds2fkho4TIl5EnYO%2BJc6p2ZNSTujJY6N25JXQ0Ip26OtNPKau8bw3d1LoG/UuY%2B62ndKPbrNbZ62Mh0vdp8uOG8NegE/CcYj6ZkvrPm%2B4FyzVnrMoD0v9IAHaokhJCOWLtIOB1e/4F5vz2OcABVHd92y5Z7Pdv4QOSRJBOy4LbMwPzvaQm24MgHQKr49Lrn9nbYc0em1EfETIzhJBAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/is_specialization_of/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/is_specialization_of.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/is_specialization_of.test.hpp)
