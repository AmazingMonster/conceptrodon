<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::InvokeResultIn`

<p style='text-align: right;'><a href="../../concepts.md#functivore-invoke-result-in">To Index</a></p>

## Description

`Functivore::InvokeResultIn` accepts a function-like type, a possible return type, and a list of argument type.
It returns true if the function-like type invoked by the argument types returns the possible return type.
If the function-like type is a pointer to a member function, then the first argument shall be the corresponding object type.

## Structure

```C++
template<typename>
concept InvokeResultIn = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Mouldivore::Confess<std::is_invocable_r, Result, Fun, Args...>;
```

Note that since `std::is_invocable_r` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
struct FO;

// This will fail.
static_assert(std::is_invocable_r_v<void, void(FO::*) () volatile &, FO>);
```

The following code will not compile:

```C++
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**, int***>, void>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOwArKSuADJ4DJgAcj4ARpjEIGbBAA6oCoRODB7evgGp6ZkC4ZExLPGJybaY9o4CQgRMxAQ5Pn5B1bVZDU0EJdFxCUnBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweH25smGgCCO3sA1AAimCmujMh4mApX%2Byfnl0c/B59npwBZgAzBFkN4sFcTMC3AQAJ4PAD6BGITEICmh2EBgIImBYKQMuOhsLxBKYRJh8IezDYADp6ZiruCmAo3spiJh8KJcaQrlTGKxMPTadh6GxBBjgVjzmgGOsUgQrh4GFRXm9oTcruzOXhuZhiaK8YwCAphZiQCAAG5iLz64FWc6A76/F27f7Oq4ASXxYuN5Ky7z27tdIeO2POuJ95LtsIRArYVwAYl4GLz%2BTTMFcAEqvLy0AhpuMZ4VnYjASXSs6y%2BWKz0MS2oADWmBzCjzBDr2OBmuVqtZxNG6AteAUiIiDdEsXoiLI2dz%2Bd5ydTV1L5bNUuhDoBX1Dbqd%2ByuABVXibA3ud7v/oDRsQvA4kwB5Tfhi6bI8IEdXADudFoVyoaK0LS16NI4yCIiySjNBAg7DqO46oJO07EIilrEg2eDoLyGHoBAiYPha2wLFcEDEQ2hJ0Jm5gAGyLk%2BUoLJuHBLLQnCBLwfgcFopCoJwbjWNYVwKCsaxUSCPCkAQmjMUsjYgJIAActLAgAnCp/jAgpGlmApgSSMC0isRwki8CwEgaBopCcdxvEcLwCggJZUlccxpBwLAMCICAKwECkXgFhQEBoPilHEFEgqcKoCnUQAtNRkhXMAyDIFcUi0mYvA6kQxCYXo/CCCIYjsFIMiCIoKjqC5pC6FwpBfqiKScDwLFsRx0k8ZwD7%2BX5iqoFQVxRbF8WJclqWSOlJEeCF9DEFC4kLLwzlaEsEBIMFKSheQlDraFIDAFIZh8HQuLEA5ECxO1sQRE0cJNbwV3MMQcIPrE2iYA4d2kMF4oEA%2BDC0LdVVYLEXjAG4Yi0A53C8FgLCGMA4hA3gHIOHglqvO1mCqO9/kbBJES4kZ3G0HgsSok9HhYO1KJ4GZ0OkOjxCxOkmB3HDRgk0Y0lLFQBjlgAai8X4PtSn35cIojiCV4vlWo7U1fo8MoAJlj6KTDmQEsqAKlkUMxYOGqmJY1hmDZjM5VgGukZ0711H4ECuBMfi1WEEQDOUQy1WkGR207eje0UDCzIMiS1XYtvdGMLSeG0ejh6j9RR8HHuh7YUd%2B2HSdu3MntLMJqzrBILUcOxVntbZA3RXFCVJSlaVmCRuCECQc3AlwC2SdzSwIJgTBYIk1tyfptIqcC/iSBokhmJI1EWYE1EqfonAmaQZlt7S1FcNRCkqQpW96VwgSj7R1m8LZ9mOZ3LkrZ5q3ed1/lbUFqDTQk4VsJwTQsJa/gxUwTIGCMKlFStIuC0m4llEguVari0KlLaQMslByyqroQ69UmCNWhsXUup8OocC6r5fyVw%2BqVyGglZkQCuAgLARoSaL8NozVbmYDuS1XJ3x2jNJ%2BHChgUP2ipLglkaD5gSGdC6VUHo3U%2BhIp6L03ofXpt9Y0f0AbtWBqDcGtBIafVhvDRG3F8Ao0cOjKGEDsbIFxp9AmNR2okzJjdSmGxuI0zphJRmzMlBs10REUA18%2BB8wUILTAwtRb01gZLYqCDZCy0qtxVBisuZGysKrWxVstY6wEHrA23ZEkmzNgkC2GNNY2wTvbR2Mc8guwYOgZO8wvaFF9uU52pAA52xqZ7YpdsejjEaXHGoEdE4zGziHOO6cemZ0GaUYZ7dlgF2KtgtqVUK6DWrgA%2BGwDQHgMbvgbKrd26LS7qQHufchjWyMivNeIDJ5BHUhpKeM9JC1VwefWwl9WE33gHfHyPUuH0NCu/DYX9hosAUJaFKloqG0kJCeTK2yoFDhgbIOBETSryCQTEnQIBgR1QandeZZdFmdQfr1fqqggUgrBRCqFow6Gv1muYYEwIWHczcmtX5nDArcMSKClIKRUJUMRFSggiJSUIOOiIygYjuLSMBhJaVsjbafUUYIZRgN9GYBBmDCGUMJI6I5o4mGyMI7GMxmYix9MrFE14LY8mcIHHUxyi43gbiWaeI5t45lvMmACyFiLRgYtEXhIkJEsqaL5aYvicYFWNgUnwDSXbKGmxYI5MsKbM%2B5tMKFOtvHO2LgqkZxCFUtpqcWlZHzSW4oQyU69K6AM7puQmnZsjhM92tS069HzdMZoRai4zNEj2oyODy6cAGmS0FVxwUgMFVs5udL5r7Ovt3Xu/dKDF3OUkEBDLAiBEngIjQDL/Db3xTZTgF8nIHLkoEMBs8NBmE3re/wUh55bqXhwYECzj12SvstYuGUj1nxPV%2BmSDMRFZHkkAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/invoke_result_in.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/invoke_result_in.test.hpp)
