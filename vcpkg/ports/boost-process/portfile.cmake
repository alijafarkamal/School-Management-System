# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/process
    REF boost-${VERSION}
    SHA512 cef528d676c3a909aff4175419dee7b2c13076d1d146e42d0840724dde31a8bce5ff3b8c22d4330dbc94ec70e8d3927c782997aa49b9d7262b309e7677c03436
    HEAD_REF master
    PATCHES
        opt-filesystem.patch
        
)

set(FEATURE_OPTIONS "")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)