# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/graph_parallel
    REF boost-${VERSION}
    SHA512 397df5d5f715d6818443888161462cf6b1671636364ba4a6551d93fd4b4d2a78956c8491511f11d5e2d4eb4d64facb1acc6a49b5084f3b92b7527a0f6240d609
    HEAD_REF master
)

set(FEATURE_OPTIONS "")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)