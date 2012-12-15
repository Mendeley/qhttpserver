project (qhttpserver)

# find and config Qt
if (USE_QT5)
  find_package(Qt5Network REQUIRED)
  include_directories(${Qt5Network_INCLUDE_DIRS})
  set(QT_LIBRARIES ${Qt5Network_LIBRARIES})
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

# # sources
# set(QHTTPSERVER_LIB_SRCS
# 	${QHTTPSERVER_SRC_DIR}/HttpStatusCodes.cpp 
# 	${QHTTPSERVER_SRC_DIR}/qhttpconnection.cpp 
# 	${QHTTPSERVER_SRC_DIR}/qhttprequest.cpp 
# 	${QHTTPSERVER_SRC_DIR}/qhttpresponse.cpp 
# 	${QHTTPSERVER_SRC_DIR}/qhttpserver.cpp	
# )

add_library(qhttpserver 
	${SOURCES}
	${MOC_SOURCES}
)

# add dependency on http-parser
target_link_libraries(qhttpserver http_parser)
