# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/phoenix
    REF boost-${VERSION}
    SHA512 216f11bd2db817a2cd94fd301db7011ec2215c48c9150e2acc182246880f4d289ba19a761c96601d0e5c453a7f79f96506a4883e2002a56b0825421e9e8b1905
    HEAD_REF master
)

set(FEATURE_OPTIONS "")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)