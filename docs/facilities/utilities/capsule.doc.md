<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Capsule`

<p style='text-align: right;'><a href="../../index.md#transportations">To Index</a></p>

## Description

`Capsule` accepts a list of elements and returns a function.
When invoked by an operation, the function instantiates the operation with the elements.

<pre><code>   Elements...
-> Operation
-> Operation&lt;Elements...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the elements.

<pre><code>size() -> sizeof...(Elements)</code></pre>

## Type Signature

```Haskell
Capsule ::   typename...
          -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Capsule
{
    static constexpr auto size() -> size_t;

    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

- We will create a `Capsule` with elements `int, int*, int**, int**`.
Then, we will transport the elements to `Operation`.

```C++
template<typename...>
struct Operation;

using PackedCapsule = Capsule<int, int*, int**, int**>;

using SupposedResult = Operation<int, int*, int**, int**>;
using Result = PackedCapsule::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Capsule`.

```C++
static_assert(PackedCapsule::size() == 4);
```

## Implementation

```C++
template<typename...Elements>
struct Capsule
{
    static constexpr size_t size()
    { return sizeof...(Elements); }

    template<template<typename...> class Container>
    struct Detail { using type = Container<Elements...>; };

    template<template<typename...> class...Containers>
    using Road = Detail<Containers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAdIADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJSbaY9kUMQgRMxATZPn6B1bWZDU0EJVGx8YnSCo3Nrbkdo739ZRXDAJS2qF7EyOwc5gHhyN5YANQmAW7Io%2BhYVEfYJhoAgje3BJgsyQZPR24EAJ7JjKyYADogdh6GxBAorg9RsQvA59m4mMkFF56A8TAB2Kx3fY4/bTRzIfZoBijTCqZLEPF4ABemAA%2BgQqbSIAsHrjDpj9sRMARVgwmZhUFQgQCICDnowCApWQELByACJo7G4p4vN6YD6q15Md7Hb6/ZhsEVXIkGBQKeGyJjheKQ5U46GwxnynnW2gcuVedJGfb6zCHALyy2Ca0RYgfcVgqXGgLXWUKo5Y%2B7233PbW6z5p9Wan5/I1Ak27JjmkUeEM24gQ2Ns3Fe8LAfYAJVQTHQAaDLsadA%2BZa7YYUMewIBAfsTaPRitlStuAHoAFQLxdL5czh7zxf7AAq2CEm6E%2ByXq7u6%2BXp4XR%2BT9zM2wYuy8Bw%2BxPWySldsvWuzetzhsBBerd0dOEAHlfmIHVMjHO41yXfYADE8ErRlsFUVhXn9Q8HjrH1lCYZAAGtMHcRFkXodt4WIlENWOcICFIfYaLnOiGMY%2BjBAXSEpygu4sIbIQvGSApCMbTASMZI4gxA%2BJwIED4aKYtj5IIBdFPY6tONuHimxElExMDfYcPwwiESRSjh2bVsPkksC6g4pMoUaAk6WLJRmggM5hwUf4nKrNxhNEui%2BIEtIhO02gCCuGU7OPGChEwYk22Q1DSIwgCHLwZBvJcggIAMgiiJM8QQHSZkFnbcT9kkSKHg4JZaE4ABWXg/A4LRSFQTg3Gsaw8RWNZ/S2HhSAITQaqWPCQHqjQATMMwAE4AA4NFm%2Br5oANiSMx0UkVb9E4SReBYCQNA0Uhmta9qOF4BQQBO4aWpq0g4FgGBEBAFYCGSLxaIoCA0BeOh4kif5OFUNaAFpVskfZgGQQkpGm3hCMIEg8HQPR%2BEEEQxHYKQZEERQVHUe7SF0LhSAAdzA5JOB4WqGqaka2s4ICvs%2BxkhX2UHVohqGYbhyRpv2CAPH%2B%2BhKQGhZeDurQlggJA/uSAGyB%2BhWlZAYApDMPg6CeStKBiRmYnCJovhp3gjeYYgviAmJtDiu7Br%2BqMgIYWhTeJrAYi8YAEVoWhru4XgsBYQxgHED2EPtvAADcRMZsk4q%2BjZBpompGdoPAYjAq2PCwRmCGIPBDsD0hY%2BIGJgpdEOjAzowRqWKgDGABQADU8EwcnJOawaMeEURxFx3uCbURnSf0UOUC6yx9Ez67ICWVAX0yAOwbOcTTEsawzHOsvC6wOeWU6KPnAgVwJj8MnQhtOYhjJgoMgEc%2B9HvupZkGBIybsY/6jGFpPDaPQX8HDdF/m/cot9bC/yfp/UB1934SCWAoXq6wEG7Q4I1U6jMLqc3BpDaGsN9jwzMELXAyNxbXi4JLIa9clgIEwK2IYh9xqBABLNAIW0NCSDMNtY69VVqzTQftUgh0AhcABKtLgq15oLUkfVSQXB6psJ2mdXgF0ro3WofdWWL05ZvVZl9cglBVZiyBmwTgTQWDR3RGDJgppQ6ENmgCMRrUkZED3ujWQWMB7SCHkoEexNdBa0poiM2dN0EM2JhdFmH0vr7A5hYqxNi7E%2Bi4I45xQsRaKzFoca8ZgqHSwero4x8RDG/VQKLIYCTrFFiMKkrgJ0aBhXiNdCABtiYWxNmbUgHSrY2ztg4LpTtJQuzdozT23tfb%2By6cHUO4dWr4G5MA2OAcXGqETk8Lpqc6rEwzlnE2ucNitQLkXLpZcK5KCrrM%2Bs9c%2BBN1bu3TuBoum9y8TjHxshh5E1aoE8edcN5WGnrsg%2BC8l4CBXmvQM/yt473iHvOO88j7AJPmff%2BuRL4MHQGA%2BYd80gPyyKii%2BpAX6ZCxRAoBdQejjAJYAmo39KV9DgeAj%2BkDejQJZc0UlH9EHIJxmEjBKimYcH2FUpJNSGypKcQCDQJD8BuJyaI/JNDSB0IYQkQ%2B2yhEiMcZw9Eij0Tog2tteRmDImcHUbdG5T1XrvTZqU4pxBTEbAsXglgCho6EmjhK9UoxEaypRmjMmLz%2B5vLxvIPxXydCJAplTUJaD%2BVYOZvo9mVBhXEBYC6t1HqvU6hEoyYW5SsnxHlQERVWjHrywLUrO1laxYgHdQJOknrZp0m9QQJyabIbayaXrVphtjZWy6T062tt7aDPKc7V27t5mYC9j7MQUyS4zJrocoOkcllx2JgnZASdNmCDTjszO2cvgHPzoXYug0zmV2eFcuuZbG5MGbm3DuXdnmeODRId5%2BNw2jyjQYP5U8bBAvgCCuoAcZzuShZYbeqjd6o3hYfclmQXAYrZVfUo8CcWFEyGy4lxRGXYsRRSqB1LP60qRT/GY%2BGyXEZyIS6YHKqNcuWKsFBlC40RPOpwVN6aoauvdfsJtAJW0yrIfKyhUslUqqwGqsJmqQBzQBAEAI9VJryOOkp9EUiTWccurYDRBSFhjX8I4/VGhUmcK4AEVa9V0RmDkWggIHHVFms0TLMJZgnOCok1opYZd0jOEkEAA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/capsule.hpp)
