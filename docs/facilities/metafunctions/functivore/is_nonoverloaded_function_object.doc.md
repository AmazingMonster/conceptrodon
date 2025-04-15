<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsNonoverloadedFunctionObject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_nonoverloaded_function_object">To Index</a></p>

## Description

`Functivore::IsNonoverloadedFunctionObject` accepts a function-like type. It returns true if the type is a function object whose function call operator is not overloaded and returns false if otherwise.

## Type Signature

```Haskell
IsNonoverloadedFunctionObject
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
struct NonoverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
};

struct OverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
    int operator()(double const, double&...) const volatile && noexcept { return 0; }
};

static_assert(IsNonoverloadedFunctionObject<NonoverloadedFO>::value);
static_assert(not IsNonoverloadedFunctionObject<OverloadedFO>::value);
```

## Implementation

`IsNonoverloadedFunctionObject` is implemented by attempting to access the address of the object's call operator.

```C++
requires {&FO::operator()};
```

The validity of such an expression indicates that the call operator exists and the access is not ambiguous, meaning the call operator is not overloaded.

```C++
template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {false};
};

template<typename FO>
requires requires {&FO::operator();}
struct IsNonoverloadedFunctionObject<FO>
{
    static constexpr bool value {true};
};

template<typename FO>
constexpr bool IsNonoverloadedFunctionObject_v
{
    requires {&FO::operator();}
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSAMykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMcTcBAAnolGKxMCDsL8hsQvA4rgpQgJUAA3aK0VBMLDoABiXgYDnSAHkItpMA5fiYAOxWE7nFnnCaOZDnNAMIaYVSJYjnCKoTznTFiLyYc4MixUMRKBkAERBTJ%2B9OVcVVv3%2BgMesNBEKhzDY50J5Lhv2ImAAjl48FaFOcrbb7ZhHTLzAA2M0gECoKHER4kCCzFVKhEEJEoy5ojHY4i4/GYIkkskCSnU2mgs0Wk4e5ms9l4Tnc3n8wXC0Xi7xSmWRyXhzV09VhvMnHW3PUgsGQ6EmnNxeEnUv/ctCkW0VHohhYnF4gnE0nVDM0ggAfUxzdVrKdNrtDuljK9Pr9AaDxBDYZbeZbTbbp0%2BH2%2B7w252wqlYtylL1%2BL8fBzpN4dnOAAVN1/mIR0fxORFkQIc5p1nBN52THMb23Vlgng/1onPEMICwrkBCGUhznQRYInoL0ADpaNmIieXgzFPEeOhazMT0vXOGc%2BRWRJ4JlXcCCWBhzg0FVD2VG8NS1GD6xRcl40TBdzXQ34d0InDAyIC9ZgIwQGJIsiKKojjaOo%2BiRzFFjHHoaUOK4njVD4gTGSEkSxIk8MCxZTSzx0/DyK8SipRHUigpCmi6MMpibLY%2BzOI47jUF4zB%2BMPCx3OIUTxM1STmxkwCHwuMChiggC5NY5A1yYBQlAaCAY0QpSUJTJcKSpVdu2auckyJc1B19atJVDO9jiLaravqggIBneCmrjXqF1TZdOqzNxFKW1CBuwIaJUwUbVQ4eZaE4ABWXg/A4LRSFQTg3Gsaw2UWZZ2LiHhSAITRjvmABrEAzskaiNEkLh6TiDQzo0DjPTMAAOOH9E4SReBYCQNA0Ugrpuu6OF4BQQExr7ruO0g4FgGBED9LwCESGnyEoNAbjY4hQhhThVDhz0AFpPUkc5gGQTkpGosxeGTQgSDwdA9H4QQRDEdgpBkQRFBUdQSdIXRWgAd0DRJOB4E7zsu77bs4ckabp7CqHOTmeb5gWhfOEWzHOCAPGZ%2BhBXMd7Zl4YmtHmCAkCZxIWYZiAw5ZkBgCkMw%2BDoCCCYgCIzYiYJ6nBQ3eAz5hiHBFcHBz0gmfuAhyQYWhs81rAIi8YA3DEWgCe4XgsBYQxgHEWvXTJbFW5uvkaRp1YPqwyozdoPAIkDAuPCwM3IzwNG29IeNhSURUAS76ejG%2B%2BYqAMYAFAANTwTAdfJI0S7l4RRHEZW77VtQze1/Qu5QR7LH0GeCcgeY/pqit25kMdAIJFSmEsNYMwON4zEGlm6eA8w7CrnSC4Bg7hPDNH8JgqYfQYitFyGkAQowWhJBSCQhg%2BCSj9HGJUNBAhOgjGwWMNojCajDG6MEXotDCG2C4WQvQEwGg0JmFwFBL0VgSGNhwC6WMza4ztlzXm/NBbCyBm7CAuBJY%2BzMH7AOB95gIEwEmGIIZSD/XiNRAAnHEekkgQZmEkJ6DGZ1PQ2KRhwFGpA0bvWop6Lgno4Y2LhkEwGXAzp2M9AozWuN8aE0%2BgfMmlMQ7U1pvTCgUdUBe2iGzNgnB6gsExPSbmTAuQGCMC7Gx1EuDA3FvgHS0tZayAVo/aQz8lCv01roBOesmAGzbrI%2BR2NeC40thkm2yiHb82QJU4A1TanA3dp7cO3t7JxDMP7JJJNg6hxyWs6Ikdo7exQPMrgNiuCYxoLQZOlA06azzlnEuTyC5F2Jh9MujAK5VxrjdOuDcm60BbiXDuu9Vj/L7o4AeZth7IFHiXCep1NbT1nlnBeEKA4INXh9DeKRMDb07kYPeoBdl8GPmfC%2BV8b5rzvm0pWHTZAvw1jdXpH995QKsD/VF/8LFAPSCAsBEDOUwLgdEBBWBeUoIYWmPwEBXBCNaIEHh0w6EULyOkRV6qqFiLVag2VzDGisPIfq6ohrdX8JEUarIJquEWpkQsJY0iJFeJGYozg0zVEVK7osupGh3Y6J0hsiRhjdnGNMVgcxsifF%2BJqSDekUT6Tg0kM4vmrRRnmzxrYRJgdSbkyposSZxyDks3yasIpjsWAKExJyTEFzqJAnAg03RzTWh0ofgylW8guksp0CABI/TBlG1dabOJFsrY03OKgW2qhK3VtrfWxtQwVklvWb7OI2zc17JQKuo5WSTn9BrYkRIG4LlriXeuWdHSk7RBTg8m6rya4fUfe8kuXzBCV2rmbAFjdm6tw%2BmC4lmLSD4CtP3JBms4UIrXkiqeM857ggxUvbFJc8Vbx3sS4IpKg7kqYCfc%2Bl9r6MFvq0jtEhGWqx7W/ft7LjDfxsDy5Bt1%2BICs4GsMBX9oGWFgWM%2BBiCpXsNlRgrBNrcHoHtUQyh1QtXEOqBJwTZrBHGuETKxTkwVUEOEUp0T4w7Uab4Q6hQUilbDNHTjD1V7zhVprWKRdepl3aMaSQYNm6jGkBMWYyg0bUYgDMDUuIcQzpQ1BhjAL9JgmxPM1mgmRM3NWLOrYs6cMOI2MkDY8G9iuAJGRXEMzYzOChqDrIsWkX8tZq3fMeMqRnCSCAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_nonoverloaded_function_object/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_nonoverloaded_function_object.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_nonoverloaded_function_object.test.hpp)
