<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Phantom`

## Description

`Phantom` accepts a list of stockrooms and returns a function.
When invoked by an operation, the function instantiates the operation with the stockrooms.

<pre><code>   Stockrooms...
-> Operation
-> Operation&lt;Stockrooms...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the stockrooms.

<pre><code>size() -> sizeof...(Stockrooms)</code></pre>

## Type Signature

```Haskell
Phantom ::   template<template<auto...> class...> class...
          -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class...>
struct Phantom
{
    static constexpr auto size() -> size_t;

    template<template<template<template<auto...> class...> class...> class>
    alias Hail = RESULT;

    template<template<template<template<auto...> class...> class...> class>
    using UniHail = RESULT;
};
```

## Examples

- We will create a `Phantom` with stockrooms `Stockroom_0, Stockroom_1, Stockroom_2, Stockroom_3`.
Then, we will transport the stockrooms to `Operation`.

```C++
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<template<auto...> class...>
struct Stockroom_3;

template<template<template<auto...> class...> class...>
struct Operation;

using PackedPhantom = Phantom
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

using SupposedResult = Operation
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

using Result = PackedPhantom::Hail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Phantom`.

```C++
static_assert(PackedPhantom::size() == 4);
```

## Implementation

```C++
template<template<template<auto...> class...> class...Stockrooms>
struct Phantom
{
    static constexpr size_t size()
    { return sizeof...(Stockrooms); }

    template<template<template<template<auto...> class...> class...> class Melancholy>
    struct Detail { using type = Melancholy<Stockrooms...>; };

    template<template<template<template<auto...> class...> class...> class...Melancholy>
    using Hail = Detail<Melancholy...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfP3eTE%2BpyYXiIADooTdDvsmAoFFCITC4QikU1UMgANbEVCoFgKG5PcbELwOQ7KBCGIgsJ4mADsVgehxZh1mjmQsIE40wqlSxDZeAAXpgAPoEQUiiBLJ6s46Mw7ETAEdYMSWYVBUJEQDHY3H4hQygIWeUAETpzNZgL%2BANeQJB3ztNtO1uB/1B4NQSJRBjR0IC2FhvsR/sDqIUhwAsnVDMgEJ4AJ5Ey0sklkiWm5VMOjyk1eTJGQ4EBOpTDHAKmqMxhhxxNfXU4vEE70Bk4mhnm40W%2B5y10Ovvux2/N224cOsGQ0NB%2BEh5EB6d%2Budh4NI6MGGvx2hJ1spw758LAQ4ACWztHLlczzToXzXsc3CZb2BAIGLpbbdPpnaZjweAHoAFSAUBwEgb%2BTwAUBhwACrYEIUFCIcwFgX%2BIGoUh3Y7HsBxll8aA1pgqQEISO4/s8Toji65Hjp6j4LrOyb3Gm5INvqLCiho74PE8A6jvag4Tl6U7ho%2BxIEKSzFEHqTailwnGkTxlFjvxNFCSuoaieJEosdJZhydxVGDgpbgCbRwnqQ8TFaZJjb4qKAR6Q8RlOQZXwmapM6mWpS4aemhwAPKlsQwLZA59wQYBhwAGJ4MQ4yHNgqisO8ZboVxDz7oWyhMNimDoJS1L4ueFJUoI%2BJ0qcsqstptkaKQxy7tVbEpPVPZVdZrGimYdWVSyjV2eVtxdml9wZYeQheKkRS5QASpgCheLQEonJWAXxMFAjlW4PWHH1tUtXKfXNdtfVdftbWYjZbH2VxrZDaRo2HLN82LUVWU5XlJU0s%2BJ7Xqcq1BQ0RJ3aJwXIKKM7xAQEAXM%2BCisGK8JfE9C0EHV42TRkM1zSjNxGt%2B4HATtmB4eg8WJb8KVAchpHsngYMQ60EBvViuX5aVLCw8KmDSuey2HJIeNPBwKy0JwACsvB%2BBwWikKgnBbZY1hsmsGw4WYAQ8KQBCaMLKxYiAYsaBCZhmAAnAAHBopti%2BbiQBJIZj0pIiT6Jwki8BzXAaLVUsy3LHC8AoIC1dr0vC6QcCwDAiAgGsBCpOC5CUGgbx0PEkTw5wqi2wAtIkkiHMAyCclIxu8LlhAkHg6B6PwggiGI7BSDIgiKCo6hh6QugpAA7kFqScDwIvi5LOuy5wfnggnEqaoc2eJHnBdFyXkjG4cEAeKn9ACjsXBLLwodaCsEBICnqRp2QFAQGfF8gMAUhdTQi3xEHEAxGPMThC0CaD7wn/MMQBMfkYjaGJqHTWKc2CCD8gwLcY8sAxC8MAYytBaBB24LwLALBDDAHEJ3fASoHB4AAG5zTHryYm4Itia3CC8UWndaB4BiEFQBHgsBjzEngDmGDSCkOIDETGmZsFGEYUYHWKwqAGGAAoAAangTAPdVpS01nXYQohxDN1UW3NQY9u76BwSgaw1h9BMKDpAFYqBCLZHQTnC4y1TCK0sGYP2fDiDVzIeY7oYDsguAYO4TwHQ9ChHCEMSoIwUhFCyAIKYfgIkZCiQweYwwEhjDqN4gQfRJgBPyKknoGSJgDBCQscJtgCkxL0LMVoSSwkpJWAoFWmwJDDw4BLUgvteD%2BznrnfOhdi6HFLmYdeuBK473VnvA%2B4iVgIEwEwLACRpSkH1oECEpsAhOw0A7Z23sxaJFNq7Dg7tSAcw1hCZIiRzYWy4IkMWkguBi1WS7dp48A62GDlrcREdo4n1jlPROV8b7bwzmwTgLQWDEPpDnJg05CxcFNhCLgEIZYVyIG4muKRVENw0dILRSgdGd10F1PuTAB4YOaa0p5/tJ7x3BIcWeoLwWQuhYeWF8LEXr03ufbexx1ZmH3u8sOx9T74k5fEJO19hW33pRCuERhYVez4HQF4sVKDv07v/b%2Bv9SDqsAcA0BDhNWQMYAQGBcD8GYEQcgsQaDNVYJwXgmWBDvGkPQUi1QlCXiatoXUMejDmHfzYVsGWnDuGaz4QIpQQi7UHg%2BZIpg0i5EKKUZqjF6im7YtkNojuMsCX6LEQ4qwlgTExDMQsyxDQbF2IrPm6wziOmuPcSWupaSiHOAgK4cpKRgnlGSXoSJDQO1pHiQ0apixcnpMaGU7JsSvEtonXMIpPaxiTryNOyphTu01KaasdYjS977PJWPTpUrGUyuZXChFGghn4BRdyjWfLD661INM2ZIwFn0MOccuFGz6T3PpPSe2Zhna3LaYezggc3kPuPl8pAcdp5ioBenTOHBQU9IJMQzkxCWV/HGOXa9Vc0UtzUY3CQ6bW64qzToEAQQiUkqHvu0endKW/JnlQQ4KGC5oYw1ht0cUN4Sq5TsAI96PnfIQ5fZO/GRjocmqKTDptRTYYIODYgLB84Kufsqt%2BH8v6AM1dqoBICwEGvxFA41sCf5motSg61PDbUiMDZgmKTqyGdwocgKhnrBDeoYUwlhCYA0cLcSG3gYbBGvCjWIgVfApGyPkYo0syjeApuI5ojN5HdFUdzcYIxhbfWNtllY7knBfww2rU4lx8RUUeIWXYcdvj/ErqCX4kdJS%2B3ZAHW10oC7N1jtnZktoU6KnNoaP1lrKTSn9AHWusbW76k7qbmShjftOBsZU6hhQ6HDhyYhIpq9Izb3jP5UfKZMy5mUGaR%2BkAZsIQBACGLQ2tzva3fpOckDjGwOvJDpMxZ/g4V/o0LCjZXAAjXPpGYG5%2ByAhLY6R9yDzSzDQ%2BeRMgVKw%2BGZGcJIIAA%3D)

## Links

- [source code](../../../conceptrodon/phantom.hpp)
