<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::AnyConfess`

<p style='text-align: right;'><a href="../../concepts.md#mouldivore-any-confess">To Index</a></p>

## Description

`Mouldivore::AnyConfess` accepts a class template predicate and a list of elements.
It returns true if there exists an element for which the predicate evaluates to `true` and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||Predicate&lt;Elements&gt;::value)</code></pre>

## Structure

```C++
template<template<typename...> class, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a class template predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0<*>::value)` and `(...||Pred_0<*>::value) && (...||Pred_1<*>::value)` are both atomic:

```C++
template<typename...>
struct Pred_0
{
    static constexpr bool value {true};
};

template<typename...>
struct Pred_1
{
    static constexpr bool value {true};
};

template<typename...Args>
requires (...||Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...||Pred_0<Args>::value) && (...||Pred_1<Args>::value)
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAnKSuADJ4DJgAcj4ARpjEEgAcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BwEmCypBvsm/m4EAJ6pjKyYAHQPp9gmGgCCc8ReDgDUysSY6AA%2BhoXq8TAB2Kxvb4w75zJiOZDfNAMOaYVSpYjfWKoTzfABuYi8mG%2BEIsBE%2BmAhABFTlCweDaf56aD9odjlSzpdrsw2A87k9QR8vgRfv8gVxQWTQbC4c1EciBGiMVicXjCd4SWSKcSaXSpYz9W9WQcjgjOecrjc%2BQ9XsRgApBW9/gBHLx4f4Kb4QfkQtx%2Bv4A4GnNx2h1PEAgDXE1aglHKzHY3G0b5ULwMCCxyH/AhbBipsRKfWG41vNlmk5cq28%2B62%2B2O/zPZ2YN0ezBen2PcH%2B7uBoEgs5hhvYSPRzCrUlmABs5in3t93YD4sBksH9YjUaJ47jSv2KqTeLTGazFhzee%2BOs5VhLYLe8MRgKYCiUrWo6ZDEQIT0zseZHHWtCcAArLwfgcFopCoJw/qWNYcKbNsWpmP4PCkAQmj/usADWIBAVOdxJFOUhAeCU6SIE/ikch%2BicJIvAsBIGgaKQYEQVBHC8AoIDMeh4H/qQcCwDAiAgJsBCpF4BDkJQaCHHQCRRLcnCqIRAC0ZHfMAyBIlIdxmLwAKECQeDoHo/CCCIYjsFIMiCIoKjqHxpC6FwpAAO7EEwqScDwAHAaBGGQZwADykkSaKqBUN8KlTupkiadp3y6WY3oeHJ9BYuYKGrLwvFaOsEBILJqTyWQFAQMVpUgMAUhmHwdD7MQXEQLEgWxBELQXD5vDtcwxAXMFsTaPUvGobJbCCMFDC0F1TlYLEXjAG4Yi0Fx3C8FgLCGMA4hzW2DT4u2gXovUkm7Khn49IFtB4LEnn9R4WCBRSeAMetpCHcQOJKNSBzbTdRgYesVAGA6ABqeCYG5wU8t1tnCKI4g2eZ8hKGogUufo20oNY1j6LdXGQOsqCpH0a2qXM6CnNSpiwZYZhsZ9xAmUdRPdL02QuAw7ieB0ehhIsFRVHoRRZAI0x%2BK5ot9MMQsrOzI2NPMEt6HUDQCAMrSy6M1QTIMKuufCWuCzrEjrAoCE7GbNEcCBLGBex0VqRpWk6ZIenergRmZchXA5WhQPrAgmBMFgiSZqQOGSP4dwUeCkgaJIZiSFOTF4cEgEcHRpAMShdxEVOSSBEkXBTkBkhcEBFFTvbTnsZx3EB3xBXCYVolhZJ0kVag6UKUpHAtCw%2BLgqpTDIgYRhJYEdxcHcEGGUQzOma5KOWUj0go/Z6NObodUeV53V%2BbbAV1yFHcRVFg/D6P4/bVPM9z6lPclRlk7%2BGY/t5fxbeVRlXe/2MK%2BI9kATxqoELgzEaC0Eas1VqTleqdThgg/qg1hoODhuNRgBApozUCvNRay1aCrThptf6uwIL4H%2BAdI6TkTrIDOnDS6mcII3Tup1R65DcrMzeqhT631MC/S2kYAGoBm58FBgoCGUMYaMDhqvRG1kN6yC3o5CCu8saA1plYSw%2BNYiEwjiTMmnAKYECpv4GmuN6aMwSEvVmEc1Z9C5jzPIksQjc21ssXW0tsgGzSBkMWDAPHC0Nj0RWGtla83yCEjm4TBhBPlkbNokTXGJPidUc2ltrJHztqxXgjsgE3xAXfLg09Z4aE9vgReb8/a5UDqQYOocxgR0ztnXO09E7giruCcE/gk4pwrrXNinAG48SBgJVuSAxLhX/s/Uqik2CcEHhpFgCh8RInxCUu4HI5gGUqcZZe8M16KPhiojGAR3KeW8utbJJ8hkcFCuJSS3xIrfCWfFFZayCSbO2aKCAaUX4JDfv4T%2BYyf6zL/uVABiQ1mpFSICDZgRAQ/MfMQFgZF6rQISLAtqHV%2BpINxQNIaI0ME9wmtg6as0KGYAWktFaa1UKkOEZw0glDFaHTWvPVQp19iMMEFdJyrD7oXA4c9bhcM%2BEZAEX9YRERRH5XEUwcGkNoaw3evIqyEglF2TRqonQ5zQE4zpjYVh%2Bjiak2yGtAA9JTQ12iLAMzyUzFmpqFbqz8BAVwviBblFNlLfxfRfHeNKCbTxqtQlus1kklxYaYn9HmGk1WETo2G3jSG4JGSthWz9jbHJDtOCvNRcs1Z6zvnmjmBU721SQXNyDiHMOlAj6tJAGYae/h/BASAonCBGg22kRSLkoKHFbCNy/qsbCIBo4z38EkcuyFO1TmQqRG2/hbl5OGU3fKR99KDLXUO0d6xPqZGcJIIAA%3D)

By turning `(...||Pred_0<*>::value)` and `(...||Pred_1<*>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<int>());
```

## Implementation

```C++
template<template<typename...> class Predicate, typename...Elements>
concept AnyConfess = (...||Predicate<Elements>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDspK4AMngMmAByPgBGmMT%2BABykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG57B0eYp%2BcAnimMrJgAdK%2Bn2ADUyAYKCh/KxEw%2BFEe1IHwI90ebFez2w9DYggU7xMGgAgmgGNsUgQPqiGLcPAwqJhfh9TgARD4QGEmAJuWluAFAvAg65nOH7RgEJEnbAgEAANzEXkwK1OVjRKNRAHoAFTyhWKpXSqVyhUfAAqJO5H0VKrRaqVRvl%2BtRUouhyYxzOEIezGhb15UtmxC8Dn%2BgPQAH0NFLaRLUR8gx9ZlaWV8BLNMKoUsQPjFUJ4PkLvJgyQELARXdcAuTxX7c/nJWiLVcbraoS9HdhnVm3Timd6uAWA8GQ01HMgIwwozG4wmkymRenM9naXmTgHx0WzSX9pbrXc7U8YajiMAeTW0YCAI5ePCAv54gkCYm/G6Nn1gtcbmlOtEY3ux%2BOJ2gfKheBgQMUZwEETYMO%2BYhKPmhbFqipZWmyS6Vqu66blKu77oeuL4oSZ48oynpXri8F3p85gAGxEahJ5EiSmGXlw154dWUqPnsfYvkmH5fj%2BFh/gB4JjpO07gaGnZekwvzxAQ1Cfjc4QEO835irxaIcGstCcAArLwfgcFopCoJw9KWNYIYbFsabmCcPCkAQmiKWsADWIAqZIzwaJIXABCcGgqRoZiEYR1TJMpHCSLwLASBoGikBpWk6RwvAKCA4WWZpimkHAsAwIgIAbAQKReAQ5CUGgBx0PEkRPJwqiJIRAC0hGSB8wDIF2UjPGYvDMkQxB4Ogej8IIIhiOwUgyIIigqOoSWkLo1EAO7EEwKScDwSmqepVnaZwADyuU5TiqBUB8FXVbV9WNR8zVmFSHhFfQcamVwKy8IlWhrBASCFSkxVkBQEDvZ9IDAFIZh8HQezEHFEAxGtMThM0tyLbw0PMMQtwbTE2h1Il5mFQiBAbQwtBwxNWAxF4wBuGItBxdwvBYCwhjAOIRMHhjeACiSa3RnUuU7OZUndGttB4DEc3Ix4WBrVmeAhdTpBs8QCZKOS%2Bz04LRhWWsVAGBuABqeCYNNG12vDw3CKI4hDb18hKGoa1Tfo9MoNY1j6ELcWQGsqDYlkVNVbM6AUqY%2BmWGYUVy51WBu9%2BXQ9FkLgMO4njtHooQLOUlR6IUmQCFMfjUZnvRDGnozUbU9QCP0kyJ3kJfdCz5dzIXIwJCXcw53ooYtI3SzN2sChGdsEjLRwakRWt0UHZVNV1Q1TWORdEC4IQJBkmYZkPRZ6trAgmBMFgCRR3ZkgnM8ACcJwBJIzlmJIhFhSphEn/onBBaQIVmc8hFcIRiQn4kX8OVwFSZ9CKjwmtFWK8UN5JReulV6mVtq5Xyj9VA10SplQ4M0FgAoAhVSYF8AwRgzon2eFwJybV8AdS6j1WQ/VzbSEtqNG2E1dBA1mvNeGQ8R6RV4NFLa2VcofD2h8TB2DcH4PpkQkhTlLooI%2BjdFeJwzDryeslOBv0bpIPUaMERODvj0y4CfLg4UaC0FBuDSGE1Eaw2NlY5GqN0YOGNtjLkeMCZrWJqTcmtBKbG1pirHYWl8CAnqGzKmWlObIG5sbPmAUtKC2FrDMWATHqdWluZOWCtMBKzpkYVWoBoF8C1goXW%2BtDaMGNpbWhg16GyEYeNLSLD7Zq0DlYSwLsYiRw9l7SMnBfYEH9icckLTrAhx4WHLq7N3bRzrn4CArg27URTmUJuGd0hZ2yFXXOqQ1kF1TismuMd64DAWdMsufQG57O7u3VumzrkDC7une66xNgDyeQFLhY9ODCOIFgnBeC9GEIMVIjQVJF4dQUfdR6m9SDb13qMKOAUX5v2Ic5AIQCAhuUkNfWq1FuHrRirYSBKiYHwDgVlHamjZGfVKmwTgmDjosAUAKLsAogVXFmOQpe4dqF9TNtUk2dTbYgBOKQNhC1qacNWmAzaCDdr7XpXVRlzLkxsqgrMGRqDbqrxOMo9WKU3pUo0d9LRCRmUpBSF6VlJ8vTsoIEJH5tVgamPiOYqGMNkY2PdSjNGGMnEoJxq4wmgTMAkzJhTKm5k/G5OSaQIJLNQkc1UFzPY0TBD8wmvEkWJ5xYTUlmk3gGT0hZOVrk8I%2BTnqFKYDrPWBsjYy0qXyiQNSRrW3qToYVTTjBOzafEzp2luk9k4NKP2jsg4WFGdpcZEd4C91rmcuOCdchbKWYsR52yihZBOfnLIDzi6nN6BXVotyDkzMPbu5u4xjnHsvZ3S5jze790GpK0BUUvkKo%2BEqllqq9jqoXhQ5ed1dXQK3jvPelAh5Iv8MQk4JwVKeRcmFGDARv4vp4ZwCBCVoWHxUqfFSiRvIn0kCfNy58uAioCicKVr6CXEqHq1VD%2BKoXAdli62OkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/concepts/any_confess.hpp)
- [unit test](../../../../tests/unit/concepts/mouldivore/any_confess.test.hpp)
