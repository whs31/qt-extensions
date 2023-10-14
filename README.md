<h2 align="center">
	<img src="./docs/images/logo.svg" width="200" alt="Logo"/><br/>
	<img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/misc/transparent.png" height="30" width="0px"/>
	Qt Extensions Library
	<img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/misc/transparent.png" height="30" width="0px"/><br/>
    <img src="./docs/images/sl/core_v.png" width="80" alt="l"/><img src="./docs/images/sl/sg_v.png" width="80" alt="l"/><img src="./docs/images/sl/geo_v.png" width="80" alt="l"/><img src="./docs/images/sl/elevation_v.png" width="80" alt="l"/><img src="./docs/images/sl/toolkit_v.png" width="80" alt="l"/><img src="./docs/images/sl/sockets_v.png" width="80" alt="l"/>
    <br/>
    <img src="https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white" alt="qt_badge"/><img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cpp_badge"/><img src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="cmake_badge"/>
</h2>

### Library for extending Qt Framework capabilities even further.



## Overview

![](./docs/images/sl/core_h.png) 

Core module provides useful utilities, such as:

- **Logging**: provides useful extension to Qt logging system - terminal coloring based on message logging level and function/class/namespace tracing.
- **Math**: provides C++20-style numeric constants, math functions such as `lerp`, `clamp` and more.
- **Type aliases**: provides aliases such as `i32`, `usize`, `f64` and Qt-specific aliases such as `String`, `Variant`, `Object`. *This feature can be disabled via CMake option*.
- **Expected and Range-v3**: Core library includes this 3rd-party libraries.

 ![](./docs/images/sl/sg_h.png)

Scenegraph library provides Qt Quick Scenegraph extensions:

- **Scenegraph Object**: utility base class for easier node management.
- **Scenegraph Utilities**: conversion functions between `QSGGeometry` types and more.
- **Quick Utilities**: QML singleton which exposes useful function to QML frontend.
- **Materials**: materials pack for scenegraph objects.
- **Gadgets**: gadget classes to use in scenegraph objects.

 ![](./docs/images/sl/geo_h.png)

Geo library includes:

- **Google Maps tile provider**: Qt Location extension class for providing Google Maps tiles.
- **Orthodromy**: classes to work with orthodromy.
- **Tile loader**: offline tile downloader from HTTP link to folder.
- **Geo-specific math**: geometry and mathematics on Earth surface

 ![](./docs/images/sl/elevation_h.png)

Elevation module provides GDAL functions nicely wrapped in C++ code:

- **Elevation at coordinate**: gives ability to get terrain elevation in meters from specified coordinate.
- **Elevation profile**: builds elevation 2D profile from specified polyline.
- **Intersection check**: gives various functions to check given polyline for intersections and more.

