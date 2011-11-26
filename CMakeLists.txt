project(plasma_potd_ngprovider)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    )

set( potd_ng_provider_SRCS
	ngprovider.cpp
)

kde4_add_plugin( plasma_potd_ngprovider ${potd_ng_provider_SRCS} )
target_link_libraries( plasma_potd_ngprovider plasmapotdprovidercore ${KDE4_KIO_LIBS}  ${KDE4_KDECORE_LIBS} ${QT_QTGUI_LIBRARY})
install( TARGETS plasma_potd_ngprovider DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES ngprovider.desktop DESTINATION ${SERVICES_INSTALL_DIR} )


