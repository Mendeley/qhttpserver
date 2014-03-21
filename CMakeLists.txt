project (qhttpserver)

if (USE_QT5)
  find_package(Qt5Network REQUIRED)
else()
  FIND_PACKAGE( Qt4 REQUIRED )
  INCLUDE( ${QT_USE_FILE} )
  SET( QT_DONT_USE_QTGUI TRUE )
endif()

# source dir
set(QHTTPSERVER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CLASSES
	HttpStatusCodes
	qhttpconnection
	qhttprequest
	qhttpresponse
	qhttpserver
)

foreach(CLASS ${CLASSES})
	set(SOURCES ${SOURCES} ${QHTTPSERVER_SRC_DIR}/${CLASS}.cpp)
	set(HEADERS ${HEADERS} ${QHTTPSERVER_SRC_DIR}/${CLASS}.h)
endforeach(CLASS ${CLASSES})	

qt4_wrap_cpp(MOC_SOURCES ${HEADERS})

# includes for http-parser
include_directories(${CMAKE_SOURCE_DIR}/external/http-parser/upstream)

# own includes
include_directories(${QHTTPSERVER_SRC_DIR})

add_library(qhttpserver 
	${SOURCES}
	${MOC_SOURCES}
)

# add dependency on http-parser
target_link_libraries(qhttpserver http_parser)

if (USE_QT5)
  qt5_use_modules(qhttpserver Network)
endif()
