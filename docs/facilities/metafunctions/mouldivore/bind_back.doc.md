<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-back">To Index</a></p>

## Description

`Mouldivore::BindBack` accepts an operation.
Its first layer accepts a list of elements and returns a function.
When invoked, the function adds the elements to the end of the argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Es...
-> Args...
-> Oper&lt;Args..., Es...&gt;</code></pre>

## Type Signature

```Haskell
BindBack
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindBack
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will bind `int, int*` to the back of `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** Supposed Result ****/
using SupposedResult = Operation<int**, int***, int, int*>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = BindBack<Operation>
::Mold<int, int*>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int**, int***>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJJmpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJkCbhBYLemEh0IAnqlGKxMAA6TGQ7A3ZAGBQKG4AeRRxDe2WxQPGxC8DhuFgi6AsTGQAGsgSYAOxWS43Pk3GFPOEIgjI1FsTHo7AMfBGBSU3n86m0gg3ZTEVBEACynnQQP5Ny5PIuBoNgvB8KhopRzAlmOwz0YBHlgWw%2BtNfK8mSMNx1tHQhsCABFiaTyQIEQ7QU6FJLSDdpbLgLGsa7IcaDVyg%2BmOYq%2BebhVaxbaMfaZRFkwqTfyvRXfbrAyH1ZrUH69VDExWU%2BjKYFjVmc5cgT8/kcASOE6pWE9MB9TsPR/9c4CzIEInivFhA240AxNqlnVWF7cSQlwww5/sAQWIUWbWjJVXlXTT2SGoPAd9DjchF5UkVMADAAlTAFC8WhVU%2BIFax9X9/wyQCQLAiDG1DM93yhCICH2eMsIOXDBAI7De37L9bi1TBmioLw93eKDLhvS0kXvO10QuYhKzTS4YOAX1KKYajaOyVCGRlZk2QRV9zyrEAQDbBEsKI3YZLk3UEXY5NHzTPtlwnJDwMg%2BduO9Xj9JQyEQwoqiaIcClMMEHCbjw/YSN078ABVQMMq8qWaRxkAAfSYAkEgICBxnQWSFDRIKXTcMyCHjOCAPQBLsSWdMOBWWhOH8Xg/A4LRSFQTg3GsawbgUNYNlncxAh4UgCE0LKVlZAJJHRDRJC4TlAg0fwNDMAA2IazAADjG/ROEkXgWAkDQNFIAqipKjheAUEBFqawqstIOBYBgRAQDWAhUi8RKKAgNBHjoBIojRThVDGoaAFohskG5gGQZAbikdEzF4QDCBIPBIq4GRBBEMR2CkCH5CUNRmtIXRwYAdzJVJOB4bLcvypHVqJc6ztVVAqBuJ7Xvez7vt%2BjqzBuCAPBu%2BhiENVcuCWXhtq0FYICQa7UlushLoFoWQGAKQUhoCCEg2iBYiR2IIhaREsd4JXmGIREiVibRMAcNXSGul4CCJBhaFVnbSCwWIvGANwxFoDbuF4LAWEMYBxCt/BiH1xwADdQKRzBVH186tgarC6iR2g8FiMktY8LAkYIYg8Dml3SED4hYgQoNQQ92OjGalYqAMZMADU8EwVHTwKhr%2BEh0RxFhxv4ZUdQrZR/QPZQcrLH0OONsgFZUAPbJnZeiKLNMSxrDMFbs7TrBh4gFY7D97IXBlKY/HBsIIiGSoRnBoosgEXe9DPhp5mGRJwY32yBD6SZPA6PRH4aF%2BBkPhYT9sCYbQ375AfoA2%2Bx977r2qpsCQOMOB5SWvjTg5NnpvQ%2Bl9H6f16YQFwMDVmdUOZcxLisBAmAmBYESGvUgbVJCBHRAATkCJySQXUzCSCGgtfwQ16FTQ4DNUgc16roiGlwIaY16FjVEf4bq/hGFDUQVbVa61NqNRLntQ6fNjpE3OuQSgosWb3TYJwFoLB/achekwXEBgfRcHoeiLgnVAb4CIMvPQbcoYt2kG3RQHcka6BSOjJgmMXZwIQctXgBNtEkzJhTNBViPa/TsQ4jQDMmaCxZmzQIZhOaqJ2rzfmqBmYJF0VdQp6SRh4g9rYrgi1pYgmIHLBWVsNYq0Ni0rWOs9YG0zsbJ0ZsLZIxtnbB2tAnaGzdoXLYRUfab0Ds7IqIcw4gkNlHHKVtY7xxVknKZXM04ZwatnXOSh87uyMEXUAeS%2BDlwUFXGuddDbuObjDLxsgfGIy7iAFI1jjD9xsBs1eo9x4CEntPYMs8rCWAXhEpeoMg4j26JvZwEBXCX33jKcBixT4ZHPjkYBe80jYpvr/O%2BH86iIsaIA1FCKn4UrmMSiBH9KV4sZXS8oJKOarHWDAjlaywlII4CgymH1Kk2KSZ1BmuCXGZMIbknmJCyEUMoHA/hgi7FdU5LIzkvVkjsO6golanBlFbTUftI6J1iYlP0XdB6HATFUxYAof2P1/a2PRBacYTi8GgzcbIDxzy4ZvM7kVXQwRAnBOxrwvlijOCE1OudG4pNyb2sdc6117rVSMzKULTJgQcnc12poq1ws9FZpZiAJ1/4AouvoQFdNAVVDvT4HQepjTFbKy1m09t2tdZ%2B0Nr0wQ/TLbTMwLbe2jtnYNQmWcnZ1s8C%2B1snM4OodkDhxWYIaO6y44J0RNslOezDaHLzgXM5FY1FlyYJXautcbQPN9U8iQLzBCBr8SAYI3y%2B5zwHv8%2BAgKGjO22BFD9EKLBQuKjCleP7qUNG3u4ZlaL0AYv/tfbIVLkOlHpZiqDvQmV5HxZ/bDrKj6YdmK/XDLLWiIcgZymqsDI142jQKhtH0HVOpuNWt1cJxgSucSQaVebiGkFIeQkYVC1kqs%2BXYwIgR/ADW6gtKTnIxH6oiYa2wKj81LFakkfwDD/BjWGvQyQ9DepMK4G%2BzggR6MGrWrKlqvCAbKeKqpjTKxs6ZGcJIIAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/bind_back/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/bind_back.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/bind_back.test.hpp)
