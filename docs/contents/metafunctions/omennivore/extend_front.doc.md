<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendFront`

## Description

`Omennivore::ExtendFront` accepts a packed vessel and returns a function. When invoked, the function appends its arguments to the front of the packed vessel.

<pre><code>   Vessel&lt;Items...&gt;
-> Args...
-> Vessel&lt;Args..., Items...&gt;</code></pre>

The returned function also handles `std::integer_sequence`.
The arguments are cast to match the value type of the packed `std::integer_sequence`.

<pre><code>   std::integer_sequence&lt;Type, Integers...&gt;
-> Args...
-> std::integer_sequence&lt;Type, Args..., Integers...&gt;</code></pre>

## Type Signature

```Haskell
--Extend a packed `Mold`
ExtendFront
 :: typename...
 -> template<typename...>

--Extend a packed `Page`
ExtendFront
 :: typename...
 -> template<auto...>

--Extend a packed `Road`
ExtendFront
 :: typename...
 -> template<template<typename...> class...>

--Extend a packed `Rail`
ExtendFront
 :: typename...
 -> template<template<auto...> class...>

--Extend a packed `Flow`
ExtendFront
 :: typename...
 -> template<template<template<typename...> class...> class...>

--Extend a packed `Sail`
ExtendFront
 :: typename...
 -> template<template<template<auto...> class...> class...>

--Extend a packed `Snow`
ExtendFront
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

--Extend a packed `Hail`
ExtendFront
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

--Extend a packed `Cool`
ExtendFront
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

--Extend a packed `Calm`
ExtendFront
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

--Extend a packed `Grit`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

--Extend a packed `Will`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

--Extend a packed `Glow`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

--Extend a packed `Dawn`
ExtendFront
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct ExtendFront
{
    template<typename...>
    alias Mold = RESULT:
};

template<typename>
struct ExtendFront
{
    template<auto...>
    alias Page = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<typename...> class...>
    alias Road = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<auto...> class...>
    alias Rail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT:
};

template<typename>
struct ExtendFront
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT:
};
```

## Example

We will append `void, void*` to the front of `Capsule<int, int*>`.

```C++
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = ExtendFront<Capsule<int, int*>>
::Mold<Args...>;

using SupposedResult = Capsule<void, void*, int, int*>;

using Result = Metafunction<void, void*>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement the case where we append elements to a packed container.

```C++
template<typename>
struct ExtendFront {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendFront<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., PreexistingElements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQBQQAOqAqETgwe3r6JpClpjgJhEdEscQmBtpj2hQxCBEzEBFk%2BfpV2mA4Z9Y0ExVGx8bkKDU0tOe2jfeEDZUOBAJS2qF7EyOwcBJgsSQZbJv5uBACeSYysmAfYJhoAgiPEXg4A1NiqWwzoAGLEss8mAHYrACACIHKx3G63LY7PaXSGHKHPZHPGG7Jj7Q4nM7MNgAOgJV2eyAMCgUzw8giYMzISJR2PO%2BIJymImEwqjwI3CwGw9DYggUUKuUIeTwIr3erh%2BsgObkpDRpspZbI5XKMvO2jAICgJeOF/mukKBdORaLhsoZuMwusimAA7hr%2BdrhXcUc8vGkjM8ALKedD/fwgimyakRYiy20OvlanUE0jPZXszmOdXRgW6/UQ26AsH%2BLNQgD0ACoS6Wy%2BWC4Wy88ACqYEbksuVu7F8tt0vN7OQsz%2BcIkrxYANuNAMdZJZ0GoV3M0Yy5Y06M62Eyd3UUvNxMJIKLz0cFT6HbdGYo4Lq2627EYCCle3D3cn2YBpULyj2oBoNvD7fX6CWUbrc7nObjhAQ8YgUW%2BqGrcIAgL6tDoLKF5Xhmk55vud5ekIXhJPkmDoAASvWO7igcQb/tuu6HAAbqgeDoPGNF0UWYGCCxBAQah%2BZ3BhwDPIRFEkYGD5Pi%2BXQCLKjH0c8kkcdcaGQquDSOMgAD6TBkvEBAQCM6AwQoFxqdebj8cR8ZYThqR4SZtAEFcCzghwSy0JwACsvB%2BBwWikKgnBuNY1jPAoKxrJg/w9jwpAEJojlLAA1iALlmHiAJmJIAAcaUuRoACciUaAAbGl/j6Jwki8CwEgaEEHleT5HC8AoIBBFFnmOaQcCwDAiAgCsBBJF4oEUBAaA7HQ8SRBcnCqGl%2BUALT5ZIzzAMgyDPFIeJmLweGECQdF6PwggiGI7BSDIgiKCo6itaQuhcKQdrEJunA8E5rnudF3mcAA8gN/XiqgVDPNNc0LUtK1rZIG3PBAHijfQxBhf4XALLwLVaEsEBICNSRjWQQ3Y7jIDAFIZh8HQWzEI1EAxB9MThI0xzPbwdPMMQxxfTE2idC1EUjU6X0MLQjPXVgMReMAG60LQjXcLwWAsIYwDiCLeCsl0VH1h97KdANGwRSB1QfbQeAxI9bMeFgH0EMQeAVbLpAa8QMSWSC2yK8bRjRUsVAGFeABqeD2l9OJM2dwiiOIp0HfIShqB9t36IrKD%2BZY%2Bgm41kBLKg44ZDLs06aRpiWNYZi1Y7NtYBnEBLB0Yl%2BBArjjH4d2hDMpTlHo%2BTpAITed6k3cMP07dDHdte1D0YyeK0ehj90UxD4MCSj1MvfL70C9zEvNfBesEivRwbmkDVvB1UDM3zYty2retZjQ7gO0I%2BYSMo5FXtLAgmBMFgCTV6Q8WSP4PE2V/AAkkBoSQqV8pVRcvlbKJUOBlVIBVJGeJ8pcEKtlNK6CXKSC4C5YB%2BUj4fTqg1Jqr9WoYy6pjHqv0BrkEoATeGE02CcEaCwKiAJZpMGJAYL0XBsp4i4HiLy20iAV32rII6kdpDRwunHa6uhSYPSerLfeh9j6fQ4D9PqA1ngA2eGwjhXCeGKzWgIoRGhoawxxvDRGZgX5ozatQxh8R6HDVQHDIYhjOEkkVvwrgQQaA2XiFTGm10WYM1DhEtmHMuYOFDnzLUAshYfVFuLSW0tQ7y3dhsLy%2BA1aOA1jLERqgdZbFDgbZy11jamwZhbXJqMbZ2wio7Z2ShXYKyMB7UAFC%2BC%2BwUAHIOId7bRykSdGRsg5FXS8ooxOnsi5WFTjUquWcc4CDzgXQMCyS5l3iBXTWmcqg1AyC4T4q9gifA3h3O6XdajnNuRkK5I8jncznr0c5s8BAT2mCUReM8V5TxyGvJoTyt7LFWLvZG8D1HEM4AY4g7DOHcN8Xw8xwi774DEYjZGqM36kA/l/IYv8qmIOQQI8BAJ8EAgBP4CBkgFp3Q0SQ2wZDHGUPgNQ3qf03EuOIMwjYbDQYsAUFRVaVF%2BF4jhCMLamLdq6TuqMiO4yw5TPjgEe6j0khMzUe9a6dVtF/T0YDQVi1hWiukhKqV4oYYeJsfERG/gHFe3aljW1uMeVuvhiAUVOEVLiuyipK1akEULTJsEymlAwleWicLCKMbYncwSR4/mgthZ5MwGLCWYhMn22yV0hppB8mvKKVrUpyBdYVMEIbapJszbHHqVbJpodWkuzdl07kzqfZMH9oHO0wdGCh0VcdCQEzzqx2mTodVvDjApxsMs%2BAqzagywLDpZOxdLClxPuXOiBzf6fPro3QFzcLnoFBX3AoGR7n91qGe0e1RXlfIBdkY9%2B7vm3tsE%2B6ewKfmzGudvCFJ0dVEL1XCk1zwzVistbOEYGKH7YqdRQ9%2Bn9v6UH3qSkAZgBH%2BH8C5LKuCqrYYBIVYDtVOCkOani/%2BAINqUq4FIbKFLgFcABPA/wurSP1XIejfem0SMnzI1xmKDsQknMkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/extend_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/extend_front.test.hpp)
