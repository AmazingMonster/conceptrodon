<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::Paste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#warehivore-paste">To Index</a></p>

## Description

`Warehivore::Paste` accepts a list of packed warehouses.
It concatenates them together and uses the first warehouse to hold the result.

<pre><code>   Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>...&gt;, Ware<sub><i>1</i></sub>&lt;Cons<sub><i>1</i></sub>...&gt;, ..., Ware<sub><i>n</i></sub>&lt;Cons<sub><i>n</i></sub>...&gt;
-> Ware<sub><i>0</i></sub>&lt;Cons<sub><i>0</i></sub>..., Cons<sub><i>1</i></sub>..., ..., Cons<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias Paste = RESULT;
```

## Examples

Here, we paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
/**** Vessels ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

/**** Items ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result = Paste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::Paste` is implemented as a shortcut to the member `type` of [`Warehivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

[*Run this snippet on GodBolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAHNIADqgKhE4MHt6%2BekkpjgJBIeEsUTHxtpj2eQxCBEzEBBk%2BflzllWk1dQQFYZHRcdIKtfWNWS2Dnd1FJf0AlLaoXsTI7BwA9ABUm1vbO7vrqyYaAIIbWwDUACKYCa6MyHiYCmfbB8enex87r0eHRwSYLASBn%2BJgAzG4CABPG7MNgAOgRYOwv0GxC8DjOABVoXhRLRlExBpgziYAOxWUkXMFWY6/VarM4WQnEtzMkC/X7/QHAzBgiHQxisYkE5AAa0w6AA6nVMAgFkokSiCGiMdiErixASiXyReKpTK5V4FaDkbTyb8zpazkbgsAzlCbiTQRczrqJdLiLL5bzQTSfpTqRy3gyAEqYZCLFIANxZbKDfwBQKYINp4ItVq5SZB4MzPL5DsF8MRJrOyAMCgUCLhSNL5aeHq9RswR1I6ctueTPohibzOYFsMwVZrZcJleL2Fro7ODcNShsbftPc7%2Bf7QqHJZHFarHkETGC0SOClIJOOVsX3OXfZha/Hk63CJ3tX3xAsR4XBYHVYA8gQENEFByJpKiqBBYjieJatmbgzt6Pzgo%2Be4hMQh7rtgx4wU2VjwbIiHRK%2BqHHj%2Bf7EGO1ZAWafpnjaRj2gKTouh%2BQpgeqEGEimRxnnyC5nhhShwW4CHPihCLHoJSH4eOranmeVpEf%2BQ7SZaSIgCABaBmaVK%2BvG7yfLpmzfDpZwAJLcgCjC1FUzxbAZem2fs8YdlBjFFnCRzEMAAHkUc1F2pBxJgi6aoavibFdm5HmoSpalabSbx2S8dLbGc2CqKwQLEglcXxfp8bmKCwRll4WBOm4aAMMsCQEJ5po/FlmxnAAao8dhPJlCYXk5S5OauLnDnWqHAeioG8ZgAD6GjqbV7VZl2jmzT1g63pupGKscqJDdOBreqNXCTZyXWzQdK7Xr1G79eOg0YiNo1mHtdXrMZXKtdZ%2B0dfNJ2LWRNXrRiO7jXd029vyH0DWtyobX9u0xVNc3HYWn2rYe4O/QIN0A7DV7w6DSMgWcf2ggDhlCF4CQ5BKYYKF4tCgW1PlnMTpPJOTjxU6BAWbZ6s5jRN2EMONomoy0eOo2YAt8wTQHQ4l5wU6zVk5ccdOy9T9GuqFgFuAu108wJqM82hJ4cVa11Q7rfNC39t0mlJRuWtdVtm6NEs1YqUv3Vijw0y9YPJrio2jtEBAQIM6AqQoQr%2B55bjKwQx4M2T6Ax0iMyTRwcy0JwACsvB%2BBwWikKgnCa5Y1hnAoCxLP5ZigjwpAEJoadzKKICZ5IcIaLEZhmAAnN3XCZx3sRcKSpLSBnHCSLwLASBoGikLn%2BeFxwvAKCAc/13naekHAsAwIgIALAQCReLHFAQGggJ0NEoRCpwqixAAbAAtA/khnMAyDIGcUhwmYvASoQEgeBQ4tH4IIEQYh2BSBkIIRQKh1Cb1ILoFoAB3YgTAEicB4OnLOOcG4F04F%2BE%2Bx9QKoCoGce%2Bz9X7v0/t/NuZgzgQA8JfegxASTVy4DMXgG8tBzAgEgC%2B6pWHkEoIIq%2BMRgBSFFjQam/5KARHwREYIdRIRYN4Eo5gxBIRfgiNocMG9a4XzYIIL8DBaCqMQVgCIXhgCsloLQVe3BeBYBYIYYA4hLF4E9A4PAMZHH50wKocMJ8Vi12CP8ce%2BdaB4AiOgrRHgsD4OVHgaeTjSAxmIBEJmVxXFGGiUYBucwqAGA8g1B4KCvwwjUTA4QeIoHSDAfIJQah8HIP0G4lA1hrD6BiavSAcxUCVTSI4p%2BIcAqmBLpYMwi8MnEGAY8eAcw7D6LSC4Bg7hPBNH8OsyYvQYgtByKkAQIxmikEOVUXZxQ%2BhjAqCsgQHRhibNGK0O51QhhdH3FMa5th3knL0OMeolzpicPmIsZYEgcEcGzvPfBS8KGPxfm/D%2BX8f4MIgLgQBbC8qcO4YUuYf4mBYBiBAJuIBJCgjhN3UEo8NCSDMJIB%2Bs9M4P27voTgk9SDTxrnCB%2BXAH6xG7kPB%2Brd%2B5UofjCxBS8V5rzroU7ee9%2BEH2ISfER59UAsOvrfDgdQWBRlJE/Jgk4aJcG7nCLg7d/74CIHMkBNSIHiGgY0uBLTEG6FFmgjBajIXQoXrwJeRCj4nzOGQ%2BFVC34jmNaa81GhGHMKEdEdhoIzBcNlZvPhAj1XxrIGfMRrCUAGCMCargc8ZH/BIvIxRyitHVI0SonReiHDVKMeZUx5j8FWJsXYhx1SXFuI8fnfA3jHB%2BPwYE4J/xqnhIqPg6JsSVEJJWPnZJqTa4ZKyUoHJfbbRyuKUwUp5TKmMGqY0%2B19SanOoQfnN17SCkTKsJYHpEQ%2BkkoLkMgQIyxnOjvdYaZfrZnzOfUs25PjnAQFcH8logRPl7OyMkI56QnmnPOWkIF3zlkgbeZ0CDLyMMPI%2BYUGDYxfmIf%2Be81D%2BylkV3BSC8ePrYWcFDYio1doTVmvbowjF1rE04tTbw/FmBCV9BfePDlXLTW0tJJnbuI9QR0oZZIFovqCHL1sDKnhW8d770PiQ1VubNVsE4Dq6hLAFBRi/lGVjPJBiWsxcAvQJ66kSAabIC9rSQCglIB6zBTjvV4MlYQ5VpDyGqGM6Z8zlnOyDFjZm8RibQQpvU%2BmlAMXhE5pS30MzpNRoWe7qNKzBBRohYaXQMtq8IAKMQbW6taSqvaN0fopt6rjEEFbRYgdmBrG2LEN2tJva8mLucV4lZI7EFjojBOtJU7Im8FnXEyEC6klzJXbwNd2SARboKWmvgJSFBlMwBUqpaSHOQKc%2Be5pl6dDuZvcYLpD7Z2AdfVURxqwQ6dMmRYX9Bd/1YAe%2BhqoayNmZFOVBgjVz9lnLg1UbDyH8jQbB/84DVQ8PYb%2B%2B0MjcPgU/KwyRojEwMfXMo2CqBvmJWLwY0Vs4JmzNnBy3CfLHGrUkG4wlvFpACVEsoJC0TIAe5wlBKCTOA8FOz356SflpO/WcGlevVnzdJCZ0pcPUks94h9y4J3Mw4rx6gj82TlTiXIV/wl8p3Faa5gZJSM4SQQA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/warehivore/paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/warehivore/paste.test.hpp)
