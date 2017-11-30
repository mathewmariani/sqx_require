# Squirrel Extension Require
A small extension for the Squirrel Programming Language to load and run libraries.

## Usage

**[sqx_require.cc](src/sqx_require.cc?raw=1)** and **[sqx_require.h](src/sqx_require.h?raw=1)** should be dropped
into an existing project — `sqstdio.h` must be registered.

Roughly, `require` does the same job as `dofile`, but with an important difference. `require` caches the value returned by the script to avoid duplication.

## License
This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. See [LICENSE](LICENSE) for details.