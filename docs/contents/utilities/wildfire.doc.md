<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Wildfire`

## Description

`Wildfire` accepts a `Will` and returns the `Will` via member `Will`.

<pre><code>Will -> Will</code></pre>

## Type Signature

```Haskell
Wildfire ::   template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...
           -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
struct Wildfire
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT;
};
```

## Examples

This function injectively maps a `Will` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Op_1 {};

constexpr auto fun(Wildfire<Op_0>) { return false; }

constexpr auto fun(Wildfire<Op_1>) { return true; }

static_assert(not fun(Wildfire<Op_0>{}));

static_assert(fun(Wildfire<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
constexpr auto gun(Wildfire<Op_0>) -> std::false_type;

constexpr auto gun(Wildfire<Op_1>) -> std::true_type;

static_assert(not decltype(gun(std::declval<Wildfire<Op_0>>()))::value);

static_assert(decltype(gun(std::declval<Wildfire<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Operation>
struct Wildfire
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Args>
    using Will = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAnKSuADJ4DJgAcj4ARpjEIADMABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyZJbnsHR5gnZ/uHTMen53cPNxf3V4%2B3l9dP36dMXiIADoQSdsABqZAGBQKEFAsGQ6Gw0FJCFQpgwuEI9GYlFopFY1GIjEKcEAeXSCXuuTBJg0AEFJsQvA5wQB1OjoGjEK4MkwAdisDPBIvBv3ePy%2BEs%2Bbxe4rlUoVso%2BbgBwLxxNx8KJOOR2vxJMJBq12IJIPpxGAClpwtFXmyRnZdFo4JOABFyZTiNSBNcLVajSchfSBW6g3SQwyAPQAKjj8YTiajEdj8fBABVsEJ00JwQnk9HE0X8xGI/KVeXJcqq88K4q69X/oDUEbNXrTYaNbrW92u2b9RGmSyCJ6APoaV2C0PhvkMysy2s1v6vRcL5fz1XNnv9jsmnU7/ed/VtwMMoesimjriTqz8sNJYMphPggBieGIkwzmE/Jdn9LQDCTJgqjpMQ4Jqqg4JUF4DAQBytBcu%2BKqXhoYIrDe4I8gQmwMFBYhKEGk5hn%2BAFASBYEQVBMFwZy3LIekV5oRhWE4WKzIfBYRGlmerSOMgo4kgkBAQAwqAjtBsHwYhPLXChtJTneKwrDOkaMrxeD8YJ7TUNRUl0bJDFcPJt5ukpKlPmmQiYAB6Bfj%2B8YFqp5hJBEUJeFgrqnICdCEAAnjaqmkXs5Hgc24LALptFIQZ45MQAtAikzoCAIBUPhmCjgQvmUuZDJBcBoGhUQ4WRQh%2BmnJeRmouhCVEklKUEOxmXZRx3FqdSmkwkJIlieCWBQlllLQNR9UgP1tAAG5iNcenRRVDGoaiYIQEpKwpVN3iYMpD5tfMfECV12njYNmDDbBo3jRtM1RTJ82MUtqIrUp61iF4W1Bhway0JwACsvB%2BBwWikKgnBuNY1jggoGxbJgrpmEkPCkAQmifWsADWIA/ZIQIaJIXD8kkGg/RoZj%2BP4ZgpGk30cJIvAsBIGgaKQANAyDHC8AoIBM8jgOfaQcCwDAiAgBsBDpIC5CUGgBx0AkUSsDsqgpP4cX%2BJI4XIMg4JSECZi8Jg%2BBEMQeDJVwMiCCIYjsFI5vyEoago6QuhmwA7t66ScDwX2/f9jts2SgLiyOqBUOCSsq2rGtazrZjghAHgy/QYHOVwKy8DzWhrBASDS%2BkstkBQEC5/nIDAFIZh8HQewfpQsSO7EERtL5nu8A3zDEL5ZKxNo1k84j0tsIIZIMLQze86QWCxF4wCqrQtCc9wvBYCwhjAOI4/4DyDh4BN36O8B1mAjsiMRHs1NA7QeCxN6HceFgjuNXg9OL6Qu/ELEWSYG6%2Byr5fRgo2sKgBgrQADU8CYBdhSRgLdbaW3EDbfgghFAqHUOPZ2%2BhV4oHBpYfQV9OaQDWKgdITQF5xSSu6UwlhrBmFZm/Y2WB8ErV6L3XILgGDuE8F0PQYQIgjGqGMM2JQcgCBmH4QRWRhEMEWKMRIZs7AsIEAMaYnDChyIaAo5oUwhi8KWAI2wWjRF6HmO0aR/DZFrChpsbYEhvYcD%2BszP2nAw7K1VurYAmttbY1jhAXAhASBwwRmnJGAC1gIEwEwLAiQmEY0kEkIEgQkj8kkLjMwkh/CMx%2Bj0amtNSD0wRkCfwXB/ApECCkIpWMuA/QSf4Bx482Ycy5sE3mWchbZxFoHCWhdi5J3lmwTgbQWATX5HFJgxJHRcECECLgON9aGxICbPQiDhCiHgdIJZyCHZoJABXN2TAPaL1sfYlmvB/YdODqHAZQyRljOANrSZ0yJzx1QInBIASzBBIznzNp3SEiSyLs8vOScQCXOGeiIwEyuBMxoLQaunMIB13Hm3JuMCkUdy7j3BwMCB6MAIMPUejtJ7T1nvPGBy9f47CBpvFhu8F5AwPsgI%2BMDT4NEdpfa%2BTc74UvTsbZ%2BiM34fyUN/FeRg/6gGaXwYBCgwEQKgQDRGSy4HWzWbIDZqCga6ArgYf%2BlCrA4LZYwwhxDcikPIUkN0OrqG0ISPQveBDmHb2cBAVwhizY8MqDIvQQimguoyBIpopjlhqL6IogxKixH2qaEo7R7qzFGNDQUcNxjo18MDRY6G1jU76B9rU1mTiQXXLBbciZUycZx18UbAJqd04hNIGEiJYwmHZLpskSZuN%2BRVP5ATSQqS1Zm2OcDTgDTuYAP5q0pAosg5/J%2BcQXpOwBmRxYAoCaWsJrFsuJMWZfj6GLNkIqiQyqkH2zVToZIpBdn7K9lmuxvs6mcADmLQE4IQ7gWICwBdS6V1rveJ%2BJ5Lzk7wySB8kd3yAX5ynaBoFy70gMVXYEUc66CACVfWrSuMKEhwoRUDVFY9EbYfRb3LFzzB64pHmPSlmAp4zzECSl%2BZKRVconkhbeNL96qEPnsJlggWXjzZTfXynKH48pgfyz%2BQrf4RDFZnCVTBQHgMgZSOVvAFUrKVbbVVjtdBJAwdq7BNh9XwENSQzgUZ6oWssDQk5dCTa2qYfIh1fgnXsJ9W6lNeivW5B9e58oOiPVBo0VGn1dnI1aIDXopNgWQs%2BdjZmyxMMbFXqOY4jgL633q0Xcu8EsGgQIbLXM/9gTq3NNCeEyJlBbE5PpmYSZSQkg/WJnjRmNX%2BTFJzScwdthGmfKUqQGJP14k/RSKTQIkhAgE0SVwLT1Mkg3tzezJpmdbF61awOubXW1hv2yM4SQQA%3D%3D)

## Links

- [source code](../../../conceptrodon/wildfire.hpp)
