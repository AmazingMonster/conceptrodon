<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreUnique`

## Description

`Varybivore::AreUnique` accepts a list of variables. It returns true if no two variables in the list are the same and returns false if otherwise.

<pre><code>Variables... -> AreUnique ? true : false</code></pre>

## Type Signature

```Haskell
AreUnique :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct AreUnique
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `0, 1, 2, -1` are unique. Then, we will append `1` and check again.

```C++
static_assert(AreUnique<0, 1, 2, -1>::value);
static_assert(! AreUnique<0, 1, 2, -1, 1>::value);
```

## Implementation

`AreUnique` is implemented as a special case of `Varybivore::AreOverlapping`:

```C++
template<typename FirstVariable, typename...RestVariables>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstVariable>
        ::template Page<RestVariables...>
        ::value
    };
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAOzSAA6oCoRODB7evgFBaRmOAmER0SxxCcm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfFJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHOYAzOHI3lgA1Cbbbl6OtIQAnifYJhoAgjt7B5jHpwRXKZgA%2BgTETEIClu9yeZl2DH2XiOJzcyDG6CwVBBj1BBEwLBSBnRsKY51QhwAas08EwYvQUQ8xsQvA5DgBZASoIgMG6oxIWQ4zRzIQ5oBhjTCqFLEQ54oiHABuYi8bxMHOJxFJ5Mw8oAIidOerNaC0RisUwcadxagAHTmynU2kEQ5CBDnAgU7ZWVGPdGY7Gq43482mgCSAu%2BDkw6EVyvowO2d0eVrpD2ImAA8pL4gYUilwsBQSBDikvOS8LzGQxmQIbqcAwog%2BjQySyRHbr7dRzQYc21z/tbDmrME06K32/KXQ926PDu6DUa3Cam1GB2OOzS6cpiKXlExgKrHgu20PDl4MkZx185ds1VLUHh0JrjokNc757f78PQQB6V%2BHABKmGQawyKcOaclBAR8J09XF8UOStq0zMN60wUgxR9c1vzGOCVUjaMR3bWMbRXNcNy3bDdxbbcd3fY4ADYNB7PtaBMajDgAdzoWgO1QFJDgTX9iAyAREKYZAEDwTBJUzLkEBIAgAFpkDwdYvEIU1H1HA9xM%2Bb53nPBEQBQAR8HqMQVMHU5jIXHSQDwBQfhiJglB%2BVBkVOYtS1ZWFoJ/RwjHQp1sFIeMkxTYg0wzIxbl06VvAQ44yJ3dtaMBWhELMscAuTVMmHTTN3MDTyQx8zAFF9RCPIcWC6xVSk4vCkANPYWr9U9Q58KIddN1hVCCAKoqLSjXS6p1V1iLHblCz5ARBWFUUYlQTwpRlOUOQsqyfgUVhfklWE6sQyVL2vOc70G4btQfIaKIsOy3iA9hQMaw0vWnSDSq84ACqqnDO2XVdWsInKq088qlXg96SOHOK1KPOqtI7dBdP5AysiM2Kx1hFLR2W6zbPsxzYRcllyzcZ7AfDL0/MONKgpC7K%2BpASLZWS5G4t2q9SDR9s7QdJ1Cdy4NayBjDiqgnmXreudGZM7B%2BpPI7qvFttRt5flJpFQ4ZrmunFosEsbQx1b1p%2BTaPhPHa9pBQ7TuO82X2RsD7ogohfW6kH90PYBmsI6GWtQNqHu62c7gtk7rYeW2pxNQ4ADF5LQir6AE5DTU6p2xapT6bQCuQGDwABHWVmzBj7DTGpX0Sm1XZrYjWYstguFzAMByYTdLgsy0Ks1OKPeK62PSZS/q7vRd32tOJOe565SU7iiKFsfIPm2fXVHlfAAqVe1/X183zXgAVbAhG3tfN6X9eT%2BXo%2BnlRcEXmhU84QEDYUgITDF9TovkB%2BOylBaCAM6z3OHo0IhIIhwzCIWklwGqGtFhHQVh/BQX8CAQHro3TAmcc551OIAw4wDQGHHAUAyBC1oHOg4MsWgnB/C8D8BwLQpBUCcDcNYawXJVjrDlOCHgpACCaFIcsAA1iASi2xTQAA4RGJA0JRfwGgNDbDMCIswABORR%2BhOCSF4CwCQMjSDUNofQjgvAFAgEAdwmhpDSBwFgDARAIBVgEDzAQcglA0CYjoPESI61OCqBEZRaSlFJCHGAMgXkUhTRmF4CGQgJArx6H4IIEQYh2BSBkIIRQKh1BmNILoIITEAQpE4DwMhFCqE8LoZwRM5wHGHEcocbxvj/GBOCdgyQYTDgQA8K4%2BgoodhcEWLwUxWhlgQCQC4jMXSnEQFGW4hIwApCgJoLQdEvFKAxFKTEcIzQrgFN4Os5gxAriJhiNoTy2zSAuLYIIRMDBaBbMyVgGIXhgDTloLQIx3BeBYBYIYYA4g7nyQBimN5tChQ/nOJsTh4R0TkMyZcGIAJ9keCwKU/4eBNHvNIEFGaSgexfKMJcIwPDlhUAMMABQhIRJMUTN8ahnC4nCFEOIZJdK0lqFKdk/Q3yUBMMsPoPAMQjGQGWBxeobzpIIhOGqUwlhrBmD0UFJUWABUQGWHYAGzgICuEmH4IIoRwiDAqMMAo6RMgCC1XoQoJqGBzCGAkIIqqyoCF6BMTw7Q9D2vqE6/oer5iGtsOMVoLq8h2v9dag1tqVWsI2BIIpHBKE6NKfo2pPi/EBKCSElpZg2m4Cid0jhfSuGEuWAgTATAsAJGVaQARkhhGKO2MkDQkgzCSGohofwlEVHQvUaQTR2wuCmkolwSiIjFEiMHf4SQXB/C1sovGzJ%2BjDHGILWYoZ1jhm2MqecCZUyukeLYJwZoLBJSJGkkwPkBgjxcEUaaPtwKDLRNhkEOlCTGXSGZUoVlmTdCgNyZlbZMa426N4Poip9jzjVKoGKYgh7j2nv2N87BV6b1tI6WM%2BIxxwRmHzQM8xa7t3xC3agTpwwD1Htkue2ZiiuCAIWUsoxEBVmZN2Zs05TH9mHOOQ4U55zGAECuTc0p9zHnPNeacz53zfm0PwNxRwgLSkgt/OiU5kLailNhfCq4iLNi0JRWizhmL0iYBxeJzMhK%2BAkrJRSqljBTlPoZUk19sgWUZNoV%2BjlBKpVWB5bCpVQrH5ZFFeKs8HmZVyviAqwq8AVW1DVX4DVDB3CBu1cEeLoaFhGqKFkM16XLWpd9e6no/qstdBi563Ltq/V9CKzMFoZXo0rDWFG3pqjY0lLnZwSD0GT1nvg5e69poNBZrvbm3tWHC2kGLaW4YFbO0aJANsK9DbEhTsSIkbYjbm0TtnXozgC6TGmcsTYuxDiCNEeILuzYB6GksAUJKXkkpeuejGBEobMTH2yGffZlJ8h33OZ0HN0gP78nvP/a17bHAQNVJqZdgJ13btSge/dMYyHCOoeG9sUby6LEjJR9Mk7qPabIHTAbS9PxHsEA/lB/xfA6C0ZWWsjZ%2ByWMM4OUck56LuOXOubcyTmAHlPLECJ9FYm8VaY%2Bf8sqsnMnybBUpwQKmYV8vU5p5FSpdO8H09ijExmCWY%2BJRuCzmBKXUps%2B9uzEgHOpJ%2B2y/75GuXSq83ynzdC/MTU4K%2BHSwXLCyqA/Kq8EXBXFYdbFzViW9C6rKDa81xr6hFYtfUWrdrotB89VVpPHqQ3esj8Gyrofs81cz2GurChI1JJB1toD7XoeHFh3dhH6IkcQGzUQYbvT%2BljYm2WygMau2aKUaabY2x/DSInTIgfiQh3l7KQY2wi7sOLH4XNyi16uBKLW8oyiiQuASKCNC7YoOK/T7nzG8Jk/51LsGcsIKfE/CSCAA)

## Links

- [source code](../../../../conceptrodon/descend/descend/varybivore/are_unique.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/are_unique.test.hpp)
