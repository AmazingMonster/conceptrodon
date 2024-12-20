<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Roadrivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#roadrivore-agent">To Index</a></p>

## Description

`Roadrivore::Agent` accepts an operation and returns a function.
When invoked by a packed warehouse, the function extracts the list of containers from the packed warehouse and instantiates the operation with the list.

<pre><code>   Operation
-> Warehouse&lt;Containers...&gt;
-> Operation&lt;Containers...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<template<typename...> class...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<template<typename...> class...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

- We will create an `Agent` of the `Operation` and invoke the returned function with `Vehicle<Con_0, Con_1, Con_2>`.

```C++
template<template<typename...> class...>
struct Vehicle;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<template<typename...> class...>
struct Operation;

template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

using SupposedResult = Operation<Con_0, Con_1, Con_2>;

using Result = Metafunction<Vehicle<Con_0, Con_1, Con_2>>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Roadrivore::Agent` uses partial template specialization to extract containers from a packed warehouse. Here is the entire implementation:

```C++
template<template<template<typename...> class...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
    struct Detail<Warehouse<Containers...>>
    { using type = Operation<Containers...>; };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJLBAA6oCoRODB7evgGp6ZkC4ZExLPGJybaY9o4CQgRMxAQ5Pn5B1bVZDU0EJdFxCUnBCo3NrXkdo739ZRXDAJS2qF7EyOwcBJgsKQZbJoFuWzt7mAdH27tM%2B4cEAJ4pjKyYAHRvB9gA1MgGCgpvLw%2B31%2BCk%2BAHlHsRrlkPiYNABBUbELwOT7w4CMAhw%2BEmADsVgRnyJn2OVxuRweTzYsMJxKRKIInwAIphGnRPnirLimQcCTjaUTSadzkLrmdbpdhbdKcw2ACgT8mH95YEvoq/p8AOpNTAIFZKUgkyVikUy54qtUggEeQRMCIJBQ0%2BHEz701Estm0c7a4i6/Xitw2tmRYj/d6qp0uzmfLwZIwkykcwJM8GQ6ECc5Bu0hsOAiOBCwc7m87FRgVGk4m6WPWWvN7o33bTGOiPl2MRYCfACynnQSZTHrtXsODcwTcEuY%2BIBA90eJYReJ5Bex2IA9AAqTdb7c71dr7efAAqmFGoO3e4RG53163F/5OLMgQiPy8WCTbjQDHWKQILewK4RUVySAgNZypOs80tJVJ1bRECGRVEADVdTwH5xT5bEQNNGtzXDf8ETdRkbQAfQ0ed7yw6twItbFCM%2BEiuHIzDjWAs05Tw2j4IZeiBGIswmMAljQKE7DqLw4FoJogiuNRCEEnTBgBPhSiKRw9iXnhYhgD/bF23jLtWSYKgvC/OoGH7NEMUEc45KhMypxAHtaHQc5NO0mjlwXBE9M7IQvBSNIlHQAAlE8vFoRkDhTWyFMzXiNENBjEt4/j8ww7y407UKFHCyLk27QzjNMmFDmQhBUPoOKGFI5Lqq4Wq%2BNhNKALg6FkGI6CEgICBRnQacFGeDqWzcbLcsNPyAvSTAQrCiKPgWXkOCWWhOH8Xg/A4LRSFQTg3GsaxXRWNZMA5R8eFIAhNCWpYAGsAgANheAAOe6pH8XF7skABOQIPsffROEkXgWAkDQEo2rado4XgFBABLLs2pbSDgWAYEQEAVgIFIvAIchKDQHY6ASKJnk4VQXoAWk%2Bz5gGQZBPikF4zF4abCBIPA%2Bvq/hBBEMR2CkGRBEUFR1ER0hdHqgB3KEUk4HhltW9aru2zgwRx7HGVQKhPnJ%2B6qckGm6YZyQmc%2BCAPEJ%2BhiFOwIuAWXgEa0JYICQAmUiJsgKAgN2PZAYApDMPg6C2UNKFiZXYgiJo7jl3hI%2BYYg7jBWJtEwBxY9IAm2EEMEGFoGOxawWIvGANwxFoWHuF4LAWEMYBxELvBfQcPAADcT2VzBVDTnGNnOiIthWsXaDwWIoUTjwsGV%2BC8BBqvSHb4hYimlla6MEejCupYqAMbTELwTBJbkjbzu54RRHEAWz%2BFtRlYl/Q65QfbLH0UfYcgJZUB/LJK4p3qotMJYawZhIaL2IBzDuH9OhpzMi4Bg7hPBtD0GEe0cwhj1UCkUbIiC8gYMKGZWYgxEj1TsDA7oYwWg4L8CQmoZD6gUMIeUdBtgKETGoSwmYqCiESCWAoI66weEAw4GtUgENeBQx1pTamtN6aMzMGbXAbNrbmFtvbC6W8lgIEwEwLAiQIC3WGC8H6uJJAaEkGYSQ90wb%2BHul9IRQNSAg1ti8V690npfSelwe6/hJBcH8D9e6ojlZQxhnDdRiNnZoxdhjdWOM8be1QJbYmpMOBNBYK3XEFMmASXjFwL6LwuAvC2qzIg4DOaC3PnzCQ0hr5KFvmLXQgdpZMFllXBWwilZiyhmrLGONPha0%2BGkjJWScmdjyQUopZsLbuytjbMwajHZI2iT7K28SVlDCGZkxURg8lcASjQCKDow4RyjonDO8do7J1TuneeWdMS53zsrIuJcy60ArhnGudcG5bXwM3Rw7dK7FO7sgXuGcB41GViPMe0dJ4bC2jPOe51F7LyUKvL5HYt58F3gofeh9j4ZzPrzS%2BNTZA31FltRpD9N6AKsC/KF799HbW/gIX%2B/9kw0uAaAhIZTIGMtIS3ZwEBXBsOQfAxh8w8EZDMiKyVWDxXMP5WZHo4wqF6EVeQzhpRuEkNYaqnVmqBhMOIbw/h/N2kiLESrDggziDpMydk7ZYz8mFI0Ao/ApSbZ2wdho0gWidFDEZUPBxTj8lmNxP43EuJAjmMsb4oJXTOChPhpilG6NMYazWYkmZyS2CcDSdTFgChW701buM04owWbuvZuUwlF9%2BYkqFnU8lOgQDBGaa0%2BWQiLXBNVrEzW2t80G0LcWz4pb8nlsZObLNHsbaBAWSm1207Vle3WYkYtAViJjuIhOjqtrPpB0OaHCA4cxYXLOfPM9ScU4wIzncnOecC4/MwMXUu5dK7nU%2BevOF1cm5kIBZ3YFoL57gqHltKF487iwunuAxFvBkUr22OizeESsVMD3gfI%2BNYCWyCJfWipZK76tqpcYZ%2BNh6XwE/syhgldVy9SfkAywIDxFgIgQy3htCBV%2BCFfAmVIQxVcKNXoTB0q9WkGE1keVxDoGceVZQ3I7D1X0INWgqT0wVXybVQwgTEqTWrAEXbLtnTIacBtSwAtRaS1lrFKMN1SjPXzoiZo7RujKDtODSAMw%2BTAiBH8P4MxeyNDeY%2Bk9eNxnoa2DCYshYBjkgFMCE9Hxj4/P3UfB9IRgQjPiMTeEp27Tmahay%2BFqLSxF4ZGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/roadrivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/roadrivore/agent.test.hpp)
