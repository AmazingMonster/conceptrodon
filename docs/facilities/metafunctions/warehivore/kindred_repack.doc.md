<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-kindred-repack">To Index</a></p>

## Description

`Warehivore::KindredRepack` accepts a list of packed warehouses and returns a function.
When invoked by an operation, the function concatenates the packed warehouses and instantiates the operation with the result.

<pre><code>   Warehouse<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Warehouse<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Warehouse<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Operation
-> Operation&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack ::   typename... 
         -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};
```

## Examples

Here, we first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
template<template<typename...> class...>
struct Warehouse;

template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult = Warehouse<Con_0, Con_1, Con_2, Con_3>;

using Result = KindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<Warehouse>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::KindredRepack` is implemented similarly to [`Warehivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Vehicle`. After all containers are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class...>
struct Vehicle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct KindredRepack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = Operation<Containers...>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct KindredRepack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Vehicle<ContainerAs..., ContainerBs...>,
            Others...
        >::template Flow<Operation>;
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcAOykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyaBbnsHR5gnZwCe6YysmAB0LyfYANTIBgoKL09vJg0AEFJsQvA53gA1TAIPBfK6BKzAwFA86HJjHU4EO4PNh/AHA0HggjvADSEXQxEw6AASph0kxkABrd4mFJWFIAEROSKBKIA9Pz3hYmEp3m5RewUSi0ZdrrKMQizvt0ZjbvdmHjXoEPl9Rb9tbrvgp3gB1NowjZKUjvBVq7Eax74nWfY1/DyCJgRBIKAkgghgiHkhiU6l0hnM67mqkIK1Kj2tb3EA3/HV%2Btm895Z20quVY3OK%2BUF%2B04zXPQ2u/XOo3694AeXuxAxuT92feRIhnMwidoKLbGb7bezXmyRltONZgU59cbzYE1wTXsiyerPMHWbZ3MR0uBbbtSv3RYuhaxpadFb1P2rlavLyBwCp%2B0YBF9ad3w9HwHeADFaKgAO6TtOXY9tc96Pmwggpm8IAgA6CK8pua7IsCgrvHSyCbNkABumDipKIA7qixZXMipzrjmx72iR8pnlqqY1reDE3ia0aWiOmBAqQFGHvmVEHnR5bMZe0EuiJZoWrGHE2DxNGno69FvCx7qyEuCQgjasn8bRClCUpIkqZ6SYWAo3Hvlm8Fln8dYEAgPrSm%2B/qBiSwahrS9KMkyUaSXGfKnIuSYgtWNpsVJShWP5qnGaJ2A2jZdkroa0rslpqoHnJyrafJuJ6WJboXsaM4JHODCttmHYkiBXq9uZrIpbVbYjhEX7wUBZIUlS7kRl5DXZtcFFDtm0KwvCC5RcuQUvDaAXLiZwUDYN9a2T6%2BK9RuOqwfuP5/v%2B1wNsVTQAtutVIcdfK1bxmVpUe13ZVZBVVg9THgZgT5QWVWZNWOv4AW1VV0GBD6vZBL7VptOLIXyXKQwKABU8MI4jSP8nDCPvAAKpgkwmojKOoUjBO40R5iBBEXxeFgk5uGgDDbOkL7psCl3M4J14GUlhIBsSEkxnGMNMxlLO6Wz%2BUMSiFU8%2BxSgAPoaPzxFZVdebqjlIuPWLnPOZLYWYNLXDy8zgus09MXi1zEKhXG0tmAbRvCxzTncx6su24rlnnhrjsQs7%2BtnTKduqw7EvOzbfsC27xue8HAjS4E8tfV%2BQheOkJRhljXi0CSJzTpbHFjQwsvTTHXBFwXZil7HR2IcCCfoenmdta5nXhp5DluBRucy3LkUF93sWsrVne677bg%2BxXoexR3Pkcdb%2BeV45MEgD9u2nEPVdEfMjjINL%2BoJAQECTOgsEKI8O%2Bvm4dIKBnBA2knKdZGnV%2BZ28Kw8hway0Jw/i8H4HBaKQqBODt0sNYdsGwth4RJjwUgBBNDvzWEyAIkgngaEkFwFIgQND%2BA0GYAAbLgswSQkj6E4JIXgLAJAaA0KQX%2B/9AEcF4AoEA1DYF/3fqQOAsAYCIBABsAg6QvA3woBANABw6AJCiI8Tgqgki4IALS4MkO8YAyBkDvCkE8MwvBqSEBIHgI%2BJd%2BCCBEGIdgUgZCCEUCodQbDSC6BLv%2BJs6ROA8A/l/H%2BcCAGcDrIIgRJJUBUHeDI%2BRijlGqPUcgsw7wIAeDEfQYgrIzCBC4CsXgrCtBrAgEgUR6RxFkGETkvJIBgBSHLjQTOPpKCxE8bECIbQbguN4LU5gxAbh1liNoTADhGmkFESDOsDBaANNsVgWIXhgASloLQJh3BeBYBYIYYA4gRl4CpA4PAuEZn/0wKoLpgidjQIiHsT%2BtjaB4FiE2VpHgsCeIDHgChszSC4WILEB%2BXYFlGDOUYOBawqAGGAAoSEeBMD/n2r/aBRjhCiHEOYyFVi1CePsfoRZKBrDWH0OcphkA1ioHprkGZcjD7Z1MCAywZg6HPOIPorG8A1h2C6U0FwIYZh%2BBLmEb0SwxglxKDkAQLK9A8qaIsUYiQS70vWQIAY0xPBdD0OKpoUqhgcpFXKqYHQZWFDFWq4V1QuV0vAdsCQbiODfxoZ4%2BhQTZEKKUSotRGiokQFwLohJUDUkwJ%2BWsOyTAsCJAgAgkAkhAhPAAJyBBSJIVBZhJC4Kof4XBwaSEcDIaQChySni4K4LgpIwakiZv8Gg/wobcFmtsfQxhzD3VsMydwrJvDfGCPIJQQp8TJFsE4G0Fg2EUhyKYJWMcXBg1PC4Cg7R%2BAiBUoMRYqFpiJDSDhUoBFtjdDl0cUwZxszjWmtobwehPj%2BGCPeAE94Hau09r7V%2BAdQ6UHRNibk%2BJiTAhmDdek9htbm0JEbSI1AcSxgnu7XqIwA6uDUPKXsZMVSal1NaT05p9T2mdO6Y8vpz4BlDM8aM8Zkzpk9PmYs5Z/98BrMcJszxOy9l7B6UchonizkXPqdcnY/87kPOgc815Sh3l4eaj8vg/zAXAtBRqHpkKTEwrnbIeFNj/7LuRd8klVhLAYtiFiv1AC8UCAJUSqc8nrDkp3ZS6lKm6UNAZbkJl7gNWspCCGHVyxuVZF5XkSzAqHNCuVbq0VvRTOSrVfysVJmJXNG1e5uzthfPOa1QsELer1ibENSkxNW7zWcGPcQTt3be0AYvYO4dGholOvHQ%2BlJaSPWkC9T6ygxrk2psHaglIhaUgYMkFGxRJdt1eIYbYCtL7q3wFrXwvxn733EFbTsDtoSWAKGwmo7Cl7LiTFHc6/RegRPQrMeJyxC6pM6BAMEVd67XGJY8aW7x9b/GBPG0oyb033izcHfNkkMTv13oSA%2BwIz6eNvue3kob334kgGmynaWd3pYPZ3mlxRfA6BgaYRAaptjYPQceYjtpHSGU9OQ4IVDwyCOYDGRMsQ2HHm4c%2BYxuZqzTMkdsWRzCFHHlUZOf/WjlybgMduVSljvA2NvP2Fx75VbeNMABUCkFYLhOyFE%2BtqdknEW7dk8YNFinaNGbU00GZ/JD6otJRYPTACDNYBV/KszEBXB%2Bes%2BgWzXKMiudyGbwVuRLeeaNz5wYZvndBai5UFVkXpUFCs/MdojujWxYgcHk5SWTscFSywCbU2ZtzcVJMfLY6SBFY%2B1Wz1mBvVjFUyc6rIAzCDsCIEfw2C0FUOLykLNJa6GcHLSw0riDJD%2BBDf4JIeDg2SGDRgsNXBggnMCMd2vnWevGq0TXnddfK0ZLWM87IzhJBAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/warehivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/warehivore/kindred_repack.test.hpp)
